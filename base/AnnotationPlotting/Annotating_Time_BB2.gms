****************************************************************************************************
****************** Equatuions
****************************************************************************************************
* Objective function
QOBJ.stage = annot_blockLast;

*** Y index in front if it is BB4

* Electricity generation equals demand (MW)
QEEQ.stage(IR,IS3,T) = annot_blockStage(IS3);

* Heat generation equals demand (MW)
QHEQ.stage(IA,IS3,T)$(SUM(DHUSER, IDH_SUMST(IA,DHUSER))) = annot_blockStage(IS3);

* Fuel consumption rate.
QGFEQ.stage(IA,G,IS3,T)$IAGK_Y(IA,G) = annot_blockStage(IS3);
* CHP generation (back pressure) limited by Cb-line (MW)
QGCBGBPR.stage(IAGK_Y(IA,IGBPR),IS3,T)$(NOT IGBYPASS(IGBPR)) = annot_blockStage(IS3);

* CHP generation (extraction) limited by Cb-line (MW)
QGCBGEXT.stage(IAGK_Y(IA,IGEXT),IS3,T) = annot_blockStage(IS3);

* CHP generation (extraction) limited by Cv-line (MW)
QGCVGEXT.stage(IAGK_Y(IA,IGEXT),IS3,T) = annot_blockStage(IS3);

* Electric heat generation (MW)
QGGETOH.stage(IAGK_Y(IA,IGETOH),IS3,T) = annot_blockStage(IS3);

*Intra-seasonal heat storage dynamic equation (MWh)
QHSTOVOLTS.stage(IA,S,T)$(SUM(IGHSTOS, IAGK_Y(IA,IGHSTOS)+IAGKN(IA,IGHSTOS))) = annot_blockStage(S);

*Transmission capacity constraint (MW)
QXK.stage(IRE,IRI,IS3,T)$((IXKINI_Y(IRE,IRI) OR IXKN(IRI,IRE) OR IXKN(IRE,IRI)) AND (IXKINI_Y(IRE,IRI) NE INF) )= annot_blockStage(IS3);


* For instance 3
QHYRSSEQ.stage(IA,S)$SUM(IGHYRS,IAGK_Y(IA,IGHYRS) or IAGKN(IA,IGHYRS)) = card(blocks) + 2;
QHYRSMINVOL.stage(IA,IS3)$(HYRSDATA(IA,'HYRSMINVOL',IS3) AND SUM(IGHYRS$(IAGK_Y(IA,IGHYRS) OR IAGKN(IA,IGHYRS)),1)) = annot_blockStage(IS3);
QHYRSMAXVOL.stage(IA,IS3)$(HYRSDATA(IA,'HYRSMAXVOL',IS3) AND SUM(IGHYRS$(IAGK_Y(IA,IGHYRS) OR IAGKN(IA,IGHYRS)),1)) = annot_blockStage(IS3);
* For instance 3
* Intra-seasonal electricty storage dynamic equation (MWh)
QESTOVOLT.stage(IA,IS3,T)$(SUM(IGESTO, IAGK_Y(IA,IGESTO)+IAGKN(IA,IGESTO)) and ord(T)<Card(T)) = annot_blockStage(IS3);
QESTOVOLTS.stage(IA,S,T)$(SUM(IGESTOS, IAGK_Y(IA,IGESTOS)+IAGKN(IA,IGESTOS)) and ord(T)<Card(T)) = annot_blockStage(S);

QESTOVOLT.stage(IA,IS3,T)$(SUM(IGESTO, IAGK_Y(IA,IGESTO)+IAGKN(IA,IGESTO)) and ord(T)=Card(T)) = annot_blockLast;
QESTOVOLTS.stage(IA,S,T)$(SUM(IGESTOS, IAGK_Y(IA,IGESTOS)+IAGKN(IA,IGESTOS)) and ord(T)=Card(T)) = annot_blockLast;

* Intra-seasonal heat storage upper loading limit (model Balbase2 only) (MW)
QHSTOLOADTLIM.stage(IA,IS3,T)$SUM(IGHSTO,IAGKN(IA,IGHSTO))  = annot_blockStage(IS3);
QHSTOLOADTLIMS.stage(IA,IS3,T)$SUM(IGHSTOS,IAGKN(IA,IGHSTOS))  = annot_blockStage(IS3);

