clear all;
clc;
close all;

%INPUTS
%----------------------------------------------
%file name and sheet 
input_file_name = 'Input\Time_Series.xlsx';

%thinning of timeslices within each season
thinning_value = 3;

%Number of seasons (1 to X)
number_of_seasons = 12;
%----------------------------------------------

[status,sheets,xlFormat] = xlsfinfo(input_file_name);
sheets=string(sheets);

for j=1:length(sheets)


%Sheet name
input_sheet_name = sheets(j);
fprintf('Sheet %s is being processed. \n', input_sheet_name)

%Output file name
outputfilename = append('Output\',sheets(j),'.xlsx');

T_fullYear = readtable(input_file_name, 'Sheet', input_sheet_name);
T_fullYear.SEASON = categorical(T_fullYear.SEASON);
T_fullYear.TIME = categorical(T_fullYear.TIME);

%add more elseif statements to 
if number_of_seasons == 1
    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S23', :);
elseif number_of_seasons == 2
    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S16' | T_fullYear.SEASON == 'S40', :);
elseif number_of_seasons == 3
    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S16' | T_fullYear.SEASON == 'S25' | T_fullYear.SEASON == 'S40', :);
elseif number_of_seasons == 4
    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S02' | T_fullYear.SEASON == 'S16' | T_fullYear.SEASON == 'S25' | T_fullYear.SEASON == 'S40', :);
elseif number_of_seasons == 5
    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S03' | T_fullYear.SEASON == 'S09' | T_fullYear.SEASON == 'S37' | T_fullYear.SEASON == 'S44' | T_fullYear.SEASON == 'S51', :);
elseif number_of_seasons == 6
    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S03' | T_fullYear.SEASON == 'S09' | T_fullYear.SEASON == 'S16' | T_fullYear.SEASON == 'S23' | T_fullYear.SEASON == 'S44' | T_fullYear.SEASON == 'S51', :);
elseif number_of_seasons == 7
    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S03' | T_fullYear.SEASON == 'S09' | T_fullYear.SEASON == 'S16' | T_fullYear.SEASON == 'S23' | T_fullYear.SEASON == 'S37' | T_fullYear.SEASON == 'S44' | T_fullYear.SEASON == 'S51', :);
elseif number_of_seasons == 8
%    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S02' | T_fullYear.SEASON == 'S08' | T_fullYear.SEASON == 'S15' | T_fullYear.SEASON == 'S21' | T_fullYear.SEASON == 'S28' | T_fullYear.SEASON == 'S34' | T_fullYear.SEASON == 'S41' | T_fullYear.SEASON == 'S47', :);
%    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S03' | T_fullYear.SEASON == 'S09' | T_fullYear.SEASON == 'S16' | T_fullYear.SEASON == 'S22' | T_fullYear.SEASON == 'S29' | T_fullYear.SEASON == 'S35' | T_fullYear.SEASON == 'S42' | T_fullYear.SEASON == 'S48', :);
%    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S04' | T_fullYear.SEASON == 'S10' | T_fullYear.SEASON == 'S17' | T_fullYear.SEASON == 'S23' | T_fullYear.SEASON == 'S30' | T_fullYear.SEASON == 'S36' | T_fullYear.SEASON == 'S43' | T_fullYear.SEASON == 'S49', :);
    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S05' | T_fullYear.SEASON == 'S11' | T_fullYear.SEASON == 'S18' | T_fullYear.SEASON == 'S24' | T_fullYear.SEASON == 'S31' | T_fullYear.SEASON == 'S37' | T_fullYear.SEASON == 'S44' | T_fullYear.SEASON == 'S50', :);
elseif number_of_seasons == 12
%    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S02' | T_fullYear.SEASON == 'S06' | T_fullYear.SEASON == 'S10' | T_fullYear.SEASON == 'S15' | T_fullYear.SEASON == 'S19' | T_fullYear.SEASON == 'S23' | T_fullYear.SEASON == 'S28' | T_fullYear.SEASON == 'S32' | T_fullYear.SEASON == 'S36' | T_fullYear.SEASON == 'S41' | T_fullYear.SEASON == 'S45' | T_fullYear.SEASON == 'S49', :);
%    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S03' | T_fullYear.SEASON == 'S07' | T_fullYear.SEASON == 'S11' | T_fullYear.SEASON == 'S16' | T_fullYear.SEASON == 'S20' | T_fullYear.SEASON == 'S24' | T_fullYear.SEASON == 'S29' | T_fullYear.SEASON == 'S33' | T_fullYear.SEASON == 'S37' | T_fullYear.SEASON == 'S42' | T_fullYear.SEASON == 'S46' | T_fullYear.SEASON == 'S50', :);
    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S04' | T_fullYear.SEASON == 'S08' | T_fullYear.SEASON == 'S12' | T_fullYear.SEASON == 'S17' | T_fullYear.SEASON == 'S21' | T_fullYear.SEASON == 'S25' | T_fullYear.SEASON == 'S30' | T_fullYear.SEASON == 'S34' | T_fullYear.SEASON == 'S38' | T_fullYear.SEASON == 'S43' | T_fullYear.SEASON == 'S47' | T_fullYear.SEASON == 'S51', :);
%    T_sel_weeks = T_fullYear(T_fullYear.SEASON == 'S05' | T_fullYear.SEASON == 'S09' | T_fullYear.SEASON == 'S13' | T_fullYear.SEASON == 'S18' | T_fullYear.SEASON == 'S22' | T_fullYear.SEASON == 'S26' | T_fullYear.SEASON == 'S31' | T_fullYear.SEASON == 'S35' | T_fullYear.SEASON == 'S39' | T_fullYear.SEASON == 'S44' | T_fullYear.SEASON == 'S48' | T_fullYear.SEASON == 'S52', :);
          
else
    disp('please choose the number of seasons between 1 to X')
end

T_sel_weeks_full=T_sel_weeks;
T_sel_weeks=T_sel_weeks(1:thinning_value:end,:);
T_sel_weeks_scaled = T_sel_weeks;

for i=3:size(T_fullYear,2)

x_f = T_fullYear{:,i};
x_sel_orig=T_sel_weeks{:,i};
x_sel_orig_full=T_sel_weeks_full{:,i};

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


%{
figure
subplot(1,2,1);
%figure;
histogram(x_f, 15, 'Normalization', 'pdf','DisplayStyle','stairs','EdgeColor','b')

hold all
histogram(x_sel_orig, 15, 'Normalization', 'pdf','DisplayStyle','stairs','EdgeColor','m')

hold all
histogram(x_sel_scaled, 15, 'Normalization', 'pdf','DisplayStyle','stairs','EdgeColor','r')
legend('Original timeseries','Original selected timeseries', 'Scaled selected timeseries')
title('Histogram')
xlabel('Standardized generation');
ylabel('PDF');
%mean(x_sel_scaled)
%std(x_sel_scaled)
%prctile(x_sel_scaled, [5, 95])
%max(x_sel_scaled)


% scatterhist(x_sel_orig, x_sel_scaled)
% xlabel('Selected week orig');
% ylabel('Selected week scaled')
t=1:1:50;
t2=1:2:49;


subplot(1,2,2);
%figure;
plot(t,x_sel_orig_full(1:50));
hold all
plot(t2,x_sel_scaled(1:25),':rs');
legend('Original timeseries', 'Scaled selected timeseries')
title('Timeseries');
xlabel('Time (hour)');
ylabel('Standardized generation');



% figure;
% ksdensity(diff(x_f));
% std(diff(x_f))
% hold all
% ksdensity(diff(x_sel_scaled));
% legend('Full', 'Selected week scaled')
% std(diff(x_sel_scaled))
%}

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
