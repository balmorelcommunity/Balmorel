%% Compute Elementary Effects(EEi) from the Morris simulations

%% this method requires scalar outputs, y:
% hence one needs to specify a meaningful property of time-series data: Let us focus on time=0.3 hr
y1s = y1(:);
y2s = y2(:);
%y3s = y3(:);

%% compile an model output matrix
Sim = [y1s y2s];
[n k] = size(X) ;
n = n / (k+1);
[mm ll] = size(Sim) ;

%% below info needed for sigma-scaling of EEi
sig_y = std(Sim);
sig_x = std(Xval);

var = {'Electricity{ }Price{}2020','Electricity{ }Price{}2030'} ;

%% read in the Morris simulations, detect which parameter changed and
%% compute the corresponding EEi

[n k] = size(X) ;
n = n / (k+1);
[mm ll] = size(Sim) ;

for i=1:n
    for j=1:k
        m1 = (k+1)*(i-1);
        r1 = m1 + j ;
        ix = find (X(r1,:) - X(r1+1,:)) ; % find the non-zero value
        if length(ix) > 1
            warning('there is more than one factor changed')
            return
        end
        m2 = k*(i-1)+j; % quality check: this is to track which params changed
        idx(m2) = ix ;

        
        %Original
        %dtheta = Xval(r1+1,ix) - Xval(r1,ix) ;
        %EEs(i,ix) = (((Sim(r1+1,1) - Sim(r1,1))/dtheta * (sig_x(ix)/sig_y(1))))  ; % SEEi = EEi* sigx/sigy where EEi = (Ytheta - Ytheta+dtheta) / dtheta *
        % EEo(i,ix) = ((Sim(r1+1,2) - Sim(r1,2))/dtheta * (sig_x(ix)/sig_y(2)));
        
        %Juan's modification
        dtheta= (Xval(r1+1,ix) - Xval(r1,ix))/par(ix);
        EEs(i,ix) = (((Sim(r1+1,1) - Sim(r1,1))/dtheta )); % SEEi = EEi* sigx/sigy where EEi = (Ytheta - Ytheta+dtheta) / dtheta *
        EEo(i,ix) = ((Sim(r1+1,2) - Sim(r1,2))/dtheta  );

    end
end

%% Calculate mean and std from Fi = EEi
for l=1:ll
    if l==1;
        Fi = EEs ;
    elseif l == 2
        Fi = EEo ;
    end
    mu(:,l)  = mean(Fi);
    sig(:,l) = std(Fi);
end

fl =strcat('./output/','ComputedEEi_r',num2str(r),'_p',num2str(p),'.mat');
save(fl,'EEs','EEo','mu','sig')


% close all
pix = 1:k;
figure(2)
for i=1:ll
    subplot(1,2,i)
    for j=1:k
        sem(j,i) = 2*sig(j,i)/sqrt(r);
        plot(mu(j,i),sig(j,i),'ko',sem(j,i),sig(j,i),'k',-sem(j,i),sig(j,i),'k')
        hold on
        text(mu(j,i),sig(j,i),[lp{j},'=',num2str(j)])
    end
    title(var{i})
    xlabel('mean, \mu')
    ylabel('stdev, \sigma')
end

figure(3)
for i=1:ll
    subplot(1,2,i)
    sem(:,i) = 2*sig(:,i)/sqrt(r);
    plot(mu(:,i),sig(:,i),'k+',sort(sem(:,i)),sort(sig(:,i)),'k',-sort(sem(:,i)),sort(sig(:,i)),'k')
    hold on
    for j=1:k;
    text(mu(j,i),sig(j,i),lp{j},'fontsize',14)
    end
    title(var{i})
    xlabel('mean, \mu_i')
    ylabel('standard deviation, \sigma_i')
end


f = 1;
if f == 1;
    for l=1:ll
        if l==1
            Fi = EEs ;
        elseif l == 2
            Fi = EEo ;
        end
        figure
        for i=1:9
            subplot(3,3,i)
            hist(Fi(:,i))
            xlabel(['EEi of ',lp{i}])
            ylabel('Frequency')
            title(var(l)) 
        end
        figure
        for i=10:18
            subplot(3,3,i-9)
            hist(Fi(:,i))
            xlabel(['EEi of ',lp{i}])
            ylabel('Frequency')
            title(var(l)) 
        end
        figure
        for i=19:27
            subplot(3,3,i-18)
            hist(Fi(:,i))
            xlabel(['EEi of ',lp{i}])
            ylabel('Frequency')
            title(var(l)) 
        end
           figure
        for i=28:36
            subplot(3,3,i-27)
            hist(Fi(:,i))
            xlabel(['EEi of ',lp{i}])
            ylabel('Frequency')
            title(var(l)) 
        end
        figure
         for i=37:45
            subplot(3,3,i-36)
            hist(Fi(:,i))
            xlabel(['EEi of ',lp{i}])
            ylabel('Frequency')
            title(var(l)) 
         end
         figure
         for i=46:52
            subplot(3,3,i-45)
            hist(Fi(:,i))
            xlabel(['EEi of ',lp{i}])
            ylabel('Frequency')
            title(var(l)) 
        end
        
        
    end
end

