* File error3.inc

* This file is part of the Balmorel model.

* File last time modified 17-05-2002 (rus), 20080414(hr), 20120914(hr), 20150519(hr)


* This file contains check on input data.
* The checks are intended to detect input values that are inconsistent
* and which therefore may prevent the solver from finding a feasible solution.
* The checks assume that all 'standard' equations are included in the model,
* and only those,
* and if this assumption is not true, the checks may be misleading!

* Check the code below to see the exact meaning of this.


PUT ERRORFILE;

PUT / "The input was investigated for additional obvious errors before optimisation of year " Y.TL:4 ":" /;
ERRCOUNT3=0;


*-------------------------------------------------------------------------------
*--- DATA IN THE FILE geogr.inc: -----------------------------------------------

*--- TABLE FKPOT ---------------------------------------------------------------
*--- TABLE FKPOT Country level: ------------------------------------------------

LOOP(C,
LOOP(FFF,
IF( (FKPOT(C,FFF) AND ((SUM(G$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')) OR (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))),
       SUM(IA$ICA(C,IA), IGKFX_Y(IA,G)) ) )  GT FKPOT(C,FFF))),
ISCALAR1=(SUM(G$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')) OR (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))),
       SUM(IA$ICA(C,IA), IGKFX_Y(IA,G)) ) );
ISCALAR2=FKPOT(C,FFF);
PUT "Error in table FKPOT: already installed capacities exceed FKPOT as specified at country level" /;
PUT " for country "C.TL:OTLW " fuel "FFF.TL:OTLW " in " Y.TL:4 ".   Capacities: "ISCALAR1 " MW,  FKPOT: " ISCALAR2 " MW"/;
ERRCOUNT3=ERRCOUNT3+1;
)));

$ontext    original
LOOP(C,
LOOP(FFF,
IF( (FKPOT(C,FFF) AND (SUM(G$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')) OR (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')) AND (GDATA(G,'GDKVARIABL') EQ 1)),
       SUM(IA$ICA(C,IA), IGKFX_Y(IA,G)) ) )  GT FKPOT(C,FFF)),
ISCALAR1=(SUM(G$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')) OR (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')) AND (GDATA(G,'GDKVARIABL') EQ 1)),
       SUM(IA$ICA(C,IA), IGKFX_Y(IA,G)) ) );
ISCALAR2=FKPOT(C,FFF);
PUT "Error in table FKPOT: already installed capacities exceed FKPOT " /;
PUT " for country "C.TL:OTLW " fuel "FFF.TL:OTLW " in " Y.TL:4 ".   Capacities: "ISCALAR1 " MW,  FKPOT: " ISCALAR2 " MW"/;
ERRCOUNT3=ERRCOUNT3+1;
)));
$offtext


*--- TABLE FKPOT Region level: -------------------------------------------------
LOOP(IR,
LOOP(FFF,
IF( (FKPOT(IR,FFF) AND
        (SUM(G$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB') OR (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')))),   SUM(IA$RRRAAA(IR,IA), IGKFX_Y(IA,G))    ))       GT FKPOT(IR,FFF)),
ISCALAR1=(SUM(G$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB') OR (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))
       )),   SUM(IA$RRRAAA(IR,IA), IGKFX_Y(IA,G))    ));
ISCALAR2=FKPOT(IR,FFF);
PUT "Error in table FKPOT: already installed capacities exceed FKPOT as specified at region level" /;
PUT " for region "IR.TL:OTLW " fuel "FFF.TL:OTLW  " in " Y.TL:4 ".   Capacities: "ISCALAR1 " MW,  FKPOT: " ISCALAR2 " MW"/;
ERRCOUNT3=ERRCOUNT3+1;
);););

*--- TABLE FKPOT Area level: ---------------------------------------------------
LOOP(IA,
LOOP(FFF,
IF( (FKPOT(IA,FFF) AND (SUM(G$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB') OR (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))
      )), IGKFX_Y(IA,G)  ))
       GT FKPOT(IA,FFF)),
ISCALAR1=(SUM(G$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB') OR (GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM'))
       )), IGKFX_Y(IA,G)  ));
ISCALAR2=FKPOT(IA,FFF);
PUT "Error in table FKPOT: already installed capacities exceed FKPOT as specified at area level" /;
PUT " for area "IA.TL:OTLW " fuel "FFF.TL:OTLW  " in " Y.TL:4  ".   Capacities: "ISCALAR1 " MW,  FKPOT: " ISCALAR2 " MW"/;
ERRCOUNT3=ERRCOUNT3+1;
);););
*--- END TABLE FKPOT -----------------------------------------------------------



*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
* The conclusion is printed:

IF ((ERRCOUNT3 EQ 0),
PUT "No obvious additional errors detected before optimisation of year " Y.TL:4 "." /;
ELSE
IF ((ERRCOUNT3 EQ 1),
PUT "An additional error was detected before optimisation of year " Y.TL:4  "." /;
ELSE
PUT ERRCOUNT3:5:0 " additional errors were detected before optimisation of year " Y.TL:4  "." /;
);
PUT "See the file error3.inc for details about errors."
PUT //;
);

put LOGFILE;
* Note: The below text: "Some Balmorel errors" is a keyword for communication with the BUI. Do not change.
IF ((ERRCOUNT3 EQ 0),
PUT "No obvious additional errors detected before optimisation of year " Y.TL:4 "." /;
ELSE
PUT "Some additional Balmorel errors were detected before optimisation of year " Y.TL:4  "." /;
);
PUT "See the file errors.out for details about errors."
PUT //;
