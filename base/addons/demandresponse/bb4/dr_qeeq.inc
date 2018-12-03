* inclusion of demand response in electricity balance

* Downward regulation for DR shed technologies:
-       SUM(IADR(IY411,IA,DR_TECH_SHED)$RRRAAA(IR,IA), VDR_DOWN(IY411,IA,DR_TECH_SHED,IS3,T))

* Balance between upward and downward regulation for DR shift technologies:
*TODO - efficiency
-       SUM(IADR(IY411,IA,DR_TECH_SHIFT)$RRRAAA(IR,IA), VDR_DOWN(IY411,IA,DR_TECH_SHIFT,IS3,T)) + SUM(IADR(IY411,IA,DR_TECH_SHIFT)$RRRAAA(IR,IA), VDR_UP(IY411,IA,DR_TECH_SHIFT,IS3,T))

