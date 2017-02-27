####### LOADING DATA #######
math <- read.table("student-mat.csv",sep=";",header=TRUE)
port <- read.table("student-por.csv",sep=";",header=TRUE)




####### UNDERSTANDING THE STRUCTURE OF THE DATA #######
# We want to explore whether if there is any relation if student taking 2 subjects.

print(names(port) %in% names(math))

# Since both dataset are from the same features, we can merge it
# because student details are provided within both portuguese and maths.
# Therefore there is a lot of redundant columns, and there will be a 
# lot of NA columns for those that are taking one subject
# and preprocessing is required.

# Outer join both dataset
merged <- merge(math,port,by=c("school","sex","age","address","famsize",
                               "Pstatus","Medu","Fedu","Mjob","Fjob",
                               "reason","nursery","internet"), all = TRUE)

# To prove that there's a lot of NAs coerced.
print(colSums(is.na(merged)))

# 275 students are not taking mathematics.
# 25 students are not taking portuguese 




####### PRE-PROCESS #######
# We will impute values for both sides eventhough 
# we will be truncating one side later for readability.

# 1. Get the missing rows.
math.missing <- which(is.na(merged$guardian.x))
port.missing <- which(is.na(merged$guardian.y))

# 2. Get the columns to be filled.
math.cols <- names(colSums(apply(merged, 2, is.na))[colSums(apply(merged, 2, is.na)) == 275])
port.cols <- names(colSums(apply(merged, 2, is.na))[colSums(apply(merged, 2, is.na)) == 25])

# 3. Remove the supposed-to-be NAs columns.
math.cols <- math.cols[!math.cols %in% c("G1.x", "G2.x", "G3.x")]
port.cols <- port.cols[!port.cols %in% c("G1.y", "G2.y", "G3.y")]

# 4. Fill values.
merged[math.missing, math.cols] <- merged[math.missing, port.cols]
merged[port.missing, port.cols] <- merged[port.missing, math.cols]

# 5. Truncate one side (can be any).
merged <- merged[, !names(merged) %in% port.cols]

# 6. Rename student information columns.
names(merged)[names(merged) %in% math.cols] <- substr(math.cols, 1, nchar(math.cols)-2)

# 7. Check whether our processed data is what we expected.
print(colSums(is.na(merged)))

# 8. Convert numeric into point grading scale 
# https://en.wikipedia.org/wiki/Academic_grading_in_Portugal
# Since our dataset includes student who didn't take, we'll have an extra level (NOT TAKEN)
require(forcats)
quantilize_grade <- function(dat)
{
        temp <- cut(dat, breaks = c(0, 3, 9, 13, 15, 17, 20), labels = c("Poor", "Weak", "Sufficient", "Good", "Very Good", "Excellent"))
        temp <- fct_explicit_na(temp, "None")
}

merged$G1.math <- quantilize_grade(merged$G1.x)
merged$G2.math <- quantilize_grade(merged$G2.x)
merged$G3.math <- quantilize_grade(merged$G3.x)
merged$G1.port <- quantilize_grade(merged$G1.y)
merged$G2.port <- quantilize_grade(merged$G2.y)
merged$G3.port <- quantilize_grade(merged$G3.y)

print(any(is.na(merged[, ! names(merged) %in% c("G1.x", "G2.x", "G3.x", "G1.y", "G2.y", "G3.y")])))
print(str(merged))




####### EXPLORATORY #######
boxplot(merged)

# Let's observe the average trends of the grade across the terms.

dev.off()
dev.new()
png("Plots/avg grade trends across the terms.png", width=1000)
plot(colMeans(merged[!is.na(merged$G1.x), c("G1.x", "G2.x", "G3.x")]), type="l",
     lwd=2, col="red", ylab="Grade", ylim=c(5, 15), xlab="Terms", xaxt ='n',
     main="Average Grade Trends Across the Terms")
axis(1, 1:3, c("G1", "G2", "G3"))

lines(colMeans(merged[!is.na(merged$G1.y), c("G1.y", "G2.y", "G3.y")]),
      lwd=2, col="blue")

legend('topright', c("Portuguese", "Mathematics"), lty=1,
       lwd=2, col=c("blue", "red"), bty="n")

# Let's see if there is a change between schools

dev.off()
dev.new()
png("Plots/avg grade trends across the terms with schools.png", width=1000)
par(mfrow=c(1, 3))

