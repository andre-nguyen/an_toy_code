% Title: Practice 1
% Course: UZH-BMINF010 Vision Algorithms for Mobile Robotics
% Author: Andre Phu-Van Nguyen <andre-phu-van.nguyen@polymtl.ca>
close all;
clc;

%% Part 3.3
n_images = 736;
poses = load('data/poses.txt');
K = load('data/K.txt');
D = load('data/D.txt');

image = imread('data/images/img_0001.jpg');
image = rgb2gray(image);
image = undistortImage(image, K, D);

figure
imshow(image);