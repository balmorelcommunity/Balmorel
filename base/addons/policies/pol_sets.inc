* Addon for securing that policy requirements are forfilled
* Policy requirements are given for userdefined policy area and policy type

SET POLAREA      'Group of policy areas';
SET POLAREAGEO(POLAREA,CCCRRRAAA)   'Defining the geografy of each policy area by CCC, RRR and AAA' ;
SET POLICY       'Group of policies';
SET POLICYTYPE   'Different policy types';
SET POLTYP(POLICY,POLICYTYPE) 'Policy type assigned to each policy';
SET POLTECH(POLICY,G) 'Technologies related to each policy';

* Addon defined technology sets
SET VETECH(G)  ''
/
WI-L15
WI-L20
WI-L25
WI-S15
WI-S20
WI-S25

/
* Userdefined technology set
SET USERTECH(G)  ''
/

ST-B8-NG


/


SET POLAREA   'Group of policy areas'  %semislash%
$if     EXIST '../data/POLAREA.inc' $INCLUDE       '../data/POLAREA.inc';
$if not EXIST '../data/POLAREA.inc' $INCLUDE       '../../base/addons/policies/data/POLAREA.inc';
%semislash%;

SET POLAREAGEO(POLAREA,CCCRRRAAA) 'Defining the geografi for each regime' %semislash%
$if     EXIST '../data/POLAREAGEO.inc' $INCLUDE    '../data/POLAREAGEO.inc';
$if not EXIST '../data/POLAREAGEO.inc' $INCLUDE    '../../base/addons/policies/data/POLAREAGEO.inc';
%semislash%;



SET POLICY 'Group of policies' %semislash%
$if     EXIST '../data/POLICY.inc' $INCLUDE        '../data/POLICY.inc';
$if not EXIST '../data/POLICY.inc' $INCLUDE        '../../base/addons/policies/data/POLICY.inc';
%semislash%;

SET POLICYTYPE 'Different policy types' %semislash%
$if     EXIST '../data/POLICYTYPE.inc' $INCLUDE    '../data/POLICYTYPE.inc';
$if not EXIST '../data/POLICYTYPE.inc' $INCLUDE    '../../base/addons/policies/data/POLICYTYPE.inc';
%semislash%;

SET POLTYP(POLICY,POLICYTYPE) 'Policy type assigned to each policy' %semislash%
$if     EXIST '../data/POLTYP.inc' $INCLUDE        '../data/POLTYP.inc';
$if not EXIST '../data/POLTYP.inc' $INCLUDE        '../../base/addons/policies/data/POLTYP.inc';
%semislash%;

SET POLTECH(POLICY,G) 'Technologies related to each policy' %semislash%
$if     EXIST '../data/POLTECH.inc' $INCLUDE        '../data/POLTECH.inc';
$if not EXIST '../data/POLTECH.inc' $INCLUDE        '../../base/addons/policies/data/POLTECH.inc';
%semislash%;















