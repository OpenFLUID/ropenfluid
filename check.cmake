

# CMake script for checking R OpenFLUID package
# usage : cmake -P check.cmake 


INCLUDE("config.in.cmake")

INCLUDE("cmake/display-infos.cmake")
INCLUDE("cmake/preprocess.cmake")


SET(AS_CRAN_OPTION)

IF(AS_CRAN_MODE)
  # .Rprofile file for dependencies checking when building package
  FILE(WRITE "${BUILDDIR}/.Rprofile" "\noptions(repos = c(CRAN=\"https://cran.r-project.org\"))\n\n")
  SET(AS_CRAN_OPTION "--as-cran")
ENDIF()


EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" 
                "-E" "chdir" "${BUILDDIR}"
                "R" "CMD" "check" "ROpenFLUID" ${AS_CRAN_OPTION})

