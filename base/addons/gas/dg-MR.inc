

* No seperate tables for gas consumption not used for electricity and district heating,
* therefore the annual values are obtained by summing the variation profiles. Hereby, consumption
* by this group of consumers is expected to remain unchanged.

DGRES(YYY,AAA)$ICA('Denmark',AAA) = sum((SSS,TTT),365/364*DG_VAR('residual',AAA,SSS,TTT));
DGOTH(YYY,AAA)$ICA('Denmark',AAA) = sum((SSS,TTT),365/364*DG_VAR('Andre timeaflæste',AAA,SSS,TTT))
                                    +sum((SSS,TTT),365/364*DG_VAR('Industriel andet formål',AAA,SSS,TTT));

DGRES(YYY,'hoejby')= sum((SSS,TTT),365/364*DG_NGF_VAR('residual',SSS,TTT));
DGOTH(YYY,'hoejby')= sum((SSS,TTT),365/364*(DG_NGF_VAR('Andre timeaflæste',SSS,TTT)
                                 +DG_NGF_VAR('Industriel andet formål',SSS,TTT)));