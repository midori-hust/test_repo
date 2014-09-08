# Install script for directory: /home/library/hungpd/np/knights-2.5.0/themes

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/share/apps/knights/themes/default.desktop;/share/apps/knights/themes/knights.desktop;/share/apps/knights/themes/knights.svgz;/share/apps/knights/themes/knights.png;/share/apps/knights/themes/plain.desktop;/share/apps/knights/themes/plain.svgz;/share/apps/knights/themes/plain.png;/share/apps/knights/themes/gray.svgz;/share/apps/knights/themes/gray.png;/share/apps/knights/themes/xboard2.desktop;/share/apps/knights/themes/xboard2.svgz;/share/apps/knights/themes/xboard2.png;/share/apps/knights/themes/east_west.desktop;/share/apps/knights/themes/east_west.svgz;/share/apps/knights/themes/east_west.png")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/share/apps/knights/themes" TYPE FILE FILES
    "/home/library/hungpd/np/knights-2.5.0/themes/default.desktop"
    "/home/library/hungpd/np/knights-2.5.0/themes/knights.desktop"
    "/home/library/hungpd/np/knights-2.5.0/themes/knights.svgz"
    "/home/library/hungpd/np/knights-2.5.0/themes/knights.png"
    "/home/library/hungpd/np/knights-2.5.0/themes/plain.desktop"
    "/home/library/hungpd/np/knights-2.5.0/themes/plain.svgz"
    "/home/library/hungpd/np/knights-2.5.0/themes/plain.png"
    "/home/library/hungpd/np/knights-2.5.0/themes/gray.svgz"
    "/home/library/hungpd/np/knights-2.5.0/themes/gray.png"
    "/home/library/hungpd/np/knights-2.5.0/themes/xboard2.desktop"
    "/home/library/hungpd/np/knights-2.5.0/themes/xboard2.svgz"
    "/home/library/hungpd/np/knights-2.5.0/themes/xboard2.png"
    "/home/library/hungpd/np/knights-2.5.0/themes/east_west.desktop"
    "/home/library/hungpd/np/knights-2.5.0/themes/east_west.svgz"
    "/home/library/hungpd/np/knights-2.5.0/themes/east_west.png"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

