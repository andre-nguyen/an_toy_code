function [ image_out] = undistortImage( image, K, D )
%UNDISTORTIMAGE Undistorts an image
width = size(image,2);
height = size(image,1);
[X, Y] = meshgrid(1:width, 1:height);
pixel_locations = [X(:)-1, Y(:)-1, ones(nnz(X), 1)]';

pixel_locations = K^(-1) * pixel_locations;
pixel_locations = distortPoints(D, pixel_locations);
pixel_locations = K * pixel_locations;
pixel_locations = pixel_locations(1:2, :);
lookup = round(pixel_locations(2,:)) + height * round(pixel_locations(1,:));
values = image(:,:,1);
values = values(lookup);
image_out = uint8(reshape(values, height, width));

end

