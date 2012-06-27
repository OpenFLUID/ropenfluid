library('ROpenFLUID', lib.loc='./ROpenFLUID.Rcheck')

OpenFLUID.addExtraFunctionsPaths('./tests/functions-bin/')

OpenFLUID.setOutputDir('./tests/outputs/dummydata.OUT')

datablob = OpenFLUID.openDataset('./tests/datasets/dummydata.IN')

OpenFLUID.runSimulation(datablob)