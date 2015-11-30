EQUATIONS
        QX3VBAL(X3VPLACE)
;

QX3VBAL(X3VPLACE).. -IX3VBAL(X3VPLACE)=E=
                                      SUM((IR,X3VSTEP,IS3,T)$X3VX(IR,X3VPLACE),
                                        (
                                             +VX3VIM_T(IR,X3VPLACE,X3VSTEP,IS3,T)
                                             -VX3VEX_T(IR,X3VPLACE,X3VSTEP,IS3,T)
                                        )*IHOURSINST(IS3,T)

                                      )  ;