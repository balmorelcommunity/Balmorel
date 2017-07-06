* File hycompprint1.inc.
* This file is part of the redesigned welfare module for Balmorel.
* This concerns the hydrogen addon.
* Author: Lars Bregnbæk
* Revision: 1.0 LB

File file_h2_rev /..\compare\%CASEID% h2_rev.med/;
File file_h2_ehfuelC /..\compare\%CASEID% h2_ehfuelC.med/;
File file_h2_tcosts /..\compare\%CASEID% h2_tcosts.med/;

Parameters
         h2_rev(Y,C)       'Revenue for hydrogen sales'
         h2_ehfuelC(Y,C)   'Cost of hydrogen as fuel for electricity and heat generation'
;