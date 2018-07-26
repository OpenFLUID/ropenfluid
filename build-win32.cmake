
# CMake script for building R OpenFLUID package (win32 binary)
# usage : cmake -P build-win32.cmake

# This script must be launched from MSYS console

# Notice that environment variables must be correctly set
# in order to find the OpenFLUID framework, the R environnement
# and GCC tools (C++11)
# See file win32-env.sh.tpl for more information


INCLUDE("config.in.cmake")

INCLUDE("cmake/display-infos.cmake")
INCLUDE("cmake/preprocess.cmake")


EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}"
                "-E" "chdir" "${BUILDDIR}"
                "R" "CMD" "build" "ROpenFLUID")

EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}"
                "-E" "chdir" "${BUILDDIR}"
                "R" "CMD" "INSTALL" "--build" "--no-test-load"
                                    "--library=${BUILDLIBRDIR}" "ROpenFLUID")
