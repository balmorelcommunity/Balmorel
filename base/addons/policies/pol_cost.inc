* Addon for securing that policy requrements are forfilled
* Slack variables are penaliced to insure that the model works and minimize errors
* in case the requrement for specific policy area and policy can not be forfilled

+ SUM((POLAREA,POLICY), VQPOLMAXCO2(POLAREA,POLICY)+VQPOLMINPROD(POLAREA,POLICY)+VQPOLCAPTARGET(POLAREA,POLICY) )*PENALTYQ/2
+ SUM((POLAREA,POLICY), VQPOLSHAREGROSS(POLAREA,POLICY)+VQPOLSHARENET(POLAREA,POLICY) )*PENALTYQ*1000






