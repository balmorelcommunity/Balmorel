* File RESEPrt4.inc to the addon REShareE.
* Hans Ravn 2007/8.

            
* -----------------------------------------------------------------------------

PUT REShareEPrt4;

* First print headings:

if ((REShareEPrt4.pw LT 32000),
REShareEPrt4.pw = 32000;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            RESEprt4.out" /;
PUT "File created:         " SYSTEM.DATE " " SYSTEM.TIME /;
PUT "Case-identification:  " OCASEID.TS //;

PUT "Output related to Add-on REShareE" / ;
PUT "Control settings:"/;
PUT "$Setglobal bb1          %bb1%" /;
PUT "$Setglobal bb2          %bb2%" /;
PUT "$Setglobal REShareE     %REShareE%" /;
put /;

);

* End of headings.

* -----------------------------------------------------------------------------

PUT "Year " Y.tl/;

PUT "  Marginal cost (price) of  the REShareE equation: "/;
LOOP(CCCRESHAREE,
PUT "    Group "  CCCRESHAREE.tl:20  ": Required share  "   RESHAREE(CCCRESHAREE):5:2     ", marginal cost " (QRESHAREE.m(CCCRESHAREE)/IOF0000001) " Money/MWh,    Group consists of countries  ";
LOOP(C$CCCRESHAREEC(CCCRESHAREE,C), PUT c.TL); PUT /;
ISCALAR1=  /* Cf. the expression in the equation QRESHAREE */
SUM(C$CCCRESHAREEC(CCCRESHAREE,C),
   SUM(IR$CCCRRR(C,IR),
     SUM((IS3,T),
       IHOURSINST(IS3,T)*
      (SUM(IAGK_Y(IA,IGE)$(RRRAAA(IR,IA) AND IGNOTETOH(IGE) AND GREE(IGE)), VGE_T.L(IA,IGE,IS3,T) )
    + SUM(IAGKN(IA,IGE)$(RRRAAA(IR,IA)  AND IGNOTETOH(IGE) AND GREE(IGE)), VGEN_T.L(IA,IGE,IS3,T)))    )

));
ISCALAR2=SUM(C$CCCRESHAREEC(CCCRESHAREE,C), SUM(IR$CCCRRR(C,IR),  DE_Y(IR)));  /* Cf. the expression in the equation QRESHAREE */

PUT "                                Prod:   "  (ISCALAR1 * IOF0001):10:0     " GWh, demand    "   (ISCALAR2 * IOF0001):10:0   " GWh" /;

);


* Tilføjelser, der er eksperimentelle, og nok ender et andet sted:

* Fuel use for