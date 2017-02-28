library(ggplot2)

data <- read.csv(file="Report II.txt", header=TRUE)

labels <- c(
    '1'="Length of Pattern: 1",
    '2'="Length of Pattern: 2",
    '3'="Length of Pattern: 3",
    '4'="Length of Pattern: 4",
    '5'="Length of Pattern: 5"
)

ggplot(data, aes(x=length.of.text)) + 
    geom_smooth(aes(y=Naive, color="Naive"), method="lm", se=FALSE) +
    geom_smooth(aes(y=Boyer.Moore, color="Boyer-Moore"), method="lm", se=FALSE) +
    geom_smooth(aes(y=Horspool, color="Horspool"), method="lm", se=FALSE) +
    facet_wrap(~length.of.pattern, labeller=as_labeller(labels)) +
    scale_color_manual(name="Color", values=c("Naive"="red", "Boyer-Moore"="blue","Horspool"="green")) +
    ylab("Time Taken [microsecond]") +
    xlab("Length of Text") +
    ggtitle("String Search Algorithms Comparison") +
    theme(plot.title=element_text(hjust=0.5),
          plot.margin = unit(c(1,1,1,1), "cm"),
          legend.position=c(0.8, 0.33),
          legend.background=element_rect(fill="white", colour="orange"))

dev.copy(png, filename = "Graph II.png")
dev.off()