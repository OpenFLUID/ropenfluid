library("RUnit")

library("ROpenFLUID")

OpenFLUID.setCurrentOutputDir(paste(getwd(),'/6fields_3reaches.OUT', sep = ""))

ofdata = OpenFLUID.openDataset("6fields_3reaches.IN")

OpenFLUID.printSimulationInfo(ofdata)


checkEquals(OpenFLUID.getDefaultDeltaT(ofdata),60)
checkEquals(OpenFLUID.getPeriodBeginDate(ofdata),"1997-06-05 04:04:00")
checkEquals(OpenFLUID.getPeriodEndDate(ofdata),"1997-06-05 16:16:00")

checkEqualsNumeric(as.numeric(OpenFLUID.getSimulatorParam(ofdata,"tests.funcA","pA1")),0.000005)
checkEqualsNumeric(as.numeric(OpenFLUID.getSimulatorParam(ofdata,"tests.funcC","pC2")),0.045)
checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.funcC","fakeparam"),"")
checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.fakefunc","fakeparam"),"")

dfSimParams = OpenFLUID.getSimulatorParams(ofdata,"tests.funcC",c("pC2","pC3"))
checkEqualsNumeric(as.numeric(dfSimParams["tests.funcC","pC2"]),0.045)
dfSimParamsOneCol = OpenFLUID.getSimulatorParams(ofdata,"tests.funcC",c("pC2"))
checkEqualsNumeric(as.numeric(dfSimParamsOneCol["tests.funcC","pC2"]),0.045)

checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"SU","tests.fixed","fixedvalue")),12.7)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","min")),20.53)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","max")),50)

dfGenParams = OpenFLUID.getGeneratorParams(ofdata,"RS","tests.random",c("min","max"))
checkEqualsNumeric(as.numeric(dfGenParams["tests.random","min"]),20.53)
dfGenParamsOneCol = OpenFLUID.getGeneratorParams(ofdata,"RS","tests.random",c("min"))
checkEqualsNumeric(as.numeric(dfGenParamsOneCol["tests.random","min"]),20.53)

checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gparam1"),"1.1;2.1")
checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gfakeparam"),"")

dfGlobParams = OpenFLUID.getModelGlobalParams(ofdata,c("gparam1","gparam2"))
checkEquals(dfGlobParams["global","gparam1"],"1.1;2.1")
dfGlobParamsOneCol = OpenFLUID.getModelGlobalParams(ofdata,c("gparam1"))
checkEquals(dfGlobParamsOneCol["global","gparam1"],"1.1;2.1")

checkEqualsNumeric(as.numeric(OpenFLUID.getObserverParam(ofdata,"tests.obsA","pA1")),10)
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsA","pA2"),"valA2")
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsA","fakeparam"),"")
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.fakeobs","fakeparam"),"")

dfObsParams = OpenFLUID.getObserverParams(ofdata,"tests.obsA",c("pA2","pA1"))
checkEquals(dfObsParams["tests.obsA","pA2"],"valA2")
dfObsParamsOneCol = OpenFLUID.getObserverParams(ofdata,"tests.obsA",c("pA2"))
checkEquals(dfObsParamsOneCol["tests.obsA","pA2"],"valA2")


checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",1,"area")),1216.29)
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",5,"area")),3024.27)
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"SU",3,"slope")),0.02)
checkEqualsNumeric(as.numeric(OpenFLUID.getAttribute(ofdata,"RS",2,"length")),170)
checkEqualsNumeric(OpenFLUID.getAttribute(ofdata,"RS",18,"length"),"")
checkEqualsNumeric(OpenFLUID.getAttribute(ofdata,"RS",1,"fakedata"),"")

# check get attributes in batch mode
dfVal = OpenFLUID.getAttributes(ofdata,"SU",c(1,5),c("area","slope"))
checkEqualsNumeric(dfVal["SU#1","area"],OpenFLUID.getAttribute(ofdata,"SU",1,"area"))
checkEqualsNumeric(dfVal["SU#5","area"],OpenFLUID.getAttribute(ofdata,"SU",5,"area"))
checkEqualsNumeric(dfVal["SU#1","slope"],OpenFLUID.getAttribute(ofdata,"SU",1,"slope"))
checkEqualsNumeric(dfVal["SU#5","slope"],OpenFLUID.getAttribute(ofdata,"SU",5,"slope"))

dfValWithID = OpenFLUID.getAttributes(ofdata,"SU",c(1,5),c("area","slope"),unitidsAsRownames = FALSE)
checkEqualsNumeric(dfVal[1,"area"],OpenFLUID.getAttribute(ofdata,"SU",1,"area"))
checkEqualsNumeric(dfVal[2,"area"],OpenFLUID.getAttribute(ofdata,"SU",5,"area"))
checkEqualsNumeric(dfVal[1,"slope"],OpenFLUID.getAttribute(ofdata,"SU",1,"slope"))
checkEqualsNumeric(dfVal[2,"slope"],OpenFLUID.getAttribute(ofdata,"SU",5,"slope"))

checkEquals(rownames(dfVal),dfValWithID$unitid)

