require(ggplot2)

# Read data.
data <- read.csv(file="Report.txt", header=TRUE)

# Plot.
Naive <- lm(Naive~length.of.text, data=data)
BoyerMoore <- lm(Boyer.Moore~length.of.text, data=data)
Horspool <- lm(Horspool~length.of.text, data=data)

par(cex.axis=0.8, cex.sub=0.8, font.axis=2)
plot(1, type="n", xlab="Length of text", ylab="Time taken [microseconds]", xlim=c(1, 2000), ylim=c(1, 10), font.lab=2)
title(main="Analysis (10,000 trials)", sub=list("Text length [1-2000], Pattern length [1-200]", font=2))

abline(Naive, col="red", lwd=3)
abline(BoyerMoore, col="green", lwd=3)
abline(Horspool, col="blue", lwd=3)

legend('topright', c("Naive", "Boyer-Moore", "Horspool"), 
       lty=1, col=c("red", "green", "blue"), bty='n', cex=.75)

# Save plot.
dev.copy(png, filename="Graph.png")
dev.off()