function output = isPrime(n)
    % n is any integer.
    
    if (n == 1)
        output = 0;
    elseif (n == 2)
        output = 1;
    elseif (n == 3)
        output = 1;
    elseif (n == 5)
        output = 1;
    elseif (n == 7)
        output = 1;
    elseif (mod(n,2)==0 | mod(n,3)==0 | mod(n,5)==0 | mod(n,7)==0)
        output = 0;
    else
        output = 1;
    end