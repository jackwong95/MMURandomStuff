function y = REX(n, min, max) %Random Exponential Distribution 

    l = rand();
    l = mod(l*100,7);
    l = ceil(l);
    
    a = rand(1,n);
    z = (-1/l)*(log(1-a));
    
    x = (z * max);
    x = mod(x, max);
    
    for i = 1:n
        if x(i) < min
            x(i) = min;
        end
    end
    
    y = round(x);