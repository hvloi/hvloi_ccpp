################################################################################
################################################################################
##                                                                            ##
##                    V N K - V I N A  K N O W L E D G E                      ##
##                                                                            ##
##                   SITE  : https://www.vinaknowledge.com                    ##
##                   EMAIL : hvloi@vinaknowledge.com                          ##
##                                                                            ##
##                       TAN BINH DST, HCMC, VIET NAM                         ##
##                                                                            ##
##                      Copyright © 2019 Vina Knowledge                       ##
##                                                                            ##
################################################################################
################################################################################

# C M A K E  D E F I N I T I O N  F I L E
# VNK CHECK LIB

# Required version
cmake_minimum_required(VERSION 3.10.2)

# Project description
project(VNK_CheckLib VERSION 1.0.0 DESCRIPTION "VNK Lib Checker")

#add_custom_target( StartMessage ALL
#    ${CMAKE_COMMAND} -E cmake_echo_color --cyan
#    "Calling vnk_checklib Makefile..."
#    COMMENT "" )

# St headers:
set(HEADER_FILES include/VNK_CheckLib.h)

# Add sources:
set(SOURCES src/VNK_CheckLib.c src/VNK_LocalFunctions.c)

#add_custom_target( FinalMessage ALL
#    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Compilation is over..."
#    COMMENT "" )
#add_dependencies( FinalMessage vnk_checklib)

# Excutable files
add_executable(vnk_checklib ${SOURCES} ${HEADER_FILES})

# Includes
# This should be below add_executable()
target_include_directories(vnk_checklib PRIVATE include)
target_include_directories(vnk_checklib PRIVATE /home/hvloi/study_space/vinaknowledge_ccpp/vnk_lib/VNK_LibNotify/include)

# Link notify lib
target_link_libraries(vnk_checklib /home/hvloi/study_space/vinaknowledge_ccpp/vnk_lib/VNK_LibNotify/build/libVNK_LibNotify_static.a)

# Link library to target
# Find more at: https://cmake.org/cmake/help/latest/command/ \
# target_link_libraries.html#command:target_link_libraries
# target_link_libraries(vnk_checklib rt)
