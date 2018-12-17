PARAMETERS
TV_FIXED(YYY,AAA,GGG) 'fixed costs including investment costs'
TV_VAREL(YYY,AAA,GGG) 'variable costs for el production'
TV_VARHEAT(YYY,AAA,GGG) 'variable costs for heat production'
;

SETS
IAGKNY_IY411(YYY,AAA,GGG) 'set of allowed investment options'
TV_IY411(Y)    'remaining years of the balbase4 model within the IY411-loop'

TV_REQMIN(YYY,AAA,GGG) 'technologies with minimum usage requirements'
TV_REQFX(YYY,AAA,GGG) 'technologies with fixed usage requirements'
TV_REQMAX(YYY,AAA,GGG) 'technologies with maximum usage requirements'

TV_REQEMIN(YYY,AAA,GGG) 'technologies with minimum usage requirements'
TV_REQEMAX(YYY,AAA,GGG) 'technologies with maximum electricity constraints'
;

*Full load hours
SET TV_FLH / 1,  1000, 2500, 4000, 6500, 8000, 8760 /;
Alias(TV_FLH, TV_FLHHEAT);

* intervals for alternative value
SET TV_PR /0, 25, 50, 75, 100/;

PARAMETER TV_CHEAPESTCND(YYY,AAA,TV_FLH) ;
PARAMETER TV_CHEAPESTHOB(YYY,AAA,TV_FLH) ;
PARAMETER TV_CHEAPESTCNDR(YYY,RRR,TV_FLH) ;

PARAMETER TV_ANNUALCOST_E(YYY,AAA,G,TV_FLH,TV_FLHHEAT,TV_PR) ;
PARAMETER TV_ANNUALCOST_H(YYY,AAA,G,TV_FLH,TV_FLHHEAT,TV_PR) ;

PARAMETER TV_CHEAPEST_E(YYY,AAA,TV_FLH,TV_FLHHEAT,TV_PR) ;
PARAMETER TV_CHEAPEST_H(YYY,AAA,TV_FLH,TV_FLHHEAT,TV_PR) ;
PARAMETER TV_CHEAPEST_EF(YYY,AAA,TV_FLH,TV_FLHHEAT,TV_PR) ;
PARAMETER TV_CHEAPEST_HF(YYY,AAA,TV_FLH,TV_FLHHEAT,TV_PR) ;

SET TV_CHEAPEST(YYY,AAA,G,TV_FLH,TV_FLHHEAT,TV_PR) ;
SET TV_NEVERCHEAP(YYY,AAA,GGG);
SET TV_NEVERCHEAP2(YYY,AAA,GGG);

