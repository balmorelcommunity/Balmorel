* File comberr2.inc for the Balmorel model.
* Checking input for the combtech addon.
* Writing to ERRORFILE.
* Last revision  20160816(hr)
* There are todo's

PUT ERRORFILE /"&" / "Now checking input data for addon OptiFlow." /;
ISCALAR2 = ERRCOUNT2;

* ------------------------------------------------------------------------------
* Test that the sets PROCSOURCE, PROCSINK, PROCBUFFER and PROCEXIM are mutually non-overlapping
* and that they together constitute all PROC (the latter fulfilled by definition of IPROCINTERIOR):

* For printing: OLTWP, OLTWF etc. for specifying the field width.
$if not declared OLTWP   SCALAR OLTWP      "                    " /10/; !! Max field with processes
$if not declared OLTWF   SCALAR OLTWF      "                    " /10/; !! Max field with flows
$if not declared OLTWCRA SCALAR OLTWCRA    "                    " /10/; !! Max field with geography
$if not declared OLTWYST SCALAR OLTWYST    "    "                 /4/;  !! Max field with time
$if not declared OLTW    SCALAR OLTW       "                    " /10/; !! Max field with general use.

OLTWP   = MAX(OLTWP,SMAX(PROC, CARD(PROC.TL)));
OLTWF   = MAX(OLTWF,SMAX(FLOW, CARD(FLOW.TL)));
OLTWCRA = MAX(OLTWCRA,SMAX(CCCRRRAAA, CARD(CCCRRRAAA.TL)));
OLTWYST = MAX(OLTWYST,SMAX(YYY, CARD(YYY.TL))); OLTWYST = MAX(OLTWYST,SMAX(SSS, CARD(SSS.TL))); OLTWYST = MAX(OLTWYST,SMAX(TTT, CARD(TTT.TL)));
OLTW    = MAX(OLTWP,OLTWF,OLTWCRA);
* end: Eventually move to error1.inc

* Initialisation of auxiliary variables:
* (No errcount1)
$if not declared IERRCOUNT2 SCALAR IERRCOUNT2 "Error count 2" /0/;
$if not declared IERRCOUNT3 SCALAR IERRCOUNT3 "Error count 3" /0/;
$if not declared IERRCOUNT4 SCALAR IERRCOUNT4 "Error count 4" /0/;

ISCALAR2 = IERRCOUNT2;
SET IHELPPROC(PROC);
IHELPPROC(PROC) = PROCSOURCE(PROC)*PROCSINK(PROC);
IF((CARD(IHELPPROC) NE 0), PUT "Error: sets PROCSOURCE and PROCSINK  have common elements, they should not"/; IERRCOUNT2 = IERRCOUNT2 + 1; );
IHELPPROC(PROC) = PROCSOURCE(PROC)*PROCBUFFER(PROC);
IF((CARD(IHELPPROC) NE 0), PUT  "Error: sets PROCSOURCE and PROCBUFFER  have common elements, they should not"/; IERRCOUNT2 = IERRCOUNT2 + 1; );
IHELPPROC(PROC) = PROCBUFFER(PROC)*PROCSINK(PROC);
IF((CARD(IHELPPROC) NE 0), PUT  "Error: sets PROCBUFFER and PROCSINK  have common elements, they should not"/; IERRCOUNT2 = IERRCOUNT2 + 1; );
IHELPPROC(PROC) = PROCSOURCE(PROC)*PROCEXIM(PROC);
IF((CARD(IHELPPROC) NE 0), PUT  "Error: sets PROCSOURCE and PROCEXIM  have common elements, they should not"/; IERRCOUNT2 = IERRCOUNT2 + 1; );
IHELPPROC(PROC) = PROCSINK(PROC)*PROCEXIM(PROC);
IF((CARD(IHELPPROC) NE 0), PUT  "Error: sets PROCSINK and PROCEXIM  have common elements, they should not"/; IERRCOUNT2 = IERRCOUNT2 + 1; );
IHELPPROC(PROC) = PROCBUFFER(PROC)*PROCEXIM(PROC);
IF((CARD(IHELPPROC) NE 0), PUT  "Error: sets PROCBUFFER and PROCEXIM  have common elements, they should not"/; IERRCOUNT2 = IERRCOUNT2 + 1; );
IF((ISCALAR2 LT IERRCOUNT2), PUT /; );
* todo:  PROCSTORAGE  !  *****Todo todo


