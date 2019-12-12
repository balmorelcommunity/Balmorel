Parameter HYDROGEN_H2TOF(GGG) 'Factor for need of hydrogen for fuel production'
*Factor: Energy content of hydrogen required for energy content of input BIOGAS or THERMGAS (MWh hydrogen input /MWh BIOGAS or THERMGAS input)
* Source: Mathiesen, B. V., Connolly, D., Lund, H., Nielsen, M. P., Schaltz, E., Wenzel, H., ... Hansen, K. (2014). CEESA 100% Renewable Energy Transport Scenarios towards 2050: Technical Background Report Part 2. Department of Development and Planning, Aalborg University.
* Source: BIOGAS_H2 p.56 Fig.42 / THERMGAS_H2 p.55 Fig.41
* Note: Factor for Biogas_up from Technology data for advanced bioenergy fuels
*Note: Electricity input for the compressor is not taken into account, it is minor
*Question: Do we also need the factor from energy content intput to energy content output?
*                                                                                                                                                                                                                                                                                                          Biomass Hydrogen Methane
*BIOGAS_H2                                                                                                                                                                                                                                                                        1                   *    54      54       100
*THERMGAS_H2                                                                                                                                                                                                                                                                      0.923076923076923   *    58.5    54       100
;
HYDROGEN_H2TOF(GGG)$(GDATA(GGG,'GDFUEL') eq BIOGAS_H2)=1.08;
HYDROGEN_H2TOF(GGG)$(GDATA(GGG,'GDFUEL') eq THERMGAS_H2)=1.02;
