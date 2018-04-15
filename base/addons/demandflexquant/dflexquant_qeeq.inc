* File dflexquant_qheq.inc for the Balmorel model.
* For use with addon dflexquant
* Latest revision 20171023 (hr)

         + ( SUM(DEUSER,
           SUM(DEF_U1,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_U1) )
         - SUM(DEF_D1,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_D1) )
         + SUM(DEF_U2,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_U2) )
         - SUM(DEF_D2,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_D2) )
         + SUM(DEF_U3,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_U3) )
         - SUM(DEF_D3,VDEF_T(IY411,IR,DEUSER,IS3,T,DEF_D3) )
         ))/(1-DISLOSS_E(IR))

