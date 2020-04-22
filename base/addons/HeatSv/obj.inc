* File obj.inc.
* To be used with add-on HeatS to the Balmorel model.

* Add-on HeatS: contribution to QOBJ:

+SUM((IA,HeatSv_P,HeatSv_ELM), (VHeatSv_SAR(IA,HeatSv_P,HeatSv_ELM)*IHeatSv_HSC_Y(HeatSv_P,HeatSv_ELM))*(SUM(C$ICA(C,IA),ANNUITYHS(HeatSv_ELM))))
