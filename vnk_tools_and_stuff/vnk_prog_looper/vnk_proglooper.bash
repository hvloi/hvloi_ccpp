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

#!/bin/bash

# N O T I C E
# Using SH if your BASH is not available in your system
#

# H O W  T H I S  W O R K ? < DESIGN
# vnk_proglooper.bash -p <"program name"> -n <number of loop> -t <rate>
#

EXIT_OK=0
EXIT_KO=1

LOOP_NUM=0 # Default this is equal 0, imply an infinitive loop
LOOP_RAT=3 # Loop rate, default is 3 seconds
PROG=""    # Program to run

help()
{
    echo
    echo -e "[V N K] - $0\n"
    echo -e "HELP: Read this script to know how to use, thanks :]]\n"
    echo
}

run()
{
    # N O T I C E :
    # Need an error check, if $? != 0, exit
    $PROG
    sleep $LOOP_RAT
    echo
    echo "------------------------------------------------------"
    echo
}

if [ $# == 0 ]
then
    echo
    echo -e "[ERROR] This script need arguments!"
    echo -e "        Type $0 -h for help."
    echo
fi

while getopts "hn:r:p:" OPTION
do
    case $OPTION in
        h)
            help
            exit $EXIT_OK
            ;;
        n)
            LOOP_NUM=$OPTARG
            ;;
        r)
            LOOP_RAT=$OPTARG
            ;;
        p)
            PROG=$OPTARG
            ;;
        *)
            help # Also show help
            exit $EXIT_OK
            ;;
     
    esac
done

# D e b u g , let it be there, do not remove
# echo -e ">> LOOP_NUM=$LOOP_NUM\n"
# echo -e ">> LOOP_RAT=$LOOP_RAT\n"
# echo -e ">> PROG=$PROG\n"

# R u n  t h e  p r o g r a m
if [ $LOOP_NUM -eq 0 ]
then
    while [ 1 ]
    do
        run
    done
elif [ $LOOP_NUM -gt 0 ]
then
    for in in `seq 1 $LOOP_NUM` # From 1 to LOOP_NUM << N I C E ! ! !
    do
        run
    done
fi

echo
echo -e "[INFO] D O N E ! BYE ! ! !"
echo

exit $EXIT_OK
