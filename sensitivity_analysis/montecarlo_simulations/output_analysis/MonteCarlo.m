%% Step 3. Perform the Monte Carlo simulations. 
% In this step, N model simulations are performed using the sampling
% matrix from the LHS (Xval) and the model outputs are recorded in a
% matrix form to be processed in the next step.
% As the model is written in Gams and this code in Matlab and both codes
% were kept separately, this step has been done independently in GAMS and
% the results of the simulation are mannually imported
% Amalia Pizarro Alonso (October, 2016)

close all
clear
clc

%% Import simulation data from GAMS (gdx file that has been exported to excel files)
addpath('./input/');

y1MC=importdata('systemcosts.xlsx')*1.73345;  %A multiplication factor is used for unit conversions
y2MC=importdata('electricityprice.xlsx');
y3MC=importdata('input/DHprice.xlsx');
yMC=[y1MC y2MC y3MC];

%y2MC_uniform=importdata('./input/electricitypriceMC_uniform.xlsx');
%y3MC_uniform=importdata('./input/DHpriceMC_uniform.xlsx');


timeMC=importdata('./input/timeBalmorel.xlsx');
%Electricity_priceMC_t=importdata('./input/Electricity_priceMC_t.xlsx');


%% Step 4. Review and analyse of the results from Monte Carlo simulations.
% In this step, the outputs are plotted and the results are statiscally analysed. 

fs=12; %Size of the font

% figure(1) % Create a new figure window
% plot(timeMC,Electricity_priceMC_t,'LineWidth',0.3)
% axis([0 73 -10 150])
% xlabel('Time (h)','FontSize',fs,'FontWeight','bold') 
% ylabel('Electricity Price (€/MWh)','FontSize',fs,'FontWeight','bold') 
% set(gca,'LineWidth',2,'FontSize',15,'FontWeight','bold') 
% saveas(1,'Figure1_MC','tiff')

% figure(2) % Create a new figure window
% y95=1.645*std(Electricity_priceMC_t');
% ym=mean(Electricity_priceMC_t');
% plot(timeMC,ym,'k',timeMC,ym+y95,'--r',timeMC,ym-y95,'--r')
% axis([0 73 -10 150])
% xlabel('Time (h)','FontSize',fs,'FontWeight','bold') 
% ylabel('Electricity Price (€/MWh)','FontSize',fs,'FontWeight','bold') 
% set(gca,'LineWidth',2,'FontSize',15,'FontWeight','bold') 
% saveas(2,'Figure2_MC','tiff')

%Perform the statistical analysis for the other output variables
yMC_95=1.645*std(yMC);
yMC_m=mean(yMC);
Uncertainty_Range=((yMC_m+yMC_95)./yMC_m)-1;

xdata=1; %This factor is only introduced for graphical purpose

figure(3)

hold on
subplot(2,5,1)
xlabel1={'Total{ }Costs{ }(€/year)'};
plot(xdata,yMC_m(1), 'rd',xdata,yMC_m(1)+yMC_95(1),'bv',xdata,yMC_m(1)-yMC_95(1),'b^')
axis([0.5 1.5 0 5E10])
set(gca, 'Xtick', xdata, 'XtickLabel', xlabel1)

subplot(2,5,2)
xlabel2={'Electricity{ }Price{ }(€/MWh)'};
plot(xdata,yMC_m(2), 'rd',xdata,yMC_m(2)+yMC_95(2),'bv',xdata,yMC_m(2)-yMC_95(2),'b^')
axis([0 2 0 90])
set(gca, 'Xtick', xdata, 'XtickLabel', xlabel2)

subplot(2,5,3)
xlabel3={'DH{ }Price{ }(€/MWh)'};
plot(xdata,yMC_m(3), 'rd',xdata,yMC_m(3)+yMC_95(3),'bv',xdata,yMC_m(3)-yMC_95(3),'b^')
axis([0 2 0 90])
set(gca, 'Xtick', xdata, 'XtickLabel', xlabel3)
hold off;
saveas(3,'./output/Figure3_MC','tiff');

figure(4)
[h_Elec]=histogram(y2MC);
HX_elec=h_Elec.BinEdges(1:h_Elec.NumBins);
HY_elec=h_Elec.Values/length(y2MC);
[h_DH]=histogram(y3MC);
HX_DH=h_DH.BinEdges(1:h_DH.NumBins);
HY_DH=h_DH.Values/length(y3MC);


hold on
subplot(1,2,1)
bar(HX_elec,HY_elec)
xlabel('Electricity Price (€/MWh)','FontSize',fs,'FontWeight','bold') 
ylabel('Probability','FontSize',fs,'FontWeight','bold'); 

subplot(1,2,2)
bar(HX_DH,HY_DH)
xlabel('District Heating Price (€/MWh)','FontSize',fs,'FontWeight','bold') 
ylabel('Probability','FontSize',fs,'FontWeight','bold') 
hold off
;
saveas(4,'./output/Figure4_MC','tiff')

Skew_YMC=skewness(yMC);

% figure
% hold on
% subplot(1,2,1)
% hold on
% cdfplot(y2MC)
% cdfplot(y2MC_uniform)
% cdf_2MC = cdfplot(y2MC);
% cdf_2MC_uniform = cdfplot(y2MC_uniform);
% set(cdf_2MC,'LineWidth',4);
% set(cdf_2MC_uniform,'LineWidth',1);
% xlabel('Electricity Price (€/MWh)','FontSize',fs,'FontWeight','bold') 
% ylabel('Probability','FontSize',fs,'FontWeight','bold'); 
% axis([min(y2MC) max(y2MC) -0.04 1.04])
% set(gca,'LineWidth',1);
% hold off
% 
% subplot(1,2,2)
% hold on
% cdfplot(y3MC)
% cdfplot(y3MC_uniform)
% cdf_3MC = cdfplot(y3MC);
% cdf_3MC_uniform = cdfplot(y3MC_uniform);
% set(cdf_3MC,'LineWidth',4);
% set(cdf_3MC_uniform,'LineWidth',1);
% xlabel('District Heating Price (€/MWh)','FontSize',fs,'FontWeight','bold') 
% ylabel('Probability','FontSize',fs,'FontWeight','bold') 
% axis([min(y3MC) max(y3MC) -0.04 1.04])
% set(gca,'LineWidth',1);
% hold off;







