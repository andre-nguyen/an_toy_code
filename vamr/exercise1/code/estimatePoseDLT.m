function [ M ] = estimatePoseDLT( p, P, K)
%ESTIMATEPOSEDLT estimate camera pose using point correspondances and K

n = length(P);
P = [P, ones(n, 1)];

p = reshape(p, 2, n);
p = [p; ones(1, length(p))];
p_normalized = K^(-1) * p;

% Build Q
Q = zeros(2*n, 3*4);
for i = 1:n
    left = kron(eye(2), P(i,:));
    right = [P(i, :) * -p_normalized(1, i); ...
             P(i, :) * -p_normalized(2, i)];
    idx = round((i-1)*2 + 1);
    Q(idx:idx+1,:) = [left, right];
end

% Solve the system QM = 0 for M by minimizing ||QM||^2 subject to ||M|| = 1
% using SVD
[~, ~, V] = svd(Q);
M = V(:,12);
M = reshape(M, 4, 3);
M = M';

% Make sure tz is positive
if M(3,4) < 0
    M = -M;
end

% M = [R|t], now extract a rotation from R through the Orthogonal
% Procrustes problem
R = M(:,1:3);
[U, ~, V] = svd(R);
R_est = U * V';

% Recovering the scale (alpha) of the projection matrix
alpha = norm(R_est, 'fro') / norm(R, 'fro');
t = alpha * M(:,4);
M = [R_est, t];


end

