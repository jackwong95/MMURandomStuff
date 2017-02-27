#############################
#                           #
#SO2 Model for Top 3 States #
#                           #
#############################

# Print the states.
print(so2_top_3)

# 1. Columbia
columbia <- data[data$State == so2_top_3[1], c("Year.Month", "SO2.AQI")]
mean_columbia <- aggregate(columbia[, "SO2.AQI"], list(columbia$Year.Month), mean)
columbia_model <- forecast(auto.arima(mean_columbia[, 2]))

# 2. Kentucky
kentucky <- data[data$State == so2_top_3[2], c("Year.Month", "SO2.AQI")]
mean_kentucky <- aggregate(kentucky[, "SO2.AQI"], list(kentucky$Year.Month), mean)
kentucky_model <- forecast(auto.arima(mean_kentucky[, 2]))

# 3. Missouri
missouri <- data[data$State == so2_top_3[3], c("Year.Month", "SO2.AQI")]
mean_missouri <- aggregate(missouri[, "SO2.AQI"], list(missouri$Year.Month), mean)
missouri_model <- forecast(auto.arima(mean_missouri[, 2]))

# Plot the models
png(filename = "Images/SO2 Models/Columbia.png")
plot(columbia_model, type = "l", main = "Forecast for District of Columbia",
     xlab = "Time-Series", ylab = "SO2 AQI")
dev.off()

png(filename = "Images/SO2 Models/Kentucky.png")
plot(kentucky_model, type = "l", main = "Forecast for Kentucky",
     xlab = "Time-Series", ylab = "SO2 AQI")
dev.off()

png(filename = "Images/SO2 Models/Missouri.png")
plot(missouri_model, type = "l", main = "Forecast for Missouri",
     xlab = "Time-Series", ylab = "SO2 AQI")
dev.off()