#!/usr/bin/env python
# Merge per-cohort MainResults_<yr>.gdx (each filtered to its committed year) into
# MainResults_2030_40_50.gdx, then run a comprehensive units/values/balance audit.
# Usage: python merge_audit_3yr.py [OUTPUT_DIR]   (default = Scenario_EU output dir)
import sys, gams.transfer as gt, pandas as pd
pd.set_option('display.width', 170)
SYS = '/appl/gams/50.4.1'
OUT = sys.argv[1] if len(sys.argv) > 1 else \
    '/work3/dhrsh/Balmorel/0_Balmorel_PB_Github/4_Balmorel_High_Res_PB_all_wo_FG_eq/Scenario_EU/output'
YEARS = ['2030', '2040', '2050']
files = {y: f'{OUT}/MainResults_{y}.gdx' for y in YEARS}
fout = f'{OUT}/MainResults_2030_40_50.gdx'
VAL = ('value', 'level', 'marginal', 'lower', 'upper', 'scale')
UNITS = {'TWh','GW','GWh','MW','MWh','Mmoney','Money','kton','ktons','Mton','Mtons',
         'Money_per_MWh','Eur/MWh','kt','Mt','PJ','MEUR','%','-'}
def vc(df): return 'value' if 'value' in df.columns else ('level' if 'level' in df.columns else df.columns[-1])
def ycol(df):
    for c in df.columns:
        if c not in VAL and df[c].astype(str).str.fullmatch(r'(19|20)\d\d').any(): return c
    return None
def ucol(df):
    for c in df.columns:
        if c not in VAL and df[c].astype(str).isin(UNITS).any(): return c
    return None

# ---------------- MERGE ----------------
src = {y: gt.Container(files[y], system_directory=SYS) for y in YEARS}
out = gt.Container(files['2030'], system_directory=SYS)
nyr = nnon = nfail = 0
for name in list(out.data):
    df = out[name].records
    if df is None or len(df) == 0: nnon += 1; continue
    yc = ycol(df)
    if yc is None: nnon += 1; continue
    parts = []
    for y in YEARS:
        if name in src[y].data:
            s = src[y][name].records
            if s is not None and len(s):
                sy = ycol(s)
                if sy: parts.append(s[s[sy].astype(str) == y])
    if not parts: nnon += 1; continue
    try: out[name].setRecords(pd.concat(parts, ignore_index=True)); nyr += 1
    except Exception as e: nfail += 1; print(f'  FAIL {name}: {e}')
print(f'MERGE: year-merged={nyr} non-year-kept={nnon} fail={nfail}')
out.write(fout); print('WROTE', fout)

m = gt.Container(fout, system_directory=SYS)
# ---------------- A. FULL INVENTORY (every symbol: years | units | sum | range) ----------------
print('\n=== A. INVENTORY (symbol | #rec | years | units | sum | min..max) ===')
anomalies = []
for n in sorted(m.data):
    df = m[n].records
    if df is None or len(df) == 0:
        print(f'  {n:34s} EMPTY')
        continue
    v = vc(df); yc = ycol(df); uc = ucol(df)
    yrs = ','.join(sorted(df[yc].astype(str).unique())) if yc else '-'
    un = ','.join(sorted(df[uc].astype(str).unique())[:4]) if uc else '-'
    s, lo, hi = df[v].sum(), df[v].min(), df[v].max()
    print(f'  {n:34s} {len(df):>6} | {yrs:14s} | {un:18s} | {s:.3e} | {lo:.2e}..{hi:.2e}')

