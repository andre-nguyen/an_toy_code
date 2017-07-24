function [ points ] = reprojectPoints( P, M, K )
%REPROJECTPOINTS Summary of this function goes here
%   Detailed explanation goes here

points = [P, ones(length(P), 1)]';          % Make homogenous
points = K * M * points;                    % Project points
points(1,:) = points(1,:) ./ points(3,:);   % normalize
points(2,:) = points(2,:) ./ points(3,:);
points = points(1:2, :);                    % remove homogeneous part

end

