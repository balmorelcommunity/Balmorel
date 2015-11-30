* -------- HYDROGEN COSTS -------- *

* Change in revenue when deviating from producing the fixed hydrogen demand
* in the transport sector specified by DH2_T_Y(AAA,S,T). Introduced to make
* it possible to specify more advanced hydrogen supply functions.
* SHOULD THE SUPPLY FUNCTION BE YEAR DEPENDANT?
*No steam reforming plants considered
$ontext
   + SUM(IA,
        SUM((IS3,T), IHOURSINST(IS3,T)
           * (SUM(DH2F_D,VDH2F_T(IA,IS3,T,DH2F_D)* IDEFP_T(IR,IS3,T,DEF_D1)  )


     )

     )
     )

   - SUM(IR,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DEF_U1, VDEF_T(IR,IS3,T,DEF_U1)* IDEFP_T(IR,IS3,T,DEF_U1)  )
     +  SUM(DEF_U2, VDEF_T(IR,IS3,T,DEF_U2)* IDEFP_T(IR,IS3,T,DEF_U2)  ))
     )
     )

revenue sale of hydrogen to the transport sector
+ SUM(DH2F_U,VDH2F_T(IA,IS3,T,DH2F_U) )
*        - SUM(DH2F_D,VDH2F_T(IA,IS3,T,DH2F_D) )
*
$offtext 

+ PENALTYQ*(SUM((IR,IS3,T),(VQH2EQ(IR,IS3,T,'IMINUS')+VQH2EQ(IR,IS3,T,'IPLUS'))))

* Cost of fuel consumption during the year for steam reforming plants:

    + SUM((IAGK_Y(IA,IGCH4TOH2),FFF)$(GDATA(IGCH4TOH2,'GDFUEL') EQ FDATA(FFF,'FDNB')),
                 IFUELP_Y(IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGH2_T(IA,IGCH4TOH2,IS3,T)/(GDATA(IGCH4TOH2,'GDFE'))))

    +SUM((IAGKN(IA,IGCH4TOH2),FFF)$(GDATA(IGCH4TOH2,'GDFUEL') EQ FDATA(FFF,'FDNB')),
                 IFUELP_Y(IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGH2N_T(IA,IGCH4TOH2,IS3,T)/(GDATA(IGCH4TOH2,'GDFE'))))

* Cost of CO2 emission during the year for steam reforming plants:

    + SUM(C, SUM(IAGK_Y(IA,IGCH4TOH2)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGCH4TOH2)*IOF0001) *
      IOF3P6 *VGH2_T(IA,IGCH4TOH2,IS3,T) /(GDATA(IGCH4TOH2,'GDFE') ) ) * (ITAX_CO2_Y(C))))

    + SUM(C, SUM(IAGKN(IA,IGCH4TOH2)$ICA(C,IA), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGCH4TOH2)*IOF0001) *
      IOF3P6 * VGH2N_T(IA,IGCH4TOH2,IS3,T) / (GDATA(IGCH4TOH2,'GDFE') ) ) * (ITAX_CO2_Y(C))))


* Costs of the H2 storage is missing
