* File compprint1.inc.
* This file is part of the redesigned welfare module for Balmorel.
* Author: Lars Bregnbæk
* Revision: 1.0 LB


* These files are used for comparison between scenarios
File compfile  /..\output\economic\%CASEID%.MED/;
File compfile1 /..\output\economic\%CASEID%lr.MED/;

File file_e_rev /..\output\economic\%CASEID% e_rev.med/;
File file_h_rev /..\output\economic\%CASEID% h_rev.med/;
File file_fxcost /..\output\economic\%CASEID% fxcost.med/;
File file_fuelcost /..\output\economic\%CASEID% fuelcost.med/;
File file_vcost /..\output\economic\%CASEID% vcost.med/;
*Erkki
File file_UCstartcost /..\output\economic\%CASEID% UCstartcost.med/;
File file_UCshutcost /..\output\economic\%CASEID% UCshutcost.med/;
File file_UCfixedcost /..\output\economic\%CASEID% UCfixedcost.med/;
*Erkki
File file_capcost_ex /..\output\economic\%CASEID% capcost_ex.med/;
File file_capcost_en /..\output\economic\%CASEID% capcost_en.med/;
File file_capcost_trans_ex /..\output\economic\%CASEID% capcost_trans_ex.med/;
File file_capcost_trans_en /..\output\economic\%CASEID% capcost_trans_en.med/;
File file_co2cost /..\output\economic\%CASEID% co2cost.med/;
File file_so2cost /..\output\economic\%CASEID% so2cost.med/;
File file_noxcost /..\output\economic\%CASEID% noxcost.med/;
File file_fueltax /..\output\economic\%CASEID% fueltax.med/;
File file_heattaxGH /..\output\economic\%CASEID% heattaxGH.med/;
File file_vindSubsidy /..\output\economic\%CASEID% vindSubsidy.med/;

File file_e_cost /..\output\economic\%CASEID% e_cost.med/;
File file_h_cost /..\output\economic\%CASEID% h_cost.med/;
File file_e_util /..\output\economic\%CASEID% e_util.med/;
File file_h_util /..\output\economic\%CASEID% h_util.med/;

File file_bottleneck /..\output\economic\%CASEID% bottleneck.med/;
File file_tradesurp /..\output\economic\%CASEID% tradesurp.med/;
File file_transcost /..\output\economic\%CASEID% transcost.med/;
File file_watervaluevar /..\output\economic\%CASEID% watervaluevar.med/;
File file_watervalue /..\output\economic\%CASEID% watervalue.med/;

File file_NOxemission /..\output\economic\%CASEID% NOxemission.med/;
File file_SO2emission /..\output\economic\%CASEID% SO2emission.med/;
File file_CO2shadowval /..\output\economic\%CASEID% CO2shadowval.med/;
File file_VEShadowval /..\output\economic\%CASEID% VEShadowval.med/;
File file_Fosshadowval /..\output\economic\%CASEID% Fosshadowval.med/;

File file_e_tax /..\output\economic\%CASEID% e_tax.med/;
File file_h_tax /..\output\economic\%CASEID% h_tax.med/;

File file_dist_e /..\output\economic\%CASEID% dist_e.med/;
File file_dist_h /..\output\economic\%CASEID% dist_h.med/;

File file_reacEf /..\output\economic\%CASEID% reacEf.med/;

put compfile; put "Dummy";

Parameters
         e_rev(Y,C)
         h_rev(Y,C)
         fxcost(Y,C)
         fuelcost(Y,C)
         vcost(Y,C)
*Erkki
         UCstartcost(Y,C)
         UCshutcost(Y,C)
         UCfixedcost(Y,C)
*Erkki
         capcost_ex(Y,C)
         capcost_en(Y,C)
         capcost_trans_ex(Y,C)
         capcost_trans_en(Y,C)

         co2cost(Y,C)
         so2cost(Y,C)
         noxcost(Y,C)
         fueltax(Y,C)
         heattax_GH(Y,C)
         vindSubsidy(Y,C)

         e_cost(Y,C)
         h_cost(Y,C)
         e_util(Y,C)
         h_util(Y,C)

         bottleneck(Y,C)
         tradesurp(Y,C)
         transcost(Y,C)

         watervaluevar(Y,C)
         watervalue(Y,C)

         NOxemission(Y,C)
         SO2emission(Y,C)
         CO2shadowval(Y,C)
         VEShadowval(Y,C)
         Fosshadowval(Y,C)

         e_tax(Y,C)
         h_tax(Y,C)

         dist_e(Y,C)
         dist_h(Y,C)

         reacEf(Y,C)


*Erkki- hourly welfare
                 hourlygenerationcost(Y,C,S,T)
                 hourlye_rev(Y,C,S,T)
                 hourlye_cost(Y,C,S,T)
                 hourlybottleneck(Y,C,S,T)
                 hourlyX3V(Y,C,S,T)
*Erkki
;

*-------------------------------------------------------------------------------
* Add output for addon modules. It is best if addon code is in include files.
*-------------------------------------------------------------------------------

$ifi %H2%==yes $include '../../base/addons/Hydrogen/compare/hycompprint1.inc';
$ifi %transport%==yes $include '../../base/addons/transport/compare/trcompprint1.inc';
