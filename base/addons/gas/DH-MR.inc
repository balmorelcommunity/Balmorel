* SOURCE: Energiproducenttælling 2004.

PARAMETER DH_MR2004(AAA)
/
billesboelle         10818.3333333333
brande               47014.8888888889
dragoer              7277.27777777778
egtved               531798.639888889
ellidshoej           164185.830555556
froeslev             642938.566666667
haverslev            556340.64

*herning              6586890.71007009 Original fra database
* Frastrukket DK_W_AARHUS
herning              3585684
DK_W_AARHUS          3001207

* hoejby               3261777.32422222 Original fra database
* Fratrukket Odense postnumre
hoejby               327055
* Kun anlæg med Odense postnummer:
DK_W_ODENSE          2934722

karup                234517.878888889
koege                217484.897777778
koelbjerg            336272.124444444
liselskaer           301802.232
litorup              49496.1
lynge                1237484.6
middelfart           90500.5288888889
maaloev              501278.626388889
noerskov             295146.515777778
nyborg               172319.452222222
nybro                58330.5
DK_E_Rural           835210.904111111
pottehuse            243976
ringsted             632562.144444445
slagelse             302631.638888889
soroe                833593.757666667
standst              301744.235777778
stenlille            6076

* Bør lige undersøges igen fordi DH TREFOR er større end skaerbaek/taulov
* Taulov          945821.5
DK_W_TREFOR          987722

terkelsboel          224073.725555556
varde                1357966.38188889

DK_W_Rural           163721.528444445
viborg               1694392.61202222



*aalborg              2754115.00622222   Original fra database
* Fratrukket DK_W_AALBORG:
aalborg              1561429
DK_W_AALBORG         1192686

* Original DK_E_Urban:
*DK_E_Urban        10056899
* DK_E_Urban dannet udfra sum af følgende MR stationer
*torslunde        415368.9156
*ullerslev        43140
*vallensbaek        1057007.5
*karlslunde        36660.37778
*avedoere        1055380.836
*amagerf        2224904.917
*HCOersted        4335603.745
DK_E_Urban        9168066.291
/;

DH(YYY,AAA)$ICA('Denmark',AAA) = 0;
DH(YYY,AAA)$(DH_MR2004(AAA)) = DH_MR2004(AAA);
















































































