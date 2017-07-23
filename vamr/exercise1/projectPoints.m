function [ p ] = projectPoints( K, T_C_W, P_w , D)
%PROJECTPOINTS Projects 3d points onto the image plane

if nargin == 4
    distort = true;
else
    distort = false;
end

num_corners = length(P_w(1,:));
p = T_C_W * [P_w; ones(1, num_corners)];

% normalize coordinates so that third component is always 1
p(1, :) = p(1, :) ./ p(3, :);
p(2, :) = p(2, :) ./ p(3, :);
p(3, :) = p(3, :) ./ p(3, :);

if distort
    p = distortPoints(D, p);
end

p = K * p;


end