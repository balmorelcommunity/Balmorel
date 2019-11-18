* Transmission ramping by Juan Gea Bermúdez 2019.


SCALAR X_RAMP 'Hourly ramping limit of transmission lines. A value of 1 means that it takes 1 hour to switch from full power in one direction to full power in the other direction. A value of 2 means it takes 0.5 hours, etc.'  %semislash%
$if     EXIST '../data/TRANSMISSION_RAMPING_X_RAMP' $INCLUDE         '../data/TRANSMISSION_RAMPING_X_RAMP.inc';
$if not EXIST '../data/TRANSMISSION_RAMPING_X_RAMP.inc' $INCLUDE '../../base/data/TRANSMISSION_RAMPING_X_RAMP.inc';
%semislash%;


