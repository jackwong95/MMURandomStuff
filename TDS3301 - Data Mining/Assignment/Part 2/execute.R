# Clean up.
rm(list = ls())

# Clean raw SQL code to containing only the information
if (!file.exists("1000_generalize_transactions.csv") || !file.exists("1000_full_transactions.csv"))
{
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
    
    # Items dataset.
    items <- LoadGoods("1000 transactions/EB-build-goods.sql")
    names <- tolower(c("id", paste(items$flavor, items$type, sep = ".")))
    
    # Receipt dataset.
    receipt <- read.csv("1000 transactions/1000-out2.csv", header = FALSE, col.names = names)
    
    receiptIDs <- receipt[, 1]
    receipt <- receipt[,2:ncol(receipt)]
    
    # Convert the receipt to logical only dataset.
    receipt <- apply(receipt, 2, as.logical)
    
    # Turn it into a dataframe.
    receipt <- as.data.frame(receipt)
    
    # Set the receipt id as the primary id of receipt dataset
    rownames(receipt) <- receiptIDs
    
    receipt$full.items <- vector(mode = "character", length = nrow(receipt))
    receipt$type.items <- vector(mode = "character", length = nrow(receipt))
    
    for (i in 1:nrow(receipt))
    {
        receipt[i,]$full.items = paste(gsub(".", " ", colnames(receipt[which(receipt[i,] == TRUE)]), fixed = TRUE), collapse = ",")
        
        temp <- strsplit(colnames(receipt[which(receipt[i,] == TRUE)]), split = '.', fixed = TRUE)
        
        v <- vector(mode = "character")
        
        for(j in 1:length(temp))
        {
            v <- c(v, temp[[j]][2])
        }
        
        receipt[i,]$type.items <- paste(v, collapse = ",")
    }
}

# Library for Association Rules Mining.
require(arules)

# 1. Get generalized items association.

# Convert the generalized data frame to transaction.
if (!file.exists("1000_generalize_transactions.csv")) {
    write(receipt$type.items, file = "1000_generalize_transactions.csv")
}

trG <- read.transactions("1000_generalize_transactions.csv", format = "basket", sep = ",")

# Plot top 15 frequent items.
itemFrequencyPlot(trG, topN = 15, type = "absolute")
dev.copy(png, "Frequency of Generalized Items.png")
dev.off()

# Check frequent items.
itemFrequency(trG)
fsets <- eclat(trG, parameter = list(supp = 0.05, minlen = 2))
inspect(fsets)

# Association Mining Rules with a 1% support, 50% confidence threshold and max length of 5.
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

# lhs           rhs      support confidence lift   
# {lemonade} => {cookie} 0.061   0.559633   1.37502
# {}         => {tart}   0.555   0.555000   1.00000

# The second rules doesn't give anything meaningful as tart is already a best seller.
# People who only buys tart doesn't give much business insights.


# 2. Explore the subset (flavours) of the items.

# Convert the generalized data frame to transaction.
if (!file.exists("1000_full_transactions.csv")) {
    write(receipt$full.items, file = "1000_full_transactions.csv")
}

tr <- read.transactions("1000_full_transactions.csv", format = "basket", sep = ",")

# Plot top 15 frequent items.
itemFrequencyPlot(tr, topN = 15, type = "absolute")
dev.copy(png, "Frequency of Items.png")
dev.off()

itemFrequency(tr)

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



# 3. Let's try to find any association with the lower selling items.
#    As the the top items are already selling well.

# Re-plot the general item.
itemFrequencyPlot(trG, topN = 15, type = "absolute")

frequent <- itemFrequency(tr)

frequent[grep(x = names(frequent), pattern = "juice", fixed = TRUE)] # no subset; only one set
frequent[grep(x = names(frequent), pattern = "soda", fixed = TRUE)]  # no subset; only one set
frequent[grep(x = names(frequent), pattern = "water", fixed = TRUE)] # no subset; only one set
frequent[grep(x = names(frequent), pattern = "twist", fixed = TRUE)] # no subset; only one set
frequent[grep(x = names(frequent), pattern = "pie", fixed = TRUE)] # no subset; only one set


frequent[grep(x = names(frequent), pattern = "coffee", fixed = TRUE)]

