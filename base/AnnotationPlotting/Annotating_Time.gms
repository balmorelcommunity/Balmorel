****************************************************************************************************

****************************************************************************************************
****************** Equatuions
****************************************************************************************************
* Objective function
QOBJ.stage = card(blocks) + 2;

*** Y index in front if it is BB4

* Electricity generation equals demand (MW)
QEEQ.stage(IR,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Heat generation equals demand (MW)
QHEQ.stage(IA,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Fuel consumption rate.
QGFEQ.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
* CHP generation (back pressure) limited by Cb-line (MW)
QGCBGBPR.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* CHP generation (extraction) limited by Cb-line (MW)
QGCBGEXT.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* CHP generation (extraction) limited by Cv-line (MW)
QGCVGEXT.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Electric heat generation (MW)
QGGETOH.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

*Intra-seasonal heat storage dynamic equation (MWh)
QHSTOVOLTS.stage(IA,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

*Transmission capacity constraint (MW)
QXK.stage(IRRRE,IRRRI,S,T)= sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;


*  Maximum fuel rampup for exogenous capacities (MWh)
*QGFRAMPUP.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Maximum fuel rampdown for exogenous capacities (MWh)
*QGFRAMPDOWN.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* For instance 3
QHYRSSEQ.stage(IA,S) = card(blocks) + 2;
QHYRSMINVOL.stage(IA,S) = card(blocks) + 2;
QHYRSMAXVOL.stage(IA,S) = card(blocks) + 2;
* For instance 3
* Intra-seasonal electricty storage dynamic equation (MWh)
QESTOVOLT.stage(IA,S,T)$(ord(T)<Card(T)) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
QESTOVOLTS.stage(IA,S,T)$(ord(T)<Card(T)) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

QESTOVOLT.stage(IA,S,T)$(ord(T)=Card(T)) = card(blocks) + 2;
QESTOVOLTS.stage(IA,S,T)$(ord(T)=Card(T)) = card(blocks) + 2;

* Intra-seasonal heat storage upper loading limit (model Balbase2 only) (MW)
QHSTOLOADTLIM.stage(IA,S,T)  = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
QHSTOLOADTLIMS.stage(IA,S,T)  = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

** Missing equations for BB2
*  'Calculate fuel consumption, new units (MW)'
QGFNEQ.stage(IA,G,S,T)          = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*  'CHP generation (extraction) Cb-line, new (MW)'
QGNCBGEXT.stage(IA,G,S,T)       = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*      'CHP generation (extraction) Cv-line, new (MW)'
QGNCVGEXT.stage(IA,G,S,T)   = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*       'Electric heat generation, new (MW)'
QGNGETOH.stage(IA,G,S,T)  = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
* 'Generation on new electricity cap, limited by capacity (MW)'
QGEKNT.stage(IA,G,S,T)          = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*             'Generation on new IGHH cap, limited by capacity (MW)'
QGHKNT.stage(IA,G,S,T)   = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*          'Generation on new windpower limited by capacity and wind (MW)'
QGKNWND.stage(IA,G,S,T)  = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*           'Generation on new solarpower limited by capacity and sun (MW)'
QGKNSOLE.stage(IA,G,S,T)        = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*   QHSTOVOLTS(AAA,S,T)         'Inter-seasonal heat storage dynamic equation (MWh)'
QHSTOVOLT.stage(IA,S,T)$(ord(T)<Card(T))       = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
QHSTOVOLTS.stage(IA,S,T)$(ord(T)<Card(T))       = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

QHSTOVOLT.stage(IA,S,T)$(ord(T)=Card(T))      = card(blocks) + 2;
QHSTOVOLTS.stage(IA,S,T)$(ord(T)=Card(T))      = card(blocks) + 2;
*     'Inter-seasonal heat storage upper loading limit (model Balbase2 only) (MW)'
QHSTOLOADTLIM.stage(IA,S,T)      = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
QHSTOLOADTLIMS.stage(IA,S,T)      = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*             'Total capacity using fuel FFF is limited in region (MW)'
QKFUELR.stage(IR,FFF)         =  card(blocks) + 2;
*  'Inter-seasonal heat storage capacity limit (model Balbase2 only) (MWh)'
QHSTOVOLTLIM.stage(IA,S,T)  = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
QHSTOVOLTLIMS.stage(IA,S,T)  = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*'CHP generation (back pressure) Cb-line, new (MW)'
QGNCBGBPR.stage(AAA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
****************************************************************************************************
****************** Variables
****************************************************************************************************
* Objective function value (MMoney)
VOBJ.stage =  1;


* Electricity generation (MW), existing units
VGE_T.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
* Heat generation (MW), existing units

*** NOT IN THE SAME BLOCK!
VGH_T.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Fuel consumption rate (MW), existing units
VGF_T.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Electricity export from region IRRRE to IRRRI (MW)

VX_T.stage(IRRRE,IRRRI,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;


* Intra-seasonal heat storage loading (MW)
VHSTOLOADTS.stage(IA,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Feasibility in electricity balance equation QEEQ (MW)
VQEEQ.stage(IR,S,T,IPLUSMINUS) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Feasibility in heat balance equation QHEQ (MW)
VQHEQ.stage(IA,S,T,IPLUSMINUS) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Feasibility in intra-seasonal heat storage equation VQHSTOVOLT (MWh)
VQHSTOVOLTS.stage(IA,S,T,IPLUSMINUS) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;

* Feasibility in Transmission capacity constraint (MW)
VQXK.stage(IRRRE,IRRRI,S,T,IPLUSMINUS) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;


* Instance 2 extra
VHYRS_S.stage(IA,S) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
VQHYRSSEQ.stage(IA,S,IPLUSMINUS) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
VQHYRSMINMAXVOL.stage(IA,S,IPLUSMINUS)  = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;


* Missing variables for BB2 mode
*                'Electricity generation (MW), new units';
VGEN_T.stage(IA,G,S,T)            = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) +1;
*                'Heat generation (MW), new units';
VGHN_T.stage(IA,G,S,T)            = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) +1;
*              'New generation capacity (MW)';
VGKN.stage(IA,G)           =  1;
*              'New electricity transmission capacity (MW)';
VXKN.stage(IRRRE,IRRRI)   = 1;
*       'Inter-seasonal electricity storage loading (MW)';
VESTOLOADT.stage(IA,S,T)      = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) +1;
VESTOLOADTS.stage(IA,S,T)      = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) +1;
*    'Inter-seasonal electricity storage contents at beginning of time segment (MWh)';
VESTOVOLT.stage(IA,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) +1;
VESTOVOLTS.stage(IA,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) +1;
* 'Inter-seasonal heat storage contents at beginning of time segment (MWh)';
VHSTOVOLT.stage(IA,S,T)             = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
VHSTOVOLTS.stage(IA,S,T)             = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
* 'Feasibility in inter-seasonal electricity storage equation QESTOVOLTS (MWh)';
VQESTOVOLT.stage(IA,S,T,IPLUSMINUS)= sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
VQESTOVOLTS.stage(IA,S,T,IPLUSMINUS)= sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
*  'Fuel consumption rate (MW), new units'
VGFN_T.stage(IA,G,S,T) = sum(blockAssignmentSeasons(blocks,S),ord(blocks)) + 1;
