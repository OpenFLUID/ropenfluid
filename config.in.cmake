
# Directories
SET(PACKAGESRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/package")
SET(RESOURCESDIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
SET(BUILDDIR "${CMAKE_CURRENT_SOURCE_DIR}/_build")
SET(PACKAGEBUILDDIR "${BUILDDIR}/ROpenFLUID")

# Title and description
SET(OpenFLUID_R_TITLE "Package for using OpenFLUID within the GNU R environment")
SET(OpenFLUID_R_DESC "This package allows to load, parameterize, run and analyze OpenFLUID simulations within the GNU R environment")

# Version
SET(OpenFLUID_R_VERSION_PATCH "4")

# Default date
SET(OpenFLUID_R_DATE "1970-01-01")


# ===========================================================================================


EXECUTE_PROCESS(COMMAND "openfluid" "--version" OUTPUT_VARIABLE OpenFLUID_VERSION)

STRING(REGEX REPLACE "(\r?\n)+$" "" OpenFLUID_VERSION "${OpenFLUID_VERSION}")

STRING(REGEX REPLACE
       "~[a-z,A-Z,0-9]*" ""
       OpenFLUID_R_VERSION ${OpenFLUID_VERSION})

IF(OpenFLUID_R_VERSION_PATCH)
  SET(OpenFLUID_R_VERSION "${OpenFLUID_R_VERSION}-${OpenFLUID_R_VERSION_PATCH}")
ENDIF()


# Date

IF(UNIX)
  EXECUTE_PROCESS(COMMAND "date" "+%Y-%m-%d" OUTPUT_VARIABLE OpenFLUID_R_DATE)
  STRING(STRIP "${OpenFLUID_R_DATE}" OpenFLUID_R_DATE)
ENDIF(UNIX)


# Prefix

FIND_PATH(OpenFLUID_PREFIX
  NAME bin/openfluid
  HINTS
    $ENV{OPENFLUID_INSTALL_PATH}    
    /usr
    /usr/local
    /sw # Fink
    /opt
    /opt/local # DarwinPorts
  PATH_SUFFIXES
)
