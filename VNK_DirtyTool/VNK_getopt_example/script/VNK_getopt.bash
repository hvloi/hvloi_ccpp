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
# V N K - G E T O P T  E X A M P L E
##

##------------------------------------------------------------------------------
# D E F I N I T I O N S
##

# Exit Codes #
EXIT_OK=0
EXIT_KO=1

# Who am I ??? #
IAM="$(basename $0)"

# Hello World #
echo ""
echo -e "[INFO]: $IAM starting...\n"

##------------------------------------------------------------------------------
# F U N C T I O N S
##

##------------------------------------------------------------------------------
# M A I N  C O D E
##

# These are arguments that we want to get from input #
FirName=""
MidName=""
LasName=""

GETOPT_SRESULT="$(getopt --name $IAM --options f:m:l: \
            --longoptions first-name:,middle-name:,last-name: \
            -- "$@")"
RetCode=$?

if [ "$RetCode" -ne "0" ]
then
    echo "[ERRO]: Error is shown as above =))! Exit!"
    exit $EXIT_KO
fi

eval set -- "$GETOPT_SRESULT"

while true
do
    case "$1" in 
        -f|--first-name)
            FirName=$2
            shift 2
            ;;
        -m|--middle-name)
            MidName=$2
            shift 2
            ;;
        -l|--last-name)
            LasName=$2
            shift 2
            ;;
        --)
            shift
            # Break the while loop #
            break
            ;;
        *)
            echo -e "[ERRO]: Internal error! Exit!\n"
            exit $EXIT_KO
            ;;
    esac
done

# Check out if we got correct input #

echo "[ V N K  G E T O P T ]"
echo "----------------------"
echo
echo "Here is what you type:"
echo "> First Name  : $FirName"
echo "> Middle Name : $MidName"
echo "> Last Name   : $LasName"
echo
echo "VN name format:"
echo "> $LasName $MidName $FirName"
echo
echo "----------------------"

echo
echo "[INFO]: Done! Bye! Bye!"
echo

exit $EXIT_OK

##
# E N D
##------------------------------------------------------------------------------
