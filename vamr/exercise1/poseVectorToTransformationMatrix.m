function [ T_C_W ] = poseVectorToTransformationMatrix( vec )
%poseVectorToTransformationMatrix Takes a vector of the form (w_1, w_2,
%w_3, t_1, t_2, t_3) and returns the joint rotation and translation matrix

omega = vec(1:3);
theta = norm(omega);
t = vec(4:6);
k = omega / theta;
k_x = k(1);
k_y = k(2);
k_z = k(3);
k_cross = [ 0     -k_z     k_y;
            k_z    0      -k_x;
           -k_y    k_x     0;];
        
R = eye(3) + sin(theta) * k_cross + (1 - cos(theta)) * k_cross^2;
T_C_W = horzcat(R, t');
end

