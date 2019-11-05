* Program OutageDispatch.

* Sketch only.
* For introduction see my UnitoutageDispatch.docx (20170918).

* The present code it largely copy-paste from some other code, content and terminology has to be adapted to present purpose.

* The presnet code is advanced for larger testing (it includes data etc., it handles inconsistency (rounding) between unit size and block size)
* but it is based on the uniform distribution. The Binomial distribution might be better, som code in Outagebyunit.

* Calculation in the central part (from declaration of calctimetestloop and 30 lines down) takes for
*    10 mio times (counterUniformtimes)  7.5 seconds
*   100 mio times (counterUniformtimes)  85 seconds     (this would cover some years in hourly resolution on a F4R model, I suppose
* This look comparable to the binomial distributions execution time (implemented as of today (20180627))



* TODO: prøv /N000*N300/: noget galt

$title  "===== OutageDispatch (hr). Latest version 20170919  =====";


$ONINLINE
$ONEOLCOM


scalar TimeelapsedCentral "Time (seconds)";
*scalar TimeelapsedUniform "Time (seconds)";

TimeelapsedCentral = TimeElapsed;

* ==============================================================================
* Directories for input and output
* ==============================================================================

* The folders inputdata and outputdata are set by the user (the remaining ones are not to be changed!)
* Set the full path for the input data to be used
$setglobal inputdata       "../data"
*!option set the full path like e.g.    C:/Balmorel/base/data
* Note: use double quotes around and no termination slash or backslash
* Note: the folder must exist

* Set the full path for the output data generated
$setglobal outputdata   "../../base/auxils/UnitoutageDispatch/dataoutput"
*!optiononly:  set the full path like e.g.    C:/Balmorel/base/data/timeaggregated
* Note that within the folder a subfolder is generated with a name that indicates the aggragation method
* Note: use double quotes around and no termination slash or backslash
* Note: the folder must exist

* The main folders are here assumed to be made by the user, while subfolders to the output will be automatically generated
$ifi not dexist "%inputdata%"  $abort "Input data folder  '%inputdata%'  does not exist";
$ifi not dexist "%outputdata%" $abort "Output data folder  '%outputdata%'  does not exist";

* The following are not meant to be changed by the user
*$setglobal output_inputdescription           "%outputdata%/inputdescription"
*$setglobal output_intermediategdx            "%outputdata%/intermediategdx"
*$setglobal output_generatedinc               "%outputdata%/generatedinc"

* Make sure that appropriate subfolders to the output data folder exist
*$ifi not dexist "%output_inputdescription%"         execute 'md "%output_inputdescription%"';
*$ifi not dexist "'%output_intermediategdx%'"        execute 'md "%output_intermediategdx%"';
*$ifi not dexist "'%output_generatedinc%'"           execute 'md "%output_generatedinc%"';

$log "        inputdata        folder was set to  '%inputdata%'";
$log "        outputdata       folder was set to  '%outputdata%'";
*$log "        inputdescription folder was set to  %output_inputdescription%";
*$log "        intermediategdx  folder was set to  %output_intermediategdx%";
*$log "        generatedinc     folder was set to  %output_generatedinc%";


* ==============================================================================
* End: Directories  for input and output
* ==============================================================================

* ==============================================================================
* Some generally applicable stuff

SCALAR INFODISPLAY  "See information next:" /NA/;
SCALAR Codeversion "August 25 2017" / 20170825 /; !! Use the same info as in $title above
SCALAR SystemDateTime "System date and time at start of execution: %system.date%,  %system.time%" /0/;
DISPLAY INFODISPLAY, "Balmorel run stared at", SystemDateTime;
SCALAR SystemTimeElapsed         "Total time elapsed since the start of the GAMS run (seconds)";
SCALAR TimeElapsed_loaddata      "Total time elapsed in loading time series related data files (seconds)e";
SCALAR TimeElapsed_describe      "Total time elapsed in describ (seconds)e";
SCALAR TimeElapsed_aggregateS    "Total time elapsed in aggregateS (seconds)";
SCALAR TimeElapsed_aggregateT    "Total time elapsed in aggregateT (seconds)";
SCALAR TimeElapsed_printaggrdata "Total time elapsed in printaggrdata (seconds)";
SCALAR ISCALAR1   '(Context dependent)';
SCALAR ISCALAR2   '(Context dependent)';
SCALAR ISCALAR3   '(Context dependent)';
SCALAR ISCALAR4   '(Context dependent)';
SCALAR ISCALAR5   '(Context dependent)';
SCALAR ISCALAR6   '(Context dependent)';
SCALAR ISCALAR7   '(Context dependent)';
SCALAR ISCALAR8   '(Context dependent)';
SCALAR IALLMOSTZERO   'Small positive number as kind of alternative to eps' /0.000011/;

file testfile / "%outputdata%/test.out" /;   !!    in case you ned to print something for test
testfile.PW = 32000;
PUT testfile / SYSTEMDATETIME.TS /;


* ==============================================================================
* ACRONYMS:

* ACRONYMS for technology types
* Each of the following ACRONYMS symbolise a technology type.
* They correspond in a one-to-one way with the internal sets IGCND, IGBRP etc. below.
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS  GCND, GBPR, GEXT, GHOB, GETOH, GHSTO, GESTO, GHSTOS, GESTOS, GHYRS, GHYRR, GWND, GSOLE, GSOLH, GWAVE;

*ACRONYMS for tech groups
* They can be used for multiple purposes
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS STEAMTURBINE_SUBCRITICAL, STEAMTURBINE_SUPERCRITICAL, RESERVOIR_PMP, WATERTURBINE, ENGINE_IC, BOILER, COMBINEDCYCLE, EXCESS_HEAT, ELECTRICITY_BATTERY, GEOTHERMAL,
GASTURBINE, DUMMY, HEATPUMP, PIT, WATERTANK, SOLARPV, SOLARHEATING,WINDTURBINE_ONSHORE, WINDTURBINE_OFFSHORE,
BACKUP_ELECTRICITY,BACKUP_HEAT;

*ACRONYMS for subtech groups
* They can be used for multiple purposes
* They should generally not be changed.
* New technology types may be added only if also code specifying their properties are added.
ACRONYMS RG1,RG2,RG3,RG1_OFF1,RG2_OFF1,RG3_OFF1,RG1_OFF2,RG2_OFF2,RG3_OFF2,RG1_OFF3,RG2_OFF3,RG3_OFF3,RG1_OFF4,RG2_OFF4,RG3_OFF4,RG1_OFF5,RG2_OFF5,RG3_OFF5,AIR,EXCESSHEAT,GROUND,HUB_OFF;
* ==============================================================================


* ==============================================================================
* Get needed data
* ==============================================================================
* Note htat all data is supposed to come from the data folder
* of the project that is to apply the output from the present program.

$offlisting
* I do not know if all this is to be used, nor if more is to be taken
$include "%inputdata%/CCCRRRAAA.inc";
$include "%inputdata%/CCC.inc";
$include "%inputdata%/C.inc";
$include "%inputdata%/RRR.inc";
$include "%inputdata%/AAA.inc";
$include "%inputdata%/CCCRRR.inc";
$include "%inputdata%/RRRAAA.inc";

ALIAS (RRR,IRRRE,IRRRI);
SET IR(RRR)            'Regions in the simulation';
SET IA(AAA)            'Areas in the simulation';
ALIAS (IR, IRE, IRI);
SET ICA(CCC,AAA)       'Assignment of areas to countries in the simulation';
ICA(CCC,AAA) = YES$(SUM(RRR$ (RRRAAA(RRR,AAA) AND CCCRRR(CCC,RRR)),1) GT 0);
IR(RRR) = YES$(SUM(C,CCCRRR(C,RRR)));
IA(AAA) = YES$(SUM(C,ICA(C,AAA)));

* Time structure.
* It is presently assumed that the only time index are SSS, S, TTT, T (i.e., no YYY or Y).
$include "%inputdata%/SSS.inc";
$include "%inputdata%/S.inc";
$include "%inputdata%/TTT.inc";
$include "%inputdata%/T.inc";
$include "%inputdata%/YYY.inc";
$include "%inputdata%/Y.inc";

$include "%inputdata%/GGG.inc";
$include "%inputdata%/G.inc";
$include "%inputdata%/FFF.inc";
$include "%inputdata%/FDATASET.inc";
$include "%inputdata%/FDATA.inc";
$include "%inputdata%/GDATASET.inc";
$include "%inputdata%/GDATA.inc";
$include "%inputdata%/GKFX.inc";

*Adding optimized investment and decommissioning in generation
PARAMETER GKACCUMNET(YYY,AAA,GGG) "Resulting technology capacity development at end of (ULTimo) previous (i.e., start of current) year (MW) (MWh for storage) to be transferred to future runs";
$if     EXIST '../../simex/GKACCUMNET.gdx' execute_load  '../../simex/GKACCUMNET.gdx', GKACCUMNET;
$if     EXIST '../../simex/GKACCUMNET.gdx' GKFX(YYY,AAA,GGG)=0;
$if     EXIST '../../simex/GKACCUMNET.gdx' GKFX(Y,IA,G)=GKACCUMNET(Y,IA,G);

SET AGKN(AAA,GGG);
$include "%inputdata%/AGKN.inc";
$include "%inputdata%/GKRATE.inc";


* gdata was somehow not appropriae, alle data set to 0, therefor repair here:
*$log "#### Main file: assigned GDATA(G,'GDUCUNITSIZE') and GDATA(G,'GDFOR') somewhat arbitrarily ####";
*GDATA(G,'GDUCUNITSIZE') = 100; !! TODO!
*GDATA(G,'GDFOR') = 0.1;      !! TODO!


* Display some data:


$onlisting
* More?


* ==============================================================================
* End: Get needed data
* ==============================================================================



*$goto ENDOFfile
* ==============================================================================

* Some preparations, maybe not needed in final

* Move the original GKRATE to some safe place

* All three valid - but the quotes have to be in the correct nesting ( the  '  outside the  " !)  Why?
* Also the slash has to be correct:  '/' does not work (everywhere, somewhere?) here
*$ifi not dexist "%outputdata%/original" execute 'md  "%outputdata%/original"';
*$ifi not dexist "%outputdata%/original" $call   'md  "%outputdata%/original"';
*$ifi not dexist "%outputdata%/original" execute 'md  "%outputdata%/original"';
*execute  'copy   "%inputdata%/GKRATE.inc"  "%outputdata%/original/GKRATE.inc"  ';
*  Summary: relevant operating system commands:
* On directories:  dexist, fjerne, skabe,
* On Files:     exist, fjerne, skabe (put), flytte, omdøbe, kopiere,
* ==============================================================================



*$GOTO ENDOFFILE
* ==============================================================================
*  Main code
* ==============================================================================

* TODO
* GKRATE  and IGKRATE have no index Y, therefore loop only over one Y (here used (ord(y) le 1))
* Consider rounding (search "1.5")
* Control the SEED
* Loop only over dispatchable techs (excluding storages), therefore create a subset GDISPATCHABLE(G) "";
* Also limit loop .......only over IA with elements in GDISPATCHABLE with installed cap
* Depending on application:
*   how must time takes the unifoirm?  alternative: save some uniform in  table
*
* How to treat investments?
*

*scalar counterYtest "" /0/;   !! NB: not a test thing,  GKRATE  and IGKRATE have no index Y

SCALAR IGKFXSREMAIN "";
SCALAR IGKFXSAVAIL "";
SCALAR IGDUCUNITSIZEDISCORD "";
*SCALAR DISPATCHGENFORDISCSIZE "";
SCALAR IFAILURE "Indicates whether unit fails or not (1/0)" ;

PARAMETER IGKRATE(AAA,GGG,SSS,TTT) "";
PARAMETER IGKRATE2(AAA,GGG,SSS,TTT) "";

* GKRATE and IGKRATE: be very careful to handle that default value is 1, and this that is to be represented by 0!  IGKRATE(IA,G,S,T) can be VERY large!
* Check:
ISCALAR1 = CARD(GKRATE);
IGKRATE(IA,G,S,T) = GKRATE(IA,G,S);
GKRATE(IA,G,S)$(GKRATE(IA,G,S) EQ 1) = 0;
ISCALAR2 = CARD(GKRATE);
*IF((ISCALAR1 ne ISCALAR2), DISPLAY "Error in input data GKRATE: value 1 is default, should not be in input, use 0", ISCALAR1, ISCALAR2; );

LOOP(Y$(ORD(Y) EQ 1),
LOOP(S,
LOOP(T,
LOOP(IA,
  LOOP(G$(GKFX(Y,IA,G) AND GDATA(G,'GDFOR')),
    IGKFXSREMAIN = GKFX(Y,IA,G);
    IGKFXSAVAIL  = GKFX(Y,IA,G);
    WHILE(((IGKFXSREMAIN GT (GDATA(G,'GDUCUNITSIZE')*1.5))),
       IGKFXSREMAIN = IGKFXSREMAIN - GDATA(G,'GDUCUNITSIZE');
       IFAILURE = 0;
       IGKFXSAVAIL$(uniform(0,1) LT GDATA(G,'GDFOR')) = IGKFXSAVAIL - GDATA(G,'GDUCUNITSIZE');
    );
    IGKRATE(IA,G,S,T) = (IGKRATE(IA,G,S,T) + 1$(NOT IGKRATE(IA,G,S,T)))*(IGKFXSAVAIL/GKFX(Y,IA,G));
    IGKRATE(IA,G,S,T)$(IGKRATE(IA,G,S,T) EQ 1) = 0;
    IGKRATE2(IA,G,S,T)=IGKRATE(IA,G,S,T);

);
);
);
*execute_unload "%outputdata%/IGKRATE.gdx", IGKRATE;
IGKRATE(AAA,GGG,SSS,TTT)=0;
));
*); !! Calc time test

* ==============================================================================
*  End Main code
* ==============================================================================



$LABEL endoffile

* ==============================================================================
$ontext
*binomial(n,k)    NLP  returns the (generalized) binomial coefficient for n,k = 0
* randBinomial(N,P)  none  generates a random number with binomial distribution where n is the number of trials and p the probability of success for each trial, see MathWorld
* NOTE: I have a more binomial dedicated tester in Outagebyunit.gms (GAMStestere)

$oneolcom
scalar isc1;
*file testfile /"testfile.out"/;  put testfile;

scalar prob /0.9/;
set N "Number of trials.  Make sure to use the ord(n) ad (ord(n)-1) correct " /N000*N100/; !! With this system for labels, e.g. with last label 'N008' there are 8 experiments, i.e. (card(N)-1).   !! Make sure to use the ord(n) ad (ord(n)-1) correct

Option Seed=1125;    !!  randBinomial er stokastisk

parameter randnum(N) "";
parameter probnum(N) "";
parameter proboccur(N) "";

isc1 =  binomial(100,prob);  display isc1;
isc1 =  randBinomial(100,prob);  display isc1;
*put / / "Binomial: Prob of events == x.  x left, prob occurrence right.  Probability in binomial distr. is " prob:3:2 /;
*$ontext  time consuing, presumably
counterUniformbasictest = TimeElapsed;
put / / "Binomial: The (generalized) binomial coefficient for number of tests " (card(n)-1):3:0 " and probability in binomial distr. is " prob:3:2 /;
loop(n,
   put (ord(n)-1):5:0 "  ";
   randnum(N) = Binomial((ord(n)-1),prob);    !! -1?
   put  (randnum(N)):5:0 /;                   !! -1?
);
counterUniformbasictest = TimeElapsed - counterUniformbasictest;


put / "Calculating probabilities of occurrence with above data:" /;
put "#succes label prob"/;


proboccur(n)$(ord(n) eq 1) = power((1-prob),(card(n)-1));  !! Initilissation: Probablity of no occurrences
*put$(ord(n) eq 1) (ord(n)-1):3:0 "  " n.te(n):4 "  " proboccur(n):6:4 /;
loop(n$(ord(n) gt 1),
   proboccur(n) = proboccur(n-1)*((card(N)-1)-(ord(n)-2))*prob/((ord(n)-1)*(1-prob));
);
loop(n,
   put "    " (ord(n)-1):3:0 "   " n.te(n):5 "    " proboccur(n):13:12 /;
);
option decimals = 4;
display  proboccur;
put  "According to theory: Mean: " (prob*(card(n)-1)):7:6 ";  Var: "  (prob*(1-prob)*(card(n)-1)):7:6 ". Found mean " (sum(n, (ord(n)-1)*proboccur(n))):7:6/;
$offtext
*/

* ==============================================================================
*$offtext

execute_unload "%outputdata%/IGKRATE.gdx", IGKRATE2=IGKRATE;

