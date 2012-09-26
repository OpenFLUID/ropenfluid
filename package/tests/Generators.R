library(RUnit)

library("ROpenFLUID")

ofsim = OpenFLUID.openDataset("Generators.IN")

OpenFLUID.setCurrentOutputDir(paste(getwd(),'/Generators.OUT', sep = ""))

OpenFLUID.printSimulationInfo(ofsim)

OpenFLUID.runSimulation(ofsim)

out=OpenFLUID.loadResult(ofsim,"TestUnits",3,"full")

plot(out$tests.random,type='l')