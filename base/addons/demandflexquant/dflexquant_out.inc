* File dflexquant_out.inc for the Balmorel model.
* For use with addon dflexquant: flexible price-dependent demand quantities
* Created 20171218 (hr)


ODFLEXQUANT(IY411,IR,DEUSER,'UP') =
  SUM((IS3,T),
          IHOURSINST(IS3,T) *
         (
                   SUM(DEF_U1,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U1))
                 + SUM(DEF_U2,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U2))
                 + SUM(DEF_U3,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U3))
         )
  );

ODFLEXQUANT(IY411,IR,DEUSER,'DOWN') =
  SUM((IS3,T),
          IHOURSINST(IS3,T) *
         (
                   SUM(DEF_D1,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D1))
                 + SUM(DEF_D2,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D2))
                 + SUM(DEF_D3,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D3))
         )
  );



ODFLEXQUANT(IY411,IR,DEUSER,'SUM') = ODFLEXQUANT(IY411,IR,DEUSER,'UP') - ODFLEXQUANT(IY411,IR,DEUSER,'DOWN');