# AVERAGE
plot(colMeans(merged[!is.na(merged$G1.x), c("G1.x", "G2.x", "G3.x")]), type="l",
     lwd=2, col="red", ylab="Grade", ylim=c(5, 15), xlab="Terms", xaxt ='n',
     main="Average Grade Trends Across the Terms")
axis(1, 1:3, c("G1", "G2", "G3"))

lines(colMeans(merged[!is.na(merged$G1.y), c("G1.y", "G2.y", "G3.y")]),
      lwd=2, col="blue")

legend('topright', c("Portuguese", "Mathematics"), lty=1,
       lwd=2, col=c("blue", "red"), bty="n")

# SCHOOL GP
plot(colMeans(merged[which((merged[,c("school")]=="GP") & !is.na(merged$G1.x)), c("G1.x", "G2.x", "G3.x")]), type="l",
     lwd=2, col="red", ylab="Grade", ylim=c(5, 15), xlab="Terms", xaxt ='n',
     main="Average Grade Trends Across the Terms For GP")
axis(1, 1:3, c("G1", "G2", "G3"))

lines(colMeans(merged[which((merged[,c("school")]=="GP") & !is.na(merged$G1.y)), c("G1.y", "G2.y", "G3.y")]),
      lwd=2, col="blue")

legend('topright', c("Portuguese", "Mathematics"), lty=1,
       lwd=2, col=c("blue", "red"), bty="n")

# SCHOOL MS
plot(colMeans(merged[which((merged[,c("school")]=="MS") & !is.na(merged$G1.x)), c("G1.x", "G2.x", "G3.x")]), type="l",
     lwd=2, col="red", ylab="Grade", ylim=c(5, 15), xlab="Terms", xaxt ='n',
     main="Average Grade Trends Across the Terms For MS")
axis(1, 1:3, c("G1", "G2", "G3"))

lines(colMeans(merged[which((merged[,c("school")]=="MS") & !is.na(merged$G1.y)), c("G1.y", "G2.y", "G3.y")]),
      lwd=2, col="blue")

legend('topright', c("Portuguese", "Mathematics"), lty=1,
       lwd=2, col=c("blue", "red"), bty="n")

dev.off()
dev.new()
png("Plots/maths grade distribution.png", width=1000)

require(ggplot2)
ggplot(data = merged[merged$G3.math != "None", ], aes(x = G3.math)) + 
        geom_bar(aes(fill = as.factor(G3.math))) +
        scale_fill_discrete(guide = guide_legend(title = "Grade")) +
        ggtitle("Mathematics")

dev.off()
dev.new()
png("Plots/portugese grade distribution.png", width=1000)

# A lot of students are not taking Mathematics.
# Ignoring the gradient, the curve is slightly skewed.
# However, if we were to combine "Good", "Very Good" and "Excellent",
# the data will follow Gaussian distribution.

ggplot(data = merged[merged$G3.port != "None", ], aes(x = G3.port)) + 
        geom_bar(aes(fill = as.factor(G3.port))) +
        scale_fill_discrete(guide = guide_legend(title = "Grade")) +
        ggtitle("Portuguese")

# Portuguese follows a Gaussian distribution.

dev.off()
dev.new()




####### INFORMATION GAIN #######
require("FSelector")

math.gain <- information.gain(G3.math~., merged)
math.gain <- math.gain[order(math.gain$attr_importance, decreasing = TRUE), , drop = FALSE]
math.gain = math.gain[math.gain$attr_importance <= 0.01, , drop = FALSE]

port.gain <- information.gain(G3.port~., merged)
port.gain <- port.gain[order(port.gain$attr_importance, decreasing = TRUE), , drop = FALSE]
port.gain = port.gain[port.gain$attr_importance <= 0.01, , drop = FALSE]

math.formula <- paste(rownames(math.gain), collapse = "-")
math.formula <- paste("G3.math", math.formula, sep = "~.-")
math.formula <- as.formula(math.formula)

port.formula <- paste(rownames(port.gain), collapse = "-")
port.formula <- paste("G3.port", port.formula, sep = "~.-")
port.formula <- as.formula(port.formula)

print(math.formula)
print(port.formula)

# Entropy shows that G2.math is a good feature.
# Let's observe the effect on predicting G3.math.

# Save plot since it's too big to be displayed in R.
png("Plots/G2 and G3 Density Plot.png", width=1000)
par(mfrow=c(1, 5))

