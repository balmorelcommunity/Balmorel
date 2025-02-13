*Energy sovereignty addon - FF 2025
*Sets associated with the SOVEREIGNTY addon

SET C_SOV(C)  					"Group of countries that collectively achieve energy sovereignty"; 
C_SOV(C)=NO;	

*** Add soveregin countries here ***
*C_SOV('DENMARK')=YES;
*C_SOV('NORWAY')=YES;		

***	Balmorel
SET IR_SOV(RRR)     			"Internal regions that belong to group of sovereign countries";
SET IR_NON_SOV(RRR) 			"Internal regions that don't belong to group of sovereign countries";

*Initialize all internal regions as non-sovereign
IR_SOV(IR) = NO;
IR_NON_SOV(IR) = YES;

*Assign sovereignty to regions based on country sovereignty
IR_SOV(RRR) = YES$(SUM(C, CCCRRR(C, RRR) * C_SOV(C)));

*Exclude sovereign regions from non-sovereign set
IR_NON_SOV(RRR)$(IR_SOV(RRR)) = NO;

*** OptiFlow

$ifi not %OPTIFLOW%==yes $goto NO_OPTI_SOV

*Initialize all optiflow areas as non-sovereign
SET AAAOPTIFLOW_SOV(AAAOPTIFLOW);
SET AAAOPTIFLOW_NON_SOV(AAAOPTIFLOW);

AAAOPTIFLOW_SOV(AAAOPTIFLOW) = NO;
AAAOPTIFLOW_NON_SOV(AAAOPTIFLOW) = YES;

*Assign sovereignty to areas based on country sovereignty
AAAOPTIFLOW_SOV(AAAOPTIFLOW) = YES$(SUM(C,ICA(C,AAAOPTIFLOW)*C_SOV(C)));

*Exclude sovereign areas from non-sovereign set
AAAOPTIFLOW_NON_SOV(AAAOPTIFLOW)$AAAOPTIFLOW_SOV(AAAOPTIFLOW) = NO;

$label NO_OPTI_SOV