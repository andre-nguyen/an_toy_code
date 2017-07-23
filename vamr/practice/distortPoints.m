function [ pout ] = distortPoints( D, pin )
%DISTORTPOINTS Applies radial tangential distortion coefficients to points
   
r = pin(1,:).^2 + pin(2,:).^2;
pout = (1 + D(1) * r + D(2) * r.^2) .* pin(1:2,:);
pout(3,:) = pin(3,:);

end

