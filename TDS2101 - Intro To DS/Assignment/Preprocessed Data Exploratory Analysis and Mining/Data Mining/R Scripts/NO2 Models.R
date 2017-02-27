#############################
#                           #
#NO2 Model for Top 3 States #
#                           #
#############################

# Print the states.
print(no2_top_3)

# 1. Arizona
arizona <- data[data$State == no2_top_3[1], c("Year.Month", "NO2.AQI")]
mean_arizona <- aggregate(arizona[, "NO2.AQI"], list(arizona$Year.Month), mean)
arizona_model <- forecast(auto.arima(mean_arizona[, 2]))

# 2. Colorado
colorado <- data[data$State == no2_top_3[2], c("Year.Month", "NO2.AQI")]
mean_colorado <- aggregate(colorado[, "NO2.AQI"], list(colorado$Year.Month), mean)
colorado_model <- forecast(auto.arima(mean_colorado[, 2]))

# 3. Mexico
mexico <- data[data$State == no2_top_3[3], c("Year.Month", "NO2.AQI")]
mean_mexico <- aggregate(mexico[, "NO2.AQI"], list(mexico$Year.Month), mean)
mexico_model <- forecast(auto.arima(mean_mexico[, 2]))

# Plot the models
png(filename = "Images/NO2 Models/Arizona.png")
plot(arizona_model, type = "l", main = "Forecast for Arizona",
     xlab = "Time-Series", ylab = "NO2 AQI")
dev.off()

png(filename = "Images/NO2 Models/Colorado.png")
plot(colorado_model, type = "l", main = "Forecast for Colorado",
     xlab = "Time-Series", ylab = "NO2 AQI")
dev.off()

png(filename = "Images/NO2 Models/Mexico.png")
plot(mexico_model, type = "l", main = "Forecast for Country Of Mexico",
     xlab = "Time-Series", ylab = "NO2 AQI")
dev.off()