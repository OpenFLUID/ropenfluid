
# CMake script for generating html doc of R OpenFLUID package
# usage : cmake -P htmldoc.cmake 


INCLUDE("config.in.cmake")

INCLUDE("cmake/preprocess.cmake")


FILE(GLOB RDFILES "${PACKAGEBUILDDIR}/man/*.Rd")                
FILE(MAKE_DIRECTORY "${BUILDDIR}/htmldoc")

FILE(COPY "${RESOURCESDIR}/htmldoc/R_logo.jpg" DESTINATION "${BUILDDIR}/htmldoc")
FILE(COPY "${RESOURCESDIR}/htmldoc/OpenFLUID_logo.jpg" DESTINATION "${BUILDDIR}/htmldoc")

FOREACH(RDF ${RDFILES})
  SET(INFILE "${RDF}")
   
  GET_FILENAME_COMPONENT(OUTFILE "${RDF}" NAME)  
  SET(OUTFILE "${BUILDDIR}/htmldoc/${OUTFILE}")
  STRING(LENGTH ${OUTFILE} OUTLEN)
  MATH(EXPR OUTLEN "${OUTLEN} - 2")
  STRING(SUBSTRING ${OUTFILE} 0 ${OUTLEN} OUTFILE)
  SET(OUTFILE "${OUTFILE}html")

  MESSAGE(${OUTFILE})

  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" 
                "-E" "chdir" "${BUILDDIR}"
                "R" "CMD" "Rdconv" "--type=html" "${INFILE}"
                OUTPUT_FILE "${OUTFILE}")        
ENDFOREACH(RDF ${RDFILES})        
