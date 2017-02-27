# Read data
data <- read.csv("../6-cols.csv", stringsAsFactors = FALSE)
data <- data[, 2:ncol(data)]

# Check data validity
str(data)
boxplot(data[, 3:ncol(data)])

mean_data <- aggregate(data[, 3:ncol(data)], list(data$State), mean)
names(mean_data) <- c("State", "CO", "SO2", "O3", "NO2")

color <- c("red", "orange", "green", "blue", "magenta", "violet")

# CO States Selection
png(filename = "Images/State Selection/CO Bar Chart.png")
barplot(mean_data$CO, names.arg = mean_data$State,
        xlab = "States", ylab = "CO AQI", col = color,
        main = "Bar chart for CO AQI")
abline(h = 10, lty = "dashed", col = "red")
dev.off()

# SO2 States Selection
png(filename = "Images/State Selection/SO2 Bar Chart.png")
barplot(mean_data$SO2, names.arg = mean_data$State,
        xlab = "States", ylab = "SO2 AQI", col = color,
        main = "Bar chart for SO2 AQI")
abline(h = 20, lty = "dashed", col = "red")
dev.off()

# O3 States Selection
png(filename = "Images/State Selection/O3 Bar Chart.png")
barplot(mean_data$O3, names.arg = mean_data$State,
        xlab = "States", ylab = "O3 AQI", col = color,
        main = "Bar chart for O3 AQI")
abline(h = 45, lty = "dashed", col = "red")
dev.off()

# NO2 States Selection
png(filename = "Images/State Selection/NO2 Bar Chart.png")
barplot(mean_data$NO2, names.arg = mean_data$State,
        xlab = "States", ylab = "NO2 AQI", col = color,
        main = "Bar chart for NO2 AQI")
abline(h = 37, lty = "dashed", col = "red")
dev.off()

# States
co_top_3 <- mean_data[mean_data$CO > 10.5, "State"]
so2_top_3 <- mean_data[mean_data$SO2 > 20.2, "State"]
o3_top_3 <- mean_data[mean_data$O3 > 45, "State"]
no2_top_3 <- mean_data[mean_data$NO2 > 37, "State"]