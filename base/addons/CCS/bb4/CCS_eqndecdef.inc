* CCS add-on. Yearly limit on geological CO2 storage

EQUATION QCCS_STORAGE(Y) "Limit on CO2 captured for storage per year, all countries (t)";

* Captured CO2 incl. the renewable part (BECCS), the amount CCS_qobj.inc charges transport and storage for.
* Balmorel has no CO2 utilisation, so all of it is stored.
QCCS_STORAGE(IY411)$CCS_STORAGE_MAX(IY411)..
      SUM(C, SUM((IA,G)$(ICA(C,IA) AND IAGK_HASORPOT(IY411,IA,G) AND CCS_G(G)), SUM((IS3,T), IHOURSINST(IS3,T) * ((IM_CO2(G)+IM_CO2RE(G))*IHOURFRAC*IOF0001) * IOF3P6 * VGF_T(IY411,IA,G,IS3,T)*CCS_CO2CAPTEFF_G(G))))
      =L= CCS_STORAGE_MAX(IY411)
$ifi %vqdebug%==yes   $setglobal equation qccs_storage
$ifi %vqdebug%==yes   $include   "../../base/addons/vqdebug/bb4/vqdebug_equations.inc";
;
