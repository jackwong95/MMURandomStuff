library(ggplot2)


# Function to save a ggplot.
#
# Input: ggplot, ggplot 
#        name, image file name.
#
#
savePlot <- function(myPlot, name = "untitled.png") {
        print(myPlot)
        ggsave(name, width = 10.0, height = 5.0)
        dev.off()
}


# Read the dataset into R.
mushroom <- read.csv("mushrooms.csv", header = TRUE, na.strings = "?")


# Count the number of mushrooms with bell shape, "b".
bellEdibleCount <- sum(mushroom$class == "e" & mushroom$cap.shape == "b")
bellNotEdibleCount <- sum(mushroom$class == "p" & mushroom$cap.shape == "b")
bellTotalCount <- bellEdibleCount + bellNotEdibleCount

# Print the percentage of bell shaped edible mushroom.
print(bellEdibleCount/bellTotalCount)

# Print the percentage of bell shaped poisonous mushroom.
print(bellNotEdibleCount/bellTotalCount)


# Count the number of mushrooms with knob shape, "k".
knobEdibleCount <- sum(mushroom$class == "e" & mushroom$cap.shape == "k")
knobNotEdibleCount <- sum(mushroom$class == "p" & mushroom$cap.shape == "k")
knobTotalCount <- knobEdibleCount + knobNotEdibleCount

# Print percentage of knob shaped edible mushroom
print(knobEdibleCount/knobTotalCount)

# Print percentage of knob shaped poisonous mushroom
print(knobNotEdibleCount/knobTotalCount)


# Reword dataset for ease of understanding.
mushroom$class <- factor(mushroom$class, levels = c("e", "p"), labels = c("Edible", "Poisonous"))
mushroom$cap.shape <- factor(mushroom$cap.shape, levels = c("b", "c", "f", "k", "s", "x"), labels = c("Bell", "Conical", "Flat", "Knobbed", "Sunken", "Convex"))
mushroom$bruises <- factor(mushroom$bruises, levels = c("f", "t"), labels = c("No bruises", "Bruises"))
mushroom$cap.color <- factor(mushroom$cap.color, levels = c("n","b","c","g","r","p","u","e","w","y"), labels = c("Brown", "Buff", "Cinnamon", "Gray", "Green", "Pink", "Purple", "Red", "White", "Yellow"))
mushroom$habitat <- factor(mushroom$habitat, levels = c("g", "l", "m", "p", "u", "w", "d"), labels = c("Grasses", "Leaves", "Meadows", "Paths", "Urban", "Waste", "Woods"))
mushroom$population <- factor(mushroom$population, levels = c("a","c","n","s","v","y"), labels = c("Abundant", "Clustered", "Numerous", "Scattered", "Several", "Solitary"))
mushroom$spore.print.color <- factor(mushroom$spore.print.color, levels = c("k", "n", "b","h","r","o","u","w","y"), labels=c("Black", "Brown", "Buff", "Chocolate", "Green", "Orange", "Purple", "White", "Yellow"))
mushroom$odor <- factor(mushroom$odor, levels = c("a","l","c","y","f","m","n","p","s"), labels=c("Almond","Anise","Creosote","Fishy","Foul","Musty","None","Pungent","Spicy"))


# Exploring the dataset.

# 1. A barchart to show the distribution of cap.shape and their respective edibility.
capShapePlot <- ggplot(mushroom, aes(x = cap.shape, fill = class)) + 
        geom_bar(position = "dodge", width = 0.5) +
        xlab("Cap Shape") + 
        ylab("Total Count") +
        theme(axis.text.x = element_text(angle = 90, hjust = 1)) + 
        scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class") 

# 2. A barchart to show the distribution of bruises and their respective edibility.
bruisesPlot <- ggplot(mushroom, aes(x = bruises, fill = class)) +
        geom_bar(position = "dodge", width = 0.5) +
        xlab("Bruises") +
        ylab("Total Count") +
        labs(fill = "Mushroom Class") +
        scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class")

# 3. A barchart to show the distribution of cap.color and their respective edibility.
capPlot <- ggplot(mushroom, aes(x = cap.color, fill = class)) +
        geom_bar(position = "dodge", width = 0.5) +
        xlab("Cap Color") +
        ylab("Total Count") +
        labs(fill = "Mushroom Class") +
        scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class") + 
        theme(legend.position = "top")

# 4. A barchart to show the distribution of cap.color and their respective edibility grouped by bruises and cap.shape.
capByBruisePlot <- ggplot(mushroom, aes(x = cap.color, fill = class)) +
        geom_bar(width = 0.5) +
        facet_wrap(~bruises + cap.shape, labeller = label_context) +
        ggtitle("Bruises, Cap Shape") + 
        xlab("Cap Color") +
        ylab("Total Count") +
        scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class") +
        theme(axis.text.x = element_text(angle = 90, hjust = 1))

# 5. A barchart to show the distribution of mushrooms by habitat and their respective edibility.
habitatPlot <- ggplot(mushroom, aes(x = habitat, fill = class)) +
        geom_bar(position = "dodge", width = 0.5) +
        xlab("Habitat") +
        ylab("Total Count") +
        scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class") 

# 6. A barchart to show the distribution of mushrooms by population and their respective edibility.
populationPlot <- ggplot(mushroom, aes(x = population, fill = class)) +
        geom_bar(position = "dodge", width = 0.5) +
        xlab("Population") +
        ylab("Total Count") +
        scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class") 

# 7. A barchart to show the distribution of mushrooms by spore.print.color and their respective edibility.
sporePrintColorPlot <- ggplot(mushroom, aes(x = spore.print.color, fill = class)) +
        geom_bar(position = "dodge", width = 0.5) +
        xlab("Spore Print Color") +
        ylab("Total Count") +
        scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class") 

# 8. A barchart to show the distribution of mushrooms by odor and their respective edibility.
odorPlot <- ggplot(mushroom, aes(x = odor, fill = class)) +
        geom_bar(position = "dodge", width = 0.5) +
        xlab("Odor") +
        ylab("Total Count") +
        scale_fill_manual(values=c("green3", "red3"), name="Mushroom Class") 

# 9. Explore odorless mushrooms.
odorless <- mushroom[mushroom$odor == "None", ]

mushroomWithNoOdor <- ggplot(odorless, aes(x = cap.shape, fill = class)) + 
        geom_bar(width = 0.5) +
        facet_wrap(~habitat + bruises) +
        xlab("Cap Color") + 
        ylab("Total Count") +
        ggtitle("Odorless Mushrooms") +
        scale_fill_manual(values = c("green3", "red3")) +
        theme(axis.text.x = element_text(angle = 90, hjust = 1))


# Save the plots.
savePlot(capShapePlot, "cap shape.png")
savePlot(bruisesPlot, "bruise.png")
savePlot(capPlot, "cap.png")
savePlot(capByBruisePlot, "cap by bruise.png")
savePlot(habitatPlot, "habitat.png")
savePlot(populationPlot, "population.png")
savePlot(sporePrintColorPlot, "spore print color.png")
savePlot(odorPlot, "odor.png")
savePlot(mushroomWithNoOdor, "mushroom with no odor.png")
