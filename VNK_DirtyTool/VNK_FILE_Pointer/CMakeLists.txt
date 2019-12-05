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

# C M A K E - D E F I N I T I O N - F I L E
# VINA KNOWLEDGE FILE POINTER BLOG EXAMPLE
# AUTHOR: Loi Huynh
#

# Required CMAKE Version
cmake_minimum_required(VERSION 3.10.2)

# Project Description
project(VNK_BlogFilePointer VERSION 1.0.0
            DESCRIPTION "VINA KNOWLEDGE FILE POINTER BLOG EXAMPLE")

#-------------------------------------------------------------------------------
# D E F I N E S
#

# ROOTFATHER get from command line arguments
set(ROOTFATHER ${ROOTFATHER})

set(WORKROOT ${ROOTFATHER}/vinaknowledge_ccpp)

set(VNK_LIB_NOTIFY_DIR ${WORKROOT}/VNK_Library/VNK_LibNotify)
set(VNK_LIB_NOTIFY_INCLUDE ${VNK_LIB_NOTIFY_DIR}/include)
set(VNK_LIB_NOTIFY_STATIC libVNK_LibNotify_static.a)
set(VNK_LIB_NOTIFY_PATH ${VNK_LIB_NOTIFY_DIR}/build/${VNK_LIB_NOTIFY_STATIC})

MESSAGE("-- [DEBG]: VNK_LIB_NOTIFY_INCLUDE= "
            ${VNK_LIB_NOTIFY_INCLUDE})
MESSAGE("-- [DEBG]: VNK_LIB_NOTIFY_STATIC_PATH= "
            ${VNK_LIB_NOTIFY_STATIC_PATH})

#-------------------------------------------------------------------------------
# F U N C T I O N S
#

# Funtion VNK_NotifyInfo():
function(VNK_NotifyInfo message)
    MESSAGE("-- [INFO]: ${message}")
endfunction(VNK_NotifyInfo)

#-------------------------------------------------------------------------------
# M A I N  C O D E
#

VNK_NotifyInfo("VINA KNOWLEDGE FILE POINTER BLOG EXAMPLE")

VNK_NotifyInfo("Generating config...")

# Set Headers:
set(HEADER_FILES include/VNK_BLogFilePointer.h)

# Add Sources:
set(SOURCES src/VNK_BlogFilePointer.c)

# Add Excutable Target
add_executable(vnkfpx ${SOURCES} ${HEADER_FILES})

# Includes
# This should be below add_executable()
target_include_directories(vnkfpx PRIVATE include)
target_include_directories(vnkfpx PRIVATE ${VNK_LIB_NOTIFY_INCLUDE})

# Link Notify Lib
target_link_libraries(vnkfpx ${VNK_LIB_NOTIFY_PATH})

# Link Library To Target
# Find more at: https://cmake.org/cmake/help/latest/command/
# target_link_libraries.html#command:target_link_libraries
# target_link_libraries(vnkfpx rt)

#
# E N D
#-------------------------------------------------------------------------------
