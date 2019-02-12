%% Performing sensitivity analysis using Morris method
%% global script executing the workflow in Morris method
%% Gurkan Sin DTU Chemical Engineeirng
%% June 24, 2015 DTU Lyngby
%% Adapted by Amalia Pizarro-Alonso for performing a Morris screening for the energy system model Balmorel (October, 2016)
%% This code has been modified for the final exercise of the course XXXX Uncertainty and S..., taught by Gurkan Sin (August, 2016)

close all
clear all
clc

%% Initial conditions
% Set the initial conditions in the initcond file. This same file you can
% also use it in the Monte Carlo simulation. Go to the file to know exactly
% what is required

%% Step 1: perform Morris sampling
%In that file, the assumptions regarding parameters, names, values and
%range of uncertainty are defined - please open it in Matlab and modify
%the selected parameters, as well as the file related to initial conditions
%Afterwards, the specific procedure for conducting Morris sampling is
%applied. Some parameters regarding the type of Morris sampling are
%required.
disp('Step 1: perform Morris sampling')
morrissampling

%save output from Morris Sampling
fl =strcat('output/','MorrisSampling_r',num2str(r),'_p',num2str(p),'.mat');
save(fl, 'Xval', 'X','p','dt','r','xl','xu','k','lp','pmor')


%% Step 2. Perform simulations with Morris Samples GAMS-Matlab
%The values you need to transfer are the Xval values, where the column
%represent the parameter (as defined in initcond) and the row represents a
%simulation run (i.e. a scenario) with the levels of the parameters as
%indicated in that row. Go to Balmorel and run the simulations through a
% loop or the GUSS function.
disp('step 2: perform simulations with Morris Samples GAMS-Matlab')
