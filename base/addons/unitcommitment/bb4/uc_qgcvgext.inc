*Removing original capacity limitation. Double check that this is the same in the main code

     +(
     (
     GKFX(IY411,IA,IGEXT)$IAGKFX(IY411,IA,IGEXT)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGEXT)$IGDECOMEXOPOT(IY411,IA,IGEXT)
      + VGKNACCUMNET(IY411,IA,IGEXT)$(IAGK_HASORPOT(IY411,IA,IGEXT) AND IAGKN(IA,IGEXT))
     )*
     (1$(NOT IGKRATE(IA,IGEXT,IS3,T)) + IGKRATE(IA,IGEXT,IS3,T))
     )$(IGUC(IGEXT))



*Introducing new capacity limitation based on units that are on
 
     -(
     (
     GDATA(IGEXT,'GDUCUNITSIZE')*VUCON(IY411,IA,IGEXT,IS3,T)
     )*
     (1$(NOT IGKRATE(IA,IGEXT,IS3,T)) + IGKRATE(IA,IGEXT,IS3,T))
     )$(IGUC(IGEXT))
