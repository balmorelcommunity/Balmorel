# One yearly CO2 storage limit for the whole model, not used in rolling runs

`CCS_STORAGE_MAX(Y)` limits all CO2 captured in a year across all countries, because storage sites and CO2 transport are shared across borders. Balmorel has no CO2 utilisation, so everything captured, BECCS included, counts as stored and pays transport, storage and compression. Rolling runs leave the limit out: each season is solved and annualised on its own, so an annual limit can't be split into seasons without prescribing when CCS runs.
