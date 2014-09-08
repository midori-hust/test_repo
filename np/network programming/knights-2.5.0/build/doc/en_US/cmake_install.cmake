# Install script for directory: /home/library/hungpd/np/knights-2.5.0/doc/en_US

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
   "/share/doc/HTML/en/knights/index.cache.bz2;/share/doc/HTML/en/knights/index.docbook;/share/doc/HTML/en/knights/Knights-board-setup.png;/share/doc/HTML/en/knights/Knights-newgame-dialog.png;/share/doc/HTML/en/knights/Knights-move-bishop.png;/share/doc/HTML/en/knights/Knights-move-queen.png;/share/doc/HTML/en/knights/Knights-server-challenges.png;/share/doc/HTML/en/knights/Knights-server-graph.png;/share/doc/HTML/en/knights/Knights-server-list.png;/share/doc/HTML/en/knights/Knights-move-limits.png;/share/doc/HTML/en/knights/Knights-move-king.png;/share/doc/HTML/en/knights/Knights-engines.png;/share/doc/HTML/en/knights/Knights-server-account.png;/share/doc/HTML/en/knights/Knights-move-rook.png;/share/doc/HTML/en/knights/Knights-castle-queenside.png;/share/doc/HTML/en/knights/Knights-board.png;/share/doc/HTML/en/knights/Knights-lastmove.png;/share/doc/HTML/en/knights/Knights-danger.png;/share/doc/HTML/en/knights/Knights-moving-queen.png;/share/doc/HTML/en/knights/Knights-move-knight.png;/share/doc/HTML/en/knights/Knights-move-pawn.png;/share/doc/HTML/en/knights/Knights-castle-kingside.png;/share/doc/HTML/en/knights/Knights-enpassant.png")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/share/doc/HTML/en/knights" TYPE FILE FILES
    "/home/library/hungpd/np/knights-2.5.0/build/doc/en_US/index.cache.bz2"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/index.docbook"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-board-setup.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-newgame-dialog.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-move-bishop.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-move-queen.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-server-challenges.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-server-graph.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-server-list.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-move-limits.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-move-king.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-engines.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-server-account.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-move-rook.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-castle-queenside.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-board.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-lastmove.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-danger.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-moving-queen.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-move-knight.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-move-pawn.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-castle-kingside.png"
    "/home/library/hungpd/np/knights-2.5.0/doc/en_US/Knights-enpassant.png"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND /usr/bin/cmake -E create_symlink "/share/doc/HTML/en/common"  "$ENV{DESTDIR}/share/doc/HTML/en/knights/common" )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

