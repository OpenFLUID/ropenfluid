library(RUnit)

library("ROpenFLUID")

OpenFLUID.runProject("Generators.PRJ")

checkTrue(file.exists("Generators.PRJ/OUT/openfluid-messages.log"))
