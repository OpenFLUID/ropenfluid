
# CMake script for building R OpenFLUID package (source on Unix systems, binary on Windows) 
# usage : cmake -P build.cmake 

# Windows Only
# Note that environment variables must be correctly set
# in order to find the OpenFLUID framework, the R environnement
# and GCC tools (C++14)
# See file msys2-mingw64-env.sh.tpl for more information


INCLUDE("config.in.cmake")

INCLUDE("cmake/display-infos.cmake")
INCLUDE("cmake/preprocess.cmake")


IF(UNIX)

  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" 
                  "-E" "chdir" "${BUILD_PATH}"
                  "R" "CMD" "build" "ROpenFLUID")

ELSEIF(WIN32)

  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}"
                  "-E" "chdir" "${BUILD_PATH}"
                  "R" "CMD" "build" "ROpenFLUID")

  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}"
                  "-E" "chdir" "${BUILD_PATH}"
                  "R" "CMD" "INSTALL" "--build" "--no-test-load" "--preclean"
                                      "--library=${LIBR_BUILD_PATH}" "ROpenFLUID")

ENDIF()
