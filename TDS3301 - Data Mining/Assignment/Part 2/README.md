###1. Objectives.

* **What is the domain?**
```
A store that performs sales. Transactional data (sales history).
The store is a bakery store which sells foods and beverages.
```

* **What are the potential benefits to derived from association rule mining?**
```
1. The store can come up with promotions.
2. The store can re-arrange items for the convenience of customers or to attract customers to buy other stuff.
3. The store can help recommend customers which products they would be interested in trying.
```


###2. Data Set Description. 

* **What is in the data?**
```
The 3 main dataset can be found in the extended bakery dataset, which are as explained in the following:
```

&nbsp;&nbsp; **1. 1000i.csv - Composite entity (bridge) between receipt and goods; It contains the transactions made by the bakery. The transaction contains quantity of goods purchased and also the receipt generated for the transaction**.

First 4 rows of 1000i.csv file:

| First | Second | Third |
|:---:|:---:|:---:|
| 1 | 3 | 7 |
| 1 | 4 | 15 |
| 1 | 2 | 49 |
| 1 | 5 | 44 |

* **First** column represents the **receipt's ID**.
* **Second** column represents the **quantity** purchased. 
* **Third** column represents the **good's ID**.

**Explanation**: **good** ```7, 15, 49, 44``` are purchased with **quantity** of ```3, 4, 2, 5``` respectively. The samples shown are from **receipt** ```1``` indicated by column one.


&nbsp;&nbsp; **2. EB-build-goods.sql - Sql insert query used for adding new type of goods into the store.**

First 2 rows of EB-build-goods.sql file:

| SQL Queries |
|---|
| insert into goods values (0,'Chocolate','Cake',8.95,'Food'); |
| insert into goods values (1,'Lemon','Cake',8.95,'Food'); |

* We know that there are 2 goods that are cake with two different flavours which are chocolate and lemon, where they are both under the category of Food.


&nbsp;&nbsp; **3. 1000-out2.csv - Full binary vectors of each goods that are purchased of each receipt.**

Example of 1000-out2.csv:
```
3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
```

&nbsp;&nbsp; We know that the first column is the receipt ID, where this receipt contains purchases of item type 1 and 19.



* **What preprocessing was done to make it amenable for association rule mining?**

&nbsp;&nbsp; 1. EB-build-goods.sql is loaded using **readLines**, where it goes through some pre-processing steps to remove the SQL syntax and only contains values that are separated by commas.

&nbsp;&nbsp; 2. The commas separated values (CSV) are then loaded onto a dataframe with its respective column data type, we set goods dataframe's row names to the first column given in the SQL file. This was done to enable joins.
```R
# Clean raw SQL code to containing only the information
LoadGoods <- function(x)
    {
        raw <- readLines(x)
        
        # Remove all empty white spaces
        processed <- gsub(" ", fixed = TRUE, "", raw)
        processed <- gsub("insertintogoodsvalues", fixed = TRUE, "", processed)
        processed <- gsub("(", "", fixed = TRUE, processed)
        processed <- gsub(")", "", fixed = TRUE, processed)
        processed <- gsub(";", "", fixed = TRUE, processed)
        
        goods <- read.table(text = processed, sep = ",", colClasses = 
                                c("numeric", "character", "character", "numeric", "character")
                            , stringsAsFactors = FALSE)
        colnames(goods) <- c("id", "flavor", "type", "price", "category")
        rownames(goods) <- goods$id
        
        goods <- goods[,2:ncol(goods)]
        
        # Return
        goods
    }
```

&nbsp;&nbsp; 3. Receipt CSV file is then loaded as a dataframe. Then, we renamed each column accordingly.
```R
# Load the names onto a vector to set the column name of receipt dataset later
names <- tolower(c("id", paste(items$flavor, items$type, sep = ".")))

# Receipt dataset, set the column to names
receipt <- read.csv("1000 transactions/1000-out2.csv", header = FALSE, col.names = names)

# Store each row's id onto receiptIDs
receiptIDs <- receipt[, 1]

# Remove that receiptIDs saved onto the vector on top
receipt <- receipt[,2:ncol(receipt)]

# Make the whole dataframe containing only logical values
receipt <- apply(receipt, 2, as.logical)

# Convert it back to a dataframe
receipt <- as.data.frame(receipt)

# Set the row name to the receipt ID
rownames(receipt) <- receiptIDs
```

