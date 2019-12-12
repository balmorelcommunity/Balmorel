PARAMETER ANNUITYCG(CCC,GGG) 'Transforms investment to annual payment (fraction)'                         
;                                                                                                         
                                                                                                          
* Interest rate assumption: 6%                                                                            
* Loan repayment assumption: lifetime of the technology if lifetime is higher than 20 years, else 20 years
ANNUITYCG(C,G)$(GDATA(G,'GDKVARIABL')=1)=1/((1-(1+0.06)**(MAX(-GDATA(G,'GDLIFETIME'),-20)))/0.06);        
                                                                                                          
                                                                                                          
                                                                                                          
                                                                                                          
                                                                                                          
                                                                                                          
                                                                                                          
