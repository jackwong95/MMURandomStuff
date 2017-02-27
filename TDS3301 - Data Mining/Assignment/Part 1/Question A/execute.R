#load mushroom dataset
mushroom <- read.csv("mushrooms.csv", na.strings = "?")

#look at all the variables and attributes
print(str(mushroom))
#we found that there are 23 variables and 8124 observations, all of them are categorial data.

#sum the missing values by column
columnSumsWithNAs <- colSums(is.na(mushroom))
print(columnSumsWithNAs)

#highlight the column that have missing value
print(columnSumsWithNAs[columnSumsWithNAs > 0])

#distribution of edible/poisonous mushrooms

#mushroom that are edible within the dataset
print(sum(mushroom$class == "e"))
#percentage of edible mushroom within the dataset
print(sum(mushroom$class == "e")/nrow(mushroom))
#mushroom that are poisonous within the dataset
print(sum(mushroom$class == "p"))
#percentage of poisonous mushroom within the dataset
print(sum(mushroom$class == "p")/nrow(mushroom))
