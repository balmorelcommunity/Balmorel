POSITIVE VARIABLES
* Physical variables
                VGUD(AAA,S,T)               'The outtake at location i (MWh)'
                VSTOCK(STORE,STORETYPE,S,T) 'Seasonal gas storage level (MWh)'
                VINJ(STORE,STORETYPE,S,T)   'Gas quantity injection rate into storage facility (MWh/h)'
                VEXT(STORE,STORETYPE,S,T)   'Gas quantity extraction rate from storage facility (MWh/h)'
                VEXP(SOURCE,S)              'Gas export quantity rate (MWh/h)'
                VTRANSIT(TRANSIT,S,T)       'Gas transit between endogenous countries (MWh/h)'
                VSUP(SOURCE,S,T)            'The inflowrate at node MMM (MWh/h)'
* Economic variables
                VTC_EN_Y(SYSENTRY)          'Reserved ENTRY Transmission Capacity, YEAR'
                VTC_EN_M(SYSENTRY,IMONTH)   'Reserved ENTRY Transmission Capacity, MONTH'
                VTC_EN_W(SYSENTRY,S)        'Reserved ENTRY Transmission Capacity, YEAR'
                VTC_EN_D(SYSENTRY,S,DAY)    'Reserved ENTRY Transmission Capacity, MONTH'
                VTC_EN_FLEX(SYSENTRY,S,T)   'Use of flexible ENTRY capacity'
                VTC_EX_Y(SYSEXIT)           'Reserved EXIT Transmission Capacity, YEAR'
                VTC_EX_M(SYSEXIT,IMONTH)    'Reserved EXIT Transmission Capacity, MONTH'
                VTC_EX_W(SYSEXIT,S)         'Reserved EXIT Transmission Capacity, WEEK'
                VTC_EX_D(SYSEXIT,S,DAY)     'Reserved EXIT Transmission Capacity, DAY'
                VTC_EX_FLEX(SYSEXIT,S,T)    'Use of flexible EXIT capacity'
                VSC(SCON)                   'Storage capacity purchased'
$ifi %HEATING%==yes VHX(i,j,s,T)            'Heat transmission between heating areas'
;

* BB2 variables
$ifi %SOLVEMIP%==yes BINARY VARIABLES
$ifi not %SOLVEMIP%==yes POSITIVE VARIABLES
         VGINFINV(NGINV)         'Investment in gas transmission'
         ;
$ifi not %SOLVEMIP%==yes VGINFINV.up(NGINV)=1;

* Ledningsdublering.
POSITIVE VARIABLES
         VGNETINV(C,GNETSTEPS)             'Investment in gas network expansion'
;


POSITIVE VARIABLES
         VGINVSTORE(STORE,STORETYPE)       'Investment in gas storage capacity'
         VGINVEXT(STORE,STORETYPE)         'Investment in gas extraction capacity'
         VGINVINJ(STORE,STORETYPE)         'Investment in gas injektion capacity'
         ;