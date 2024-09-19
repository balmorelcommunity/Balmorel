* OPTIFLOW ANNUITY CALCULATIONS

$ifi not %inv%==yes $goto NO_PROC_INVESTMENTS

SCALAR ILOOPBREAK     "Scalar used as binary number to break any loop function";
PARAMETER IWEIGHTY(Y)                  "Relative weight of the individual years in Y";
* Set the relative weight of the individual years in Y.
* Two ideas implemented here. Used according to option bb4weighty.
* Simple idea is to give equal weights:
$ifi "%bb4weighty%"=="same"      IWEIGHTY(Y) = 1;
* More complex weighting of the individual years (years in YYY but not in Y are shared between two nearest (first and last years double the shared weight contribution)):
$ifi "%bb4weighty%"=="shareYYY"  IWEIGHTY(Y)$(ORD(Y) EQ 1) = 1$(CARD(Y) EQ 1) + ((YVALUE(Y+1)-YVALUE(Y)-1)+1)$(CARD(Y) GT 1);
$ifi "%bb4weighty%"=="shareYYY"  IWEIGHTY(Y)$((ORD(Y) GT 1) AND (ORD(Y) LT CARD(Y))) = (YVALUE(Y) - YVALUE(Y-1) -1)/2  + (YVALUE(Y+1) - YVALUE(Y) -1)/2    +1;
$ifi "%bb4weighty%"=="shareYYY"  IWEIGHTY(Y)$((ORD(Y) EQ CARD(Y)) AND (CARD(Y) GT 1)) = ((YVALUE(Y)-YVALUE(Y-1)-1)+1);

* HERE COMES SOME ANNUITY RELATED PARAMETERS, THE INTENTION IS TO MAKE ANNUITY PAYMENST WORK FOR OPTIFLOW
* SO THAT PREVIOUS YEAR INVESTMENTS WILL BE PAID LATER
PARAMETER IYHASANNUITYPROC(Y,Y,PROC)        "Binary parameter to establish whether the annuity of an investment of a process made in Y (first index) should be paid in the time period Y (second index) (0,1)" ;
PARAMETER IINVYEARPROC_LEFT(Y,Y,PROC)      	"Remaining years of the lifetime of PROC of an investment made in Y (first index) at the beggining of Y (second index) (years)";
PARAMETER IN_INV_PROC(Y,PROC)              	"Number of investments made OF PROC within Y (fraction)";

**PROCESS
LOOP(IPROCFIND,
  LOOP(IYALIAS,
    LOOP(Y$(ORD(Y) EQ ORD(IYALIAS)),
      IINVYEARPROC_LEFT(IYALIAS,Y,IPROCFIND)=PROCDATA(IPROCFIND,'PROCLIFETIME');
    );
  );
);

LOOP(IPROCFIND,
  LOOP(IYALIAS,
    ILOOPBREAK=0;
    IN_INV_PROC(IYALIAS,IPROCFIND)=ROUND(IWEIGHTY(IYALIAS)/PROCDATA(IPROCFIND,'PROCLIFETIME'));
*Correction of IN_INV_PROC
      IF (IN_INV_PROC(IYALIAS,IPROCFIND) EQ 0,
        IN_INV_PROC(IYALIAS,IPROCFIND)=1;
      );
      LOOP(Y$(ORD(Y) GE ORD(IYALIAS) AND (ILOOPBREAK EQ 0)),
*First year's annuity
        IF (ORD(Y) EQ ORD(IYALIAS),
          IYHASANNUITYPROC(IYALIAS,Y,IPROCFIND)= 1;
          IF(IINVYEARPROC_LEFT(IYALIAS,Y,IPROCFIND)*IN_INV_PROC(IYALIAS,IPROCFIND) LE IWEIGHTY(Y),
            ILOOPBREAK=1;
          );
          IINVYEARPROC_LEFT(IYALIAS,Y+1,IPROCFIND)$(ORD(Y) NE CARD(IYALIAS2))=PROCDATA(IPROCFIND,'PROCLIFETIME')*IN_INV_PROC(IYALIAS,IPROCFIND)-IWEIGHTY(Y);
        );
*Remaining year's annuity
      IF (ORD(Y) GT ORD(IYALIAS),
        IF ( IINVYEARPROC_LEFT(IYALIAS,Y,IPROCFIND) GT IWEIGHTY(Y) ,
          IYHASANNUITYPROC(IYALIAS,Y,IPROCFIND)= 1;
            IINVYEARPROC_LEFT(IYALIAS,Y+1,IPROCFIND)$(ORD(Y) NE CARD(IYALIAS2))=IINVYEARPROC_LEFT(IYALIAS,Y,IPROCFIND)-IWEIGHTY(Y);
          );
          IF ((IINVYEARPROC_LEFT(IYALIAS,Y,IPROCFIND) GE IWEIGHTY(IYALIAS)/2) AND (IINVYEARPROC_LEFT(IYALIAS,Y,IPROCFIND) LE IWEIGHTY(Y)) ,  !!Assumption: if the reamining years are more ore equal than half of IWEIGHTY, then the technology is in in this snapshot
            IYHASANNUITYPROC(IYALIAS,Y,IPROCFIND)= 1;
            ILOOPBREAK=1;
          );
          IF ((IINVYEARPROC_LEFT(IYALIAS,Y,IPROCFIND) LT IWEIGHTY(IYALIAS)/2) AND (IINVYEARPROC_LEFT(IYALIAS,Y,IPROCFIND) LE IWEIGHTY(Y)) , !!Assumption: if the reamining years are less than half of IWEIGHTY, then the technology is out in this snapshot
            IYHASANNUITYPROC(IYALIAS,Y,IPROCFIND)= 0;
            ILOOPBREAK=1;
          );
        );
      );
  );
);


PARAMETER ANNUITYCPROC(CCC,PROC)			"Parameter for annuity values of processes";

ANNUITYCPROC(CCC,PROC)$(PROCDATA(PROC,'PROCKAPVARIABLE') EQ 1) = RateOfReturn / (1 - (1 + RateOfReturn) ** (-PROCDATA(PROC,'PROCLIFETIME')));

$label NO_PROC_INVESTMENTS