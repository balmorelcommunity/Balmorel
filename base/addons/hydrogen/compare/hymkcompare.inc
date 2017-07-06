* File hymkcompare.inc.
* This file is part of the redesigned welfare module for Balmorel.
* This concerns the hydrogen addon.
* Author: Lars Bregnbæk
* Revision: 1.0 LB

* This file adds hydrogen related accounting elements to the output.

put        file_h2_rev        ;
Put "Revenue for hydrogen sales"/;
$libinclude gams2tbl h2_rev

put        file_h2_ehfuelC        ;
Put "Cost of hydrogen as fuel for electricity and heat generation"/;
$libinclude gams2tbl h2_ehfuelC




