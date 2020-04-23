
# CMake script for generating html doc of R OpenFLUID package
# usage : cmake -P htmldoc.cmake 


INCLUDE("config.in.cmake")

INCLUDE("cmake/display-infos.cmake")
INCLUDE("cmake/preprocess.cmake")


FILE(GLOB RDFILES "${PACKAGE_BUILD_PATH}/man/*.Rd")                
FILE(MAKE_DIRECTORY "${BUILD_PATH}/htmldoc")

FILE(COPY "${RESOURCES_PATH}/htmldoc/R_logo.png" DESTINATION "${BUILD_PATH}/htmldoc")
FILE(COPY "${RESOURCES_PATH}/htmldoc/OpenFLUID_logo.png" DESTINATION "${BUILD_PATH}/htmldoc")

FOREACH(RDF ${RDFILES})
  SET(INFILE "${RDF}")
   
  GET_FILENAME_COMPONENT(OUTFILE "${RDF}" NAME)  
  SET(OUTFILE "${BUILD_PATH}/htmldoc/${OUTFILE}")
  STRING(LENGTH ${OUTFILE} OUTLEN)
  MATH(EXPR OUTLEN "${OUTLEN} - 2")
  STRING(SUBSTRING ${OUTFILE} 0 ${OUTLEN} OUTFILE)
  SET(OUTFILE "${OUTFILE}html")

  MESSAGE(${OUTFILE})

  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" 
                "-E" "chdir" "${BUILD_PATH}"
                "R" "CMD" "Rdconv" "--type=html" "${INFILE}"
                OUTPUT_FILE "${OUTFILE}")        
ENDFOREACH(RDF ${RDFILES})        