# ---------------- B. ENERGY BALANCE per commodity per year ----------------
print('\n=== B. ENERGY BALANCE per year (TWh) ===')
pr = m['PRO_YCRAGF'].records; pv = vc(pr); yp = ycol(pr)
dd = m['EL_DEMAND_YCR'].records; dv = vc(dd); yd = ycol(dd)
h2 = m['H2_DEMAND_YCR'].records if 'H2_DEMAND_YCR' in m.data else None
for y in YEARS:
    ge = pr[(pr[yp] == y) & (pr.COMMODITY == 'ELECTRICITY')][pv].sum()
    de = dd[dd[yd] == y][dv].sum()
    line = f'  {y} ELEC: gen={ge:.1f} demand={de:.1f} gap={ge-de:.1f} ({(ge-de)/ge*100:.1f}% ~ biomass-CCS compression; not captured by fossil-only ENDO_CCS)'
    print(line)
    gh = pr[(pr[yp] == y) & (pr.COMMODITY == 'HYDROGEN')][pv].sum()
    if h2 is not None:
        yh = ycol(h2); dh = h2[h2[yh] == y][vc(h2)].sum()
        print(f'  {y} H2  : gen={gh:.1f} demand={dh:.1f} gap={gh-dh:.1f} (= within-system H2: storage discharge +/- H2-to-power, not in H2_DEMAND)')
    ght = pr[(pr[yp] == y) & (pr.COMMODITY == 'HEAT')][pv].sum()
    print(f'  {y} HEAT: gen={ght:.1f}  (no H_DEMAND symbol in MainResults -> cannot close from this file)')

# ---------------- C. CAPACITY FEASIBILITY per year ----------------
print('\n=== C. CAPACITY FEASIBILITY (max implied CF must be <=1) ===')
cap = m['G_CAP_YCRAF'].records; cv = vc(cap); yc2 = ycol(cap)
for y in YEARS:
    ce = cap[(cap[yc2] == y) & (cap.COMMODITY == 'ELECTRICITY')].groupby(['AAA', 'G'])[cv].sum()
    pe = pr[(pr[yp] == y) & (pr.COMMODITY == 'ELECTRICITY')].groupby(['AAA', 'G'])[pv].sum()
    j = pd.DataFrame({'c': ce, 'p': pe}).dropna(); j = j[j.c > 0.01]; j['cf'] = j.p / (j.c * 8.76)
    print(f'  {y}: techs={len(j)} maxCF={j.cf.max():.3f} #CF>1={int((j.cf>1.001).sum())} sysCF={pe.sum()/(ce.sum()*8.76):.3f}')

# ---------------- D. PB transgression + E. prices/costs ----------------
print('\n=== D. PB transgression TL_* per year (>1 = over boundary) ===')
for s in sorted(x for x in m.data if x.startswith('TL_')):
    df = m[s].records; v = vc(df); ys = ycol(df)
    if df is not None and ys: print(f'  {s:30s}', {k: round(val, 3) for k, val in df.groupby(ys)[v].sum().to_dict().items()})
print('\n=== E. PRICES (Money/MWh) + COST (Mmoney) per year ===')
for p in ['EL_PRICE_YCR', 'H_PRICE_YCRA']:
    if p in m.data:
        df = m[p].records; v = vc(df); yy = ycol(df)
        for y in YEARS:
            s = df[df[yy] == y][v]
            if len(s): print(f'  {p} {y}: {s.min():.1f}..{s.max():.1f} mean {s.mean():.1f} neg={int((s<0).sum())}')
ob = m['OBJ_YCR'].records; ov = vc(ob); yo = ycol(ob)
for y in YEARS:
    print(f'  OBJ_YCR {y}: total {ob[ob[yo]==y][ov].sum():.1f} Mmoney')
try:
    from pybalmorel import MainResults
    _m = MainResults('MainResults_2030_40_50.gdx', paths=OUT, scenario_names='merged', system_directory=SYS)
    _p = _m.get_result('PRO_YCRAGF')
    print(f'\n=== F. pybalmorel read OK: {len(_p)} rows; years={sorted(_p["Year"].astype(str).unique())} ===')
except Exception as _e:
    print(f'\n=== F. pybalmorel note: {_e} ===')
print('\n=== AUDIT COMPLETE ===')
