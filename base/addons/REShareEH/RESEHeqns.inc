* File equations.inc to the addon REShareEH.


* Equation  QRESHAREEH  is with inspiration from equations QEEQ and QHEQ:
QRESHAREEH(CCCRESHAREEH)..

SUM(C$CCCRESHAREEHC(CCCRESHAREEH,C),
*   SUM(IR$CCCRRR(C,IR),
     SUM((IS3,T),
       IHOURSINST(IS3,T)*
      (
      SUM(IAGK_Y(IA,IGE)$(ICA(C,IA) AND IGNOTETOH(IGE) AND GREEH(IGE)), VGE_T(IA,IGE,IS3,T) )
    - SUM(IA$ICA(C,IA), VESTOLOADT(IA,IS3,T))
    + SUM(IAGKN(IA,IGE)$(ICA(C,IA)  AND IGNOTETOH(IGE) AND GREEH(IGE)), VGEN_T(IA,IGE,IS3,T))
* NEW?
    + SUM(IAGK_Y(IA,IGH)$(ICA(C,IA)    AND IGNOTETOH(IGH) AND GREEH(IGH)), VGH_T(IA,IGH,IS3,T) )
    - SUM(IA$ICA(C,IA), VHSTOLOADT(IA,IS3,T))
    + SUM(IAGKN(IA,IGH)$(ICA(C,IA)  AND IGNOTETOH(IGH) AND GREEH(IGH)), VGHN_T(IA,IGH,IS3,T))
* NEW?
     )

/*  This (outcommneted) expresses fuel use:
       (
      SUM(IAGK_Y(IA,IGE)$(RRRAAA(IR,IA) AND IGNOTETOH(IGE) AND GREEH(IGE)), VGE_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE') * (1-GEFFDERATE(IA,IGE))) )
    + SUM(IAGKN(IA,IGE)$(RRRAAA(IR,IA)  AND IGNOTETOH(IGE) AND GREEH(IGE)), VGEN_T(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IA,IGE))) )
    + SUM(IAGK_Y(IA,IGH)$(RRRAAA(IR,IA) AND IGNOTETOH(IGH) AND GREEH(IGH)), VGH_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE') * (1-GEFFDERATE(IA,IGH))) )
    + SUM(IAGKN(IA,IGH)$(RRRAAA(IR,IA)  AND IGNOTETOH(IGH) AND GREEH(IGH)), VGHN_T(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IA,IGH))) )
       )
*/
    )
)

=G=
* Distribution and transmission loss?
RESHAREEH(CCCRESHAREEH)* SUM(C$CCCRESHAREEHC(CCCRESHAREEH,C), SUM(IR$CCCRRR(C,IR),  DE_Y(IR)) + SUM(IA$ICA(C,IA),  DH_Y(IA)) );

/*
*(271569 )*1000;
271669*1000
$ifi %NEPcase%==6             + (37*1000000)
$ifi %NEPcase%==12            + (74*1000000)
$ifi %NEPcase%==18            + (111*1000000)
  -1000000000
*/

;

/*
Tillægene  6, 12, 18% giver  hhv 37, 74, 111 TWh.
Jeg tror, aftalen var at dette skulle gælde for 2020.
Det kunne så være rimeligt med en lineær interpolation, f.eks.  1/3 i 2010, 1/1 i 2020, 4/3 i 2030?
*/
