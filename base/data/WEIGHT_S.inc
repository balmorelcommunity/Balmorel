* PARAMETER WEIGHT_S reflects how much of the year each season represents    
* expressed relatively between the seasons.                                  
* Units: (none).                                                             
* One way of doing it is to state the number of days in each season          
* (should sum up to 365). Another is to give percentages (summing up to 100).
PARAMETER WEIGHT_S(SSS)  'Weight of each season';                            
WEIGHT_S(SSS)=168;                                                           
