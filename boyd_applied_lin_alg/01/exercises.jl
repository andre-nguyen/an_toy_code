using LinearAlgebra

function exe01()
    a = randn(10^8);
    b = randn(10^8);
    return @time dot(a, b);
end

function exe02a()
    x = collect(1:10);
    a = [zeros(4); 1; zeros(5)];
    return a' * x;
end

function exe02b()
    x = collect(1:3);
    a = [0.3, 0.4, 0.3];
    return a' * x;
end

function exe02c()
    x = rand(22);
    a = zeros(22);
    a[collect(4:4:22)] = ones(5);
    a[collect(7:7:22)] = -1 * ones(3);
    return a' * x;
end

function exe02d()
    x = ones(11);
    a = [zeros(3); ones(5); zeros(3)] ./ 5;
    return a' * x;
end

# exe01()
exe02a();
exe02b();
exe02c();
exe02d()
