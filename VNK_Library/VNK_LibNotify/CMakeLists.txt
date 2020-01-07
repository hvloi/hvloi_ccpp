################################################################################
##                                                                            ##
##                          VNK - VINA KNOWLEDGE                              ##
##                                                                            ##
##                  Site : https://www.vinaknowledge.com                      ##
##                  Email: hvloi@vinaknowledge.com                            ##
##                                                                            ##
##                     Copyright © 2019 Vina Knowledge                        ##
##                                                                            ##
################################################################################

# C M A K E  D E F I N I T I O N  F I L E

# Required version
cmake_minimum_required(VERSION 3.10.2)

# Project description
project(VNK_LibNotify VERSION 1.0.0 DESCRIPTION "VNK Lib Notification")

#-------------------------------------------------------------------------------

# Include
include(GNUInstallDirs)

#-------------------------------------------------------------------------------

add_library(VNK_LibNotify SHARED
    src/vnk_lib_notify.c
)

add_library(VNK_LibNotify_static STATIC
    src/vnk_lib_notify.c
)

# Set version property for the lib
set_target_properties(VNK_LibNotify PROPERTIES VERSION ${PROJECT_VERSION})

# Set SOVERSION
set_target_properties(VNK_LibNotify PROPERTIES SOVERSION 1)

set_target_properties(VNK_LibNotify PROPERTIES PUBLIC_HEADER
            include/vnk_lib_notify.h)

# Add includes for SHARED #
target_include_directories(VNK_LibNotify PRIVATE include)
target_include_directories(VNK_LibNotify PRIVATE src)

# Add include for STATIC #
target_include_directories(VNK_LibNotify_static PRIVATE include)
target_include_directories(VNK_LibNotify_static PRIVATE src)

# Install rule for lib:
# Install library directory: CMAKE_INSTALL_LIBDIR
# Install include directory: CMAKE_INSTALL_INCLUDEDIR
install(TARGETS VNK_LibNotify
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(VNK_LibNotify.pc.in VNK_LibNotify.pc @ONLY)

# Install package configuration:
install(FILES ${CMAKE_BINARY_DIR}/VNK_LibNotify.pc
            DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

