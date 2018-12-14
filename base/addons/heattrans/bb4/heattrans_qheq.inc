* File heattrans_qheq.inc for addon heattrans
* Latest revision 20181014(hr)

* Functions here:
* HP in exporting area: neutralze HP form standard expression in QHEQ (leave in fuel cons, leave in qobj)
* HP in importing area: neutralize the HP input in the traditonal ormulation.


* Any heat from heat pumps used for temperature lift in the heat transmission is neutralized in the standard expression of QHEQ
 +SUM(IGETOH$(IAGK_HASORPOT(IY411,IA,IGETOH) AND XHGETOH(IGETOH)), VGH_T(IY411,IA,IGETOH,IS3,T))

* Adjust export and import according to HP role:
* Heat tranmission import an export,
- (SUM(IAE$(IXHK_HASORPOT(IY411,IAE,IA) AND (NOT XHTEMPLIFT(IAE,IA))), VXH_T(IY411,IAE,IA,IS3,T)*(1-XHLOSS(IAE,IA))))                      !! Import to IA
+ (SUM(IAI$(IXHK_HASORPOT(IY411,IA,IAI) AND (NOT XHTEMPLIFT(IA,IAI))), VXH_T(IY411,IA,IAI,IS3,T)))                                         !! Export from IA

* In case of temperature lift:
- (SUM(IAE$(IXHK_HASORPOT(IY411,IAE,IA) AND XHTEMPLIFT(IAE,IA)), VXH_T(IY411,IAE,IA,IS3,T)*(1-XHLOSS(IAE,IA))))  !! Import to IA
+ (SUM(IAI$(IXHK_HASORPOT(IY411,IA,IAI) AND XHTEMPLIFT(IA,IAI)), VXH_T(IY411,IA,IAI,IS3,T)))                                               !! Export from IA

