* File errorBB4 to the Balmorel model.
* This is for addon BB4.
* Created 20081103 (hr).

* Set SIMYEARS and parameter SIMDELTA must be consistent.
* Note that the following checks implicitly assures that all elements in SIMYEARS are given appropriate values,
* and further that no values can be assigned to elements in SIMDELTA.
LOOP(SIMYEARS,
   IF ((ORD(SIMYEARS) = 1) AND (SIMDELTA(SIMYEARS) <> 0),
      put ERRORFILE;
      put "ERROR in SIMDELTA(" SIMYEARS.tl ") for BB4: value must be 0."/;
      ERRCOUNT2=ERRCOUNT2+1;
   );
   IF ((ORD(SIMYEARS) > 1) AND (SIMDELTA(SIMYEARS) <= 0),
      put ERRORFILE;
      put "ERROR in SIMDELTA(" SIMYEARS.tl ") for BB4: value must be greater than 0."/;
      ERRCOUNT2=ERRCOUNT2+1;
   );
);

IF((CARD(SIMYEARS) > CARD(Y)),
      put ERRORFILE;
      put "ERROR in SIMYEARS for BB4: (CARD(SIMYEARS) > CARD(Y)). No Balbase4 model will be generated"/;
      ERRCOUNT2=ERRCOUNT2+1;
);

IF((SUM(SIMYEARS,SIMDELTA(SIMYEARS)) > CARD(Y)-1),
      put ERRORFILE;
      put "ERROR in SIMDELTA for BB4: The number of model years (cf. SIMYEARS) and the distance (cf. SIMDELTA) between them in Balbase4 is so large that no Balbase4 model will be generated."/;
      ERRCOUNT2=ERRCOUNT2+1;
);


