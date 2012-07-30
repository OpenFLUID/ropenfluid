

# CMake script for building R OpenFLUID package
# usage : cmake -P build.cmake 


INCLUDE("config.in.cmake")

INCLUDE("cmake/preprocess.cmake")


EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" 
                "-E" "chdir" "${BUILDDIR}"
                "R" "CMD" "check" "ROpenFLUID")