* **Where choices were made describe your reasoning behind the choices?**
```
Transaction CSV is not used. 
We have agreed that we can't obtain any association rules related to our problem with quantity and cost.
We're mainly looking at what the customer will buy or the combinations of purchases; not the price. 
Another reason would be Customers' data like wages or savings was not provided.

Our final data consists of only strings, therefore we will be using "transaction" (basket). 
No discretization nor quantization was needed for our final data set.
```

###3-4. Association Mining

&nbsp;&nbsp; **1. We first loaded the "arules" package.**
```R
require(arules)
```
&nbsp;&nbsp; *or*
```R
library(arules)
```

* The package can be installed by typing,
```R
install.packages("arules")
```


&nbsp;&nbsp; **2. Then, we wrote the generalized data into a CSV file.**
```R
write(receipt$type.items, file = "1000_generalize_transactions.csv")
```


&nbsp;&nbsp; **3. Next, we read the output file as a "transaction" with format set to "basket".**
```R
trG <- read.transactions("1000_generalize_transactions.csv", format = "basket", sep = ",")
```

&nbsp;&nbsp; **4. Then, we plotted a bar chart for the top 15 items.**
```R
itemFrequencyPlot(trG, topN = 15, type = "absolute")
```

* The bar chart can be seen below:
![alt tag1](https://github.com/jackwong95/TDS3301DataMining/blob/master/Part%202/Frequency%20of%20Generalized%20Items.png)


&nbsp;&nbsp; **5. Next, we applied association mining rules onto **trG**, using **apriori** with a support threshold of 5%, confidence of 50% and a max length of 5 items.**
```R
rulesG <- apriori(trG,
                  control = list(verbose = F),
                  parameter = list(supp = 0.05, conf = 0.5, maxlen = 5)
)

# Sort rules by confidence.
rulesG <- sort(rulesG, by = "confidence", decreasing = TRUE)

# Remove redundant rules.
redundantG <- which(colSums(is.subset(rulesG, rulesG)) > 1)
rulesG <- rulesG[-redundantG]
inspect(rulesG)
```

* **5% support** is chosen because trG is the generalized item set. If the item isn't even 5%, we considered it as infrequent. 
* **50% confidence** to ensure strong association.
* **Max item length of 5** is reduce the time and processing power required. Furthermore, it is not reasonable to do any promotion with so much items.

* However, we couldn't get much information (rules).
&nbsp;&nbsp; Therefore, we tried to observe the entire dataset (subsets of each item) instead of the generalized dataset.


&nbsp;&nbsp; **6. We repeated what we've done to convert the dataset into a transaction on the full data set.**
```R
write(receipt$full.items, file = "1000_full_transactions.csv")
tr <- read.transactions("1000_full_transactions.csv", format = "basket", sep = ",")
```

&nbsp;&nbsp; **7. Once again, we plotted a bar chart for the top 15 items to observe the distribution to act as a basis and to drive our analysis.**
```R
itemFrequencyPlot(tr, topN = 15, type = "absolute")
```

* The bar chart can be seen below:
![alt tag2](https://github.com/jackwong95/TDS3301DataMining/blob/master/Part%202/Frequency%20of%20Items.png)

&nbsp;&nbsp; **8. Next, we applied association mining as before.**
```R
rules <- apriori(tr,
                 control = list(verbose = F),
                 parameter = list(supp = 0.01, conf = 0.5, minlen = 2, maxlen = 5)
)

# Sort rules by confidence.
rules <- sort(rules, by = "confidence", decreasing = TRUE)

# Remove redundant rules.
redundant <- which(colSums(is.subset(rules, rules)) > 1)
rules <- rules[-redundant]
inspect(rules)
```

* **1% support** is chosen because **tr** is specified item set (Subsets of items are not grouped together).
* **50% confidence** to ensure strong association.
* **Min item length of 2** to obtained useful rules; ignore rules with 1 item.
* **Max item length of 5** is reduce the time and processing power required. Furthermore, it is not reasonable to do any promotion with so much items.

* Once again, we couldn't get much useful or solid information.
&nbsp;&nbsp; Therefore, we tried another approach (try searching for items with a general item), ```eg: Apple Tart => Cookie```


&nbsp;&nbsp; **9. We first ran some R code shown below to find which items in the lower sales group have subsets.**
```R
frequent[grep(x = names(frequent), pattern = "juice", fixed = TRUE)] # no subset; only one set
frequent[grep(x = names(frequent), pattern = "soda", fixed = TRUE)]  # no subset; only one set
```

&nbsp;&nbsp; **10. After several trials, we found that coffee has two subsets, {"chocolate coffee", "hot coffee"}. In addition, we found that coffee is also a subset of eclair, {"coffee eclair"}.**
```R
frequent[grep(x = names(frequent), pattern = "coffee", fixed = TRUE)]
```

&nbsp;&nbsp; **11. We assumed that those items would have a strong association and tried checking for its pattern. "Does coffee lovers buy coffee eclair?"**
```R
rules <- apriori(tr,
                 control = list(verbose = FALSE),
                 parameter = list(supp = 0.01, conf = 0.1),
                 appearance = list(lhs = c("chocolate coffee", "hot coffee"), 
                                   default = "rhs")
)
rules <- sort(rules, by = "confidence", decreasing = TRUE)
inspect(rules)
```

* However, the data shows otherwise. Therefore, we tried the inverse of the previous statement. "Does coffee eclair-buyers buy coffee?"

```R
rules <- apriori(tr,
                 control = list(verbose = FALSE),
                 parameter = list(supp = 0.01, conf = 0.1),
                 appearance = list(lhs = "coffee eclair", 
                                   default = "rhs")
)
rules <- sort(rules, by = "confidence", decreasing = TRUE)
inspect(rules)
```

* Once again, the data shows that our hypothesis is false.
&nbsp;&nbsp; Later, we tried the same observation for apple-flavoured items, results shows a slightly better pattern, however, it wasn't enough to convince anyone.
&nbsp;&nbsp; Therefore, we decided to change our approach. "What leads people to buy Tarts?"

&nbsp;&nbsp; **12. First, we grouped all the tarts into a vector.**
```R
tarts <- c(names(frequent[grep(x = names(frequent), pattern = "tart", fixed = TRUE)]))
```

&nbsp;&nbsp; **13. Next, we ran apriori on the dataset (the dataset with subsets) again.**
```R
rules <- apriori(tr,
                 control = list(verbose = F),
                 parameter = list(supp = 0.01, conf = 0.5, maxlen = 5)
)
```

&nbsp;&nbsp; **14. Then, we subsetted the rules discovered to show the rules with "Tarts" as its right-hand side.**
```R
rules_subset <- subset(rules, (rhs %in% tarts))
rules_subset <- sort(rules_subset, by = "confidence", decreasing = TRUE)
redundant_subset <- which(colSums(is.subset(rules_subset, rules_subset)) > 1)
rules_subset <- rules_subset[-redundant_subset]
inspect(rules_subset)
```

&nbsp;&nbsp; **15. From this, we've gotten some very convincing results.**
```
# lhs                                    rhs               support confidence lift     
# {vanilla frappuccino,walnut cookie} => {chocolate tart}  0.018   1.0000000  19.607843
# {coffee eclair,single espresso}     => {blackberry tart} 0.023   0.9583333  13.127854
# {apple croissant,apple danish}      => {apple tart}      0.040   0.9523810  12.055455
# {apple danish,cherry soda}          => {apple tart}      0.031   0.9393939  11.891063
# {apple croissant,cherry soda}       => {apple tart}      0.031   0.9393939  11.891063
```



###5. What can be suggested to the client? 

1. **Promotion**, special discounts can be made based on the lhs and rhs of the rules mined. ```eg: Buy 2 free 1 combo with discounts.```
 * Where the 2 items must be selected from the lhs's set {Apple croissant, apple danish, cherry soda} pick any of these 2 combos, free 1 apple tart.
 * Combinations of these 3 items gives a very high confidence >.9, therefore we can make an assumption that this combo will work.
2. **Recommendations** to chocolate tart buyers, vanilla, frappucino, walnut cookie, similarly for the second rule.
3. **Placement** for customers' convenience (tarts).
