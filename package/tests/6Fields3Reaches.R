library(RUnit)

library("ROpenFLUID")

OpenFLUID.setCurrentOutputDir(paste(getwd(),'/6fields_3reaches.OUT', sep = ""))

ofdata = OpenFLUID.openDataset("6fields_3reaches.IN")

OpenFLUID.printSimulationInfo(ofdata)


checkEquals(OpenFLUID.getDeltaT(ofdata),60)
checkEquals(OpenFLUID.getPeriodBeginDate(ofdata),"1997-06-05 04:04:00")
checkEquals(OpenFLUID.getPeriodEndDate(ofdata),"1997-06-05 16:16:00")

checkEqualsNumeric(as.numeric(OpenFLUID.getSimulatorParam(ofdata,"tests.funcA","pA1")),0.000005)
checkEqualsNumeric(as.numeric(OpenFLUID.getSimulatorParam(ofdata,"tests.funcC","pC2")),0.045)
checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.funcC","fakeparam"),"")
checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.fakefunc","fakeparam"),"")
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"SU","tests.fixed","fixedvalue")),12.7)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","min")),20.53)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","max")),50)
checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gparam1"),"1.1;2.1")
checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gfakeparam"),"")
checkEqualsNumeric(as.numeric(OpenFLUID.getObserverParam(ofdata,"tests.obsA","pA1")),10)
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsA","pA2"),"valA2")
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsA","fakeparam"),"")
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.fakeobs","fakeparam"),"")

checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",1,"area")),1216.29)
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",5,"area")),3024.27)
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",3,"slope")),0.02)
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"RS",2,"length")),170)
checkEqualsNumeric(OpenFLUID.getAttribute(ofdata,"RS",18,"length"),"")
checkEqualsNumeric(OpenFLUID.getAttribute(ofdata,"RS",1,"fakedata"),"")

uclasses = OpenFLUID.getUnitsClasses(ofdata)
print(uclasses)
checkEqualsNumeric(length(uclasses),2)
uRS = OpenFLUID.getUnitsIDs(ofdata,"RS")
print(uRS)
checkEqualsNumeric(length(uRS),3)
uSU = OpenFLUID.getUnitsIDs(ofdata,"SU")
print(uSU)
checkEqualsNumeric(length(uSU),6)
uFU = OpenFLUID.getUnitsIDs(ofdata,"FU")
print(uFU)
checkEqualsNumeric(length(uFU),0)


# dataset modifications

OpenFLUID.setDeltaT(ofdata,300)
OpenFLUID.setPeriodBeginDate(ofdata,"1997-06-05 00:00:00")
OpenFLUID.setPeriodEndDate(ofdata,"1997-06-05 20:00:00")
OpenFLUID.setSimulatorParam(ofdata,"tests.funcA","pA1",1.9)
OpenFLUID.setSimulatorParam(ofdata,"tests.funcB","pB1","codetoto")
OpenFLUID.setGeneratorParam(ofdata,"RS","tests.random","min",0)
OpenFLUID.setGeneratorParam(ofdata,"RS","tests.random","max",100)
OpenFLUID.setModelGlobalParam(ofdata,"gparam1",3.1)
OpenFLUID.setModelGlobalParam(ofdata,"gparam2",18.0)
OpenFLUID.setObserverParam(ofdata,"tests.obsA","pA1", 0.5)
OpenFLUID.setObserverParam(ofdata,"tests.obsB","format","format1")
OpenFLUID.createAttribute(ofdata,"SU","coeff",1.5)
OpenFLUID.setAttribute(ofdata,"SU",3,"coeff",37.1)
OpenFLUID.createAttribute(ofdata,"RS","coeffv","0.0;10.0")
OpenFLUID.setAttribute(ofdata,"RS",2,"coeffv","100.1;110.1")

checkEquals(OpenFLUID.getDeltaT(ofdata),300)
checkEquals(OpenFLUID.getPeriodBeginDate(ofdata),"1997-06-05 00:00:00")
checkEquals(OpenFLUID.getPeriodEndDate(ofdata),"1997-06-05 20:00:00")
checkEqualsNumeric(as.numeric(OpenFLUID.getSimulatorParam(ofdata,"tests.funcA","pA1")),1.9)
checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.funcB","pB1"),"codetoto")
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","min")),0)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","max")),100)
checkEqualsNumeric(as.numeric(OpenFLUID.getModelGlobalParam(ofdata,"gparam1")),3.1)
checkEqualsNumeric(as.numeric(OpenFLUID.getModelGlobalParam(ofdata,"gparam2")),18)
checkEqualsNumeric(as.numeric(OpenFLUID.getObserverParam(ofdata,"tests.obsA","pA1")),0.5)
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsB","format"),"format1")
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",1,"coeff")),1.5)
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",2,"coeff")),1.5)
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",3,"coeff")),37.1)
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",5,"coeff")),1.5)
checkEquals(OpenFLUID.getAttribute(ofdata,"RS",1,"coeffv"),"0.0;10.0")
checkEquals(OpenFLUID.getAttribute(ofdata,"RS",2,"coeffv"),"100.1;110.1")
checkEquals(OpenFLUID.getAttribute(ofdata,"RS",3,"coeffv"),"0.0;10.0")


# dataset deletions

OpenFLUID.removeSimulatorParam(ofdata,"tests.funcA","pA1")
OpenFLUID.removeSimulatorParam(ofdata,"tests.funcB","pB1")
OpenFLUID.removeModelGlobalParam(ofdata,"gparam1")
OpenFLUID.removeModelGlobalParam(ofdata,"gparam2")
OpenFLUID.removeObserverParam(ofdata,"tests.obsA","pA1")
OpenFLUID.removeObserverParam(ofdata,"tests.obsB","format")


checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.funcA","pA1"),"")
checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.funcB","pB1"),"")
checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gparam1"),"")
checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gparam2"),"")
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsA","pA1"),"")
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsB","format"),"")




