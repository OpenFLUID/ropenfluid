library("RUnit")
library("ROpenFLUID")

ofsim <- OpenFLUID.openDataset("External.IN")

ret <- OpenFLUID.runSimulationAsExternalProcess(
         ofsim,
         workpath = paste(getwd(), "External.RUN", sep = "/"),
       )
checkEquals(ret, 0)

ret <- OpenFLUID.runSimulationAsExternalProcess(
         ofsim,
         workpath = paste(getwd(), "External.RUNverbose", sep = "/"),
         verbose = ""
       )
checkEquals(ret, 0)

ret <- OpenFLUID.runSimulationAsExternalProcess(
         ofsim,
         workpath = paste(getwd(), "External.RUNlog", sep = "/"),
         verbose = paste(getwd(), "External.RUNlog", "output.log", sep = "/")
       )
checkEquals(ret, 0)