plot(density(merged[!is.na(merged$G1.x) & merged$G2.math=="Weak",]$G2.x), col="blue", main="Weak")
lines(density(merged[!is.na(merged$G1.x) & merged$G3.math=="Weak",]$G3.x), col="red")

plot(density(merged[!is.na(merged$G1.x) & merged$G2.math=="Sufficient",]$G2.x), col="blue", main="Sufficient")
lines(density(merged[!is.na(merged$G1.x) & merged$G3.math=="Sufficient",]$G3.x), col="red")

plot(density(merged[!is.na(merged$G1.x) & merged$G2.math=="Good",]$G2.x), col="blue", main="Good")
lines(density(merged[!is.na(merged$G1.x) & merged$G3.math=="Good",]$G3.x), col="red")

plot(density(merged[!is.na(merged$G1.x) & merged$G2.math=="Very Good",]$G2.x), col="blue", main="Very Good")
lines(density(merged[!is.na(merged$G1.x) & merged$G3.math=="Very Good",]$G3.x), col="red")

plot(density(merged[!is.na(merged$G1.x) & merged$G2.math=="Excellent",]$G2.x), col="blue", main="Excellent")
lines(density(merged[!is.na(merged$G1.x) & merged$G3.math=="Excellent",]$G3.x), col="red")

legend('topright', c("G2", "G3"), lty=1, col=c("blue", "red"), bty='n')
dev.off()
# The plots confirms that there are very little variations from G2 to G3.

# If the FSelector packages is not supported.
math.formula <- as.formula(G3.math~.-guardian-nursery-Pstatus-activities-famsup-famsize
                           -age-traveltime-studytime-famrel-freetime-goout-Dalc-Walc-health,
                           train)
port.formula <- as.formula(G3.port~.-address-famsup-sex-romantic-nursery-activities
                           -famsize-Pstatus-Medu-Fedu-traveltime-studytime-famrel
                           -freetime-goout-Dalc-Walc-health-absences, train)




####### SAMPLING #######
# Seed.
require(caTools)
set.seed(123)

# Holdout, 0.7 for training 0.3 for testing.
temp <- sample.split(merged, SplitRatio = .7)
train <- subset(merged, temp == TRUE)[, !names(merged) %in% c("G1.x", "G2.x", "G3.x", "G1.y", "G2.y", "G3.y")]
test <- subset(merged, temp == FALSE)[, !names(merged) %in% c("G1.x", "G2.x", "G3.x", "G1.y", "G2.y", "G3.y")]




####### DECISION TREE #######
require("tree")

# 1. Decision Tree for classifying the grade for Mathematics.
math.tree <- tree(math.formula, train)

plot(math.tree)
text(math.tree, pretty=0)
title("Classification Tree Final Math Grades")
dev.off()

# As observed, we would like to remove the last branch, where
# absences < 1, we already know that if G1.math or G2.math is none,
# G3.math will 100% be none since we are the ones who imputed it.
math.tree <- prune.misclass(math.tree, best = 5)

# Save plot.
png("Plots/Maths Decision Tree.png")
plot(math.tree)
text(math.tree, pretty=0)
title("Classification Tree Final Math Grades")
dev.off()

# Test the Tree.
math.predict <- predict(math.tree, test, type="class")

# Confusion Table
math.tree.table <- table(math.predict, test$G3.math)


# 2. Decision Tree for classifying the grade for Portuguese.
port.tree <- tree(port.formula, train)

plot(port.tree)
text(port.tree, pretty=0)
title("Classification Tree Final Portuguese Grades")
dev.off()

# This time, the tree is more balanced. We will just
# prune the last few branches.
port.tree <- prune.misclass(port.tree, best = 6)

# Save plot.
png("Plots/Portuguese Decision Tree.png")
plot(port.tree)
text(port.tree, pretty=0)
title("Classification Tree Final Portuguese Grades")
dev.off()

# Test the Tree.
port.predict <- predict(port.tree, test, type="class")

# Confusion Table
port.tree.table <- table(port.predict, test$G3.port)




####### NAIVE BAYES #######
require(e1071)

# Since Naive Bayes can support every feature and it's really
# fast since it relies on bayesian probability (prior and posterior).
# Therefore, we will use all features.

# 1. Naive Bayes for Mathematics.
naive.bayes.math <- naiveBayes(G3.math~., train)
math.prediction <- predict(naive.bayes.math, test)

