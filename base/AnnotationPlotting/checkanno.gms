$ontext
- Introduced versions for annotation statistics and time stamp

Annotation statistics
- 0.1 Individual entries per linking variable / constraint.
- 0.2 Individual stages per linking variable / constraint.
- 0.3 Individual stages per linking variable / constraint with maximal spacing of 10 blocks.
- 0.4 PIPS check implemented. Reimplemented calculation of min / max stage.
- 0.5 Fixed bug which reported wrong annotation as "Passed".
- 0.6 Added counting of linking constraints and variables in A0.
- 0.7 Fix negative local linking constraints. Added writeDebug option. (Manuel W 20190426, 10.45)
$offtext

$if not set jacFileName $abort --jacFileName missing
$if not set maxStages   $set maxStages 1000

$GDXIN '%jacFileName%'
$onempty

Set i(*) Equation names ;
$LOADDC i<i.dim1

Set j(*) Variable names ;
$LOADDC j<j.dim1

Set jobj(j) Objective name ;
$LOADDC jobj

Scalar objcoef Objective coefficient ;
$LOADDC objcoef

Equation e(i) Equations ;
$LOADDC e

free     Variable x(j) Variables ;
$LOADDC x

Parameter A(i,j) Jacobian ;
$LOADDC A

Set ANl(i,j) Non-linear Jacobian indicator / /;

Set s stages /0*%maxStages%/;
Scalar maxVarStage; maxVarStage = smax(j, x.stage(j));
Scalar blocks; blocks = maxVarStage-1;

if (maxVarStage+1>%maxStages%,
  put_utility 'log' / 'Increase --maxStages to at least ' (maxVarStage+2):0:0 ' for a proper report';
);
Abort$(maxVarStage+1>%maxStages%)   'More stages found than given by --maxStages'

Set A_ji_nz(j,i); Option A_ji_nz < A;
$if set skipFix Option clear=A;

Set s_0(s); s_0(s)$(ord(s)=1) = yes;
Set s_1(s); s_1(s)$(ord(s)=2) = yes;

Set x_stage(j,s); x_stage(j,s+x.stage(j))$s_0(s) = yes;
Set e_stage(i,s); e_stage(i,s+e.stage(i))$s_0(s) = yes;

Set x_link(j); x_link(j) = x.stage(j)=1;
Set e_link_A0(i); e_link_A0(i) = e.stage(i)=1;
Set e_link_An(i); e_link_An(i) = e.stage(i)=maxVarStage+1;

Set x_stages_used_in_equ(i,s);
Set x_stages_used_in_equ_helper(j,i,s);
x_stages_used_in_equ_helper(j,i,s)$(A_ji_nz(j,i) AND x_stage(j,s)) = yes;
Option x_stages_used_in_equ < x_stages_used_in_equ_helper;
Option clear=x_stages_used_in_equ_helper;

Set x_stages_used_in_equ_check(i,s) 
Option x_stages_used_in_equ_check < x_stages_used_in_equ;
x_stages_used_in_equ_check(i,s_1) = no;

Parameter maxStage(i), minStage(i),  badAnnotation /0/, badPIPS /0/;
maxStage(i) = smax(x_stages_used_in_equ_check(i,s), s.val);
minStage(i) = smin(x_stages_used_in_equ_check(i,s), s.val);

Option clear=x_stages_used_in_equ_check;
x_stages_used_in_equ(i,s)$(NOT e_link_An(i)) = no;

Set e_stages_used_in_var(j,s);
Set e_stages_used_in_var_helper(j,i,s);
e_stages_used_in_var_helper(j,i,s)$(A_ji_nz(j,i) AND x_link(j) AND e_stage(i,s)) = yes;
Option e_stages_used_in_var < e_stages_used_in_var_helper;
Option clear=e_stages_used_in_var_helper;


