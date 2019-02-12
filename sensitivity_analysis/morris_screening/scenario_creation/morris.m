function X = morris(p,dt,k,r)
%% Morris screening method
%% Morris, 1991 and Campolongo and Saltelli, 1997
% %% input arguments
% p == number of levels
% dt == incremental factor
% k = number of factors
% r = number of orientations /desired samples
% Output
% X = r times oriented sampling matrix B wiht dimensions as r*(k+1) x k
% 
D = [];
J = [];
B = [] ; % kXk+1 Lower triangular matrix with 1;
Bs = [] ; % kXk+1 orientation matrix
Bp = [];
X = [];
ii1 = [];
ii2 = [];
xb = [];
xp = [];

% step 0; Prepare the base matrices
B = tril(ones(k+1,k),-1) ;
J = ones(k+1,k);
% generate the discrete range from which x can take values
xb =0:(1/(p-1)):(1-dt) ; 
m = length(xb);

% start random orientation of B
for i = 1:r
% step 1: make a diagonal matrix with integer values of 1 or -1 selected with equal probability.
ii0 = rand(k,1);
ii1 = find(ii0 < 0.5) ; % randomly generate k values ([0 1])
di = ones(k,1);
di(ii1) = -1 ; % -1 and +1 has equal probability
D = diag(di);

% step 2: select randomly from discrete uniform distribution with p levels for each input factors k 
xp = zeros(k,1);
ii2 = unidrnd(m,1,k);
xp = xb(ii2);

%% step 3: randomly permuted identity matrix
Pp = eye(k);
Pp(:,randperm(k)) = Pp;

Bp = (J(:,1)*xp + (dt/2)*((2*B - J)*D + J))*Pp ;
X = [X; Bp];
end
