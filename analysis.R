library(ggplot2)

preds <- read.csv("test_2.csv")

pps <- unique(preds$pp)
phs <- unique(preds$ph)
m <- c()
for (ph in phs){
  print(paste("ph: ",ph))
  for(pp in pps){
    print(pp)
    # append to list (?) I need a more "R" way of doing this
    sim <- preds[(preds$ph == ph) & (preds$pp == pp),]
    m <- c(m, mean(sim$cells_with_predators))
  }
}

mm <- matrix(m, nrow = length(phs), byrow = TRUE)

image(pps, phs, mm)

plot_all <- function (){
  for (i in unique(preds$id)){
    sim <- preds[preds$id == i,]
    p <- ggplot(sim, aes(x = age, y = cells_with_predators))
    print(p + geom_line() + ggtitle(
      paste("ph:", sim$ph[[1]], " pp:", sim$pp[[1]])
    ))
  }
}