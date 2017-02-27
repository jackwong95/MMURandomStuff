mushroom <- read.csv("mushrooms.csv", header = TRUE, na.strings = "?")

#count the number of NA by column
naColumnCount <- colSums(is.na(mushroom))
print(naColumnCount)

#count the number that are not NA
noNAColumnCount <- colSums(!is.na(mushroom))
print(noNAColumnCount)

#print out column that are contains NA
print(naColumnCount[naColumnCount > 0])

#we found that all columns have complete observations of 8124, 
#except for the stalk.root which only have 5644 complete observations.