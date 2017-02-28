function y = MCG(n, min, max) % Multiplicative Congruential Generator
    % max must be a prime number and should not be divisible by 4.    
    
    if (~(isPrime(max))
        disp('Warning, parameter for 'max' is not a prime number.');
        disp('Result might be distorted.');
    end
    
    a = 13;
    x = min + (max-min)*rand();
    x = round(x);
    
    for i = 1:n
        z = a*x;
        y(i) = mod(z, max + 1);
        
        x = y(i);
        
        % to prevent values lower than min
        if y(i) < min
            y(i) = min;
        end
    end