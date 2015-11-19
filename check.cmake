

# CMake script for checking R OpenFLUID package
# usage : cmake -P check.cmake 


INCLUDE("config.in.cmake")

INCLUDE("cmake/display-infos.cmake")
INCLUDE("cmake/preprocess.cmake")


EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" 
                "-E" "chdir" "${BUILDDIR}"
                "R" "CMD" "check" "ROpenFLUID")

