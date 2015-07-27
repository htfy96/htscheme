 #_____________________________________
#/ "His eyes were cold. As cold as the \
#| bitter winter snow that was falling |
#| outside. Yes, cold and therefore    |
#\ difficult to chew..."               /
 #-------------------------------------
        #\   ^__^
         #\  (oo)\_______
            #(__)\       )\/\
                #||----w |
                #||     ||
cmake_minimum_required(VERSION 3.2)
project(htScheme)

set (htScheme_VERSION_MAJOR 1)
set (htScheme_VERSION_MINOR 0)

aux_source_directory(. SRC_LIST)
aux_source_directory(types TYPES_LIST)
aux_source_directory(utility UTILITY_LIST)
aux_source_directory(parsers PARSERS_LIST)
aux_source_directory(funs FUNS_LIST)


include_directories (${PROJECT_BINARY_DIR})
include_directories (SYSTEM ${PROJECT_SOURCE_DIR}/sys)
include_directories (${PROJECT_SOURCE_DIR})
configure_file(base.ht ${CMAKE_CURRENT_BINARY_DIR}/base.ht COPYONLY)
add_executable(htcli ${SRC_LIST} ${TYPES_LIST} ${UTILITY_LIST} ${PARSERS_LIST} ${FUNS_LIST})

add_definitions(-D INTEST)
SET(CMAKE_CXX_FLAGS "-O2 -std=c++11  -Wno-non-template-friend")
SET(CMAKE_CXX_FLAGS_DEBUG " -g ")

install (TARGETS htcli DESTINATION bin)

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
    ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set (CPACK_PACKAGE_VERSION_MAJOR ${Tutorial_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${Tutorial_VERSION_MINOR})
include (CPack)

