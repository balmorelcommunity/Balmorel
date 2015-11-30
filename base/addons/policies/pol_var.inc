* Addon for securing policy requrements are forfilled
* Slack variables are created to insure that the model works
* even if the policy requirements is not forfilled

Positive Variables
                    VQPOLSHAREGROSS(POLAREA,POLICY)   'Penalty on not forefilling the gross share requirement for policy area'
                    VQPOLSHARENET  (POLAREA,POLICY)   'Penalty on not forefilling the net share requirement for policy area'
                    VQPOLMAXCO2    (POLAREA,POLICY)   'Penalty on not forefilling the maximum CO2 requirement for policy area'
                    VQPOLMINPROD   (POLAREA,POLICY)   'Penalty on not forefilling the minimum production requirement for policy area'
                    VQPOLCAPTARGET (POLAREA,POLICY)   'Penalty on not forefilling the minimum capacity requirement for policy area'
;
