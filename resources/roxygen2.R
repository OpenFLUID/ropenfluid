library(roxygen2)
roxygenize(package.dir = ".", roclets = c("rd"), load = "source", clean = TRUE)
