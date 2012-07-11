library(RUnit)

library("ROpenFLUID")

ofdata = OpenFLUID.openDataset("simple.IN")

OpenFLUID.printSimulationInfo(ofdata)


checkEquals(OpenFLUID.getDeltaT(ofdata),60)




# modifications of dataset

OpenFLUID.setDeltaT(ofdata,300)

checkEquals(OpenFLUID.getDeltaT(ofdata),300)