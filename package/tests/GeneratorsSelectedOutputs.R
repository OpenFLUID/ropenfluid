library("RUnit")

library("ROpenFLUID")

ofsim <- OpenFLUID.openDataset("Generators.IN")

OpenFLUID.setCurrentOutputDir(paste(getwd(), "/GeneratorsSelectedOutputs.OUT", sep = ""))

OpenFLUID.addVariablesExportAsCSV(ofsim, "TestUnits", c(1,3), c("tests.fixed","tests.random","tests.fixed"))

OpenFLUID.printSimulationInfo(ofsim)

OpenFLUID.runSimulation(ofsim)

checkTrue(file.exists(paste(getwd(), "/GeneratorsSelectedOutputs.OUT/ropenfluidTestUnits_TestUnits1_tests.fixed.csv", sep = "")))
checkTrue(file.exists(paste(getwd(), "/GeneratorsSelectedOutputs.OUT/ropenfluidTestUnits_TestUnits3_tests.fixed.csv", sep = "")))
checkTrue(file.exists(paste(getwd(), "/GeneratorsSelectedOutputs.OUT/ropenfluidTestUnits_TestUnits1_tests.random.csv", sep = "")))
checkTrue(file.exists(paste(getwd(), "/GeneratorsSelectedOutputs.OUT/ropenfluidTestUnits_TestUnits3_tests.random.csv", sep = "")))
checkEquals(length(list.files(paste(getwd(), "/GeneratorsSelectedOutputs.OUT", sep = ""), pattern="*.csv")), 4)

out <- OpenFLUID.loadResult(ofsim, "TestUnits", 3, "tests.random")

print(out)

plot(out$tests.random, type = "l")
