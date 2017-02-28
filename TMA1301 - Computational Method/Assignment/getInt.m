function output = getInt()
    % a function to get a positive integer from user.
    % reads a line as a string.
    % converts the string into an integer and check whether it's valid.
    % if valid, return it.
    % if not valid, ask again.
    
    disp('Enter an integer greater than 0.');
    a = getline;
    o = str2num(a);
    check = ~mod(o,1);
    
    while (true)
        if (check && o >= 1) break;
        else
            disp('Invalid input, enter again.');
            a = getline;
            o = str2num(a);
            check = ~mod(o,1);
        end
    end
    
    output = o;