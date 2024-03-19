*Industry add-on. Implemented by Juan Gea Bermudez 2019

*$onmulti
*$if     EXIST '../data/INDUSTRY_XHLOSS.inc' $INCLUDE         '../data/INDUSTRY_XHLOSS.inc';
*$if not EXIST '../data/INDUSTRY_XHLOSS.inc' $INCLUDE '../../base/data/INDUSTRY_XHLOSS.inc';
*$offmulti