* ------------------------------------------------------------------------------
* Assumptions for good data: for any (PROC,FLOWINDIC) there should be non-zero values in at most one of the three above files.
* Further, these files are relevant only for Source, Sink and Buffer nodes.
* Check: only ource, Sink and Buffer nodes, i.e., non-interior nodes:
ISCALAR2 = IERRCOUNT2;
$ONTEXT
LOOP(IPROCINTERIOR,
  IF(SUM(FLOWINDIC,ABS(SOSIBU2INDIC(IPROCINTERIOR,FLOWINDIC))),   !! Error:
    PUT "Error with SOSIBU2INDIC... : Values should be zero for interior PROC, it is not";
  );
);
$OFFTEXT
LOOP(Y,
LOOP((IPROCINTERIOR,FLOW),
  IF(SUM(FLOWINDIC,ABS(SOSIBU2INDIC(Y,IPROCINTERIOR,FLOW,FLOWINDIC))),   !! Error:
    PUT "Error with SOSIBU2INDIC... : Values should be zero for interior PROC, it is not";  IERRCOUNT2 = IERRCOUNT2 + 1;
  );
););
* Check: for any (PROC,FLOWINDIC) there should be non-zero values in at most one of the three above files:
LOOP(PROC$(NOT IPROCINTERIOR(PROC)),
  !! TODO
);
IF((ISCALAR2 LT IERRCOUNT2), PUT /; );


* ------------------------------------------------------------------------------
* Todo: 'verify that there are two or more leaving FLOW  with IONEMANY'
* check location of this statement in the .gms file

* ------------------------------------------------------------------------------
* Todo: 'verify that there are two or more entering FLOW  with IMANYONE'
* check location of this statement in the .gms file

* ------------------------------------------------------------------------------
* TODO: verify that with IONEMANY and IMANYONE the value in PROCINOUTFLOW
* is 1 (or whatever value is used)


* ------------------------------------------------------------------------------
* TODO:
* PARAM TRANSDIST(IAAAE,IAAAI) and SET ITRANSFROMTO(IAAAE,IAAAI): warning (error?) if not symmetric
* ------------------------------------------------------------------------------

* ------------------------------------------------------------------------------
* TODO:
* SET PROCEXIM: CNA IT HAVE MOE THAN ONE ELEMENT? hOW THEN OTHER CODE?
* ------------------------------------------------------------------------------

* ------------------------------------------------------------------------------
* Set ITWWT is internal, but check it anyway because assumption is essential.
* Set ITWWT should have only one element:
ISCALAR2 = IERRCOUNT2;
IF((CARD(ITWWT) EQ 0),
  PUT "Error: Set ITWWT must have one element, it does not have any." /;
  IERRCOUNT2 = IERRCOUNT2 + 1;
);
IF((CARD(ITWWT) GT 1),
  PUT "Error: Set ITWWT must have only one element, it has more." /;
  IERRCOUNT2 = IERRCOUNT2 + 1;
);
IF((ISCALAR2 LT IERRCOUNT2), PUT /; );
* ------------------------------------------------------------------------------

