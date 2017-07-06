

* No seperate tables for gas consumption not used for electricity and district heating,
* therefore the annual values are obtained by summing the variation profiles. Hereby, consumption
* by this group of consumers is expected to remain unchanged.

DGRES(YYY,'DK_E_Urban')= sum((SSS,TTT),365/364*DG_HNG_VAR('residual',SSS,TTT));
DGOTH(YYY,'DK_E_Urban')= sum((SSS,TTT),365/364*(DG_HNG_VAR('Andre timeaflæste',SSS,TTT)
                                +DG_HNG_VAR('Industriel andet formål',SSS,TTT)));
DGRES(YYY,'DK_E_Rural')= sum((SSS,TTT),365/364*DG_DongOest_VAR('residual',SSS,TTT));
DGOTH(YYY,'DK_E_Rural')= sum((SSS,TTT),365/364*(DG_DongOest_VAR('Andre timeaflæste',SSS,TTT)
                               +DG_DongOest_VAR('Industriel andet formål',SSS,TTT)));
DGRES(YYY,'DK_W_AALBORG')= sum((SSS,TTT),365/364*DG_MidtNord_VAR('residual',SSS,TTT));
DGOTH(YYY,'DK_W_AALBORG')= sum((SSS,TTT),365/364*(DG_MidtNord_VAR('Andre timeaflæste',SSS,TTT)
                                  +DG_MidtNord_VAR('Industriel andet formål',SSS,TTT)));
DGRES(YYY,'DK_W_TREFOR')= sum((SSS,TTT),365/364*DG_DongVest_VAR('residual',SSS,TTT));
DGOTH(YYY,'DK_W_TREFOR')= sum((SSS,TTT),365/364*(DG_DongVest_VAR('Andre timeaflæste',SSS,TTT)
                                 +DG_DongVest_VAR('Industriel andet formål',SSS,TTT)));

DGRES(YYY,'DK_W_ODENSE')= sum((SSS,TTT),365/364*DG_NGF_VAR('residual',SSS,TTT));
DGOTH(YYY,'DK_W_ODENSE')= sum((SSS,TTT),365/364*(DG_NGF_VAR('Andre timeaflæste',SSS,TTT)
                                 +DG_NGF_VAR('Industriel andet formål',SSS,TTT)));

