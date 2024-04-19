* File  for addon testbb1234 for the Balmorel model

SCALAR IBB1234VERSION "" / 303.20170102 /;

PUT  " - Addon testbb1234 (incomplete, but useful anyway)" /;

IF((IBB1234VERSION LT IBALVERSN),
  PUT "   *** Addon testbb1234 is older than Balmorel version. You should verify consistency. (Message from \base\addons\bb1234compare\bb1234_hellolog.inc)" /;
);




$ontext

This addon is for comparing output from BB1/BB2/BB3 with simular output from appropriate BB4.
It is intended for use in a transitional phase, where BB4 is developed.

It is assumed that a single year only is considered.
The input that are similar between the two model to be compared must be identical.
The additional data for BB4 must be set up to be consistent with BB1/BB2/BB3 data.
In order for marginals to be the same in BB1/BB2/BB3 as in BB4, the BB4 discount factor must be 1.

When activate, the addon will produce a gdx file with model results and place it in simex. File naves are
BB1234_BB1.gdx/BB1234_BB2.gdx/BB1234_BB3.gdx to be compared with BB1234_BB4.gdx.
To compare the two gdx files, use GDXDiff (under Untilities in the the IDE).

Involved files are, besides this one:
bb1234_checkassumptions, bb12234_vardecl, bb12234_varassign


$offtext
