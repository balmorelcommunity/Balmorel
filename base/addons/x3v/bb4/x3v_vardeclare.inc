POSITIVE VARIABLES

   VX3VIM_T(Y,RRR,X3VPLACE0,X3VSTEP0,S,T) "Imported third country price dependent electricity (MW)"
   VX3VEX_T(Y,RRR,X3VPLACE0,X3VSTEP0,S,T) "Exported third country price dependent electricity (MW)"
 ;

*Set the third country price dependent exchange capacities for each step:
VX3VIM_T.UP(Y,RRR,X3VPLACE,X3VSTEP,S,T)=X3VQIM(Y,RRR,X3VPLACE,X3VSTEP,S,T)$X3VX(RRR,X3VPLACE);
VX3VEX_T.UP(Y,RRR,X3VPLACE,X3VSTEP,S,T)=X3VQEX(Y,RRR,X3VPLACE,X3VSTEP,S,T)$X3VX(RRR,X3VPLACE);
;