* Check the annotation 
$ifthen.skipCheck not set skipCheck
  loop(i,
    if (mapval(maxStage(i))=mapval(-inf),
      if (e.stage(i)<>1,
        put_utility 'log' / i.tl:0 ' has stage ' e.stage(i):0:0 ' but should have stage 1';
        badAnnotation = badAnnotation+1;
      )
    elseif maxStage(i)=minStage(i),
      if (minStage(i)<>e.stage(i),
        put_utility 'log' / i.tl:0 ' has stage ' e.stage(i):0:0 ' but should have stage ' minStage(i):0:0;
        badAnnotation = badAnnotation+1;
      )
    elseif maxStage(i)>minStage(i),
      if (maxVarStage+1<>e.stage(i),
        put_utility 'log' / i.tl:0 ' has stage ' e.stage(i):0:0 ' but should have stage ' (maxVarStage+1):0:0;
        badAnnotation = badAnnotation+1;
      );      
    else
      put_utility 'log' / i.tl:0 ' unexpected min/max stage: ' minStage(i):0:0 ',' maxStage(i):0:0 ',' e.stage(i):0:0
      abort 'unexpected behavior';
    )
  );
  put_utility$badAnnotation 'log' / 'Original jacobian has no proper annotation';
$else.skipCheck
  badAnnotation = 1;
$endif.skipCheck


* Fix the annotation if problems have been found
$setnames '%jacFileName%' fp fn fe
$ifthen.skipFix not set skipFix
  parameter repSize(s,*) / /; option repSize:0:1:1;
  if (badAnnotation,
    loop(s$sameas('0',s), loop(i, repSize(s+e.stage(i),'m orig') = repSize(s+e.stage(i),'m orig')+1));
    loop(s$sameas('0',s), loop(j, repSize(s+x.stage(j),'n orig') = repSize(s+x.stage(j),'n orig')+1));
    e.stage(i) = 1              $(mapval(maxStage(i))=mapval(-inf)) +
                 minStage(i)    $(maxStage(i)=minStage(i)) +
                 (maxVarStage+1)$(maxStage(i)>minStage(i));
    put_utility 'log' / 'Writing modified jacobian with proper annotation';
    execute_unload '%fp%%fn%_fixedanno_novenames%fe%', i, j, jobj, objcoef, e, x, A, ANl;
    loop(s$sameas('0',s), loop(i, repSize(s+e.stage(i),'m fixed') = repSize(s+e.stage(i),'m fixed')+1));
    loop(s$sameas('0',s), loop(j, repSize(s+x.stage(j),'n fixed') = repSize(s+x.stage(j),'n fixed')+1));
    display repSize;
  );
$endif.skipFix


* Report the annotation statistics
$ifthen.skipStats not set skipStats

* Calculate the annotation key indicators based on A
Scalar vars; vars = card(j);
Scalar equs; equs = card(i);
Scalar nnz;  nnz  = sum(A_ji_nz(j,i), 1);

Parameter e_link_count(i);  e_link_count(i) = sum(x_stages_used_in_equ(i,s) $(e_link_An(i) AND s.val>1), 1);
Parameter e_link_range(i);  e_link_range(i) = smax(x_stages_used_in_equ(i,s)$(e_link_An(i) AND s.val>1), s.val)
                                            - smin(x_stages_used_in_equ(i,s)$(e_link_An(i) AND s.val>1), s.val);
Set       e_link_x1(i);     e_link_x1(i)    = sum(x_stages_used_in_equ(i,s) $(e_link_An(i) AND s.val=1), 1) > 0;
            
Set       e_link_global(i); e_link_global(i)$(e_link_An(i) AND (e_link_x1(i) OR e_link_count(i) > 4 OR e_link_range(i) > 9)) = yes;
Set       e_link_local(i);  e_link_local(i) $(e_link_An(i) AND NOT e_link_global(i)) = yes;
            
Set       x_link_A0(j);     x_link_A0(j)    = smax(e_stages_used_in_var(j,s)$(x_link(j)), s.val) = 1;
Set       x_link_An(j);     x_link_An(j)    = smax(e_stages_used_in_var(j,s)$(x_link(j)), s.val) > 1;
Parameter x_link_count(j);  x_link_count(j) = sum(e_stages_used_in_var(j,s) $(x_link(j) AND s.val>1 AND s.val<maxVarStage+1), 1);
Parameter x_link_range(j);  x_link_range(j) = smax(e_stages_used_in_var(j,s)$(x_link(j) AND s.val>1 AND s.val<maxVarStage+1), s.val) 
                                            - smin(e_stages_used_in_var(j,s)$(x_link(j) AND s.val>1 AND s.val<maxVarStage+1), s.val);
