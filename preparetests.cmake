
INCLUDE("config.in.cmake")


FILE(MAKE_DIRECTORY ${BUILDDIR})
FILE(REMOVE_RECURSE ${BUILDDIR}/tests)
FILE(MAKE_DIRECTORY ${BUILDDIR}/tests)
FILE(MAKE_DIRECTORY ${BUILDDIR}/tests/functions-build)
FILE(MAKE_DIRECTORY ${BUILDDIR}/tests/functions-bin)
FILE(MAKE_DIRECTORY ${BUILDDIR}/tests/datasets)


SET(FUNCLIST "tests.funcA" 
             "tests.funcB"
             "tests.funcC")


FOREACH(FUNC ${FUNCLIST}) 

  FILE(MAKE_DIRECTORY ${BUILDDIR}/tests/functions-build/${FUNC})

  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" 
                 "-E" "chdir" "${BUILDDIR}/tests/functions-build/${FUNC}"
                 "${CMAKE_COMMAND}"
                 "-DNOFUNC2DOC=1" 
                 "-DUSER_FUNCTIONS_INSTALL_PATH=${BUILDDIR}/tests/functions-bin"                              
                 "${CMAKE_SOURCE_DIR}/tests/functions/${FUNC}")

  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" "--build" "${BUILDDIR}/tests/functions-build/${FUNC}"
                                             "--target" "install")

ENDFOREACH(FUNC ${FUNCLIST})                
               


FILE(COPY "tests/datasets/" 
     DESTINATION "${BUILDDIR}/tests/datasets/"
     PATTERN ".svn" EXCLUDE)

FILE(COPY "tests/R/" 
     DESTINATION "${BUILDDIR}/tests/R/"
     PATTERN ".svn" EXCLUDE)
