* PARAMETER WEIGHT_T reflects how much of the day each time period represents 
* expressed relatively between the time periods.                              
* Units: (none).                                                              
* Like above one way of doing it is to state the number of hours of a day that
* each period represents (sums up to 24).                                     
* Alternatively it can be stated in percentage (summing up to 100).           
 WEIGHT_T(TTT)=1;                                                             
$ifi %bb3%==yes WEIGHT_T(T)=1;                                                
