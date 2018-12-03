* File internal.inc.
* To be used with add-on HeatSv to the Balmorel model.

PARAMETER IHeatSv_SUMST(AAA) 'Annual amount of heat saving';

$ifi %BB1%==yes    IHeatSv_SUMST(IA) = SUM((S,T), IHOURSINST(S,T)*HeatSv_VAR_T(IA,S,T));
$ifi %BB2%==yes    IHeatSv_SUMST(IA) = SUM((S,T), IHOURSINST(S,T)*HeatSv_VAR_T(IA,S,T));
$ifi %BB3%==yes    IHeatSv_SUMST(IA) = SUM((SSS,T), IHOURSINST(SSS,T)*HeatSv_VAR_T(IA,SSS,T));

PARAMETER IHeatSv_SHP_T(HeatSv_P,HeatSv_ELM,S,T) 'Varying heat saving potentials in different type of buildings in kWh/m2';

IHeatSv_SHP_T(HeatSv_P,HeatSv_ELM,S,T)  =
    ((HeatSv_SHP(HeatSv_P,HeatSv_ELM) * HeatSv_VAR_T('DK_W_INDIVIDUAL',S,T)) / IHeatSv_SUMST('DK_W_INDIVIDUAL'))$(IHeatSv_SUMST('DK_W_INDIVIDUAL') GT 0);


PARAMETER IHeatSv_HSC_Y(HeatSv_P,HeatSv_ELM) 'Cost for renovation of different building elements in different building types in a simulation year, EUR/m2floor';
SCALAR IOF001     'Multiplier 0.01'       /0.01/;


PARAMETER DIVHS(HeatSv_ELM) 'Parameter for calculating annuity';
   
	DIVHS(HeatSv_ELM)=(1-power((1+HeatSv_DR), -1*HeatSv_LIFE(HeatSv_ELM)));


PARAMETER ANNUITYHS(HeatSv_ELM) 'Transforms investment into heat saving measures to annual payment'    ;

	ANNUITYHS(HeatSv_ELM)$(DIVHS(HeatSv_ELM) NE 0)=HeatSv_DR/DIVHS(HeatSv_ELM) ;

