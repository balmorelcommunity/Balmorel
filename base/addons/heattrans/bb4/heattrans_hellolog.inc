* File heattrans_hellolog.inc for the Balmorel model. For use with addon heattrans.
* Latest revision 20180923(hr)

PUT  " - Addon heattrans" /;


$ontext

Explanation - todo.

$offtext

$ontext



All heat pumps for temperature lift are identified and specified in GGG, G, GATA, GKFX, AGKN, ...   as usual.
All such heat pumps are additionally set as member of set GETOHXH(GGG)
For a specific pair of Areas with heat transmisison from low to high temperature Areas
there is zero or a single the heat pump; if there is one it is located at one of the two connected areas (GKFX, AGKN).
The heat pump enters the balance equation QEEQ as usual;
but not QHEQ, as the produced heat is handled as part of the heat transmission.
The heat produced by the heat pump is required to be proportional to the heat transmitted between the two areas.
The coefficient for that is specified in positive parameter XHTEMPLIFT.
The amount of heat (as implicitly specified in XHTEMPLIFT) from the heat pump is as needed for increasing the temperature of the transmitted heat,
including compensation for the heat loss in the transmision.


$offtext

