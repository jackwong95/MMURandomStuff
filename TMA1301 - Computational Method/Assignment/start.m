disp('-- SIMULATOR --');
disp('Enter number of servers 1 - 3.');

num_of_servers = 0;
randomizer = '';

while (1==1)
    disp('Please enter an integer from 1 - 3.');
    num_of_servers = getInt;
    if(num_of_servers>=1 && num_of_servers<=3)
        break;
    end
end
    
while (1==1)
    disp('Enter type for number generator:');
    disp('==> ACG');
    disp('==> LCG');
    disp('==> MCG');
    disp('==> REX');
    disp('==> RUN');
    randomizer = getline;
    if (randomizer(1)=='A'&randomizer(2)=='C'&randomizer(3)=='G')
        randomizer = 'ACG';
        break;
    elseif (randomizer(1)=='L'&randomizer(2)=='C'&randomizer(3)=='G')
        randomizer = 'LCG';
        break;
    elseif (randomizer(1)=='M'&randomizer(2)=='C'&randomizer(3)=='G')
        randomizer = 'MCG';
        break;
    elseif (randomizer(1)=='R'&randomizer(2)=='E'&randomizer(3)=='X')
        randomizer = 'REX';
        break;
    elseif (randomizer(1)=='R'&randomizer(2)=='U'&randomizer(3)=='N')
        randomizer = 'RUN';
        break;
    end
end

