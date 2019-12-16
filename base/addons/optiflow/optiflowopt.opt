* File optiwastegams.opt to the OptiWaste model.
* This file contains Optiwaste options.
* This file is part of the OptiWaste model, version ....

*-------------------------------------------------------------------------------
* Input data files format:
*-------------------------------------------------------------------------------
* Option semislash is used to control input data format for text files
* for sets and parameters/tables (not for acronyms).
* With "$Setglobal semislash ;" the input files must include
* the declaration statement initially and must terminate with a "/;".
* With "$Setglobal semislash /" the input files do not contain this, but only data.
* Note that parameters and tables are identical declarations, however,
* when using "$Setglobal semislash /" make sure
* that the use of either "parameter" or "table" in Balmorel.gms for any data file
* corresponds to the data format used in the file.
$Setglobal semislash ";"
*!optiononly ;
*!option ;
*-------------------------------------------------------------------------------
* End: Input data files format
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
* Addon APKNdisc: discrete size investments in PROC.
$setglobal APKNdisc
*!option yes
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
* Energy system modeling:
*-------------------------------------------------------------------------------


* Option enersys indicates if the energy system is modeled otherwise than as marginal values for electricity, heat and gas.
* Presently MUST BE  ''
$setglobal enersys  ''
*! option yes

$setglobal inv yes
*! option yes

$setglobal enersys

$setglobal solveOptiFlowmip yes


*-------------------------------------------------------------------------------
* End: Energy system modeling
*-------------------------------------------------------------------------------


*-------------------------------------------------------------------------------
* Debug possibilities:
*-------------------------------------------------------------------------------
$Setglobal addEPStoL
*! option yes

* Not needed if there are no capacity bounds on internal proc
* It will be needed if there are capacity bounds on some internal proc, therefore add them only in that case (requires some coding, TODO).
* With such minimal use the infeasibilities will be moved to SOSIBU proc whenever possible.
$Setglobal useQNODEslack
*! option

$Setglobal useSSBslack
*! option yes

$Setglobal useShareSlack
*! option yes

* Option uniquesol permit to use quadratic terms in QOBJ in order to attain unique solution.
* Should be used for debug on small systems only.
$Setglobal uniquesol
*! option yes

* Testing ONLY:
$setglobal singlearea
*! option yes

* Testing ONLY:
$setglobal addUP
*! option yes


*-------------------------------------------------------------------------------
* End Debug possibilities
*-------------------------------------------------------------------------------



