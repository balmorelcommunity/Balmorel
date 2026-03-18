SET IHASBEV(RRR)  "Internal set: region has BEV demand";
SET IHASPHEV(RRR)  "Internal set: region has PHEV demand";

* If the sum =/= 0 then YES
* Used as condition in calculations, to reduce computational time.
IHASBEV(IR) = YES$(SUM((Y,S,T), EV_BEV_available(Y,IR)) > 0);
IHASPHEV(IR) = YES$(SUM((Y,S,T), EV_PHEV_available(Y,IR)) > 0);