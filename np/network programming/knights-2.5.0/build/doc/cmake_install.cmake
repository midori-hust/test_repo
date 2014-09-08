# Install script for directory: /home/library/hungpd/np/knights-2.5.0/doc

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

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/sv/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/de/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/pt_BR/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/it/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/et/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/uk/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/pt/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/nl/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/es/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/en_US/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/doc/ru/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

