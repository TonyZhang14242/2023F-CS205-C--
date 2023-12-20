aux_source_directory(. LIBA)

include_directories(../include)

add_library(MYLIBA STATIC ${LIBA})