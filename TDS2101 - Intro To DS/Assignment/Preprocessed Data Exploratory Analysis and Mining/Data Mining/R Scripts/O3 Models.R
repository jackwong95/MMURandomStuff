#############################
#                           #
# O3 Model for Top 3 States #
#                           #
#############################

# Print the states.
print(o3_top_3)

# 1. Indiana
indiana <- data[data$State == o3_top_3[1], c("Year.Month", "O3.AQI")]
mean_indiana <- aggregate(indiana[, "O3.AQI"], list(indiana$Year.Month), mean)
indiana_model <- forecast(auto.arima(mean_indiana[, 2]))

# 2. North Carolina
carolina <- data[data$State == o3_top_3[2], c("Year.Month", "O3.AQI")]
mean_carolina <- aggregate(carolina[, "O3.AQI"], list(carolina$Year.Month), mean)
carolina_model <- forecast(auto.arima(mean_carolina[, 2]))

# 3. Tennessee
tennessee <- data[data$State == o3_top_3[3], c("Year.Month", "O3.AQI")]
mean_tennessee <- aggregate(tennessee[, "O3.AQI"], list(tennessee$Year.Month), mean)
tennessee_model <- forecast(auto.arima(mean_tennessee[, 2]))

# Plot the models
png(filename = "Images/O3 Models/Indiana.png")
plot(indiana_model, type = "l", main = "Forecast for Indiana",
     xlab = "Time-Series", ylab = "O3 AQI")
dev.off()

png(filename = "Images/O3 Models/Carolina.png")
plot(carolina_model, type = "l", main = "Forecast for North Carolina",
     xlab = "Time-Series", ylab = "O3 AQI")
dev.off()

png(filename = "Images/O3 Models/Tennessee.png")
plot(tennessee_model, type = "l", main = "Forecast for Tennessee",
     xlab = "Time-Series", ylab = "O3 AQI")
dev.off()