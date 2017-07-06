* File RESEHPrt4.inc to the addon REShareEH.
* Hans Ravn 2007/8.



* -----------------------------------------------------------------------------

PUT REShareEHPrt4;

* First print headings:

if ((REShareEHPrt4.pw LT 32000),
REShareEHPrt4.pw = 32000;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            RESEHprt4.out" /;
PUT "File created:         " SYSTEM.DATE " " SYSTEM.TIME /;
PUT "Case-identification:  " OCASEID.TS //;

PUT "Output related to Add-on REShareEH" / ;
PUT "Control settings:"/;
PUT "$Setglobal bb1          %bb1%" /;
PUT "$Setglobal bb2          %bb2%" /;
PUT "$Setglobal REShareEH    %REShareEH%" /;
put /;



* Here we also print some info on technologies:
PUT / /  "Technologies qualified as producing renewable electricity and heat, and its fuel: "/ /;
LOOP(GREEH,
PUT GREEH.TL:OTLG;
LOOP(FFF$IGF(GREEH,FFF), PUT FFF.TL;



          ); PUT      /;
);

put / / ;

);
* End of headings.

* -----------------------------------------------------------------------------

PUT "Year " Y.tl/;

PUT "  Marginal cost (price) of the REShareEH equation: "/;
LOOP(CCCRESHAREEH,
PUT "    Group "  CCCRESHAREEH.tl:20  ": Required share:  "   RESHAREEH(CCCRESHAREEH):5:2     ", marginal cost: " (QRESHAREEH.m(CCCRESHAREEH)/IOF1_) " Money/MWh,";
PUT "    Group consists of countries:  "; LOOP(C$CCCRESHAREEHC(CCCRESHAREEH,C), PUT C.TL); PUT /;
ISCALAR1= /* Electricity production */ /* Cf. the expression in the equation QRESHAREEH */
SUM(C$CCCRESHAREEHC(CCCRESHAREEH,C),
*   SUM(IR$CCCRRR(C,IR),
     SUM((IS3,T),
       IHOURSINST(IS3,T)*
    (
      SUM(IAGK_Y(IA,IGE)$(ICA(C,IA) AND IGNOTETOH(IGE) AND GREEH(IGE)), VGE_T.L(IA,IGE,IS3,T) )
    - SUM(IA$ICA(C,IA), VESTOLOADT.L(IA,IS3,T))
    + SUM(IAGKN(IA,IGE)$(ICA(C,IA)  AND IGNOTETOH(IGE) AND GREEH(IGE)), VGEN_T.L(IA,IGE,IS3,T))
* NEW ESTO?
*    + SUM(IAGK_Y(IA,IGH)$(RRRAAA(IR,IA) AND IGNOTETOH(IGH) AND GREEH(IGH)), VGH_T.L(IA,IGH,IS3,T) )
*    + SUM(IAGKN(IA,IGH)$(RRRAAA(IR,IA)  AND IGNOTETOH(IGH) AND GREEH(IGH)), VGHN_T.L(IA,IGH,IS3,T))
      )
 /*
     (
      SUM(IAGK_Y(IA,IGE)$(RRRAAA(IR,IA) AND IGNOTETOH(IGE) AND GREEH(IGE)), VGE_T.L(IA,IGE,IS3,T) /(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IA,IGE))) )
     + SUM(IAGKN(IA,IGE)$(RRRAAA(IR,IA)  AND IGNOTETOH(IGE) AND GREEH(IGE)), VGEN_T.L(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IA,IGE))) )
*     + SUM(IAGK_Y(IA,IGH)$(RRRAAA(IR,IA) AND IGNOTETOH(IGH) AND GREEH(IGH)), VGH_T.L(IA,IGH,IS3,T) /(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IA,IGH))) )
*     + SUM(IAGKN(IA,IGH)$(RRRAAA(IR,IA)  AND IGNOTETOH(IGH) AND GREEH(IGH)), VGHN_T.L(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IA,IGH))) )
   )
 */
));

ISCALAR2=  /* Heat production */ /* Cf. the expression in the equation QRESHAREEH */
SUM(C$CCCRESHAREEHC(CCCRESHAREEH,C),
     SUM((IS3,T),
       IHOURSINST(IS3,T)*
    (
*      SUM(IAGK_Y(IA,IGE)$(ICA(C,IA)   AND IGNOTETOH(IGE)    AND GREEH(IGE)), VGE_T.L(IA,IGE,IS3,T) )
*    + SUM(IAGKN(IA,IGE)$(ICA(C,IA)    AND IGNOTETOH(IGE)    AND GREEH(IGE)), VGEN_T.L(IA,IGE,IS3,T))
    + SUM(IAGK_Y(IA,IGH)$(ICA(C,IA)    AND IGNOTETOH(IGH)    AND GREEH(IGH)), VGH_T.L(IA,IGH,IS3,T) )
    - SUM(IA$ICA(C,IA), VHSTOLOADT.L(IA,IS3,T))
    + SUM(IAGKN(IA,IGH)$(ICA(C,IA)     AND IGNOTETOH(IGH)    AND GREEH(IGH)), VGHN_T.L(IA,IGH,IS3,T))
* NEW?   VHSTOLOADT.L ?

      )

 /*
   (
*      SUM(IAGK_Y(IA,IGE)$(RRRAAA(IR,IA) AND IGNOTETOH(IGE) AND GREEH(IGE)), VGE_T.L(IA,IGE,IS3,T) /(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IA,IGE))) )
*    + SUM(IAGKN(IA,IGE)$(RRRAAA(IR,IA)  AND IGNOTETOH(IGE) AND GREEH(IGE)), VGEN_T.L(IA,IGE,IS3,T)/(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IA,IGE))) )
    + SUM(IAGK_Y(IA,IGH)$(RRRAAA(IR,IA) AND IGNOTETOH(IGH) AND GREEH(IGH)), VGH_T.L(IA,IGH,IS3,T) /(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IA,IGH))) )
    + SUM(IAGKN(IA,IGH)$(RRRAAA(IR,IA)  AND IGNOTETOH(IGH) AND GREEH(IGH)), VGHN_T.L(IA,IGH,IS3,T)/(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IA,IGH))) )
   )
 */


));


ISCALAR3=SUM(C$CCCRESHAREEHC(CCCRESHAREEH,C), SUM(IR$CCCRRR(C,IR), DE_Y(IR)) );               /* Cf. the expression in the equation QRESHAREEH */
ISCALAR4=SUM(C$CCCRESHAREEHC(CCCRESHAREEH,C), SUM(IA$ICA(C,IA), DH_Y(IA)) );                  /* Cf. the expression in the equation QRESHAREEH */


PUT "                                Renewable production (GWh):      "   ((ISCALAR1+ISCALAR2)*IOF0001):10:0     " of which: electricity: "(ISCALAR1*IOF0001):10:0 "  and heat: " (ISCALAR2*IOF0001):10:0 /;
PUT "                                Nominal demand:      (GWh):      "   ((ISCALAR3+ISCALAR4)*IOF0001):10:0     " of which: electricity: "(ISCALAR3*IOF0001):10:0 "  and heat: " (ISCALAR4*IOF0001):10:0 /;

);

                    /*
iscalar1= sum(c,sum(ia$ica(c,ia),  SUM((IS3,T),
       IHOURSINST(IS3,T)* (
    + SUM(IAGK_Y(IA,IGH)$(RRRAAA(IR,IA) AND IGNOTETOH(IGH) AND GREEH(IGH)), VGH_T.L(IA,IGH,IS3,T) )
    + SUM(IAGKN(IA,IGH)$(RRRAAA(IR,IA)  AND IGNOTETOH(IGH) AND GREEH(IGH)), VGHN_T.L(IA,IGH,IS3,T))

                   )
)));
put "varmeialt: " iscalar1;
*/
