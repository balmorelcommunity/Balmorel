* File dflexquant_qheq.inc for the Balmorel model.
* For use with addon dflexquant
* Latest revision 20171023 (hr)

        + (SUM(DHUSER,
          SUM(DHF_U1,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_U1) )
        - SUM(DHF_D1,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_D1) )
        + SUM(DHF_U2,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_U2) )
        - SUM(DHF_D2,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_D2) )
        + SUM(DHF_U3,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_U3) )
        - SUM(DHF_D3,VDHF_T(IY411,IA,DHUSER,IS3,T,DHF_D3) )
          ))/(1-DISLOSS_H(IA))

