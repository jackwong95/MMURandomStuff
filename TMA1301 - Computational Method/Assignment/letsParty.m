function letsParty(numOfCounters, numOfCustomers, randomizerChoice)
    
    %<parameter list>
    
    %num_of_counters
    %num_of_customers
    
    %randomizer_choice
    %randomizerChoice
    
    %number_of_products
    
    %min_price
    %max_price
    
    %min_limit
    %max_limit
    
    %products_price[]
    %prices_low[]
    %prices_high[]
    
    %NUM_OF_INTERARRIVAL_TIMES
    %NUM_OF_SERVICE_TIMES
    %SERVICE_TIME_DEFAULT_BUMP
    %INTERARRIVAL_TIME_DEFAULT_BUMP
    %SERVICE_TIME_RN_SIZE
    %INTERARRIVAL_TIME_RN_SIZE
    
    %server_service_times[]
    %interarrival_times[]
    
    %rn_service_times[]
    %rn_interarrival_times[]
    
    %</parameter list>

    %<Varibles and Constants For Later Use>
    NUM_OF_INTERARRIVAL_TIMES      = 8;
    NUM_OF_SERVICE_TIMES           = 5;
    SERVICE_TIME_DEFAULT_BUMP      = 5;
    INTERARRIVAL_TIME_DEFAULT_BUMP = 0;
    SERVICE_TIME_RN_SIZE           = 100;
    INTERARRIVAL_TIME_RN_SIZE      = 100;
    %</Varibles and Constants For Later Use>
    
    %<Beginning Message>
    disp(' ');
    disp(' ');
    disp(' ');
    disp('----------AND SO, THE QUEUEING SYSTEM SIMULATION BEGINS---------');
    disp(' ');
    %</Beginning Message>
    
    %<Get number of Counters>
    disp('----------------------------------------------------------------');
    num_of_counters = getIntWithCustomMessage('How many counters are operational, from 1 to 3 : ');
    
    while(num_of_counters <= 0 | num_of_counters > 3)
        disp('----------------------------------------------------------------');
        disp(' ');
        num_of_counters = getIntWithCustomMessage('How many counters are operational, from 1 to 3 : ');
    end
    %</Get number of Counters>
    
    %<Get number of Customers>
    disp(' ');
    disp('----------------------------------------------------------------');
    num_of_customers = getIntWithCustomMessage('How many customers are there : ');
    %</Get number of Customers>
    
    %<Temporary>
    server_ending_times          = zeros(1, num_of_counters); % to track who ends first in the loop
    server_spent_times           = zeros(1, num_of_counters); % to track total time spent by each server
    server_num_of_customers      = zeros(1, num_of_counters); % track num of customers each of them served

    customer_interarrival_times  = zeros(1, num_of_customers);
    customer_arrival_times       = zeros(1, num_of_customers);
    customer_served_by           = zeros(1, num_of_customers); % track ID of servers
    customer_service_begin_times = zeros(1, num_of_customers);
    customer_service_duration    = zeros(1, num_of_customers);
    customer_service_end_times   = zeros(1, num_of_customers);
    customer_queued_times        = zeros(1, num_of_customers);
    customer_total_spent_times   = zeros(1, num_of_customers); % queue + service
    
    product_selection            = ones(1, num_of_customers);
    product_quantity             = ones(1, num_of_customers);
    total_price                  = zeros(1, num_of_customers); % product_price * product_quantity
    %</Temporary>
    
    %<Get random generator used>
    disp(' ');
    disp('----------------------------------------------------------------');
	disp('Pick a number generator for the simulation:');
	disp('1. Additive Linear Congruential Generator');
	disp('2. Mixed Linear Congruential Generator');
	disp('3. Multiplicative Linear Congruential Generator');
	disp('4. Random Exponential Distribution');
	disp('5. Random Uniform Distribution');
    disp('----------------------------------------------------------------');
    
    randomizer_choice = getIntWithCustomMessage('Pick a number generator : ');
    
    while(randomizer_choice > 5)
        disp(' ');
        disp('----------------------------------------------------------------');
        disp('Pick a number generator for the simulation:');
        disp('1. Additive Linear Congruential Generator');
        disp('2. Mixed Linear Congruential Generator');
        disp('3. Multiplicative Linear Congruential Generator');
        disp('4. Random Exponential Distribution');
        disp('5. Random Uniform Distribution');
        disp('----------------------------------------------------------------');
        randomizer_choice = getIntWithCustomMessage('Pick a number generator : ');
    end
    %</Get random generator used>
    
    %<Determine random generator used>
    if (randomizer_choice == 1)
        randomizerChoice = 'ADDLCG';
    elseif (randomizer_choice == 2)
        randomizerChoice = 'MIXLCG';
    elseif (randomizer_choice == 3)
        randomizerChoice = 'MULLCG';
    elseif (randomizer_choice == 4)
        randomizerChoice = 'REXPO';
    else (randomizer_choice == 5)
        randomizerChoice = 'RUNIF';
    end
    %</Determine random generator used>
    
    %<Product number and prices>
    disp('----------------------------------------------------------------');
    number_of_products = getIntWithCustomMessage('How many products are available : ');
    disp(' ');disp(' ');
    
    disp('----------------------------------------------------------------');
    min_price = getIntWithCustomMessage('Minimun price of a product : ');
    disp(' ');disp(' ');
    
    disp('----------------------------------------------------------------');
    max_price = getIntWithCustomMessage('Maximum price of a product : ');
    disp(' ');disp(' ');
    
    while(max_price <= min_price)
        disp('----------------------------------------------------------------');
        max_price = getIntWithCustomMessage('Maximum price of a product : ');
        disp(' ');disp(' ');
    end
    %</Product number and prices>
    
    %<Allowed Purchased quantity>
    min_limit = 1;
    disp('----------------------------------------------------------------');
    max_limit = getIntWithCustomMessage('Customer allowed to purchase how many products : ');
    disp(' ');disp(' ');
    %</Allowed Purchased quantity>
    
    %<Stuff about price>
    %<prices_low initialization>
    prices_low = rand(1, number_of_products);
    %</prices_low initialization>
    
    %<prices_high initialization>
    for(i = 1:number_of_products)
        prices_high(i) = round(min_price + (max_price-min_price)*rand());
    end
    %</prices_high initialization>
    
    %<prices initialization>
    for(i = 1:number_of_products)
        if (prices_high(i) == max_price)
            products_price(i) = prices_high(i);
        else
            products_price(i) = prices_high(i) + prices_low(i);
        end
    end
    %</prices initialization>
    %</Stuff about price>
    
    %<Print Table of Products>
    disp('Products Table : ');
    disp('#----------------#------------------#');
    disp('# No. of Product # Price of Product #');
    
    for(i = 1:number_of_products)
        disp('#----------------#------------------#');
        printf('#      %3d       #      %6.2f      #\n', i, products_price(i));
    end
    
    disp('#----------------#------------------#');
    disp(' ');disp(' ');disp(' ');
    %</Print Table of Products>
    

    
    