** Missing equations for BB2
*  'Calculate fuel consumption, new units (MW)'
QGFNEQ.stage(IA,G,IS3,T)$IAGKN(IA,G)          = annot_blockStage(IS3);
*  'CHP generation (extraction) Cb-line, new (MW)'
QGNCBGEXT.stage(IAGKN(IA,IGEXT),IS3,T)      = annot_blockStage(IS3);
*      'CHP generation (extraction) Cv-line, new (MW)'
QGNCVGEXT.stage(IAGKN(IA,IGEXT),IS3,T)   = annot_blockStage(IS3);
*       'Electric heat generation, new (MW)'
QGNGETOH.stage(IAGKN(IA,IGETOH),IS3,T)  = annot_blockStage(IS3);
* 'Generation on new electricity cap, limited by capacity (MW)'
QGEKNT.stage(IAGKN(IA,IGKE),IS3,T)$IGDISPATCH(IGKE)         = annot_blockStage(IS3);
*             'Generation on new IGHH cap, limited by capacity (MW)'
QGHKNT.stage(IAGKN(IA,IGKH),IS3,T)$IGDISPATCH(IGKH)   = annot_blockStage(IS3);
*          'Generation on new windpower limited by capacity and wind (MW)'
QGKNWND.stage(IAGKN(IA,IGWND),IS3,T)$IWND_SUMST(IA)  = annot_blockStage(IS3);
*           'Generation on new solarpower limited by capacity and sun (MW)'
QGKNSOLE.stage(IAGKN(IA,IGSOLE),IS3,T)$ISOLESUMST(IA)        = annot_blockStage(IS3);
*   QHSTOVOLTS(AAA,S,T)         'Inter-seasonal heat storage dynamic equation (MWh)'
QHSTOVOLT.stage(IA,IS3,T)$(SUM(IGHSTO, IAGK_Y(IA,IGHSTO)+IAGKN(IA,IGHSTO)) and ord(T)<Card(T))       = annot_blockStage(IS3);
QHSTOVOLTS.stage(IA,S,T)$(SUM(IGHSTOS, IAGK_Y(IA,IGHSTOS)+IAGKN(IA,IGHSTOS)) and ord(T)<Card(T))       = annot_blockStage(S);

QHSTOVOLT.stage(IA,IS3,T)$(SUM(IGHSTO, IAGK_Y(IA,IGHSTO)+IAGKN(IA,IGHSTO)) and ord(T)=Card(T))      = annot_blockLast;
QHSTOVOLTS.stage(IA,S,T)$(SUM(IGHSTOS, IAGK_Y(IA,IGHSTOS)+IAGKN(IA,IGHSTOS)) and ord(T)=Card(T))      = annot_blockLast;
*     'Inter-seasonal heat storage upper loading limit (model Balbase2 only) (MW)'
QHSTOLOADTLIM.stage(IA,IS3,T)$SUM(IGHSTO,IAGKN(IA,IGHSTO))       = annot_blockStage(IS3);
QHSTOLOADTLIMS.stage(IA,IS3,T)$SUM(IGHSTOS,IAGKN(IA,IGHSTOS))      = annot_blockStage(IS3);
*             'Total capacity using fuel FFF is limited in region (MW)'
* Should have stage 1 which is achieved when not assigned
*QKFUELR.stage(IR,FFF)$FKPOT(IR,FFF)         =  card(blocks) + 2;
*  'Inter-seasonal heat storage capacity limit (model Balbase2 only) (MWh)'
QHSTOVOLTLIM.stage(IA,IS3,T)$SUM(IGHSTO,IAGKN(IA,IGHSTO))  = annot_blockStage(IS3);
QHSTOVOLTLIMS.stage(IA,IS3,T)$SUM(IGHSTOS,IAGKN(IA,IGHSTOS))  = annot_blockStage(IS3);
*'CHP generation (back pressure) Cb-line, new (MW)'
QGNCBGBPR.stage(IAGKN(IA,IGBPR),IS3,T)$(NOT IGBYPASS(IGBPR))  = annot_blockStage(IS3);


$ifi     %HYDROGEN%==yes      QHYDROGEN_EQ.stage(IR,IS3,T)=   annot_blockStage(IS3);
$ifi     %HYDROGEN%==yes      QHYDROGEN_HNGEHTOH2.stage(IAGKN(IA,IHYDROGEN_GEHTOH2),IS3,T)  =   annot_blockStage(IS3);
$ifi     %HYDROGEN%==yes      QHYDROGEN_HNGETOH2.stage(IAGKN(IA,IHYDROGEN_GETOH2),IS3,T)  =   annot_blockStage(IS3);

$ifi     %HYDROGEN%==yes      QHYDROGEN_GNGETOH2.stage(IAGKN(IA,IHYDROGEN_GETOH2),IS3,T)  =   annot_blockStage(IS3);
$ifi     %HYDROGEN%==yes      QHYDROGEN_STOMAXUNLD.stage(IA,IHYDROGEN_GH2STO,IS3,T)$(IAGK_Y(IA,IHYDROGEN_GH2STO) OR IAGKN(IA,IHYDROGEN_GH2STO))   =  annot_blockStage(IS3);
$ifi     %HYDROGEN%==yes      QHYDROGEN_STOMAXLOAD.stage(IA,IHYDROGEN_GH2STO,IS3,T)$(IAGK_Y(IA,IHYDROGEN_GH2STO) OR IAGKN(IA,IHYDROGEN_GH2STO))  =  annot_blockStage(IS3);

