function y = RUN(n, min, max) % Random Uniform Distribution

    
    x = rand(1, n);
    
    z = min + (max-min)*x;
    
    y = round(z);