Set       x_link_e1_en(j);  x_link_e1_en(j) = sum(e_stages_used_in_var(j,s) $(x_link(j) AND (s.val=1 OR s.val=maxVarStage+1)), 1) > 0;
            
Set       x_link_global(j); x_link_global(j)$(x_link_An(j) AND (x_link_e1_en(j) OR x_link_count(j) > 4 OR x_link_range(j) > 9)) = yes;
Set       x_link_local(j);  x_link_local(j) $(x_link_An(j) AND NOT x_link_global(j)) = yes;


Scalar nb_link_vars_A0;         nb_link_vars_A0     = sum(x_link_A0(j), 1);
Scalar nb_link_vars_An;         nb_link_vars_An     = sum(x_link_An(j), 1);
Scalar nb_link_vars_global;     nb_link_vars_global = sum(x_link_An(j)$x_link_global(j), 1);
Scalar nb_link_vars_local;      nb_link_vars_local  = sum(x_link_An(j)$x_link_local(j), 1) / blocks;

Scalar nb_link_equs_A0;         nb_link_equs_A0     = sum(e_link_A0(i), 1);
Scalar nb_link_equs_An;         nb_link_equs_An     = sum(e_link_An(i), 1);
Scalar nb_link_equs_global;     nb_link_equs_global = sum(e_link_An(i)$e_link_global(i), 1);
Scalar nb_link_equs_local;      nb_link_equs_local  = sum(e_link_An(i)$e_link_local(i), 1) / blocks;

* Compare the annotation statistics with PIPS requirements
if (nb_link_vars_global + nb_link_equs_global>20000,
  put_utility 'log' / 'Too many global elements. (' nb_link_vars_global:0:0 ' global linking variables and ' nb_link_equs_global:0:0 ' global linking constraints)';
  badPIPS = badPIPS+1;
);
if (nb_link_vars_local>2000,
  put_utility 'log' / 'Too many local linking variables. (' nb_link_vars_local:0:0 ' local linking variables per block)';
  badPIPS = badPIPS+1;
);
if (nb_link_equs_local>2000,
  put_utility 'log' / 'Too many local linking constraints. (' nb_link_equs_local:0:0 ' local linking constraints per block)';
  badPIPS = badPIPS+1;
);

* Write the annotation key indicators to csv, use the jacFileName
File results / %fn%_stats.csv /;
results.pc = 5;
put results;
put 'Instance', '%jacFileName%' /;
put 'Datetime', '%system.date% %system.time%'  /;
put 'Version', '0.7' /;

$ifthen.skipCheck not set skipCheck
  if (badAnnotation,
    put 'Annotation Check', 'Errors found' /;
  else
    put 'Annotation Check', 'Passed' /;
  );
$else.skipCheck
put 'Annotation Check', 'Unchecked' /;
$endif.skipCheck

if (badPIPS,
  put 'PIPS Check', 'Problems found' /;
else
  put 'PIPS Check', 'Passed' /;
);

put 'Variables',                            vars:0:0 /;
put 'Equations',                            equs:0:0 /;
put 'Non-zeros',                            nnz:0:0 /;
put 'Blocks',                               blocks:0:0 /;

put 'Linking variables A0',                 nb_link_vars_A0:0:0 /;
put 'Linking variables An',                 nb_link_vars_An:0:0 /;
put 'Global linking variables',             nb_link_vars_global:0:0 /;
put 'Local linking variables per block',    nb_link_vars_local /;

put 'Linking constraints A0',               nb_link_equs_A0:0:0 /;
put 'Linking constraints An',               nb_link_equs_An:0:0 /;
put 'Global linking constraints',           nb_link_equs_global:0:0 /;
put 'Local linking constraints per block',  nb_link_equs_local /;
putclose;

$if set writeDebug Execute_Unload '%fn%_debug.gdx' x_link_A0, x_link_global, e_link_A0, e_link_global;

$endif.skipStats
