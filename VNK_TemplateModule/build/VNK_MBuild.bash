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

#!/bin/bash

##
# Shell script should be added the extension .bash, to let IDE recognize the
# format of the file.
##

##
# V N K - M O D U L E  T E M P L A T E
##

##------------------------------------------------------------------------------
# D E F I N I T I O N S
##

EXIT_OK=0
EXIT_KO=1

BUILD_DIR="$(pwd)"
WORKSPACE="$(dirname "$BUILD_DIR")"

MAKEFILE="Makefile"

CLEARED_FILE="CMakeCache.txt "
CLEARED_FILE+="CMakeFiles "
CLEARED_FILE+="cmake_install.cmake "
CLEARED_FILE+="Makefile "

# Hello World #
echo ""
echo -e "[INFO]: $0 starting...\n"

##
# Check for needed tools:
##

# W H I C H #
echo -e "[INFO]: checking WHICH..."
WHICH="$(which -h 2> /dev/null)"        # Redirect error to /dev/null
if [ -z "$WHICH" ]
then
    echo "[ERRO]: WHICH is not found, exit!"
    exit $EXIT_KO
fi
echo "" # Make a blank line

# G R E P #
echo -e "[INFO]: checking GREP..."
GREP="$(which grep 2> /dev/null)"       # Redirect error to /dev/null
echo "[DEBG]: GREP=$GREP"
if [ -z "$GREP" ]
then
    echo "[ERRO]: GREP is not found, exit!"
    exit $EXIT_KO
fi
echo "" # Make a blank line

# P W D #
##
# Using built-in pwd of Shell instead of /bin/pwd
##
echo -e "[INFO]: checking PWD..."
PWD="pwd"
TYPE_CMD="type -a"
BUILTIN_STR="builtin"
PWD_BUILTIN="$($TYPE_CMD $PWD | $GREP $BUILTIN_STR)"
echo "[DEBG]: PWD=$PWD"
if [ -z "$PWD_BUILTIN" ]
then
    echo "[ERRO]: PWD is not found, exit!"
    exit $EXIT_KO
else
    echo "[NOTI]: Using built-in PWD of the Shell!"
fi
echo "" # Make a blank line

# S E D #
echo -e "[INFO]: checking SED..."
SED="$(which sed 2> /dev/null)"         # Redirect error to /dev/null
echo "[DEBG]: SED=$SED"
if [ -z "$SED" ]
then
    echo "[ERRO]: SED is not found, exit!"
    exit $EXIT_KO
fi
echo "" # Make a blank line

# D I R N A M E #
echo -e "[INFO]: checking DIRNAME..."
DIRNAME="$(which dirname 2> /dev/null)" # Redirect error to /dev/null
echo "[DEBG]: DIRNAME=$DIRNAME"
if [ -z "$DIRNAME" ]
then
    echo "[ERRO]: DIRNAME is not found, exit!"
    exit $EXIT_KO
fi
echo "" # Make a blank line

# C M A K E #
echo -e "[INFO]: checking CMAKE..."
CMAKE="$(which cmake 2> /dev/null)"     # Redirect error to /dev/null
echo "[DEBG]: CMAKE=$CMAKE"
if [ -z "$CMAKE" ]
then
    echo "[ERRO]: CMAKE is not found, exit!"
    exit $EXIT_KO
fi
echo "" # Make a blank line

##
# Some more definitions
##

ROOTSOURCE="vinaknowledge_ccpp"
PWD_CMD="$PWD -L"
ROOTFATHER="$($PWD_CMD | $SED -e "s/\/$ROOTSOURCE\/.*$//")"
echo "[DEBG]: ROOTFATHER=$ROOTFATHER..."

l_CurrentDir="$(pwd)"
MODULEDIR="$(dirname "$l_CurrentDir")"
echo "[DEBG]: MODULEDIR=$MODULEDIR..."

##------------------------------------------------------------------------------
# F U N C T I O N S
##

help()
{
    echo -e ""
    echo -e "[ VNK - VINAKNOWLEDGE BUILD MODULE ]"
    echo -e "------------------------------------"
    echo -e "  Usage:"
    echo -e "    g: generate Makefile by calling cmake"
    echo -e "    m: make, call make"
    echo -e "    c: clean, clean up build directory"
    echo -e "    r: remove, remove built result (after call make)"
    echo -e "    w: wipe, wipe build space"
    echo -e "    h: Show this help"
    echo -e "------------------------------------"
    echo -e "\n"
}

c_make()
{
    echo -e "\n"
    echo -e "Calling \"$CMAKE $MODULEDIR\"\n"

    # Calling CMAKE #
    $CMAKE $MODULEDIR -DROOTFATHER="$ROOTFATHER"

    echo -e "\n"
    echo -e ">> Done!\n"
}

m_make()
{
    echo -e "\n"
    echo -e "Calling Makefile . . .\n"

    # Check if Makefile is existed #
    if [ ! -f $MAKEFILE ]
        then
        echo -e "Could not find Makefile!"
        echo -e "Make sure \"$0 -g\" was called\n"
    fi

    # Calling make #
    make

    echo -e "\n"
    echo -e ">> Done!\n"
}

c_clean()
{
    echo -e "\n"
    echo -e "Clean up build directory . . .\n"
    echo -e "    Removing: $CLEARED_FILE"

    # rmrmrmrmrmrm #
    rm -rf $CLEARED_FILE

    echo -e "\n"
    echo -e ">> Done!\n"
}

m_clean()
{
    echo -e "\n"
    echo -e "Removing binaries . . ."

    # Call make clean #
    make clean

    echo -e "\n"
    echo -e ">> Done!\n"
}

w_wipe()
{
    echo -e "\n"
    echo -e "Wiping build space . . .\n"
    # Clean build result first #
    m_clean
    # Clean cmake result #
    c_clean
    echo -e "\n"
    echo -e ">> Done!\n"
}

##------------------------------------------------------------------------------
# M A I N  C O D E
##

if [ $# -eq 0 ]
then
    echo -e "\n"
    echo -e ">> Missing options!"
    echo -e "Please run $0 -h for help"
    echo -e ""
fi

# Turn of echo #
# ECHO="false"

while getopts "hecgmrw" OPTION; do
    case $OPTION in
        e)
            ECHO="true"
            ;;

        h)
            help
            ;;

        c)
            c_clean
            ;;

        g)
            c_make
            ;;

        m)
            m_make
            ;;

        r)
            m_clean
            ;;

         w)
            w_wipe
            ;;

        *)
            help
            ;;

        esac
done

# Turn on back ECHO #
# ECHO="true"

echo -e "[INFO]: $0 done, exiting...\n"

# Exiting... #
exit $EXIT_OK

##
# E N D
##------------------------------------------------------------------------------
