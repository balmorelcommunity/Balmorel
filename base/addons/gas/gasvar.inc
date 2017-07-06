
* The following parameters contain aggregated variation profiles to match an
* aggregated geografical resolution.

PARAMETER DG_HNG_VAR(gasanvendelser,SSS,TTT),
          DG_MidtNord_VAR(gasanvendelser,SSS,TTT),
          DG_DongOest_VAR(gasanvendelser,SSS,TTT),
          DG_DongVest_VAR(gasanvendelser,SSS,TTT),
          DG_NGF_VAR(gasanvendelser,SSS,TTT);

* This file contains the variation profiles. Profiles are based on a datacollection
* effort under the EFP2005GasEl project.
execute_load '../../base/addons/gas/gasforbrug.gdx', DG_HNG_VAR,DG_MidtNord_VAR, DG_DongOest_VAR, DG_DongVest_VAR,  DG_NGF_VAR;


DGRES_VAR('DK_E_Urban',SSS,TTT)= DG_HNG_VAR('residual',SSS,TTT);
DGOTH_VAR('DK_E_Urban',SSS,TTT)= DG_HNG_VAR('Andre timeaflæste',SSS,TTT)
                                +DG_HNG_VAR('Industriel andet formål',SSS,TTT);
DGRES_VAR('DK_E_Rural',SSS,TTT)= DG_DongOest_VAR('residual',SSS,TTT);
DGOTH_VAR('DK_E_Rural',SSS,TTT)= DG_DongOest_VAR('Andre timeaflæste',SSS,TTT)
                                +DG_DongOest_VAR('Industriel andet formål',SSS,TTT);
DGRES_VAR('DK_W_AALBORG',SSS,TTT)= DG_MidtNord_VAR('residual',SSS,TTT);
DGOTH_VAR('DK_W_AALBORG',SSS,TTT)= DG_MidtNord_VAR('Andre timeaflæste',SSS,TTT)
                                  +DG_MidtNord_VAR('Industriel andet formål',SSS,TTT);
DGRES_VAR('DK_W_TREFOR',SSS,TTT)= DG_DongVest_VAR('residual',SSS,TTT);
DGOTH_VAR('DK_W_TREFOR',SSS,TTT)= DG_DongVest_VAR('Andre timeaflæste',SSS,TTT)
                                 +DG_DongVest_VAR('Industriel andet formål',SSS,TTT);
DGRES_VAR('DK_W_ODENSE',SSS,TTT)= DG_NGF_VAR('residual',SSS,TTT);
DGOTH_VAR('DK_W_ODENSE',SSS,TTT)= DG_NGF_VAR('Andre timeaflæste',SSS,TTT)
                                 +DG_NGF_VAR('Industriel andet formål',SSS,TTT);





*TABLE DEF_STEPS
*                             DEF_D1_9    DEF_D1_8    DEF_D1_7    DEF_D1_6    DEF_D1_5    DEF_D1_4    DEF_D1_3    DEF_D1_2        DEF_D1_1
*NYBRO.S01.T001.DF_QUANT       0.82        0.84        0.88        0.92        0.96        0.98        0.99        0.995           1



*TABLE DEF_STEPS
*                             DEF_D1_9    DEF_D1_8    DEF_D1_7    DEF_D1_6    DEF_D1_5    DEF_D1_4    DEF_D1_3    DEF_D1_2        DEF_D1_1
*NYBRO.S01.T001.DF_QUANT       0.82        0.84        0.88        0.92        0.96        0.98        0.99        0.995           1