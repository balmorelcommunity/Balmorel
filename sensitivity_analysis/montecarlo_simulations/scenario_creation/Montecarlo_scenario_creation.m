%% Sampling strategies: Stratified random (LHS) for Monte Carlo Simulation
%Code provided by Gurkan Sin during the course XXXX (August, 2016)
%Modified by Amalia Pizarro Alonso for the preparation of the report for
%the abovementioned course
%it is all above how you subsample from the k dimensional (continous) input space.
clear all
clc
close all

%% Parameters range, as specified for the Global Sensitivity Analysis, no change needed 
addpath('.\input\');
initcond

lp = {
    'FLH WIND ON DK','FLH WIND OFF DK','FLH WATER NO','FLH WATER SE','FLH PV',...
       'CPX PV 2020','CPX PV 2025','CPX PV 2030','CPX Wind Onshore 2020','CPX Wind Onshore 2025',...
       'CPX Wind Onshore 2030','CPX Wind Offshore 2020','CPX Wind Offshore 2025','CPX Wind Offshore 2030',...
       'CPX ST BP STR 2020','CPX ST BP STR 2025','CPX ST BP STR 2030','CPX ST BP MW 2020','CPX ST BP MW 2025',...
       'CPX ST BP MW 2030','CPX ST CND CO 2020','CPX ST CND CO 2025','CPX ST CND CO 2030','CPX GT CND NG 2020',...
       'CPX GT CND NG 2025','CPX GT CND NG 2030','CPX GTCC EXT NG 2020','CPX GTCC EXT NG 2025','CPX GTCC EXT NG 2030',...
       'CPX GTCC BP NG 2020','CPX GTCC BP NG 2025','CPX GTCC BP NG 2030','CPX ENG EXT NG 2020','CPX ENG EXT NG 2025',...
       'CPX ENG EXT NG 2030','CPX HP EL 2020','CPX HP EL 2025','CPX HP EL 2030','CPX BO NG 2020','CPX BO NG 2025','CPX BO NG 2030'}; %These names are the same that the ones used in the report

%Lower limit:
xl=[0 0 0 0 0 0.936 0.644 0.436 0.860 0.828 0.796 2.675 2.516 2.357 1.108 1.085 1.062 1.108 1.085 1.062 0.764 0.748 0.733 0.382 0.374 0.366 0.764 0.748 0.733 1.051 1.019 0.987 0.860 0.844 0.828 0.478 0.478 0.478 0.033 0.033 0.033];
%Upper limit
xu=[0 0 0 0 0 1.144 0.966 0.809 1.051 1.035 1.019 3.249 3.137 3.026 1.357 1.344 1.332 1.357 1.344 1.332 1.720 1.704 1.688 0.860 0.852 0.844 1.147 1.131 1.115 1.720 1.688 1.656 1.051 1.051 1.051 0.955 0.955 0.955 0.239 0.239 0.239];



%% Sampling method: Latin Hypercube sampling 
%n. of parameters selected with Morris screening, only those that have an
%importance
pMC=par([1 2 6 7]);
xlMC=xl([1 2 6 7]);
xuMC=xu([1 2 6 7]);
lpMC=lp([1 2 6 7]);

pmor_normal=([1:2]);
pmor_unif=([3:4]);
%sigma_pmor(pmor_normal)=(pMC(pmor_normal)-xlMC(pmor_normal))./2; %A number of 2 has been assumed because is it considered that the lower range represents a 95.6% confidence interval
sigma_pmor(pmor_normal)=[213 281];

k=length(pMC);

%n. of sample points, please select how many Monte Carlo simulations you
%want to perform, based on the number of parameters you are considering and
%the the computational constraints.
N=300;

X = lhs(N, k);

%% Now we will calculate the sample metdhology with real values
%From uniform distribution [0 1] to real values
Xnorm=X;
Xnorm(Xnorm==0)=0.01;
Xnorm(Xnorm==1)=0.99;

for i=1:N
  Xval(i,pmor_normal) =norminv(Xnorm(i,pmor_normal),pMC(pmor_normal),sigma_pmor(pmor_normal));  
  Xval(i,pmor_unif) = xlMC(pmor_unif) + (xuMC(pmor_unif)-xlMC(pmor_unif)).*X(i,pmor_unif) ;
end

%save output
fl =strcat('./output/','LHS_Sampling_k',num2str(k),'_N',num2str(N),'.mat');
save(fl, 'Xval', 'X','N','xlMC','xuMC','k','lpMC','pMC')

%% Plot of the results
%Note: Plotting the results can take quite some time, by default not
%activated

% figure(1)
% [h,ax,bax,P] = plotmatrix(X) ;
% set(ax,'FontSize',8)
% for i=1:k
% ylabel(ax(i,1),lpMC(i));
% xlabel(ax(k,i),lpMC(i));
% end
% title(['Latin Hypercube Sampling for k input ',num2str(k),' with sampling number N = ',num2str(N)])
% 
% figure(2)
% [h,ax,bax,P] = plotmatrix(Xval) ;
% set(ax,'FontSize',10)
% for i=1:k
% ylabel(ax(i,1),lpMC(i));
% xlabel(ax(k,i),lpMC(i));
% end
% title(['Latin Hypercube Sampling for k input ', num2str(k),' with sampling number  N = ',num2str(N),' and real values'])

%% Step 3. Perform the Monte Carlo simulations. 
% In this step, N model simulations are performed using the sampling
% matrix from the LHS (Xval) and the model outputs are recorded in a
% matrix form to be processed in the next step.
% As the model is written in Gams and this code in Matlab and both codes
% were kept separately, this step has been done independently in GAMS and
% the results of the simulation are mannually imported
% Amalia Pizarro Alonso (October, 2016)

