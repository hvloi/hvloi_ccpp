################################################################################
################################################################################
##                                                                            ##
##                  [ V N K - V I N A  K N O W L E D G E ]                    ##
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

##
# C M A K E - D E F I N I T I O N - F I L E
# VINA KNOWLEDGE GNU GETOPT EXAMPLE MODULE
# AUTHOR: Loi Huynh
##

# Required CMAKE Version #
cmake_minimum_required(VERSION 3.10.2)

# Project Description #
project(VNK_Getopt VERSION 1.0.0
            DESCRIPTION "VINA KNOWLEDGE GNU GETOPT EXAMPLE MODULE")

##------------------------------------------------------------------------------
# D E F I N E S
##

# ROOTFATHER get from command line arguments #
set(ROOTFATHER ${ROOTFATHER})

set(WORKROOT ${ROOTFATHER}/vinaknowledge_ccpp)

set(VNK_LIB_NOTIFY_DIR ${WORKROOT}/VNK_Library/VNK_LibNotify)
set(VNK_LIB_NOTIFY_INCLUDE ${VNK_LIB_NOTIFY_DIR}/include)
set(VNK_LIB_NOTIFY_STATIC libVNK_LibNotify_static.a)
set(VNK_LIB_NOTIFY_PATH ${VNK_LIB_NOTIFY_DIR}/build/${VNK_LIB_NOTIFY_STATIC})

MESSAGE("-- [DEBG]: VNK_LIB_NOTIFY_INCLUDE= "
            ${VNK_LIB_NOTIFY_INCLUDE})
MESSAGE("-- [DEBG]: VNK_LIB_NOTIFY_PATH= "
            ${VNK_LIB_NOTIFY_PATH})

# Specifying Binary #
set(BIN vnkcgo)

##------------------------------------------------------------------------------
# F U N C T I O N S
##

##
# Funtion VNK_NotifyInfo():
##
function(VNK_NotifyInfo message)
    MESSAGE("-- [INFO]: ${message}")
endfunction(VNK_NotifyInfo)

##------------------------------------------------------------------------------
# M A I N  C O D E
##

VNK_NotifyInfo("VINA KNOWLEDGE GNU GETOPT EXAMPLE MODULE")

VNK_NotifyInfo("Generating config...")

##
# Set Headers:
##
set(HEADER_FILES source/VNK_CGO_Utils.h)

##
# Add Sources:
##
set(SOURCES source/VNK_CGetoptExample.c source/VNK_CGO_Utils.c)

##
# Add Excutable Target:
##
add_executable(${BIN} ${SOURCES} ${HEADER_FILES})

##
# Includes
# This should be below add_executable()
##
target_include_directories(${BIN} PRIVATE include)
target_include_directories(${BIN} PRIVATE ${VNK_LIB_NOTIFY_INCLUDE})

##
# Link Notify Lib:
##
target_link_libraries(${BIN} ${VNK_LIB_NOTIFY_PATH})

##
# E N D
##------------------------------------------------------------------------------
