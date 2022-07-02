cmake_minimum_required(VERSION 3.20)
project(lua_smaz C)

set(CMAKE_C_STANDARD 11)
include_directories(F:/conda/Library/include ./smaz)
link_directories("F:\\conda\\Library\\lib" F:/conda/Library/bin)


set(SOURCES smaz/smaz.c)

add_library(smaz SHARED src/lsmaz.c ${SOURCES})
target_link_libraries(smaz lua)

set_target_properties(smaz PROPERTIES OUTPUT_NAME smaz)

