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

# CMAKE DEFINITION FILE

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
set(SOURCES src/vnk_mq_main.c src/vnk_mq_create.c src/vnk_mq_tumlum.c
            src/vnk_notify.c src/vnk_mq_unlink.c src/vnk_mq_retrieve.c
            src/vnk_mq_edit.c src/vnk_mq_communi.c)

#add_custom_target( FinalMessage ALL
#    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Compilation is over..."
#    COMMENT "" )
#add_dependencies( FinalMessage vnkmq)

# Excutable files
add_executable(vnkmq ${SOURCES})

# Link library to target
# Find more at: https://cmake.org/cmake/help/latest/command/ \
# target_link_libraries.html#command:target_link_libraries
target_link_libraries(vnkmq rt)
