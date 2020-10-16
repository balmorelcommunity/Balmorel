** declaring internal sets

SET DR_TECH_SHIFT(DR_TECH)'Shifting demand response technology'
SET DR_TECH_SHED(DR_TECH) 'Shedding demand response technology'

SET DR_TECH_USER(DR_TECH,DEUSER)

SET IADR(Y,AAA,DR_TECH)  'Set of areas and demand side management technologies in the simulation';

SET DR_TECH_INVEST(DR_TECH) 'demand response technologies that can be invested in';
** Defining internal sets

* DR tech is SHED or SHIFT
DR_TECH_SHIFT(DR_TECH) = YES$(DR_DATA(DR_TECH,'DRTYPE') eq 2);
DR_TECH_SHED(DR_TECH) = YES$(DR_DATA(DR_TECH,'DRTYPE') eq 1);

* Relationship between DR_TECH and Balmorel user group
DR_TECH_USER(DR_TECH,'RESE') = YES$(DR_DATA(DR_TECH,'DRUSER') eq 1);
DR_TECH_USER(DR_TECH,'OTHER') = YES$(DR_DATA(DR_TECH,'DRUSER') eq 3);
DR_TECH_USER(DR_TECH,'PII') = YES$(DR_DATA(DR_TECH,'DRUSER') eq 2);

DR_TECH_INVEST(DR_TECH)$DR_DATA(DR_TECH,'DRINVCOST') = YES;
$ifi %import_results%==YES $ifi %ADDTECHDEV%==yes DR_TECH_INVEST(DR_TECH) = NO;

