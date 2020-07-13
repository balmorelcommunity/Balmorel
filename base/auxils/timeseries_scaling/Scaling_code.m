% When applying this method, mind to reference the following paper which describes the methodology: 
% J.  Gea-Bermúdez et al.  Optimal  generation  and  transmission  development  of  the  north  sea  region:  
% Impact of  grid  architecture  and  planning  horizon,  Energy  191  (2020)  
% https://doi.org/10.1016/j.energy.2019.116512

clear all;
clc;
close all;
delete Output\*.xlsx %All excel files in the output are deleted to avoid overwritting issues

%INPUTS
%----------------------------------------------
%file name and sheet 
input_file_name = 'Input\Time_Series.xlsx';

%Selected S
Selected_S=readtable('Input\Selected_S.csv');

%Selected T
Selected_T=readtable('Input\Selected_T.csv');

%Plotting allowed (1 means yes, 0 means no)?
plotting=0;
%----------------------------------------------

[status,sheets,xlFormat] = xlsfinfo(input_file_name);
sheets=string(sheets);

iteration=1;
for j=1:length(sheets)

%Sheet name
input_sheet_name = sheets(j);
fprintf('Sheet %s is being processed. \n', input_sheet_name)

%Output file name
outputfilename = append('Output\',sheets(j),'.xlsx');

T_fullYear = readtable(input_file_name, 'Sheet', input_sheet_name);
T_fullYear.SEASON = categorical(T_fullYear.SEASON);
T_fullYear.TIME = categorical(T_fullYear.TIME);

if iteration ==1
    iteration=0;
    count=1;
    for i=1:size(T_fullYear,1) 
        S=string(T_fullYear.SEASON(i));
        T=string(T_fullYear.TIME(i));
        if sum(contains(string(Selected_S.SELECTED_S(:,1)),S)) == 1
                index_full(count,1)=1;
            if sum(contains(string(Selected_T.SELECTED_T(:,1)),T)) == 1
                index(count,1)=i;
                count=count+1;
            end
        end
    end
end

T_sel_weeks=T_fullYear(index,:);
T_sel_weeks_scaled = T_sel_weeks;

if plotting==1
    T_sel_weeks_full=T_fullYear(index_full,:); 
end

for i=3:size(T_fullYear,2)

x_f = T_fullYear{:,i};
x_sel_orig=T_sel_weeks{:,i};
if plotting==1
    x_sel_orig_full=T_sel_weeks_full{:,i}; 
end

if max(x_f) == min(x_f)
    T_sel_weeks_scaled{:,i}=x_sel_orig;
    continue
end

OBJ_target = paretotails(x_f, 0, 1); % ECDF fit (full)
u_f = OBJ_target.cdf(x_f);

OBJ_short = paretotails(x_sel_orig, 0, 1); % ECDF fit (original week selection)
u_sel_orig = OBJ_short.cdf(x_sel_orig);

x_sel_scaled = OBJ_target.icdf(u_sel_orig);

%Additional filter since GAMS does not accept numbers with many decimals
x_sel_scaled(x_sel_scaled < 0) = 0;
x_sel_scaled(x_sel_scaled < 1e-12) = 0;

max_original=max(x_f);
x_sel_scaled(x_sel_scaled > max_original)=max_original;


T_sel_weeks_scaled{:,i}=x_sel_scaled;


if plotting==1
figure
subplot(1,2,1);
figure;
histogram(x_f, 15, 'Normalization', 'pdf','DisplayStyle','stairs','EdgeColor','b')

hold all
histogram(x_sel_orig, 15, 'Normalization', 'pdf','DisplayStyle','stairs','EdgeColor','m')

hold all
histogram(x_sel_scaled, 15, 'Normalization', 'pdf','DisplayStyle','stairs','EdgeColor','r')
legend('Original timeseries','Original selected timeseries', 'Scaled selected timeseries')
title('Histogram')
xlabel('Standardized generation');
ylabel('PDF');
mean(x_sel_scaled)
std(x_sel_scaled)
prctile(x_sel_scaled, [5, 95])
max(x_sel_scaled)


scatterhist(x_sel_orig, x_sel_scaled)
xlabel('Selected week orig');
ylabel('Selected week scaled')
t=1:1:50;
t2=1:2:49;


subplot(1,2,2);
figure;
plot(t,x_sel_orig_full(1:50));
hold all
plot(t2,x_sel_scaled(1:25),':rs');
legend('Original timeseries', 'Scaled selected timeseries')
title('Timeseries');
xlabel('Time (hour)');
ylabel('Standardized generation');


figure;
ksdensity(diff(x_f));
std(diff(x_f))
hold all
ksdensity(diff(x_sel_scaled));
legend('Full', 'Selected week scaled')
std(diff(x_sel_scaled))
end

end
writetable(T_sel_weeks_scaled,outputfilename);

%Modify headers because Matlab might have converted them
headers=T_sel_weeks_scaled.Properties.VariableDescriptions;
headers(cellfun(@isempty,headers))=T_sel_weeks_scaled.Properties.VariableNames(cellfun(@isempty,headers));
headers=strrep(headers,"'",'');
headers=strrep(headers,"Original column heading: ",'');
headers=cellstr(headers);
writecell(headers,outputfilename,'Range','A1');

clear T_fullYear
end
