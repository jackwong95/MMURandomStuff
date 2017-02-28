function output = getIntWithCustomMessage(str)
    % a function to get a positive integer from user.
    % reads a line as a string.
    % converts the string into an integer and check whether it's valid.
    % if valid, return it.
    % if not valid, ask again.
    
    disp(str);
    disp('----------------------------------------------------------------');
    input = getline;
    int_from_string = str2num(input);
    check = ~mod(int_from_string,1);
    
    while (true)
        if (check && int_from_string >= 1) break;
        else
            disp('Invalid input. Enter again.');
            disp(str);
            disp('----------------------------------------------------------------');
            input = getline;
            int_from_string = str2num(input);
            check = ~mod(int_from_string,1);
        end
    end
    
    output = int_from_string;