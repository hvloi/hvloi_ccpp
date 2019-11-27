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

#!/bin/bash

# Shell script should be added the extension .bash, to let IDE recognize the
# format of the file

# V N K - C H E C K  L I B  B U I L D  S C R I P T

EXIT_OK=0
EXIT_KO=1

BUILD_DIR="$(pwd)"
WORKSPACE="$(dirname "$BUILD_DIR")"
CMAKE="cmake"

MAKEFILE="Makefile"

CLEARED_FILE="CMakeCache.txt "
CLEARED_FILE+="CMakeFiles "
CLEARED_FILE+="cmake_install.cmake "
CLEARED_FILE+="Makefile "

help()
{
    echo -e ""
    echo -e "[ VNK - VINAKNOWLEDGE MAKE ]"
    echo -e "  Usage:"
    echo -e "    g: generate Makefile by calling cmake"
    echo -e "    m: make, call make"
    echo -e "    c: clean, clean up build directory"
    echo -e "    r: remove, remove built result (after call make)"
    echo -e "    w: wipe, wipe build space"
    echo -e "    h: Show this help"
    echo -e "\n"
}

c_make()
{
    echo -e "\n"
    echo -e "Calling \"cmake ..\" . . .\n"

    # Calling cmake ..
    $CMAKE .. ##

    echo -e "\n"
    echo -e ">> Done!\n"
}

m_make()
{
    echo -e "\n"
    echo -e "Calling Makefile . . .\n"

    # Check if Makefile is existed
    if [ ! -f $MAKEFILE ]
        then
        echo -e "Could not find Makefile!"
        echo -e "Make sure \"$0 -g\" was called\n"
    fi

    # Calling make
    make

    echo -e "\n"
    echo -e ">> Done!\n"
}

c_clean()
{
    echo -e "\n"
    echo -e "Clean up build directory . . .\n"
    echo -e "    Removing: $CLEARED_FILE"

    # rmrmrmrmrmrm
    rm -rf $CLEARED_FILE

    echo -e "\n"
    echo -e ">> Done!\n"
}

m_clean()
{
    echo -e "\n"
    echo -e "Removing binaries . . ."

    # Call make clean
    make clean

    echo -e "\n"
    echo -e ">> Done!\n"
}

w_wipe()
{
    echo -e "\n"
    echo -e "Wiping build space . . .\n"
    # Clean build result first
    m_clean
    # Clean cmake result
    c_clean
    echo -e "\n"
    echo -e ">> Done!\n"
}

if [ $# -eq 0 ]
then
    echo -e "\n"
    echo -e ">> Missing options!"
    echo -e "Please run $0 -h for help"
    echo -e ""
fi

# Turn of echo
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

# Turn on back ECHO
# ECHO="true"

# Exiting.........
exit $EXIT_OK
