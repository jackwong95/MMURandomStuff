#server.R

#Please run these four line before run the web App
library(shiny)
library(ggplot2)
mushroom <- read.csv("mushrooms.csv", header = TRUE, na.strings = "?")
mushroom$odor <- factor(mushroom$odor, levels = c("a","l","c","y","f","m","n","p","s"), labels=c("Almond","Anise","Creosote","Fishy","Foul","Musty","None","Pungent","Spicy"))

server <- function(input,output){

  output$barChart<-renderPlot({
    
    Char <- input$Var
    
    if(Char == "Bruises")
    {
      ggplot(mushroom, aes(x = bruises, fill = class)) +
      geom_bar(position = "dodge", width = 0.5) +
      xlab("Bruises") +
      ylab("Total Count") +
      labs(fill = "Mushroom Class") +
      scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class")
    }
    else if (Char == "Cap shape")
    {
      ggplot(mushroom, aes(x = cap.shape, fill = class)) + 
      geom_bar(position = "dodge", width = 0.5) +
      xlab("Cap Shape") + 
      ylab("Total Count") +
      theme(axis.text.x = element_text(angle = 90, hjust = 1)) + 
      scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class")
    }
    else if (Char == "Cap by bruises")
    {
      ggplot(mushroom, aes(x = cap.color, fill = class)) +
        geom_bar(width = 0.5) +
        facet_wrap(~bruises + cap.shape, labeller = label_context) +
        ggtitle("Bruises, Cap Shape") + 
        xlab("Cap Color") +
        ylab("Total Count") +
        scale_fill_manual(values = c("green3", "red3"), name = "Mushroom Class") +
        theme(axis.text.x = element_text(angle = 90, hjust = 1))
    }
    else if (Char == "Odor")
    {
      ggplot(mushroom, aes(x = odor, fill = class)) +
        geom_bar(position = "dodge", width = 0.5) +
        xlab("Odor") +
        ylab("Total Count") +
        scale_fill_manual(values=c("green3", "red3"), name="Mushroom Class") 
    }
    else if (Char == "Odorless")
    {
      odorless <- mushroom[mushroom$odor == "None", ]
      
      ggplot(odorless, aes(x = cap.shape, fill = class)) + 
        geom_bar(width = 0.5) +
        facet_wrap(~habitat + bruises) +
        xlab("Cap Color") + 
        ylab("Total Count") +
        ggtitle("Odorless Mushrooms") +
        scale_fill_manual(values = c("green3", "red3")) +
        theme(axis.text.x = element_text(angle = 90, hjust = 1))
      
    }
    
    },height = 400,width = 600)}