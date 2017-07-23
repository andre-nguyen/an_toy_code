% Title: Practice 1
% Course: UZH-BMINF010 Vision Algorithms for Mobile Robotics
% Author: Andre Phu-Van Nguyen <andre-phu-van.nguyen@polymtl.ca>
close all;
clc;
%% Part 1

n_images = 736;

% Create a matrix containing the 3D positions of all the checkerboard corners 
% P_w. You can use the function meshgrid from Matlab to achieve this.
square_size = 0.04;
width = 9;
height = 6;
[x, y] = meshgrid(0:width-1, 0:height-1);
x = x .* square_size;
y = y .* square_size;
P_w = [x(:) y(:)];                    % zip up coordinates
P_w = [P_w zeros(length(P_w), 1)]';   % Put all points on z = 0

% Write a function to project the corners P_w on the image plane. You will 
% need the transformation [R|t] from world coordinates to camera 
% coordinates, which you can read from the first line of the file 
% poses.txt, as a tuple (ω x , ω y , ω z , t x , t y , t z ) = (ω, t) . 
% You will find it convenient to write two functions 
% poseVectorToTransformationMatrix and projectPoints.

poses = load('data/poses.txt');
K = load('data/K.txt');
D = load('data/D.txt');

outputVideo = VideoWriter(fullfile('./','shuttle_out.avi'));
outputVideo.FrameRate = 30;
open(outputVideo)

figure;
for i = 1:n_images
    % Read the image into Matlab (imread) and convert it to grayscale (rgb2gray).
    file = sprintf('data/images/img_%04d.jpg', i);
    image = imread(file);
    image = rgb2gray(image);
    T_C_W = poseVectorToTransformationMatrix(poses(i,:));
    points = projectPoints(K, T_C_W, P_w, D);
    imshow(image);
    hold on;
    scatter(points(1,:), points(2,:), 50, 'filled', 'r');
    hold off;
    writeVideo(outputVideo,image)
end

%points = projectPoints(K, T_C_W, P_w, D);

%%
close all;
figure;
imshow(image);
hold on;
scatter(points(1,:), points(2,:), 50, 'filled', 'r');
hold off;

figure 
imshow(image);
hold on;
points = projectPoints(K, T_C_W, genCube(square_size), D);
line(points(1, :), points(2, :), 'Color', 'r', 'LineWidth', 4);
hold off;

