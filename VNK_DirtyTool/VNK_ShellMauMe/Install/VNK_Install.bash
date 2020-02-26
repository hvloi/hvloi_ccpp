################################################################################
################################################################################
##                                                                            ##
##                  [ V N K  -  V I N A  K N O W L E D G E ]                  ##
##                                                                            ##
##                   SITE  : https://www.vinaknowledge.com                    ##
##                   EMAIL : hvloi@vinaknowledge.com                          ##
##                                                                            ##
##                        TAN BINH DST, HCMC, VIET NAM                        ##
##                                                                            ##
##                 Copyright © 2019-2020 VNK - Vina Knowledge                 ##
##                                                                            ##
################################################################################
################################################################################

#!/bin/bash

##
# Shell script should be added the extension .bash, to let IDE recognize the
# format of the file.
##

##
# V N K  -  S C R I P T  M A` U  M E`  N O T  M A' U  M E
##

##------------------------------------------------------------------------------
# D E F I N I T I O N S
##

EXIT_OK=0
EXIT_KO=1

##
# We have mkDirr() functions to create directory where we can store all needed
# scripts
##
# mkDirr()

##
# Who I am ?
##
I_Am="$(whoami)"

##
# Oh where is our HOME ?
##
HOME="/home/$I_Am"



##
# What is our Directory ?
##
DIR="$HOME/.vnksmm"

##
# Where we are standing ?
##
CURE_DER="$(pwd)"

PARE_DIR="$(dirname $CURE_DER)"

SCRI_DIR="$PARE_DIR/Script"

##------------------------------------------------------------------------------
# M A I N  C O D E S S
##

##
# Exiting when error happens
##
exitt()
{
    echo "[INFO] Exiting,..."
    exit $1
}

##
# Making directory at the HOME of current user
##
mkdirr()
{
    echo -e "[INFO] Creating $DIR"

    mkdir $DIR

    local l_ret=$?
    if [ $l_ret -ne $EXIT_OK ]
    then
        echo "[ERRO] mkdir failed,..."
        exitt $l_ret
    fi
}

##
# Coping all needed script to made directory
##
copyy()
{
    echo "[INFO] Copying scripts,..."

    if [ ! -d $DIR ]
    then
        echo "[ERRO] $DIR dose not exist,..."
        exitt $EXIT_KO
    fi

    cp $SCRI_DIR/* $DIR/

    local l_ret=$?
    if [ $l_ret -ne 0 ]
    then
        echo "[ERRO] cp command,..."
        exitt $l_ret
    fi
}

##
# Running code from here #
##

# Making dir first #
mkdirr

# Copying needed scripts #
copyy

##
# E N D  S C R I P T
##------------------------------------------------------------------------------
