* These add-on equations pertain to price sensitive electricity exchange with third countries.

EQUATIONS
        QX3VBAL(YYY,X3VPLACE) "net exported/imported electricity (MWh)"
;

QX3VBAL(YYY,X3VPLACE).. -IX3VBAL(YYY,X3VPLACE)=E=
                                      SUM((Y,IR,X3VSTEP,IS3,T)$X3VX(IR,X3VPLACE),
                                        (
                                             +VX3VIM_T(Y,IR,X3VPLACE,X3VSTEP,IS3,T)
                                             -VX3VEX_T(Y,IR,X3VPLACE,X3VSTEP,IS3,T)
                                        )*IHOURSINST(IS3,T)

                                      )  ;
