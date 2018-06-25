* These internal parameters pertain to price sensitivy electricity exchange with third countries.

PARAMETER IX3VBAL(YYY,X3VPLACE) "price of the annual balance constraint"
          IX3VBALSP(YYY,X3VPLACE) "Get shadow price of the annual balance constraint"
          IX3VPIM_Y(YYY,RRR,X3VPLACE,X3VSTEP0,S,T) "Third country price dependent import price current year (Money/MWh)"
          IX3VPEX_Y(YYY,RRR,X3VPLACE,X3VSTEP0,S,T) "Third country price dependent export price current year (Money/MWh)"
;

* LARS: Nyt - Indført årlig netto balance imellem det modellerede område og 3. lande.
* Måske et problem hvis man ikke har alle lande med som eksportere til det samme 3. land.
* Oftest vil denne balance dog være 0, så foreløbigt efterlades spørgsmålet åbent.

IX3VBAL(YYY,X3VPLACE)=X3VBAL(YYY,X3VPLACE);

*IX3VBALSP(YYY,X3VPLACE)=X3VBALSP(YYY,X3VPLACE);

* Price dependent exchange with places outside the simulated countries:
* Set of relevant price dependent electricity exhanges this year:
* Update price dependent exchange prices to current simulation year:

IX3VPIM_Y(YYY,IR,X3VPLACE,X3VSTEP,S,T)=X3VPIM(YYY,IR,X3VPLACE,X3VSTEP,S,T)$(X3VQIM(YYY,IR,X3VPLACE,X3VSTEP,S,T) OR X3VQEX(YYY,IR,X3VPLACE,X3VSTEP,S,T));

IX3VPEX_Y(YYY,IR,X3VPLACE,X3VSTEP,S,T)=X3VPEX(YYY,IR,X3VPLACE,X3VSTEP,S,T)$(X3VQIM(YYY,IR,X3VPLACE,X3VSTEP,S,T) OR X3VQEX(YYY,IR,X3VPLACE,X3VSTEP,S,T));

$ifi %X3VfxQ%==yes execute_unload '../../base/addons/x3v/data/X3V_%X3VPRICECASE%_BALSP.gdx',X3VBALSP;    
