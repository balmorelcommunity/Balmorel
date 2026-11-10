# EV charging infrastructure is sized only in investment runs

Charging infrastructure is an investment decision, so only investment runs (`TechInvest`) size it and export it to simex. Operational runs fix it and can exceed the G2V capacity only through a slack priced at `PENALTYQ`. Investment runs usually have fewer time periods than operational runs, so they build G2V capacity `EV_G2V_INFRA_MARGIN` (5 %) above the highest charging they see; without the margin, operational runs hit the slack.
