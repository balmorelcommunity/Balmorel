* File equations.inc.
* To be used with add-on HeatSv to the Balmorel model.

* Renovation rate constrained
QVHeatSv_SAR(IA,HeatSv_P,HeatSv_ELM)..

        VHeatSv_SAR(IA,HeatSv_P,HeatSv_ELM) =l= HeatSv_AR(IA,HeatSv_P)*HeatSv_SHELM(HeatSv_P,HeatSv_ELM)*HeatSv_REN(HeatSv_P)*IOF001;

* Cumulative renovation amount constrained
QVHeatSv_SARCUM(IA,HeatSv_P,HeatSv_ELM)..

        VHeatSv_SAR(IA,HeatSv_P,HeatSv_ELM) =l= HeatSv_AR(IA,HeatSv_P)*HeatSv_SHELM(HeatSv_P,HeatSv_ELM)-HeatSv_SARCUM(IA,HeatSv_P,HeatSv_ELM);

*QVHeatSv_HS(IA,IS3,T)..

*        VHeatSv_HS(IA,IS3,T) =e= SUM((HeatSv_P,HeatSv_ELM), VHeatSv_SAR(IA,HeatSv_P,HeatSv_ELM)*IHeatSv_SHP_T(HeatSv_P,HeatSv_ELM,IS3,T));