* Since the check anno says it should have stage one for the ends
$ifi     %HYDROGEN%==yes      QHYDROGEN_STOMAXCON.stage(IA,IHYDROGEN_GH2STO,S,T)$(IAGK_Y(IA,IHYDROGEN_GH2STO) OR IAGKN(IA,IHYDROGEN_GH2STO) and ord(T)>1)  =  annot_blockStage(S);

$ifi     %HYDROGEN%==yes      QHYDROGEN_STOVOL.stage(IA,IHYDROGEN_GH2STO,S,T)$(IAGK_Y(IA,IHYDROGEN_GH2STO) OR IAGKN(IA,IHYDROGEN_GH2STO))     =  annot_blockStage(S);

****************************************************************************************************
****************** Variables
****************************************************************************************************
* Objective function value (MMoney)
VOBJ.stage =  1;


* Electricity generation (MW), existing units
VGE_T.stage(IA,G,S,T) = annot_blockStage(S);
* Heat generation (MW), existing units

*** NOT IN THE SAME BLOCK!
VGH_T.stage(IA,G,S,T) = annot_blockStage(S);

* Fuel consumption rate (MW), existing units
VGF_T.stage(IA,G,S,T) = annot_blockStage(S);

* Electricity export from region IRRRE to IRRRI (MW)

VX_T.stage(IRRRE,IRRRI,S,T) = annot_blockStage(S);


* Intra-seasonal heat storage loading (MW)
VHSTOLOADTS.stage(IA,S,T) = annot_blockStage(S);

* Feasibility in electricity balance equation QEEQ (MW)
VQEEQ.stage(IR,S,T,IPLUSMINUS) = annot_blockStage(S);

* Feasibility in heat balance equation QHEQ (MW)
VQHEQ.stage(IA,S,T,IPLUSMINUS) = annot_blockStage(S);

* Feasibility in intra-seasonal heat storage equation VQHSTOVOLT (MWh)
VQHSTOVOLTS.stage(IA,S,T,IPLUSMINUS) = annot_blockStage(S);

* Feasibility in Transmission capacity constraint (MW)
VQXK.stage(IRRRE,IRRRI,S,T,IPLUSMINUS) = annot_blockStage(S);


* Instance 2 extra
VHYRS_S.stage(IA,S) = annot_blockStage(S);
VQHYRSSEQ.stage(IA,S,IPLUSMINUS) = annot_blockStage(S);
VQHYRSMINMAXVOL.stage(IA,S,IPLUSMINUS)  = annot_blockStage(S);


* Missing variables for BB2 mode
*                'Electricity generation (MW), new units';
VGEN_T.stage(IA,G,S,T)            = annot_blockStage(S);
*                'Heat generation (MW), new units';
VGHN_T.stage(IA,G,S,T)            = annot_blockStage(S);
*              'New generation capacity (MW)';
VGKN.stage(IA,G)           =  1;
*              'New electricity transmission capacity (MW)';
VXKN.stage(IRRRE,IRRRI)   = 1;
*       'Inter-seasonal electricity storage loading (MW)';
VESTOLOADT.stage(IA,S,T)      = annot_blockStage(S);
VESTOLOADTS.stage(IA,S,T)      = annot_blockStage(S);
*    'Inter-seasonal electricity storage contents at beginning of time segment (MWh)';
VESTOVOLT.stage(IA,S,T) = annot_blockStage(S);
VESTOVOLTS.stage(IA,S,T) = annot_blockStage(S);
* 'Inter-seasonal heat storage contents at beginning of time segment (MWh)';
VHSTOVOLT.stage(IA,S,T)             = annot_blockStage(S);
VHSTOVOLTS.stage(IA,S,T)             = annot_blockStage(S);
* 'Feasibility in inter-seasonal electricity storage equation QESTOVOLTS (MWh)';
VQESTOVOLT.stage(IA,S,T,IPLUSMINUS)= annot_blockStage(S);
VQESTOVOLTS.stage(IA,S,T,IPLUSMINUS)= annot_blockStage(S);
*  'Fuel consumption rate (MW), new units'
VGFN_T.stage(IA,G,S,T) = annot_blockStage(S);


$ifi     %HYDROGEN%==yes      VHYDROGEN_GH2N_T.stage(IA,G,S,T) = annot_blockStage(S);
$ifi     %HYDROGEN%==yes      VHYDROGEN_STOVOL_T.stage(IA,G,S,T)$(ord(T)>1) = annot_blockStage(S);
$ifi     %HYDROGEN%==yes      VHYDROGEN_STOVOL_T.stage(IA,G,S,T)$(ord(T)=1) = 1;

$ifi     %HYDROGEN%==yes      VHYDROGEN_STOLOADT.stage(IA,G,S,T)  = annot_blockStage(S);
