PARAMETER ANNUITYCX(CCC) 'Transforms investment to annual payment (fraction)'
;                                                                            
* Interest rate assumption: Socio-economic discount rate                     
* Loan repayment  assumption for all the lines: 40 YEARS                     
                                                                             
ANNUITYCX(CCC)=1/((1-(1+DISCOUNTRATE)**(-40))/DISCOUNTRATE);                 
                                                                             
                                                                             
                                                                             
                                                                             
