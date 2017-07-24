% Title:    Exercise 1
% Course:   UZH-BMINF010 Vision Algorithms for Mobile Robotics
% Author:   Andre Phu-Van Nguyen <andre-phu-van.nguyen@polymtl.ca>
close all;
clc;

%% Data load
corners = load('../data/detected_corners.txt');
K = load('../data/K.txt');
p_W = load('../data/p_W_corners.txt');
p_W = 0.01 * p_W;   % the corners were in centimeters
n_images = 210;

%% preallocation
q = zeros(4, n_images);
t = zeros(3, n_images);

%% Computations

%figure;
for i = 1:n_images
    im_path = sprintf('../data/images_undistorted/img_%04d.jpg', i);
    image = imread(im_path);
    image = rgb2gray(image);
    M = estimatePoseDLT(corners(i,:), p_W, K);
    points = reprojectPoints(p_W, M, K);
    
    % Trajectory plot
    M_W_C = [M(:,1:3)' -M(:,4)];
    q(:,i) = rotMatrix2Quat(M_W_C(:,1:3));
    t(:,i) = M_W_C(:,4);

    % Display
%     imshow(image);
%     hold on;
%     scatter(points(1,:), points(2,:), 50, 'filled', 'r');
%     hold off;
%     drawnow;
end

plotTrajectory3D(30, t, q, p_W');


