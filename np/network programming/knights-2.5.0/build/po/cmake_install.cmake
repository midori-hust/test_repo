# Install script for directory: /home/library/hungpd/np/knights-2.5.0/po

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
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/ca@valencia/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/da/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/el/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/bs/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/sv/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/de/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/gl/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/pt_BR/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/nb/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/it/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/km/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/sr@latin/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/pl/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/et/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/uk/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/fi/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/nds/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/sr/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/cs/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/zh_TW/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/pt/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/sr@ijekavian/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/nl/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/lt/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/sl/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/nn/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/fr/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/ca/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/es/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/sr@ijekavianlatin/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/ga/cmake_install.cmake")
  INCLUDE("/home/library/hungpd/np/knights-2.5.0/build/po/ru/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

