library(shiny)

# Define UI for application that draws a histogram
shinyUI(fluidPage(
        
        tags$head(
                tags$style(HTML("
                        @import url('//fonts.googleapis.com/css?family=Lobster|Cabin:400,700');
                        
                        h1 {
                        font-family: 'Lobster', cursive, bold;
                        font-weight: 500;
                        line-height: 3;
                        color: 	#00FFFF;
                        }
                
                "))
        ),
        
        headerPanel("My Convincing Results"),
        mainPanel(
                list(tags$head(tags$style("body {background-color: #ff3399; font-family: 'sans-serif; '}"))),
                p("lhs                                    rhs               support confidence lift  "),
                p("{vanilla frappuccino,walnut cookie} => {chocolate tart}  2%   100%  19.607843"),
                p("{coffee eclair,single espresso}     => {blackberry tart} 2%   96%  13.127854"),
                p("{apple croissant,apple danish}      => {apple tart}      4%   95%  12.055455"),
                p("{apple danish,cherry soda}          => {apple tart}      3%   94%  11.891063"),
                p("{apple croissant,cherry soda}       => {apple tart}      3%   94%  11.891063")
        )
))