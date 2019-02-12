
%% Morris screening method
% Refs: Morris, 1991 and Campolongo and Saltelli, 1997
% This script performs morris sampling of parameter space needed for the
% morris screening method.
%
% Gurkan Sin, PhD
% Updated DTU Chemical Engineering July 11 2015
% Adapted by Amalia Pizarro Alonso for using it in the energy systems model
% Balmorel
% 
%% Parameters range
%Write how many paremeters and the names of the parameters whose
%uncertainty range you want to evaluate through Morris screening

%Write the selected parameters and their reference value, as already
%indicated in the input file

addpath('.\input\');
initcond

pmor=par(1:length(par)); % get the reference parameter values from the initcond file, this means we will look at the 27 parameters defined

% The name lp is the name you will have in legends, so write the name as
% you wish it to appear in Figures (use subscripts or superscripts for nicer names)  

lp = {'FLH WIND ON DK','FLH WIND OFF DK','FLH WATER NO','FLH WATER SE','FLH PV',...
       'CPX PV 2020','CPX PV 2030','CPX Wind Onshore 2020',...
       'CPX Wind Onshore 2030','CPX Wind Offshore 2020','CPX Wind Offshore 2030',...
       'CPX ST BP STR 2020','CPX ST BP STR 2030','CPX ST BP MW 2020',...
       'CPX ST BP MW 2030','CPX ST CND CO 2020','CPX ST CND CO 2030','CPX GT CND NG 2020',...
       'CPX GT CND NG 2030','CPX GTCC EXT NG 2020','CPX GTCC EXT NG 2030',...
       'CPX GTCC BP NG 2020','CPX GTCC BP NG 2030','CPX ENG EXT NG 2020',...
       'CPX ENG EXT NG 2030','CPX HP EL 2020','CPX HP EL 2030',...
       'PR CO2 2020','PR CO2 2030','PR NG 2020','PR NG 2030','PR CO 2020','PR CO 2030','PR WP 2020',...
       'PR WP 2030','PR STR 2020','PR STR 2030','PR WC 2020','PR WC 2030',...
       'TRANS','DE DK 2020','DE DK 2030','DE NO 2020','DE NO 2030','DE SE 2020',...
       'DE SE 2030','DE GER 2020','DE GER 2030','DH_DK_2020','DH_DK_2030','NUC','DR'}; %These names are the same that the ones used in the report

%This parameter is not used, in this case but you could use it if you wish
%to set an uncertainty range in % from the reference value, rather an a lower and upper range
inputunc=[0.25 0.10]; % expert input uncertainty indicates degree of uncertainty [0: Low , 1: High]
k=length(pmor); % number of parameters
%xl= pmor .* (ones(1,k)-inputunc);
%xu= pmor .* (ones(1,k)+inputunc);

%Write the uncertainty range
%Lower limit:
xl=[0 0 0 0 0 0.936 0.436 0.860 0.796 2.675 2.357 1.108 1.062 1.108 1.062 0.764 0.733 0.382 0.366 0.764 0.733 1.051 0.987 0.860 0.828 0.478 0.478 15.494 27.027 5.630 7.669 1.704 1.674 7.700 7.700 5.200 5.300 5.700 5.900 0.5 23586213.62 24643438.71 84629438.86 87863171.72 99023225.49 103316214.6 397186400.8 411568308.9 26502747.42 32380279.66 0 0.03];
%Upper limit
xu=[0 0 0 0 0 1.144 0.809 1.051 1.019 3.249 3.026 1.357 1.332 1.357 1.332 1.720 1.688 0.860 0.844 1.147 1.115 1.720 1.656 1.051 1.051 0.955 0.955 18.018 90.090 5.956 9.056 1.909 2.350 9.000 9.500 6.400 7.200 7.100 8.000 0.9 39310356.03 41072397.84 141049064.8 146438619.5 165038709.1 172193691.1 661977334.7 685947181.5 44171245.7 53967132.76 7146 0.05];

%Select which parameters have a normal distribution, and which ones a
%uniform one.
pmor_normal=([1:5]);
pmor_unif=([6:length(xu)]);
%sigma_pmor(pmor_normal)=(pmor(pmor_normal)-xl(pmor_normal))./2; %A number of 2 has been assumed because is it considered that the lower range represents a 95.6% confidence interval
sigma_pmor(pmor_normal)=[212.665 280.625 367.495 416.338 115.151];
%% Morris sampling parameters
% You need to specify "p" and "r", depending on the number of simulations
% you wish to conduct (computational limitations), but also knowing the
% disadvantages from decreasing sampling scenarios.
k = length(pmor) ; % no of parameters or factors
p = 6 ; % number of levels {4,6,8}
dt = p/(2*(p-1)) ; % perturbation factor .
r = 100; % number of repetion for calculating the EEi, e.g. 4 - 15

%% Morris sampling will produce discrete uniform probabilities for each
% factor.
X = morris(p,dt,k,r);
Xmean = mean(X) ;

%% from uniform distribution [0 1] to real values
Xnorm=X;

Xnorm(Xnorm==0)=0.01;
Xnorm(Xnorm==1)=0.99;

for i=1:length(X)
  Xval(i,pmor_normal) =norminv(Xnorm(i,pmor_normal),pmor(pmor_normal),sigma_pmor(pmor_normal));  
  Xval(i,pmor_unif) = xl(pmor_unif) + (xu(pmor_unif)-xl(pmor_unif)).*X(i,pmor_unif) ;
end

%% Plot Morris sampling results for the visualization
%Note: it can take a long time to run this section (by default not
%activated

% figure(1)
% [h,ax,bax,P] = plotmatrix(X) ;
% set(ax,'FontSize',6)
% for i=1:k
% ylabel(ax(i,1),lp(i))
% xlabel(ax(k,i),lp(i))
% end
% title(['Morris Sampling with r=', num2str(r),', p=',num2str(p),' levels,',' and \Delta =',num2str(dt,'%5.2f'),': unit range'])
% 
% figure(2)
% [h,ax,bax,P] = plotmatrix(Xval) ;
% set(ax,'FontSize',6)
% for i=1:k
% ylabel(ax(i,1),lp(i))
% xlabel(ax(k,i),lp(i))
% end
% title(['Morris Sampling with r=', num2str(r),', p=',num2str(p),' levels,',' and \Delta =',num2str(dt,'%5.2f'),': real values'])

