
SET(PACKAGESRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/package")
SET(RESOURCESDIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
SET(BUILDDIR "${CMAKE_CURRENT_SOURCE_DIR}/_build")
SET(PACKAGEBUILDDIR "${BUILDDIR}/ROpenFLUID")


SET(openfluid_R_TITLE "Package for using OpenFLUID from the GNU R environment")
SET(openfluid_R_DESC "This package allows to load, parameterize, run and analyse OpenFLUID simulations from the GNU R environment")

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(openfluid REQUIRED openfluid)

STRING(REGEX REPLACE
       "~[a-z,A-Z,0-9]*" ""
       openfluid_R_VERSION ${openfluid_VERSION})

SET(openfluid_R_DATE "1970-01-01")


IF(UNIX)
  EXECUTE_PROCESS(COMMAND "date" "+%Y-%m-%d" OUTPUT_VARIABLE openfluid_R_DATE)
  STRING(STRIP "${openfluid_R_DATE}" openfluid_R_DATE)
ENDIF(UNIX)

