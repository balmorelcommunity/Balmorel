* File xbottle.inc
* Printing information relative to bottle necks in the electricity transmission system

* Modified last time: 02-11-2003 (hr), 2005.07.31 (hr), 2005.10.29 (hr), 20060328(hr), 200804xx(hr)




put xbottle;

* -----------------------------------------------------------------------------

* First print headings:

if ((xbottle.pw LT 32000),
xbottle.pw=32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "xbottle.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Bottle neck information........" //;
put "Observe: bottle neck income on a transmission line between regions IRE and IRI in a time segment (S,T) calculated as "/;
put "the difference between the electricity prices in the regions multiplied by the transmission. "/;
put "This implies that any transmissison cost XCOST(IRE,IRI) is considered a real cost, hence not an income. "/;
put "Note: transmission losses are disregarded in this version."//;
);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

PUT "  Bottle neck income, " omoney.ts " for " Y.TL:4 //;

* If iscalar1 is 0 then bottle neck income for both directions on a line are summed
* If iscalar1 is not 0 then the bottle neck income is given for the two directions separately.

iscalar1=1;
if(iscalar1,

put "                         ";
loop(irrre$ire(irrre), loop(irrri$(iri(irrri) and  (ord(irrre) ne ord(irrri)) and ((VXKN.l(IRRRE,IRRRI) gt 0) or (IXKINI_Y(IRRRE,IRRRI) gt 0 ))),
                            xbottle.lj=1 put "("irrre.tl:10"."; xbottle.lj=2; put irrri.tl:10")   "); ); put /;

loop((S,t),
put   S.tl:12 t.tl:12;
loop(irrre$ire(irrre), loop(irrri$(iri(irrri) and  (ord(irrre) ne ord(irrri)) and ((VXKN.l(IRRRE,IRRRI) gt 0) or (IXKINI_Y(IRRRE,IRRRI) gt 0 ))),
                            XBOTTLEIN(IRRRE,IRRRI,S,T)=IHOURSINST(S,T)*vx_t.l(irRRe,irRRi,S,t)*max((abs(1e6*(qeeq.m(IRRRe,S,T) - qeeq.m(IRRRi,S,T))
                            /IHOURSINST(S,T))-XCOST(IRrrE,IRrrI)),0);
put (  omoney* XBOTTLEIN(IRRRE,IRRRI,S,T)   ):14:1 "            ";
)) put /;);


put "Sum,   "y.tl:4":";

loop(irrre$ire(irrre), loop(irrri$(iri(irrri) and  (ord(irrre) ne ord(irrri)) and ((VXKN.l(IRRRE,IRRRI) gt 0) or (IXKINI_Y(IRRRE,IRRRI) gt 0 ))),
   put (omoney* sum((S,t),  XBOTTLEIN(IRRRE,IRRRI,s,T)  )):26:1   ;
)) put /;

put "Sum, all transmission links, "y.tl:4":"  (omoney* sum((s,t),

SUM(irrre$ire(irrre), SUM(irrri$(iri(irrri) and  (ord(irrre) ne ord(irrri))and ((VXKN.l(IRRRE,IRRRI) gt 0) or (IXKINI_Y(IRRRE,IRRRI) gt 0 ))),  XBOTTLEIN(IRRRE,IRRRI,s,T)  )))):26:1   ;

ELSE



);



* LARS: Indfoert beregning af flaskehalsindtaegter til 3. lande.
XBOTTLEX3(IR,S,T) = IOF1000000*QEEQ.m(IR,S,T)*(-IX3FX_T_Y(IR,S,T));
$ifi %X3V%==yes XBOTTLEX3V(IR,X3VPLACE,S,T)$X3VX(IR,X3VPLACE) = (IOF1000000*QEEQ.m(IR,S,T)/IHOURSINST(S,T)-(X3VBALSP(Y,X3VPLACE)+IX3VPIM_Y(IR,X3VPLACE,'X3VSTEP01',S,T)) ) *SUM(X3VSTEP, VX3VIM_T.l(IR,X3VPLACE,X3VSTEP,S,T))*IHOURSINST(S,T)
$ifi %X3V%==yes                                                -(IOF1000000*QEEQ.m(IR,S,T)/IHOURSINST(S,T)-(X3VBALSP(Y,X3VPLACE)+IX3VPEX_Y(IR,X3VPLACE,'X3VSTEP01',S,T)) ) *SUM(X3VSTEP, VX3VEX_T.l(IR,X3VPLACE,X3VSTEP,S,T))*IHOURSINST(S,T);
*$ifi %X3V%==yes XBOTTLEX3V(IR,X3VPLACE,S,T)$X3VX(IR,X3VPLACE) = (IOF1000000*QEEQ.m(IR,S,T)/IHOURSINST(S,T)-(X3VBALSP(Y,X3VPLACE)+SMAX(X3VSTEP$(VX3VIM_T.l(IR,X3VPLACE,X3VSTEP,S,T)>0), IX3VPIM_Y(IR,X3VPLACE,X3VSTEP,S,T)) )) *SUM(X3VSTEP, VX3VIM_T.l(IR,X3VPLACE,X3VSTEP,S,T))*IHOURSINST(S,T)
*$ifi %X3V%==yes                                                -(IOF1000000*QEEQ.m(IR,S,T)/IHOURSINST(S,T)-(X3VBALSP(Y,X3VPLACE)+SMIN(X3VSTEP$(VX3VEX_T.l(IR,X3VPLACE,X3VSTEP,S,T)>0), IX3VPEX_Y(IR,X3VPLACE,X3VSTEP,S,T)) )) *SUM(X3VSTEP, VX3VEX_T.l(IR,X3VPLACE,X3VSTEP,S,T))*IHOURSINST(S,T);
