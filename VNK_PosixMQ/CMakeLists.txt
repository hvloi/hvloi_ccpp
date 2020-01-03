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

##------------------------------------------------------------------------------
# C M A K E  D E F I N I T I O N  F I L E
# VINA KNOWLEDGE POSIX MESSAGE QUEUE EXAMPLE
# Author: Loi Huynh
#

# Required CMAKE Version #
cmake_minimum_required(VERSION 3.10.2)

# Project Description #
project(VNKMQ VERSION 1.0.0
            DESCRIPTION "VINA KNOWLEDGE POSIX MESSAGE QUEUE EXAMPLE")

##------------------------------------------------------------------------------
# D E F I N E S
##

# Set SOURCES #
set(SOURCES src/vnk_mq_main.c src/vnk_mq_create.c src/vnk_mq_tumlum.c
            src/vnk_notify.c src/vnk_mq_unlink.c src/vnk_mq_retrieve.c
            src/vnk_mq_edit.c src/vnk_mq_communi.c src/vnk_mq_sigNoti.c
            src/vnk_mq_ThreadNoti.c)

##
# Set Headers:
##
set(HEADER_FILES src/vnk_mq_sigNoti.h src/vnk_mq_ThreadNoti.h)

##------------------------------------------------------------------------------
# F U N C T I O N S
##

# No funtions #

##------------------------------------------------------------------------------
# M A I N  C O D E
##

# add_custom_target( StartMessage ALL
#    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Calling vnkmq Makefile..."
#    COMMENT "" )

# add_custom_target( FinalMessage ALL
#    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Compilation is over..."
#    COMMENT "" )
# add_dependencies( FinalMessage vnkmq)

# Excutable files #
add_executable(vnkmq ${SOURCES} ${HEADER_FILES})

##
# Includes 
# This should be below add_executable()
##
target_include_directories(vnkmq PRIVATE include)
# target_include_directories(vnkmq PRIVATE ${VNK_LIB_NOTIFY_INCLUDE})

##
# Link library to target 
# Find more at: https://cmake.org/cmake/help/latest/command/ \
# target_link_libraries.html#command:target_link_libraries
##
target_link_libraries(vnkmq rt)

##
# E N D
##------------------------------------------------------------------------------
