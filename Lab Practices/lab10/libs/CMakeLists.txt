aux_source_directory(. LIBS)

include_directories(../include)

add_library(MYLIBS SHARED ${LIBS})