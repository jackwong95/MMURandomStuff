function main(num_of_servers, num_of_customers, randomizer)
	
	disp('-- SIMULATOR --');
	disp('Enter number of servers 1 - 3.');
	num_of_servers = getInt;
	
	while (num_of_servers > 3)
		disp('Please enter an integer from 1 - 3.');
		num_of_servers = getInt;
	end
	
    fprintf('\n\n');
 
	disp('Enter number of customers.');
	num_of_customers = getInt;
 
    fprintf('\n\n');
	
	disp('Enter type for number generator:');
	disp('1. Additive Congruential Generator');
	disp('2. Linear Congruential Generator');
	disp('3. Multiplicative Congruential Generator');
	disp('4. Random Exponential Distribution');
	disp('5. Random Uniform Distribution');
	RNG = getInt;
    
    while (RNG > 5)
        disp('Please enter an integer from 1 - 5.');
        RNG = getInt;
    end
    
    if (RNG == 1)
        randomizer = 'ACG';
    elseif (RNG == 2)
        randomizer = 'LCG';
    elseif (RNG == 3)
        randomizer = 'MCG';
    elseif (RNG == 4)
        randomizer = 'REX';
    else (RNG == 5)
        randomizer = 'RUN';
    end
	
    fprintf('\n\n');
    
    NUM_OF_INTERARRIVAL_TIMES      = 8;
    NUM_OF_SERVICE_TIMES           = 5;
    SERVICE_TIME_DEFAULT_BUMP      = 5;
    INTERARRIVAL_TIME_DEFAULT_BUMP = 0;
    SERVICE_TIME_RN_SIZE           = 100;
    INTERARRIVAL_TIME_RN_SIZE      = 100;

    % Will be generated before the main loop
    server_service_times  = [];
    interarrival_times    = [];

    rn_service_times      = [];
    rn_interarrival_times = [];
    
    
    % Generate Table of Products
    % Product and prices.
    disp('Enter number of products available.');
    num_of_products = getInt;
    fprintf('\n\n');
    
    disp('What is the minimum price of a product?');
    min_price = getInt;
    fprintf('\n\n');
    
    disp('What is the maximum price of a product?');
    max_price = getInt;
    fprintf('\n\n');
    
    % how much a customer can buy?
    disp('How much can a customer buy?');
    max_limit = getInt;
    fprintf('\n\n');
    min_limit = 1;
    
    product_price   = [];
    price_low       = []; % .00 - .99
    price_high      = []; % min_price - max_price
    
    % initiate the price_low
    price_low = rand(1, num_of_products);
    
    % initiate the price_high
    for i = 1:num_of_products
        price_high(i) = round(min_price + (max_price-min_price)*rand);
    end
    
    % initiate the price
    for i = 1:num_of_products
        if (price_high(i) == max_price)
            product_price(i) = price_high(i);
        else
            product_price(i) = price_high(i) + price_low(i);
        end
    end
    
    % print Table of Products
    disp('Table of Products');
    disp('|-------------+---------------|');
    disp('|Product no.  | Product Price |');
    disp('|-------------+---------------|');
    
    for i = 1:num_of_products
        fprintf('|    %3d      |    %6.2f     |\n', i, product_price(i));
    end
    
    disp('|-------------+---------------|');
    fprintf('\n\n\n');    
    
    
    % Temporary 
    server_ending_times          = zeros(1, num_of_servers); % to track who ends first in the loop
    server_spent_times           = zeros(1, num_of_servers); % to track total time spent by each server
    server_num_of_customers      = zeros(1, num_of_servers); % track num of customers each of them served

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
    
    % Generate servers' profiles - their minimum service time, probability of each service time
    for i = 1:num_of_servers;

        % The newcomer servers are slower
        server_minimum_service_time = i + SERVICE_TIME_DEFAULT_BUMP;

        % First we get a list of numbers ranging from 1 - 100
        service_time_candidates = [];

        for j = 1:NUM_OF_SERVICE_TIMES;
            service_time_candidates(j) = feval(randomizer, 1, 1, SERVICE_TIME_RN_SIZE)(1);
        end

        % Find the denominator for the candidate numbers to divide against
        service_time_candidates_sum = sum(service_time_candidates);

        % Now make them random number range of 1 - 100
        service_time_random_range = [];

        for j = 1:NUM_OF_SERVICE_TIMES;
            service_time_random_range(j) = round(100 * service_time_candidates(j) / service_time_candidates_sum);

            if (j >= 2);
                service_time_random_range(j) = service_time_random_range(j) + service_time_random_range(j - 1);
            end
        end

        % Sometimes the range max ends not at 100, heres a hack
        service_time_random_range = service_time_random_range + (100 - service_time_random_range(NUM_OF_SERVICE_TIMES));

        % Now we generate a vector of service times that appears at the frequency of service time random range
        service_time = [];
        % Initialise array for random no range
        service_randno_range_start = [];
        % Random no range always start with 1 ( 1 - *)
        service_randno_range_start(1) = 1;

        for j = 1:NUM_OF_SERVICE_TIMES;

            if j >= 2;
                start_point = service_time_random_range(j - 1) + 1;
                service_randno_range_start(j) = start_point;
            else;
                start_point = 1;
            end

            for k = start_point:service_time_random_range(j);

                service_time = [service_time (j + i - 1)];
                
            end

        end

        % Bump
        
        service_time = service_time + server_minimum_service_time;

        % Lets put these data into server[]
        
        server_service_times = [server_service_times; service_time];

        % Generate CDF,F(x)  
        service_time_random_range = service_time_random_range / 100;
        service_time_random_range = service_time_random_range';
        % Calculate Probability from randomly generated CDF
        
        % Calculate service time

        server_probability = [];
        server_probability(1) = service_time_random_range(1);
        for pa = 1:NUM_OF_SERVICE_TIMES - 1;
            pb = pa + 1; % pa = probability after || probability before
            server_probability(pb) = service_time_random_range(pb) - service_time_random_range(pa);   
        end

        service_randno_range_end = [];
        
        service_randno_range_end(NUM_OF_SERVICE_TIMES) = 100;
        for startrange = 1:NUM_OF_SERVICE_TIMES - 1;
            endrange = startrange + 1;
            service_randno_range_end(startrange) = service_randno_range_start(endrange) - 1;
        end

        fprintf('\nServer %d Service Time\n',i)
        disp('|-------------+-------------+--------+-------------|')
        disp('|Service      | Probability | CDF    | Random No   |')
        disp('|Time         |             | F(X)   | Range       |')
        disp('|-------------+-------------+--------+-------------|')
        
        for j = 1:NUM_OF_SERVICE_TIMES             
            fprintf('|     %2d      |     %2.2f    |  %2.2f  | %3d - %3d   |\n',[server_minimum_service_time,server_probability(j),service_time_random_range(j) service_randno_range_start(j) service_randno_range_end(j)])
            server_minimum_service_time = server_minimum_service_time+1;
        end
        disp('|-------------+-------------+--------+-------------|')
        fprintf('\n\n')    
    end

    
    % Generate Interarrival Times, for-loop used only to indent the code
    for i = 1:1;

        % First we get a list of numbers ranging from 1 - 100
        interarrival_time_candidates = [];

        for j = 1:NUM_OF_INTERARRIVAL_TIMES;
            interarrival_time_candidates(j) = feval(randomizer, 1, 1, INTERARRIVAL_TIME_RN_SIZE)(1);
        end

        % Find t...he denominator for the candidate numbers to divide against
        interarrival_time_candidates_sum = sum(interarrival_time_candidates);

        % Now make them random number range of 1 - 100
        interarrival_time_random_range = [];

        for j = 1:NUM_OF_INTERARRIVAL_TIMES;
            interarrival_time_random_range(j) = round(100 * interarrival_time_candidates(j) / interarrival_time_candidates_sum);

            if (j >= 2);
                interarrival_time_random_range(j) = interarrival_time_random_range(j) + interarrival_time_random_range(j - 1);
            end
        end

        % Sometimes the range max ends not at 100, heres a hack
        interarrival_time_random_range = interarrival_time_random_range + (100 - interarrival_time_random_range(NUM_OF_INTERARRIVAL_TIMES));
        % Acquire random no range lower limit 
        randno_range_start = [];
        % Random no range always start with 1 ( 1 - *)
        randno_range_start(1) = 1;

        for j = 1:NUM_OF_INTERARRIVAL_TIMES;

            if j >= 2;
                start_point = interarrival_time_random_range(j - 1) + 1;
                %Stores the start point into an array for IAT Table 
                randno_range_start(j) = start_point;
            else;
                start_point = 1;
            end

            for k = start_point:interarrival_time_random_range(j);
                interarrival_times = [interarrival_times (j + i - 1 + INTERARRIVAL_TIME_DEFAULT_BUMP)];
            end

        end

    end

    % First generate the RN interarrival and RN service time
    rn_interarrival_times = feval(randomizer, num_of_customers, 1, SERVICE_TIME_RN_SIZE);
    rn_service_times      = feval(randomizer, num_of_customers, 1, INTERARRIVAL_TIME_RN_SIZE);

    % Generate Interarrival Table
    disp('|-------------+-------------+--------+-------------|')
    disp('|Interarrival | Probability | CDF    | Random No   |')
    disp('|Time         |             | F(X)   | Range       |')
    disp('|-------------+-------------+--------+-------------|')
    
    interarrival_time_random_range = interarrival_time_random_range / 100;
    interarrival_time_random_range = interarrival_time_random_range';
    
    probability = [];
    probability(1) = interarrival_time_random_range(1);
    for i = 1:NUM_OF_INTERARRIVAL_TIMES - 1;
        j = i + 1;
        probability(j) = interarrival_time_random_range(j) - interarrival_time_random_range(i);
    end
    
    randno_range_end = [];
    
    randno_range_end(NUM_OF_INTERARRIVAL_TIMES) = 100;
    for i = 1:(NUM_OF_INTERARRIVAL_TIMES-1)
        j = i + 1;
        randno_range_end(i) = randno_range_start(j) - 1;
    end
    for i = 1:NUM_OF_INTERARRIVAL_TIMES;
        fprintf('|    %d        |   %2.2f      |  %2.2f  | %3d - %3d   |\n',[i probability(i) interarrival_time_random_range(i) randno_range_start(i) randno_range_end(i)])
    end
    disp('|-------------+-------------+--------+-------------|')
    fprintf('\n\n\n')

    % Let's simulate all the customers
    disp('|-----+--------------+---------+--------+--------+---------+----------+---------+------------+--------+--------+--------|')
    disp('|Cust | Interarrival | Arrival |  Wait  | Server | Service | Service  | Service | Total      |Product |Quantity| Total  |')
    disp('|no.  | Time         | Time    |  Time  | Number | Starts  | Duration | Ends    | Time Spent |Chosen  |        | Price  |')
    disp('|-----+--------------+---------+--------+--------+---------+----------+---------+------------+--------+--------+--------|')

    for customer = 1:num_of_customers;

        % Calculate interarrival & arrival times
        if customer > 1;
            customer_interarrival_times(customer) = interarrival_times(rn_interarrival_times(customer));
            customer_arrival_times(customer) = customer_arrival_times(customer - 1) + customer_interarrival_times(customer);
        else
            customer_interarrival_times(customer) = 0;
            customer_arrival_times(customer)      = 0;
        end

        arrival_time = customer_arrival_times(customer);

        % Get a free server, or soonest-to-be-free
        chosen_server = [0 (num_of_customers*100)]; % [server_id server_ending_time]

        for i = 1:num_of_servers;
            if (server_ending_times(i) < chosen_server(2));
                chosen_server = [i server_ending_times(i)];
            end
        end

        % Special case for 1st customer 1st server, to avoid potentially slower servers:
        if server_service_times(1) == 0;
            chosen_server = [1 0];
        end

        chosen_server_id          = chosen_server(1);
        chosen_server_ending_time = chosen_server(2);

        % Server found
        customer_served_by(customer) = chosen_server_id;
        customer_service_duration(customer) = server_service_times(chosen_server_id, rn_service_times(customer));

        % Calculate the times
        customer_service_begin_times(customer) = max([arrival_time chosen_server_ending_time]);
        customer_service_end_times(customer)   = customer_service_begin_times(customer) + customer_service_duration(customer);
        customer_queued_times(customer)        = customer_service_begin_times(customer) - arrival_time;
        customer_total_spent_times(customer)   = customer_service_end_times(customer) - arrival_time;

        % Update server's int
        server_num_of_customers(chosen_server_id) = server_num_of_customers(chosen_server_id) + 1;
        server_spent_times(chosen_server_id)      = server_spent_times(chosen_server_id) + customer_service_duration(customer);

        % Update server ending time
        server_ending_times(chosen_server(1)) = customer_service_end_times(customer);
        
        % Generate product, take corresponding price, quantity and calculate total price.
        product_selection(customer) = round(1 + (num_of_products - 1)*rand);
        product_quantity(customer) = round(min_limit + (max_limit - min_limit)*rand);
        total_price(customer) = product_price(product_selection(customer)) * product_quantity(customer);

        % Print result
        fprintf('|%3d  |     %3d      |   %3d   |  %3d   |  %3d   |   %3d   |   %3d    |   %3d   |     %3d    |  %3d   |  %3d   | %6.2f |\n', [customer customer_interarrival_times(customer) customer_arrival_times(customer) customer_queued_times(customer) customer_served_by(customer) customer_service_begin_times(customer) customer_service_duration(customer) customer_service_end_times(customer) customer_total_spent_times(customer) product_selection(customer) product_quantity(customer) total_price(customer)])

    end;
    disp('|-----+--------------+---------+--------+--------+---------+----------+---------+------------+--------+--------+--------|')
    
    
    %Activity Log
    fprintf('\n\n\n');
    disp('|===========================================================================================|')
    disp('|                                      ACTIVITY LOG                                         |')
    disp('|===========================================================================================|')
    fprintf('\n');
    for customer = 1:num_of_customers;
        fprintf('Customer %d arrives at minute %d and queues at Server %d\n',customer,customer_arrival_times(customer),customer_served_by(customer));
        fprintf('Service Time is %d and Service starts at %d\n',customer_service_duration(customer),customer_service_begin_times(customer));
        fprintf('Customer %d departs at %d\n\n',customer,customer_service_end_times(customer));
    end
    
    disp('|===========================================================================================|')
    disp('|                                   END OF ACTIVITY LOG                                     |')
    disp('|===========================================================================================|')
    
    
    % Testing
    fprintf('\n\n\n');
    %Initialize server_busy array
    server_busy=[]; 
    for server = 1:num_of_servers;
        fprintf('Server %d spent total of %d minutes serving total of %d customers.\n', [server server_spent_times(server) server_num_of_customers(server)]);
        server_busy(server)=(server_spent_times(server)/customer_service_end_times(num_of_customers))* 100;
        fprintf('Percentage of Server %d being busy is %2.2f percent.\n\n',server,server_busy(server))
    end

    fprintf('\n');

    % Average customer waiting time + Chance of them queueing up
    customer_avg_queue_time = mean(customer_queued_times);
    percentage_of_customers_queue_up = 100 * length(nonzeros(customer_queued_times)) / num_of_customers;

    fprintf('%3.2f percent of customers have spent time queueing up\n', [percentage_of_customers_queue_up]);
    fprintf('Average waiting time: %5.2f\n', [customer_avg_queue_time])

    % Average service time
    customer_avg_service_time = mean(customer_service_duration);
    customer_avg_interarrival_time = mean(customer_interarrival_times);
    customer_avg_spent_time = mean(customer_total_spent_times);

    fprintf('Average service time: %5.2f\nAverage interarrival time: %5.2f\nAverage time spent per customer: %5.2f\n\n\n', [customer_avg_service_time customer_avg_interarrival_time customer_avg_spent_time]);

    disp('Conclusion drawn:')
    if (percentage_of_customers_queue_up <= 25)
        disp('Customers have a low chance of waiting in queue.')
    elseif (percentage_of_customers_queue_up > 25 && percentage_of_customers_queue_up <= 50)
        disp('Customers have a moderate chance of waiting in queue.')
    elseif (percentage_of_customers_queue_up > 50 && percentage_of_customers_queue_up <= 75)
        disp('Customers have a high chance of waiting in queue.')
    else
        disp('Customers have a very high chance of waiting in queue.')            
    end