* ------------------------------------------------------------------------------
* PARAMETER SOSIBUFLOW_VAR_T(AAA,PROC,FLOW,SSS,TTT) "Variation in some Source, Sink or Buffer Flows over the year"  -and all the similar SOSIBUxxx
* verify that only sosibu elements have data
* todo
* Is it possible that SO, SI or BU are connected? If not,check it.
* todo
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
* Verify consistency between FLOWFROMTOPROC and PROCINOUTFLOW:
LOOP((Y,IA),
   ISCALAR2 = IERRCOUNT2;
* Flows entering an interior Proc according to FLOWFROMTO must in PROCINOUTFLOW be connected to a Flow leaving the Proc:
  LOOP((IPROCINTERIOR,IFLOWIN)$IENTERPROC(Y,IA,IPROCINTERIOR,IFLOWIN), !! IENTERPROC is derived from FLOWFROMTO
    ISCALAR1 = 0;
    LOOP(IFLOWOUT$(IPROCINOUTFLOW(Y,IA,IPROCINTERIOR,IFLOWIN,IFLOWOUT) OR IPROCINOUTFLOW(Y,IA,IPROCINTERIOR,IFLOWOUT,IFLOWIN)),  !! IPROCINOUTFLOW is derived from PROCINOUTFLOW
      ISCALAR1 = ISCALAR1 + 1;
    );
    IF((ISCALAR1 EQ 0),
      PUT "Error: Inconsistency between FLOWFROMTOPROC and PROCINOUTFLOW:   Area " IA.TL:OLTWCRA " PROC " IPROCINTERIOR.TL:OLTWP " ";
      PUT "FLOW " IFLOWIN.TL:OLTWF " enters the interior PROC according to FLOWFROMTOPROC but it does not link to any FLOW leaving  the PROC according to PROCINOUTFLOW"/;
      IERRCOUNT2 = IERRCOUNT2 + 1;
    ));
* Flows leaving an interior Proc according to FLOWFROMTO must in PROCINOUTFLOW be connected to a Flow entering the Proc:
  LOOP((IPROCINTERIOR,IFLOWOUT)$ILEAVEPROC(Y,IA,IPROCINTERIOR,IFLOWOUT), !! IENTERPROC is derived from FLOWFROMTO
    ISCALAR1 = 0;
    LOOP(IFLOWIN$(IPROCINOUTFLOW(Y,IA,IPROCINTERIOR,IFLOWOUT,IFLOWIN) OR IPROCINOUTFLOW(Y,IA,IPROCINTERIOR,IFLOWIN,IFLOWOUT)),  !! IPROCINOUTFLOW is derived from PROCINOUTFLOW
      ISCALAR1 = ISCALAR1 + 1;
    );
    IF((ISCALAR1 EQ 0),
      PUT "Error: Inconsistency between FLOWFROMTOPROC and PROCINOUTFLOW:   Area " IA.TL:OLTWCRA " PROC " IPROCINTERIOR.TL:OLTWP " ";
      PUT "FLOW " IFLOWOUT.TL:OLTWF " leaves the interior PROC according to FLOWFROMTOPROC but it does not link to any FLOW entering the PROC according to PROCINOUTFLOW"/;
      IERRCOUNT2 = IERRCOUNT2 + 1;
    ));
  IF((ISCALAR2 LT IERRCOUNT2), PUT /; );
);
*-------------------------------------------------------------------------------

*-------------------------------------------------------------------------------
* TODO
* Check that no FLOW enters a SOURCE PROC (VSOURCE is not a FLOW in this context).
* Check that no FLOW leaves a SINK PROC (VSINK is not a FLOW in this context).
* Check that no interior PROC has only entering or only leaving FLOW.
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
* Check that no element from IPROCINTERIOR has values in SOSIBUBOUND

ISCALAR2 = IERRCOUNT2;
LOOP(IA,
LOOP(IPROCINTERIOR,
LOOP(FLOW, LOOP((Y,S,T),
LOOP(ILOUPFXSET$SOSIBUBOUND(Y,IA,IPROCINTERIOR,FLOW,ILOUPFXSET),
  IERRCOUNT2 = IERRCOUNT2 + 1;
  PUT "Error: SOSIBUBOUND has a value for an element in IPROCINTERIOR, this is illegal:  Area "IA.TL:OLTWCRA " Process "  IPROCINTERIOR.TL:OLTWP " Flow "   FLOW.TL:OLTWF /;
)
))));
* TODO:  SOSIBUBOUND_xxx
IF((ISCALAR2 LT IERRCOUNT2), PUT /; );



IF((ISCALAR2 EQ ERRCOUNT2),
       PUT  "Finished checking input data for addon OptiFlow, no obvious errors found, total number of observed errors is unchanged at " ERRCOUNT2:4:0   /;
ELSE   PUT  "Finished checking input data for addon OptiFlow, total number of observed errors is now " ERRCOUNT2:4:0   /;);
PUT "#" /;
