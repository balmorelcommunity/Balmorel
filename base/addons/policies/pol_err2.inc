* File pol_err2.inc
* This file is part of the policies addon

* Geografy defining Policy Area is checked for dobbelt reprecentation of areas and regionss
* Writing to ERRORFILE.

PUT ERRORFILE / "Now checking input data for addon Policies." /;

*------------------------------------------------------------------------------
*--- DATA IN THE FILE POLAREAGEO.inc:-------------------------------------------------
* Check Area and Regions in Countries
LOOP( POLAREA,
         LOOP(CCCRRRAAA$(POLAREAGEO(POLAREA,CCCRRRAAA)),
                 LOOP(C$(sameas(C,CCCRRRAAA)),
                         LOOP(CCCRRRAAAALIAS$(POLAREAGEO(POLAREA,CCCRRRAAAALIAS)),
                                 LOOP(IA$(sameas(IA,CCCRRRAAAALIAS)),
                                         If (ICA(C,IA),
                                                 PUT "Invalid geografy for Policy Area: " POLAREA.TL " Area: " IA.TL " is already countained in " C.TL;
                                                 PUT "Error is automaticly corrected";
                                                 POLAREAGEO(POLAREA,IA) = NO;
                                                 PUT //;
ERRCOUNT2=ERRCOUNT2+1;
                                         )
                                 )
                         )
                         LOOP(CCCRRRAAAALIAS$(POLAREAGEO(POLAREA,CCCRRRAAAALIAS)),
                                 LOOP(IR$(sameas(IR,CCCRRRAAAALIAS)),
                                         If (CCCRRR(C,IR),
                                                 PUT "Invalid geografy for Policy Area: " POLAREA.TL " Region: " IR.TL " is already countained in " C.TL;
                                                 PUT "Error is automaticly corrected";
                                                 POLAREAGEO(POLAREA,IR) = NO;
                                                 PUT //;
ERRCOUNT2=ERRCOUNT2+1;
                                         )
                                 )
                         )

                 )
         )
);



* Check Area in Region
LOOP( POLAREA,
         LOOP(CCCRRRAAA$(POLAREAGEO(POLAREA,CCCRRRAAA)),
                 LOOP(IR$(sameas(IR,CCCRRRAAA)),
                         LOOP(CCCRRRAAAALIAS$(POLAREAGEO(POLAREA,CCCRRRAAAALIAS)),
                                 LOOP(IA$(sameas(IA,CCCRRRAAAALIAS)),
                                         If (RRRAAA(IR,IA),
                                                 PUT "Invalid geografy for Policy Area: " POLAREA.TL " Area: " IA.TL " is already countained in Region " IR.TL;
                                                 PUT "Error is automaticly corrected";
                                                 POLAREAGEO(POLAREA,IA) = NO;
ERRCOUNT2=ERRCOUNT2+1;
                                         )
                                 )
                         )
                 )
         )
);
PUT //;

