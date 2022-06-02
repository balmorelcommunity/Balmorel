PARAMETER DC_GDHE(GGG)                                    'Consumption/production of chiller technologies from/to district heating (MWt-hot/MWt-cold)';
PARAMETER DC_FREECOOLING_POTENTIAL(SSS,TTT,AAA,DHUSER)    'Fraction of cooling demand that can be covered by free-cooling';

* ----- DC_GDHE ----- *
* If DC_GDHE is negative, then the chiller is a consumer of heat to the district heating. E.g. Absorption chillers.
* If DC_GDHE is positive, then the chiller is a producer of heat to the district heating. E.g. Heat pumps.
* Electric chillers that release its waste heat into the environment have a null DC_GDHE.

* ----- DC_FREECOOLING_POTENTIAL ----- *
* A free-cooling potential of one means that all current cooling demand can be covered by free-cooling technologies.
* A free-cooling potential of zero means that no cooling demand can be covered by free-cooling technologies.
