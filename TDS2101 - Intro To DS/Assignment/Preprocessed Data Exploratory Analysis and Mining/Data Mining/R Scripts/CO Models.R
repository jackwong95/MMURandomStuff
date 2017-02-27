#############################
#                           #
# CO Model for Top 3 States #
#                           #
#############################

# Print the states.
print(co_top_3)

# 1. Arizona
arizona <- data[data$State == co_top_3[1], c("Year.Month", "CO.AQI")]
mean_arizona <- aggregate(arizona[, "CO.AQI"], list(arizona$Year.Month), mean)
arizona_model <- forecast(auto.arima(mean_arizona[, 2]))

# 2. Mexico
mexico <- data[data$State == co_top_3[2], c("Year.Month", "CO.AQI")]
mean_mexico <- aggregate(mexico[, "CO.AQI"], list(mexico$Year.Month), mean)
mexico_model <- forecast(auto.arima(mean_mexico[, 2]))

# 3. Columbia
columbia <- data[data$State == co_top_3[3], c("Year.Month", "CO.AQI")]
mean_columbia <- aggregate(columbia[, "CO.AQI"], list(columbia$Year.Month), mean)
columbia_model <- forecast(auto.arima(mean_columbia[, 2]))

# Plot the models
png(filename = "Images/CO Models/Arizona.png")
plot(arizona_model, type = "l", main = "Forecast for Arizona",
     xlab = "Time-Series", ylab = "CO AQI")
dev.off()

png(filename = "Images/CO Models/Mexico.png")
plot(mexico_model, type = "l", main = "Forecast for Country of Mexico",
     xlab = "Time-Series", ylab = "CO AQI")
dev.off()

png(filename = "Images/CO Models/Columbia.png")
plot(columbia_model, type = "l", main = "Forecast for District of Columbia",
      xlab = "Time-Series", ylab = "CO AQI")
dev.off()