library(RUnit)

library("ROpenFLUID")

ofdata = OpenFLUID.openDataset("6fields_3reaches.IN")

OpenFLUID.printSimulationInfo(ofdata)


checkEquals(OpenFLUID.getDeltaT(ofdata),60)
checkEquals(OpenFLUID.getPeriodBeginDate(ofdata),"1997-06-05 04:04:00")
checkEquals(OpenFLUID.getPeriodEndDate(ofdata),"1997-06-05 16:16:00")

checkEqualsNumeric(as.numeric(OpenFLUID.getFunctionParam(ofdata,"tests.funcA","pA1")),0.000005)
checkEqualsNumeric(as.numeric(OpenFLUID.getFunctionParam(ofdata,"tests.funcC","pC2")),0.045)
checkEquals(OpenFLUID.getFunctionParam(ofdata,"tests.funcC","fakeparam"),"")
checkEquals(OpenFLUID.getFunctionParam(ofdata,"tests.fakefunc","fakeparam"),"")
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"SU","tests.fixed","fixedvalue")),12.7)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","min")),20.53)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","max")),50)
checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gparam1"),"1.1;2.1")
checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gfakeparam"),"")


# dataset modifications

OpenFLUID.setDeltaT(ofdata,300)
OpenFLUID.setPeriodBeginDate(ofdata,"1997-06-05 00:00:00")
OpenFLUID.setPeriodEndDate(ofdata,"1997-06-05 20:00:00")
OpenFLUID.setFunctionParam(ofdata,"tests.funcA","pA1",1.9)
OpenFLUID.setFunctionParam(ofdata,"tests.funcB","pB1","codetoto")
OpenFLUID.setGeneratorParam(ofdata,"RS","tests.random","min",0)
OpenFLUID.setGeneratorParam(ofdata,"RS","tests.random","max",100)
OpenFLUID.setModelGlobalParam(ofdata,"gparam1",3.1)
OpenFLUID.setModelGlobalParam(ofdata,"gparam2",18.0)

checkEquals(OpenFLUID.getDeltaT(ofdata),300)
checkEquals(OpenFLUID.getPeriodBeginDate(ofdata),"1997-06-05 00:00:00")
checkEquals(OpenFLUID.getPeriodEndDate(ofdata),"1997-06-05 20:00:00")
checkEqualsNumeric(as.numeric(OpenFLUID.getFunctionParam(ofdata,"tests.funcA","pA1")),1.9)
checkEquals(OpenFLUID.getFunctionParam(ofdata,"tests.funcB","pB1"),"codetoto")
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","min")),0)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","max")),100)
checkEqualsNumeric(as.numeric(OpenFLUID.getModelGlobalParam(ofdata,"gparam1")),3.1)
checkEqualsNumeric(as.numeric(OpenFLUID.getModelGlobalParam(ofdata,"gparam2")),18)

