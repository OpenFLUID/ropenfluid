FILE(MAKE_DIRECTORY ${BUILD_PATH})
FILE(REMOVE_RECURSE ${PACKAGE_BUILD_PATH})
FILE(MAKE_DIRECTORY ${PACKAGE_BUILD_PATH})
FILE(MAKE_DIRECTORY ${LIBR_BUILD_PATH})


FOREACH(PACK ${REQUIRED_R_PACKAGES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}"
                          "-E" "chdir" "${PACKAGE_BUILD_PATH}"
                          "Rscript"  "--vanilla" "${RESOURCES_PATH}/checkPackage.R" "${PACK}"
                  RESULT_VARIABLE CHECK_STATUS)
  IF(NOT ${CHECK_STATUS})
    MESSAGE(FATAL_ERROR "R package ${PACK} is not installed")
  ELSE()
    MESSAGE(STATUS "Found required R package : ${PACK}")  
  ENDIF()
ENDFOREACH()



FILE(COPY "${PACKAGE_SRC_PATH}/"
       DESTINATION "${PACKAGE_BUILD_PATH}"
       PATTERN ".*" EXCLUDE
       PATTERN "_*" EXCLUDE
       PATTERN "*.cmake" EXCLUDE)


CONFIGURE_FILE(${RESOURCES_PATH}/DESCRIPTION.in ${PACKAGE_BUILD_PATH}/DESCRIPTION @ONLY)

CONFIGURE_FILE(${RESOURCES_PATH}/man/ROpenFLUID-package.Rd.in ${PACKAGE_BUILD_PATH}/man/ROpenFLUID-package.Rd @ONLY)
CONFIGURE_FILE(${RESOURCES_PATH}/tests/00tests.R.in ${PACKAGE_BUILD_PATH}/tests/00tests.R @ONLY)
CONFIGURE_FILE(${RESOURCES_PATH}/tests/PrimitivesExample.R.in ${PACKAGE_BUILD_PATH}/tests/PrimitivesExample.R @ONLY)
CONFIGURE_FILE(${RESOURCES_PATH}/tests/PrimitivesExampleVerbose.R.in ${PACKAGE_BUILD_PATH}/tests/PrimitivesExampleVerbose.R @ONLY)
CONFIGURE_FILE(${RESOURCES_PATH}/tests/PrimitivesExampleSelectedOutputs.R.in ${PACKAGE_BUILD_PATH}/tests/PrimitivesExampleSelectedOutputs.R @ONLY)



EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}"
                "-E" "chdir" "${PACKAGE_BUILD_PATH}"
                "R" "CMD" "BATCH" "--vanilla" "${RESOURCES_PATH}/roxygen2.R")

FILE(REMOVE "${PACKAGE_BUILD_PATH}/roxygen2.Rout")
