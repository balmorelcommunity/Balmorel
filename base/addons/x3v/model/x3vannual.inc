* LARS: Nyt - Indført årlig netto balance imellem det modellerede område og 3. lande.
* Måske et problem hvis man ikke har alle lande med som eksportere til det samme 3. land.
* Oftest vil denne balance dog være 0, så foreløbigt efterlades spørgsmålet åbent.

$ifi %X3VfxQ%==yes IX3VBAL(X3VPLACE)=X3VBAL(Y,X3VPLACE);

$ifi %X3VfxP%==yes IX3VBALSP(X3VPLACE)=X3VBALSP(Y,X3VPLACE);


* Set the third country price dependent exchange capacities for each step:
$ifi %X3V%==yes     VX3VIM_T.UP(IR,X3VPLACE,X3VSTEP,S,T)=X3VQIM(IR,X3VPLACE,X3VSTEP,S,T)$X3VX(IR,X3VPLACE);
$ifi %X3V%==yes     VX3VEX_T.UP(IR,X3VPLACE,X3VSTEP,S,T)=X3VQEX(IR,X3VPLACE,X3VSTEP,S,T)$X3VX(IR,X3VPLACE);



* Price dependent exchange with places outside the simulated countries:
* Set of relevant price dependent electricity exhanges this year:
* Update price dependent exchange prices to current simulation year:
$ifi %X3V%==yes  IX3VPIM_Y(Y,IR,X3VPLACE,X3VSTEP,S,T)=X3VPIM(Y,IR,X3VPLACE,X3VSTEP,S,T)$
$ifi %X3V%==yes     (X3VQIM(IR,X3VPLACE,X3VSTEP,S,T) OR X3VQEX(IR,X3VPLACE,X3VSTEP,S,T));
$ifi %X3V%==yes  IX3VPEX_Y(Y,IR,X3VPLACE,X3VSTEP,S,T)=X3VPEX(Y,IR,X3VPLACE,X3VSTEP,S,T)$
$ifi %X3V%==yes     (X3VQIM(IR,X3VPLACE,X3VSTEP,S,T) OR X3VQEX(IR,X3VPLACE,X3VSTEP,S,T));
