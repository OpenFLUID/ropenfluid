
# CMake script for building R OpenFLUID package
# usage : cmake -P build.cmake 


INCLUDE("config.in.cmake")

FILE(REMOVE_RECURSE ${BUILDDIR})
FILE(MAKE_DIRECTORY ${BUILDDIR})
FILE(MAKE_DIRECTORY ${BUILDDIR}/ROpenFLUID)

FILE(COPY "${CMAKE_CURRENT_SOURCE_DIR}/" 
       DESTINATION "${BUILDDIR}/ROpenFLUID"
       PATTERN ".*" EXCLUDE
       PATTERN "_*" EXCLUDE
       PATTERN "*.cmake" EXCLUDE)


EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" 
                "-E" "chdir" "${BUILDDIR}"
                "R" "CMD" "build" "ROpenFLUID")