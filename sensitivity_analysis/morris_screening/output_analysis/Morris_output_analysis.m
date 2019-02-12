%% Performing sensitivity analysis using Morris method
%% global script executing the workflow in Morris method
%% Gurkan Sin DTU Chemical Engineeirng
%% June 24, 2015 DTU Lyngby
%% Adapted by Amalia Pizarro Alonso for performing a Morris screening for the energy system model Balmorel (October, 2016)
%% This code has been modified for the final exercise of the course XXXX Uncertainty and S..., taught by Gurkan Sin (August, 2016)

close all
clear
clc

%Load the previous results from the file MorrisBalmorelinput
%Please be sure of setting the right name of the file, otherwise a
%mathematical formulation could also be applied
%What parameters are loaded are defined in the aforementioned file

addpath('.\input\');
load xval

%%%%%%

%Plot matrix of input data
%It can take a lot of time to run so by default not activated

% figure(1)
% [h,ax,bax,P] = plotmatrix(Xval) ;
% set(ax,'FontSize',6)
% for i=1:k
% ylabel(ax(i,1),lp(i))
% xlabel(ax(k,i),lp(i))
% end
% title(['Morris Sampling with r=', num2str(r),', p=',num2str(p),' levels,',' and \Delta =',num2str(dt,'%5.2f'),': real values'])


%% Step 2: perform simulations with Morris Samples GAMS-Matlab
disp('step 2: perform simulations with Morris Samples GAMS-Matlab')
%As the Balmorel model is implemented in GAMS an in order to avoid a higher complexity of the model
%Linkage of the Matlab resuls and GAMS is done manually
%Therefore simulation results have to be loaded in this step

y1=importdata('El_price_2020_GSA.xlsx');
y2=importdata('El_price_2030_GSA.xlsx');


%% Step 3: visualize the simulation results
disp('Step 3: visualize the simulation results')

%TBD

%% step 4: compute Elementary Effects, EEi
% Open the file and specify which results you are looking at(var parameter)
% You might want to change the way in which Elementary Effects are display,
% depending on the number of parameters you have. Please make sure this
% satisfy your needs and aesthetic preferences
disp('step 4: compute Elementary Effects, EEi')
computeEEi

%saving figures
drn='./output/figures/step4';
mkdir(drn)
f4s=2+ll*3;
for i=1:f4s
    fg = strcat(['ElementaryEffects',num2str(i),'_',datestr(date,'ddmmmyy')]);
    f1 = fullfile(pwd,drn,fg) ;
    saveas(i,f1,'tiff') ;
end
%% step 5: interpret the results by viewing the sigma versus mean values of
%%EEi - this step is done manually by the user.