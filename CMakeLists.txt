cmake_minimum_required(VERSION 3.13)
project(RTypeProject)

set(CMAKE_CXX_STANDARD 17)

IF (WIN32)
    message(STATUS "Start initializing rtype WIND32")
    include(CPack)

    set(CPACK_PACKAGE_NAME "R-Type")
    set(CPACK_PACKAGE_VENDOR "Bear")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "R-Type game and server")
    set(CPACK_PACKAGE_VERSION "1.0.0")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

    set(CPACK_GENERATOR "TGZ")
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/assets/rtype.ico")
ELSEIF (UNIX AND NOT MINGW)
    message(STATUS "Start initializing rtype UNIX")
ENDIF ()

add_subdirectory(Libs/ECS)
add_subdirectory(Libs/Platformer)
add_subdirectory(Libs/LibLoader)
add_subdirectory(Server)
add_subdirectory(Client)

