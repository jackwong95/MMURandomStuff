#import libraries
library(editrules)

mushroom <- read.csv("mushrooms.csv", header = TRUE, na.strings = "?")

#check if there is any unknown values using editrules
#load the rules from rules.txt
E <- editfile("rules.txt")
VE <- violatedEdits(E, mushroom)

print(summary(VE))
#we found that there are no violations of rules within this dataset, can therefore conclude that all #values in this dataset are legit
