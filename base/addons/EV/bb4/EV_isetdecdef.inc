$ifi not %STEPCHARGSCHEME%==yes $goto STEPCHARGSCHEME_SET_END
set CHARGINGSTRAGEGY /dumb, smart, v2g/;
set cs(CHARGINGSTRAGEGY,Y);
cs('dumb',Y)$(Y.val =2020) = yes;
cs('dumb',Y)$(Y.val =2030) = yes;
cs('smart',Y)$(Y.val =2040) = yes;
cs('v2g',Y)$(Y.val =2050) = yes;

$label  STEPCHARGSCHEME_SET_END