
SET FBLINE              'All critical elements in the system';
SET FBHUB(RRR)          'Hubs (market regions) in the FB model';
*Option to keep NTC limits between certain market regions where PTDF data might cover the limit. Usual suspects: DC links (Remember to define it both ways if neccesary).
SET FB_NTCRRR(RRR,RRR) 'Regions between which NTC values should be kept';

ALIAS(FBHUB,IFBHUB);

*Set of X3V hubs of which are contributing to the net exchange calculation (regions which have values for VX3VIM_T and/or VX3VEX_T with members of X3VPLACE mentioned in this set)
$ifi %X3V%==yes   SET FBX3VHUB(X3VPLACE0)   'X3V regions in which one wants to take Fb flows into account';

*Set of hubs in the FB model which consider X3FX flows in their net exchange
SET FBX3FXHUB(FBHUB)             'X3FX regions in which one wants to take Fb flows into account';