# Two types of coffee, and one type of eclair.
# Let's see if coffee buyers buy coffee eclair as well.
rules <- apriori(tr,
                 control = list(verbose = FALSE),
                 parameter = list(supp = 0.01, conf = 0.1),
                 appearance = list(lhs = c("chocolate coffee", "hot coffee"), 
                                   default = "rhs")
)
rules <- sort(rules, by = "confidence", decreasing = TRUE)
inspect(rules)

# hot coffee => coffee eclair only has a 0.28 confidence.
# chocolate coffee => coffee eclair isn't in the list, therefore even lower confidence.

# Let's try the inverse.
rules <- apriori(tr,
                 control = list(verbose = FALSE),
                 parameter = list(supp = 0.01, conf = 0.1),
                 appearance = list(lhs = "coffee eclair", 
                                   default = "rhs")
)
rules <- sort(rules, by = "confidence", decreasing = TRUE)
inspect(rules)

# Similarly, coffee eclair => hot coffee is around 0.28 confidence.
# Therefore, coffee eclair and coffee doesn't have a solid association.


# Let's continue looking for others.
frequent[grep(x = names(frequent), pattern = "danish", fixed = TRUE)]

# Three types of danish, apple, apricot, blueberry.
# Let's see if danish have any association with apple pie.
rules <- apriori(tr,
                 control = list(verbose = FALSE),
                 parameter = list(supp = 0.01, conf = 0.1),
                 appearance = list(lhs = "apple danish", 
                                   default = "rhs")
)
rules <- sort(rules, by = "confidence", decreasing = TRUE)
inspect(rules)

# Let's try the inverse.
rules <- apriori(tr,
                 control = list(verbose = FALSE),
                 parameter = list(supp = 0.01, conf = 0.1),
                 appearance = list(lhs = "apple pie", 
                                   default = "rhs")
)
rules <- sort(rules, by = "confidence", decreasing = TRUE)
inspect(rules)

# No assocation.


# Let's try check "apple" flavour products.
frequent[grep(x = names(frequent), pattern = "apple", fixed = TRUE)]

# 4 products with apple flavour: apple croissant, apple danish, apple pie, apple tart.
rules <- apriori(tr,
                 control = list(verbose = FALSE),
                 parameter = list(supp = 0.01, conf = 0.1),
                 appearance = list(lhs = "apple croissant", 
                                   default = "rhs")
)
rules <- sort(rules, by = "confidence", decreasing = TRUE)
inspect(rules)

rules <- apriori(tr,
                 control = list(verbose = FALSE),
                 parameter = list(supp = 0.01, conf = 0.1),
                 appearance = list(lhs = "apple tart", 
                                   default = "rhs")
)
rules <- sort(rules, by = "confidence", decreasing = TRUE)
inspect(rules)

# Considerable.
# Apple Tart => Apple Croissant
# Apple Tart => Apple Danish
# They both have a confidence over 0.5.
# The bakery can increase their Apple Croissant and Apple Danish sales together with Apple Tart.


# Let's try another approach / look from different perspective.
# What's leads to people buying Tarts?

# A vector containing all the different types of tart.
tarts <- c(names(frequent[grep(x = names(frequent), pattern = "tart", fixed = TRUE)]))

rules <- apriori(tr,
                 control = list(verbose = F),
                 parameter = list(supp = 0.01, conf = 0.5, maxlen = 5)
)

rules_subset <- subset(rules, (rhs %in% tarts))
rules_subset <- sort(rules_subset, by = "confidence", decreasing = TRUE)
redundant_subset <- which(colSums(is.subset(rules_subset, rules_subset)) > 1)
rules_subset <- rules_subset[-redundant_subset]
inspect(rules_subset)

# Useful rules found.
# lhs                                    rhs               support confidence lift     
# {vanilla frappuccino,walnut cookie} => {chocolate tart}  0.018   1.0000000  19.607843
# {coffee eclair,single espresso}     => {blackberry tart} 0.023   0.9583333  13.127854
# {apple croissant,apple danish}      => {apple tart}      0.040   0.9523810  12.055455
# {apple danish,cherry soda}          => {apple tart}      0.031   0.9393939  11.891063
# {apple croissant,cherry soda}       => {apple tart}      0.031   0.9393939  11.891063
