#random forest
library(randomForest)

mushroom <- read.csv("mushrooms.csv", header = TRUE, na.strings = "?")

#to ensure the result is reproducible
set.seed(07734) #olleh hello 

#50% random sample without replacement
idx <- sample(nrow(mushroom), nrow(mushroom)/2)

#split into testing and training set
mush_train <- mushroom[idx, ]
mush_test <- mushroom[-idx, ]

#check if both of them are really random
head(mush_test)
head(mush_train)

#FOR SIMPLE SAMPLE ONLY this is suppose to be done in part 2
#we omit column that contains NA values
mush_train$stalk.root <- NULL
mush_test$stalk.root <- NULL

#apply random forest, we select class, class ~ . for all other columns to be applied to training set
rfm <- randomForest(class ~ ., mush_train)

#print out the random forest's accuracy and result
print(rfm)

#predict the value with the model
p<-predict(rfm, mush_test)

#print out how many rows are classified wrongly
print(sum(mush_test[,1]!=p))

#check the accuracy and the number of observations that are predicted correctly
print(table(mush_test[,1], p))

#get which column contributes the most to the result
print(importance(rfm))
