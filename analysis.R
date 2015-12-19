library(ggplot2)
library(grid)

predator_means <- read.csv("100_100__predator_means.csv")
life_means <- read.csv("100_100__life_means.csv")
qplot(x = pp, y = ph, 
      data=predator_means, 
      geom = "tile",
      fill = mean_predators,
      main = "Average Number of Cells Containing Predators",
      ylab = "Prey Migration Parameter",
      xlab = "Predator Migration Parameter")

qplot(x = pp, y = ph, 
      data=life_means, 
      geom = "tile",
      fill = mean_life,
      main = "Average Number of Cells Containing Life",
      ylab = "Prey Migration Parameter",
      xlab = "Predator Migration Parameter")