# Confusion Table
math.bayes.table <- table(math.prediction, test$G3.math)


# 2. Naive Bayes for Portuguese.
naive.bayes.port <- naiveBayes(G3.port~., train)
port.prediction <- predict(naive.bayes.port, test)

# Confusion Table
port.bayes.table <- table(port.prediction, test$G3.port)




####### NEURAL NETWORKS #######
require(neuralnet)

# Since neural networks works very well with numerical data,
# We will be building the model using the original grades.
# We will first normalize it then "stretch" it back to 0-20
# and finally classify it as a post-processing.

numeric_data <- merged[, sapply(merged, is.numeric)]
numeric_data[is.na(numeric_data)] <- -1

# Normalization
numeric_data <- sapply(numeric_data, function(x){x <- (x-min(x))/(max(x)-min(x))})

train <- subset(numeric_data, temp == TRUE)
test <- subset(numeric_data, temp == FALSE)

# As neural network requires a lot of processing
# We will drop some features that we feel are not suitable.
drop <- c("age", "traveltime", "freetime", "goout", "Dalc", "Walc")

train <- train[, !colnames(train) %in% drop]
test <- test[, !colnames(test) %in% drop]

# Formula for NN.
names <- colnames(train)

math.formula <- paste(names[names != "G3.x"], collapse = "+")
math.formula <- paste("G3.x~", math.formula)
math.formula <- as.formula(math.formula)

port.formula <- paste(names[names != "G3.y"], collapse = "+")
port.formula <- paste("G3.y~", port.formula)
port.formula <- as.formula(port.formula)

# 1. Mathematics.
# Hidden layers are chosen 6 and 3 to some a "pyramid",
# 12 inputs nodes, first hidden layer with 6, second with 3, and 1 output.
math.nn <- neuralnet(math.formula, train, hidden=c(6, 3), threshold=0.05)

math.prediction <- compute(math.nn, test[,!colnames(test) %in% c("G3.x")])
math.prediction.result <- math.prediction$net.result

math.nn.table <- table(ceiling(math.prediction.result * 7), ceiling(test[, "G3.x"] * 7))


# 2. Portuguese.
port.nn <- neuralnet(port.formula, train, hidden=c(6, 3), threshold=0.05)

port.prediction <- compute(port.nn, test[,!colnames(test) %in% c("G3.y")])
port.prediction.result <- port.prediction$net.result

port.nn.table <- table(ceiling(port.prediction.result * 7), ceiling(test[, "G3.y"] * 7))




####### COMPARISON #######
# Accuracy Comparison.
# 1. Mathematics.
#    - math.tree.table
#    - math.bayes.table
#    - math.nn.table

# 2. Portuguese.
#    - port.tree.table
#    - port.bayes.table
#    - port.nn.table

print.accuracy <- function(text, table)
{
        numerator <- 0
        denominator <- sum(table)
        
        for (i in 1:nrow(table))
        {
                numerator <- numerator + table[i, i]
        }
        accuracy <- numerator/denominator
        
        cat(text)
        cat(paste("Accuracy: ", accuracy, "\n", sep=""))
}

print.stuff <- function(math, port)
{
        cat("1. Mathematics\n")
        for (i in seq(1, length(math), 2))
        {
                print.accuracy(math[[i]], math[[i+1]])
        }
        cat("\n")
        
        cat("2. Portuguese\n")
        for (i in seq(1, length(port), 2))
        {
                print.accuracy(port[[i]], port[[i+1]])
        }
}

math <- list("i) Decision Tree, ", math.tree.table,
             "ii) Naive Bayes, ", math.bayes.table,
             "iii) Neural Networks ", math.nn.table)

port <- list("i) Decision Tree, ", port.tree.table,
             "ii) Naive Bayes, ", port.bayes.table,
             "iii) Neural Networks ", port.nn.table)

print.stuff(math, port)


# Overall, Decision Tree did a lot better than Naive Bayes.
# However, Decision Tree does not support missing values unlike Naive Bayes.
# Furthermore, our trees relied too much on the second term grade, G2.
# Neural networks works only with numerical data and its accuracy solely
# depends on the number of nodes in the hidden layer and number of epoch used to train it.

# Another reason why Decision Tree worked better here is because
# Naive Bayes and Neural Networks was not able to capture the "best" feature (through gain)
# instead they used whatever features they were trained with.

# Conversely, less features means more imputation if the new data has a lot of missing values.