TABLE GOMFCOST(AAA,GGG)  'Annual fixed operating and maintenance costs (kEUR90/MW)'                
* Default values given by GDATA(TG,'GOMFCOST0')                                                    
*                                                                                   DK_E_Rural_WI  
* DK_E_Rural                                                                        0              
;                                                                                                  
GOMFCOST(AAA,GGG)$(GOMFCOST(AAA,GGG) EQ 0)= GDATA(GGG,'GDOMFCOST0');                               
                                                                                                   
* AGT: O&M cost data from TopWaste to be included                                                  
                                                                                                   
                                                                                                   
