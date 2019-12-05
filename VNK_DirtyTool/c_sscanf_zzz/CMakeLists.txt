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

# C M A K E - D E F I N I T I O N - F I L E

# FOR SSCANF EXAMPLE

# Required version
cmake_minimum_required(VERSION 3.10.2)

# Project name
project(vinaknowledge_ccpp)

#add_custom_target( StartMessage ALL
#    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Calling vnkmq Makefile..."
#    COMMENT "" )

# Includes
include_directories(include)

# Add sources
set(SOURCES src/vnk_sscanf_exp_main.c)

#add_custom_target( FinalMessage ALL
#    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Compilation is over..."
#    COMMENT "" )
#add_dependencies( FinalMessage vnkmq)

# Excutable files
add_executable(vnksscanf ${SOURCES})

# Link library to target
# Find more at: https://cmake.org/cmake/help/latest/command/ \
# target_link_libraries.html#command:target_link_libraries
# target_link_libraries(vnkmq rt)
