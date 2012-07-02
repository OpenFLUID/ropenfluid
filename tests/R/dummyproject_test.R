library('ROpenFLUID', lib.loc='./ROpenFLUID.Rcheck')

OpenFLUID.addExtraFunctionsPaths('./tests/functions-bin/')

datablob = OpenFLUID.openProject('./tests/datasets/dummyproject')

OpenFLUID.runSimulation(datablob)
