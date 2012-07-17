library(RUnit)

library("ROpenFLUID")

ofdata = OpenFLUID.openDataset("simple.IN")

OpenFLUID.printSimulationInfo(ofdata)


checkEquals(OpenFLUID.getDeltaT(ofdata),60)
checkEquals(OpenFLUID.getPeriodBeginDate(ofdata),"1997-06-05 04:04:00")
checkEquals(OpenFLUID.getPeriodEndDate(ofdata),"1997-06-05 16:16:00")



# modifications of dataset

OpenFLUID.setDeltaT(ofdata,300)
OpenFLUID.setPeriodBeginDate(ofdata,"1997-06-05 00:00:00")
OpenFLUID.setPeriodEndDate(ofdata,"1997-06-05 20:00:00")

checkEquals(OpenFLUID.getDeltaT(ofdata),300)
checkEquals(OpenFLUID.getPeriodBeginDate(ofdata),"1997-06-05 00:00:00")
checkEquals(OpenFLUID.getPeriodEndDate(ofdata),"1997-06-05 20:00:00")