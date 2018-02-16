library("RUnit")

library("ROpenFLUID")

OpenFLUID.setCurrentOutputDir(paste(getwd(),'/6fields_3reaches.OUT', sep = ""))

ofdata = OpenFLUID.openDataset("6fields_3reaches.IN")

# check get wares IDs
genVarNames = OpenFLUID.getGeneratorsVarNames(ofdata,"SU")
#[1] "tests.fixed" "tests.random"
checkEquals(length(genVarNames),2)
checkEquals(("tests.fixed" %in% genVarNames),TRUE)
checkEquals(("tests.random" %in% genVarNames),TRUE)

genVarNames = OpenFLUID.getGeneratorsVarNames(ofdata,"RS")
#[1] "tests.random"
checkEquals(length(genVarNames),1)
checkEquals(("tests.random" %in% genVarNames),TRUE)

simIDs = OpenFLUID.getSimulatorsIDs(ofdata)
#[1] "tests.funcA" "tests.funcB" "tests.funcC"
checkEquals(length(simIDs),3)
checkEquals(("tests.funcA" %in% simIDs),TRUE)
checkEquals(("tests.funcB" %in% simIDs),TRUE)
checkEquals(("tests.funcC" %in% simIDs),TRUE)

obsIDs = OpenFLUID.getObserversIDs(ofdata)
#[1] "tests.obsA" "tests.obsB"
checkEquals(length(obsIDs),2)
checkEquals(("tests.obsA" %in% obsIDs),TRUE)
checkEquals(("tests.obsB" %in% obsIDs),TRUE)

# check get wares parameters names
globParams = OpenFLUID.getModelGlobalParamNames(ofdata)
#[1] "gparam1" "gparam2"
checkEquals(length(globParams),2)
checkEquals(("gparam1" %in% globParams),TRUE)
checkEquals(("gparam2" %in% globParams),TRUE)

OpenFLUID.setModelGlobalParam(ofdata,"gparam3",4.3)
globParams = OpenFLUID.getModelGlobalParamNames(ofdata)
#[1] "gparam1" "gparam2" "gparam3"
checkEquals(length(globParams),3)
checkEquals(("gparam3" %in% globParams),TRUE)

OpenFLUID.removeModelGlobalParam(ofdata,"gparam1")
globParams = OpenFLUID.getModelGlobalParamNames(ofdata)
#[1] "gparam2" "gparam3"
checkEquals(length(globParams),2)
checkEquals(("gparam1" %in% globParams),FALSE)

genParams = OpenFLUID.getGeneratorParamNames(ofdata,"SU","tests.random")
#[1] "max" "min"
checkEquals(length(genParams),2)
checkEquals(("max" %in% genParams),TRUE)
checkEquals(("min" %in% genParams),TRUE)

genParams = OpenFLUID.getGeneratorParamNames(ofdata,"SU","tests.fixed")
#[1] "fixedvalue"
checkEquals(length(genParams),1)
checkEquals(("fixedvalue" %in% genParams),TRUE)

simParams = OpenFLUID.getSimulatorParamNames(ofdata,"tests.funcA")
#[1] "pA1"
checkEquals(length(simParams),1)
checkEquals(("pA1" %in% simParams),TRUE)

simParams = OpenFLUID.getSimulatorParamNames(ofdata,"tests.funcB")
#NULL
checkEquals(is.null(simParams),TRUE)

obsParams = OpenFLUID.getSimulatorParamNames(ofdata,"tests.funcC")
#[1] "pC1" "pC2" "pC3"
checkEquals(length(obsParams),3)
checkEquals(("pC1" %in% obsParams),TRUE)
checkEquals(("pC2" %in% obsParams),TRUE)
checkEquals(("pC3" %in% obsParams),TRUE)

obsParams = OpenFLUID.getObserverParamNames(ofdata,"tests.obsA")
#[1] "pA1" "pA2"
checkEquals(length(obsParams),2)
checkEquals(("pA1" %in% obsParams),TRUE)
checkEquals(("pA2" %in% obsParams),TRUE)

obsParams = OpenFLUID.getObserverParamNames(ofdata,"tests.obsB")
#NULL
checkEquals(is.null(obsParams),TRUE)
OpenFLUID.setObserverParam(ofdata,"tests.obsB","pB1",0)
obsParams = OpenFLUID.getObserverParamNames(ofdata,"tests.obsB")
#[1] "pB1"
checkEquals(length(obsParams),1)
checkEquals(("pB1" %in% obsParams),TRUE)

OpenFLUID.removeObserverParam(ofdata,"tests.obsB","pB1")
obsParams = OpenFLUID.getObserverParamNames(ofdata,"tests.obsB")
#NULL
checkEquals(is.null(obsParams),TRUE)

# check get attributes names
attrbSU = OpenFLUID.getAttributesNames(ofdata,"SU")
#[1] "area"     "flowdist" "slope"
checkEquals(length(attrbSU),3)
checkEquals(("area" %in% attrbSU),TRUE)
checkEquals(("flowdist" %in% attrbSU),TRUE)
checkEquals(("slope" %in% attrbSU),TRUE)

attrbRS = OpenFLUID.getAttributesNames(ofdata,"RS")
#[1] "length" "slope"  "width"
checkEquals(length(attrbRS),3)
checkEquals(("length" %in% attrbRS),TRUE)
checkEquals(("slope" %in% attrbRS),TRUE)
checkEquals(("width" %in% attrbRS),TRUE)

OpenFLUID.createAttribute(ofdata,"SU","varinit",1)
attrbSU = OpenFLUID.getAttributesNames(ofdata,"SU")
#[1] "area"     "flowdist" "slope" "varinit"
checkEquals(length(attrbSU),4)
checkEquals(("varinit" %in% attrbSU),TRUE)

OpenFLUID.removeAttribute(ofdata,"RS","width")
attrbRS = OpenFLUID.getAttributesNames(ofdata,"RS")
#[1] "length" "slope"
checkEquals(length(attrbRS),2)
checkEquals(("width" %in% attrbRS),FALSE)
