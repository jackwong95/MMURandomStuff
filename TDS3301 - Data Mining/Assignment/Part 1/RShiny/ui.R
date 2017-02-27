#ui.R

ui <- fluidPage(
  titlePanel("The edible or Poisonous Mushrooms"),
  sidebarPanel( 
    helpText("Show the bar chart with information of mushrooms."),
    
    selectInput("Var",
                label = "Choose a variable to display :",
                choices = c("Bruises","Cap shape","Cap by bruises", "Odor","Odorless"),
                selected = "Bruises")
  ),
  mainPanel(plotOutput("barChart")))