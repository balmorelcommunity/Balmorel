function x = lhs(Nsam, k);

for j=1:k,
    x(:,j) = randperm(Nsam)'./(Nsam+1); %latin hypercube
end
