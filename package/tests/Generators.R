library(RUnit)

library("ROpenFLUID")

ofsim = OpenFLUID.openDataset("Generators.IN")

OpenFLUID.setCurrentOutputDir(paste(getwd(),'/Generators.OUT', sep = ""))

OpenFLUID.addVariablesExportAsCSV(ofsim,"TestUnits")

OpenFLUID.printSimulationInfo(ofsim)

OpenFLUID.runSimulation(ofsim)

out=OpenFLUID.loadResult(ofsim,"TestUnits",3,"tests.random")

print(out)

plot(out$tests.random,type='l')