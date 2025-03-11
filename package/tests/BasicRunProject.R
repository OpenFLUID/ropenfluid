library(RUnit)

library("ROpenFLUID")


# RUN PROJECT

OpenFLUID.runProject("Generators.PRJ")
checkTrue(file.exists("Generators.PRJ/OUT/openfluid-messages.log"))

#   RERUN
OpenFLUID.runProject("Generators.PRJ")


# DELETE SIMULATION BLOB

ofdata <- OpenFLUID.openDataset("Generators.IN")

OpenFLUID.printSimulationInfo(ofdata)
checkTrue(!identical(ofdata, new("externalptr")))

OpenFLUID.deleteSimulationBlob(ofdata)
checkTrue(identical(ofdata, new("externalptr")))