# check get attributes in batch mode for one row
dfValOneRow = OpenFLUID.getAttributes(ofdata,"SU",c(2),c("area","slope"))
checkEqualsNumeric(dfValOneRow["SU#2","area"],OpenFLUID.getAttribute(ofdata,"SU",2,"area"))
checkEqualsNumeric(dfValOneRow["SU#2","slope"],OpenFLUID.getAttribute(ofdata,"SU",2,"slope"))

# check get attributes in batch mode for one row
dfValOneRowOneCol = OpenFLUID.getAttributes(ofdata,"SU",c(2),c("area"))
checkEqualsNumeric(dfValOneRow["SU#2","area"],OpenFLUID.getAttribute(ofdata,"SU",2,"area"))

# check set attributes in batch mode
dfValPlusOne = dfVal
dfValPlusOne$area  = as.character(as.numeric(dfValPlusOne$area)+c(1,1)) # add 1 to column "area"
dfValPlusOne$slope = as.character(as.numeric(dfValPlusOne$slope)+c(1,1)) # add 1 to column "slope"
OpenFLUID.setAttributes(ofdata,"SU",dfValPlusOne)

checkEquals(as.numeric(dfVal[1,"area"]),as.numeric(OpenFLUID.getAttribute(ofdata,"SU",1,"area"))-1)
checkEquals(as.numeric(dfVal[2,"area"]),as.numeric(OpenFLUID.getAttribute(ofdata,"SU",5,"area"))-1)
checkEquals(as.numeric(dfVal[1,"slope"]),as.numeric(OpenFLUID.getAttribute(ofdata,"SU",1,"slope"))-1)
checkEquals(as.numeric(dfVal[2,"slope"]),as.numeric(OpenFLUID.getAttribute(ofdata,"SU",5,"slope"))-1)

# reset attributes to their initial value using data.frame with the column "unitid"
OpenFLUID.setAttributes(ofdata,"SU",dfValWithID)
# check setAttributes on specific cases one row, one row/one column
OpenFLUID.setAttributes(ofdata,"SU",dfValOneRow)
OpenFLUID.setAttributes(ofdata,"SU",dfValOneRowOneCol)



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

OpenFLUID.setDefaultDeltaT(ofdata,300)
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

checkEquals(OpenFLUID.getDefaultDeltaT(ofdata),300)
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

# batch parameters modifications

OpenFLUID.setSimulatorParams(ofdata,"tests.funcB",data.frame("pB1"="codetiti","pB2"=0.1,stringsAsFactors=FALSE))
OpenFLUID.setGeneratorParams(ofdata,"RS","tests.random",data.frame("min"=-100,"max"=0,stringsAsFactors=FALSE))
OpenFLUID.setModelGlobalParams(ofdata,data.frame("gparam1"=3.0,"gparam2"=28.0,stringsAsFactors=FALSE))
OpenFLUID.setObserverParams(ofdata,"tests.obsB",data.frame("format"="format2","precision"=12,stringsAsFactors=FALSE))

checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.funcB","pB1"),"codetiti")
checkEqualsNumeric(as.numeric(OpenFLUID.getSimulatorParam(ofdata,"tests.funcB","pB2")),0.1)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","min")),-100)
checkEqualsNumeric(as.numeric(OpenFLUID.getGeneratorParam(ofdata,"RS","tests.random","max")),0)
checkEqualsNumeric(as.numeric(OpenFLUID.getModelGlobalParam(ofdata,"gparam1")),3.0)
checkEqualsNumeric(as.numeric(OpenFLUID.getModelGlobalParam(ofdata,"gparam2")),28)
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsB","format"),"format2")
checkEqualsNumeric(as.numeric(OpenFLUID.getObserverParam(ofdata,"tests.obsB","precision")),12)

# dataset deletions

OpenFLUID.removeSimulatorParam(ofdata,"tests.funcA","pA1")
OpenFLUID.removeSimulatorParam(ofdata,"tests.funcB","pB1")
OpenFLUID.removeModelGlobalParam(ofdata,"gparam1")
OpenFLUID.removeModelGlobalParam(ofdata,"gparam2")
OpenFLUID.removeObserverParam(ofdata,"tests.obsA","pA1")
OpenFLUID.removeObserverParam(ofdata,"tests.obsB","format")

OpenFLUID.removeAttribute(ofdata,"SU","coeff")
OpenFLUID.removeAttribute(ofdata,"RS","coeffv")


checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.funcA","pA1"),"")
checkEquals(OpenFLUID.getSimulatorParam(ofdata,"tests.funcB","pB1"),"")
checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gparam1"),"")
checkEquals(OpenFLUID.getModelGlobalParam(ofdata,"gparam2"),"")
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsA","pA1"),"")
checkEquals(OpenFLUID.getObserverParam(ofdata,"tests.obsB","format"),"")

checkEqualsNumeric(OpenFLUID.getAttribute(ofdata,"SU",1,"coeff"),"")
checkEqualsNumeric(OpenFLUID.getAttribute(ofdata,"SU",3,"coeff"),"")
checkEquals(OpenFLUID.getAttribute(ofdata,"RS",1,"coeffv"),"")
checkEquals(OpenFLUID.getAttribute(ofdata,"RS",2,"coeffv"),"")
