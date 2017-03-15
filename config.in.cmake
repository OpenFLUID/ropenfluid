
# Directories
SET(PACKAGESRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/package")
SET(RESOURCESDIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
SET(BUILDDIR "${CMAKE_CURRENT_SOURCE_DIR}/_build")
IF(WIN32)
  SET(BUILDDIR "${BUILDDIR}-win32")
ENDIF()
SET(PACKAGEBUILDDIR "${BUILDDIR}/ROpenFLUID")

# Title and description
SET(OpenFLUID_R_TITLE "R Interface to OpenFLUID Platform Framework for Modelling and Simulation of Landscapes")
SET(OpenFLUID_R_DESC "Provides a collection of functions to load, parameterize, run and analyze OpenFLUID simulations within the GNU R environment.")

# Version
SET(OpenFLUID_R_VERSION_PATCH "20170315")


# ===========================================================================================


# Prefix

FIND_PATH(OpenFLUID_PREFIX
  NAMES bin/openfluid bin/openfluid.exe
  HINTS
    $ENV{OPENFLUID_INSTALL_PREFIX}    
    /usr
    /usr/local
    /sw # Fink
    /opt
    /opt/local # DarwinPorts
  PATH_SUFFIXES
)


SET(OpenFLUID_CMDCLI "${OpenFLUID_PREFIX}/bin/openfluid")
IF(WIN32)
  SET(OpenFLUID_CMDCLI "${OpenFLUID_CMDCLI}.exe")
ENDIF()


EXECUTE_PROCESS(COMMAND "${OpenFLUID_CMDCLI}" "--version" 
                OUTPUT_VARIABLE OpenFLUID_VERSION
                RESULT_VARIABLE OpenFLUID_VERSION_RESULT
                OUTPUT_STRIP_TRAILING_WHITESPACE)

IF(OpenFLUID_VERSION_RESULT)
  MESSAGE(FATAL_ERROR "Error getting current openfluid version")
ENDIF()


STRING(REGEX REPLACE
       "~[a-z,A-Z,0-9]*" ""
       OpenFLUID_R_VERSION ${OpenFLUID_VERSION})

IF(OpenFLUID_R_VERSION_PATCH)
  SET(OpenFLUID_R_VERSION "${OpenFLUID_R_VERSION}-${OpenFLUID_R_VERSION_PATCH}")
ENDIF()


# use R to get the current date
EXECUTE_PROCESS(COMMAND "R" "--vanilla" "--slave" "-e" "cat(format(Sys.time(),'%Y-%m-%d'))"
                OUTPUT_VARIABLE OpenFLUID_R_DATE
                OUTPUT_STRIP_TRAILING_WHITESPACE)

