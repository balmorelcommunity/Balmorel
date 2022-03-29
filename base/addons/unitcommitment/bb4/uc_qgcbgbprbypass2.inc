*Removing original capacity limitation. Double check that this is the same in the main code

     -(
      (1+(GDATA(IGBPR,'GDBYPASSC')/GDATA(IGBPR,'GDCB')))*(
      GKFX(IY411,IA,IGBPR)$IAGKFX(IY411,IA,IGBPR)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,IGBPR)$IGDECOMEXOPOT(IY411,IA,IGBPR)
      + VGKNACCUMNET(IY411,IA,IGBPR)$(IAGK_HASORPOT(IY411,IA,IGBPR) AND IAGKN(IA,IGBPR))
      )*(1$(NOT GEFFRATE(IA,IGBPR))+GEFFRATE(IA,IGBPR))*(1$(NOT IGKRATE(IA,IGBPR,IS3,T)) + IGKRATE(IA,IGBPR,IS3,T))
     )$(IGUC(IGBPR))



*Introducing new capacity limitation based on units that are on

     +(
      (1+(GDATA(IGBPR,'GDBYPASSC')/GDATA(IGBPR,'GDCB')))*(
     GDATA(IGBPR,'GDUCUNITSIZE')*VUCON(IY411,IA,IGBPR,IS3,T)
      )*(1$(NOT GEFFRATE(IA,IGBPR))+GEFFRATE(IA,IGBPR))
     )$(IGUC(IGBPR))
