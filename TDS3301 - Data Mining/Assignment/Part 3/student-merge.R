require("caTools")
require("reshape2")
require("FSelector")
require("rpart")
require("randomForest")
require("caret")
require("leaps")

rm(list = ls())

setwd("C:/Users/Jack/Documents/TDS3301DataMining/Part 3")

math <- read.table("student-mat.csv",sep=";",header=TRUE)

set.seed(123)

#0.7 for training 0.3 for testing, standard ratio
temp <- sample.split(math, SplitRatio = .7)
math_train <- subset(math, temp == TRUE)
math_test <- subset(math, temp == FALSE)

# A. exploratory analysis

print(dim(math_train))
print(colnames(math_train))
print(str(math_train))
print(unique(math_train$G3))
print(apply(apply(math_train, 2, is.na), 2, sum))

get_outliers <- function(vec)
{
        if(is.numeric(vec))
        {
                plt <- boxplot(vec)
                plt$out      
        }
}

#print out of the outliers of all numeric columns
print(apply(math_train[,sapply(math_train, is.integer)], 2, get_outliers))

#check if the 2 datasets have same column so we can merge them
print(names(port) %in% names(math))

#look at the information gain using entropy
weights <- information.gain(G3~., math_train)
#sort them to see which feature i should investigate deeper into
weights <- weights[order(weights$attr_importance, decreasing = TRUE), , drop = FALSE]
print(weights)

#Buidling the models
#1. recursive partioning and regression tree

#take all information gain until 12th, because it's only less than 10% of information gain.
formula <- as.simple.formula(cutoff.k(weights, 12), "G3")
tree1 <- rpart(formula, math_train)

#accuracy measurement of tree
printcp(tree1)
plotcp(tree1)
summary(tree1)

#plot the decision tree
plot(tree1, uniform = TRUE, main = "Classification Tree For Final Grade G3")
text(tree1, use.n=TRUE, all=TRUE, cex=.8)
#data.frame(row.names = as.numeric(idx), dat = lol)

rplot <- predict(tree1, math_test)

predictionDF <- data.frame(row.names = as.numeric(rownames(math_test)), actual = math_test$G3, predicted = rplot)
predictionDF$error <- abs(predictionDF$actual - predictionDF$predicted)

print(sum(predictionDF$error < 1) / nrow(predictionDF))
print(sum(predictionDF$error))

#2. random forest
tree2 <- randomForest(formula, math_train)
print(tree2)
print(importance(tree2))

rf <- predict(tree2, math_test)

predictionDF <- data.frame(row.names = as.numeric(rownames(math_test)), actual = math_test$G3, predicted = rf)
predictionDF$error <- abs(predictionDF$actual - predictionDF$predicted)

print(sum(predictionDF$error < 1) / nrow(predictionDF))
print(sum(predictionDF$error))

#3. bayers theorem 
tree3 <- train(formula, math_train)

bayer <- predict(tree3, math_test)
        
predictionDF <- data.frame(row.names = as.numeric(rownames(math_test)), actual = math_test$G3, predicted = bayer)
predictionDF$error <- abs(predictionDF$actual - predictionDF$predicted)

print(sum(predictionDF$error < 1) / nrow(predictionDF))
print(sum(predictionDF$error))
  
#4. multiple linear regression
lm <- lm(formula, math_train)

lm_pred <- predict(lm, math_test)

predictionDF <- data.frame(row.names = as.numeric(rownames(math_test)), actual = math_test$G3, predicted = lm_pred)
predictionDF$error <- abs(predictionDF$actual - predictionDF$predicted)

print(sum(predictionDF$error < 1) / nrow(predictionDF))
print(sum(predictionDF$error))

#ceil all the values if there is any decimal, the classified value should only contain integer.
rplot <- ceiling(rplot)
rf <- ceiling(rf)
bayer <- ceiling(bayer)
lm_pred <- ceiling(lm_pred)
#make all of their IDs the same so we can compare the graph later.
names(rplot) <- 1:length(rplot)
names(rf) <- 1:length(rf)
names(bayer) <- 1:length(lm_pred)
names(lm_pred) <- 1:length(bayer)
actual <- math_test$G3
names(actual) <- 1:length(actual)
predicted <- cbind(rplot, rf, bayer, lm_pred, actual = actual)
tidy <- melt(predicted)
colnames(tidy) <- c("id", "classifier", "value")

p <- ggplot(data = tidy, aes(x = id, y = value, col = classifier, group = classifier)) + geom_line() + facet_wrap(~classifier)
print(p)

#print confusion table
print("CONFUSION TABLE")
print(table(actual, rplot))
print(table(actual, rf))
print(table(actual, bayer))
print(table(actual, lm_pred))


#TO DO
port <- read.table("student-por.csv",sep=";",header=TRUE)

#outer join
math_port <- merge(math,port,by=c("school","sex","age","address","famsize","Pstatus","Medu","Fedu","Mjob","Fjob","reason","nursery","internet"), all = TRUE)
