library("RUnit")
library("ROpenFLUID")

ofsimsrc <- OpenFLUID.openDataset("Generators.IN")

OpenFLUID.writeDataset(ofsimsrc, paste(getwd(), "WriteFluidX.IN", sep = "/"))

ofsim <- OpenFLUID.openDataset("WriteFluidX.IN")
OpenFLUID.setCurrentOutputDir(paste(getwd(), "WriteFluidX.OUT", sep = "/"))
OpenFLUID.runSimulation(ofsim)