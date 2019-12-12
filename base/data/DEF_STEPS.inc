* File for generating a CES function for electricity demand, to be specified in DEF_STEPS.                                                            
* One can here choose between constant elasticity of substitution, or a linear function of the elasticity                                             
                                                                                                                                                      
* $ONTEXT                                                                                                                                             
* The following, between $ONTEXTand $OFFTEXT, may be used to give the specification of DEF_STEPS.                                                     
* It specifies the elasticity in electricity demand as a CES (constant elasticity of substitution) type.                                              
* Iscalar1 is the elasticity, where e.g. -0.1 (must be negative) means that an increase in price of 1%                                                
* will imply a decrease in consumption of 0.1%.                                                                                                       
* Iscalar2 is the steplength (0<Iscalar2<1) in price, where e.g. 0.05 means that each step is 5% of the price.                                        
                                                                                                                                                      
SET IANYSET / IANYSET001 * IANYSET100 /;                                                                                                              
ISCALAR1=-0.15;                                                                                                                                       
ISCALAR2= 0.1;                                                                                                                                        
*SCALAR ISCALAR1 /-0.15 /;                                                                                                                            
*SCALAR ISCALAR2 / 0.1 /;                                                                                                                             
                                                                                                                                                      
                                                                                                                                                      
                                                                                                                                                      
LOOP(DEF_D1$(ORD(DEF_D1) EQ CARD(DEF_D1)),                                                                                                            
DEF_STEPS(RRR,DEUSER,S,T,'DF_PRICE',DEF_D1)=1+ISCALAR2/2;                                                                                             
DEF_STEPS(RRR,DEUSER,S,T,'DF_QUANT',DEF_D1)=1+ISCALAR1*ISCALAR2/2;                                                                                    
);                                                                                                                                                    
LOOP(IANYSET$((2 LE ORD(IANYSET)) AND (ORD(IANYSET) LE CARD(DEF_D1))),                                                                                
LOOP(DEF_D1$(ORD(DEF_D1) EQ (CARD(DEF_D1)-ORD(IANYSET)+1)),                                                                                           
DEF_STEPS(RRR,DEUSER,S,T,'DF_PRICE',DEF_D1)=DEF_STEPS(RRR,DEUSER,S,T,'DF_PRICE',DEF_D1+1)*(1+ISCALAR2);                                               
DEF_STEPS(RRR,DEUSER,S,T,'DF_QUANT',DEF_D1)=DEF_STEPS(RRR,DEUSER,S,T,'DF_QUANT',DEF_D1+1)*(1+ISCALAR1*ISCALAR2);                                      
));                                                                                                                                                   
LOOP(DEF_U1$(ORD(DEF_U1) EQ 1),                                                                                                                       
DEF_STEPS(RRR,DEUSER,S,T,'DF_PRICE',DEF_U1)=1-ISCALAR2/2;                                                                                             
DEF_STEPS(RRR,DEUSER,S,T,'DF_QUANT',DEF_U1)=1-ISCALAR1*ISCALAR2/2;                                                                                    
);                                                                                                                                                    
LOOP(DEF_U1$(ORD(DEF_U1) GE 2), DEF_STEPS(RRR,DEUSER,S,T,'DF_PRICE',DEF_U1)=DEF_STEPS(RRR,DEUSER,S,T,'DF_PRICE',DEF_U1-1)*(1-ISCALAR2));              
LOOP(DEF_U1$(ORD(DEF_U1) GE 2), DEF_STEPS(RRR,DEUSER,S,T,'DF_QUANT',DEF_U1)=DEF_STEPS(RRR,DEUSER,S,T,'DF_QUANT',DEF_U1-1)*(1-ISCALAR1*ISCALAR2));     
* $OFFTEXT                                                                                                                                            
                                                                                                                                                      
$ONTEXT                                                                                                                                               
* The following, between $ONTEXTand $OFFTEXT, may be used to give the specification of DEF_STEPS.                                                     
* It specifies the elasticity in electricity demand as a linear function type (specifying price as a function of quantity).                           
* Iscalar1 is the steplength (0<Iscalar2<1) in price, where e.g. -0.1 (must be negative) means that an increase in consumption of one step (see below)
* will be associated with a decrease in price of 10% of the price at nominal demand.                                                                  
* Iscalar2 is the steplength (0<Iscalar2<1) in quantity, where e.g. 0.05 means that each step is 5% of the quantity at nominal demand.                
* The elasticity at nominal demand is then approximately (Iscalar1/Iacalar2).                                                                         
                                                                                                                                                      
SET IANYSET / IANYSET001 * IANYSET100 /; /* obs: den skal jo ikke staa her ! */                                                                       
ISCALAR1=-0.1;                                                                                                                                        
ISCALAR2= 0.1;                                                                                                                                        
                                                                                                                                                      
LOOP(DEF_D1$(ORD(DEF_D1) EQ CARD(DEF_D1)),                                                                                                            
DEF_STEPS(IR,S,T,'DF_PRICE',DEF_D1)=1-ISCALAR1;                                                                                                       
DEF_STEPS(IR,S,T,'DF_QUANT',DEF_D1)=1-ISCALAR2;                                                                                                       
);                                                                                                                                                    
LOOP(IANYSET$((2 LE ORD(IANYSET)) AND (ORD(IANYSET) LE CARD(DEF_D1))),                                                                                
LOOP(DEF_D1$(ORD(DEF_D1) EQ (CARD(DEF_D1)-ORD(IANYSET)+1)),                                                                                           
DEF_STEPS(IR,S,T,'DF_PRICE',DEF_D1)=DEF_STEPS(IR,S,T,'DF_PRICE',DEF_D1+1)-ISCALAR1;                                                                   
DEF_STEPS(IR,S,T,'DF_QUANT',DEF_D1)=DEF_STEPS(IR,S,T,'DF_QUANT',DEF_D1+1)-ISCALAR2;                                                                   
));                                                                                                                                                   
LOOP(DEF_U1$(ORD(DEF_U1) EQ 1),                                                                                                                       
DEF_STEPS(IR,S,T,'DF_PRICE',DEF_U1)=1+ISCALAR1;                                                                                                       
DEF_STEPS(IR,S,T,'DF_QUANT',DEF_U1)=1+ISCALAR2;                                                                                                       
);                                                                                                                                                    
LOOP(DEF_U1$(ORD(DEF_U1) GE 2), DEF_STEPS(IR,S,T,'DF_PRICE',DEF_U1)=DEF_STEPS(IR,S,T,'DF_PRICE',DEF_U1-1)+ISCALAR1);                                  
LOOP(DEF_U1$(ORD(DEF_U1) GE 2), DEF_STEPS(IR,S,T,'DF_QUANT',DEF_U1)=DEF_STEPS(IR,S,T,'DF_QUANT',DEF_U1-1)+ISCALAR2);                                  
$OFFTEXT                                                                                                                                              
