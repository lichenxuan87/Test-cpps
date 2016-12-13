#!/bin/sh


# "d" and "directory" have required arguments
# "s" and "stream" have required arguments
# "a" use optional arguments, use "a::". 
# "b" have no arguments, just use "b"


# read the options
TEMP=`getopt -o d:s: --long directory:,stream: -n 'covAnalyzeCommit.sh' -- "$@"`
eval set -- "$TEMP"

# extract options and their arguments into variables.
while true ; do
    case "$1" in
        -d|--directory) 
            case "$2" in
                "") shift 2 ;;
                *) DIRECTORY=$2 ; shift 2 ;;
            esac ;;
        -s|--stream)
            case "$2" in
                "") shift 2 ;;
                *) STREAM=$2 ; shift 2 ;;
            esac ;;
#        -a|--arga)
#            case "$2" in
#                "") ARG_A='some default value' ; shift 2 ;;
#                *) ARG_A=$2 ; shift 2 ;;
#            esac ;;
#        -b|--argb) ARG_B=1 ; shift ;;

        --) shift ; break ;;
        *) echo "Internal error!" ; exit 1 ;;
    esac
done

if [ "${YUNOS_VERSION}" = "" ]; then
    echo "Yunos Version not defined"
else
    echo ${YUNOS_VERSION}
fi



if [ "${DIRECTORY}" = "" ] || [ "${STREAM}" = "" ]; then
    echo "Usage: ./covAnalyze -d <build_directory> -s <commit stream>"
    exit 1
else
    if [ -d ${DIRECTORY} ] && [ -d ${STREAM} ]; then
        echo "${DIRECTORY} exists"
    else
        echo "${DIRECTORY} doesn't exists"
        exit
    fi
    
    echo "Build target directory: $DIRECTORY"
    echo "Issue commit stream: $STREAM"
fi


rm -rf ~/result_coverity/*

cd $DIRECTORY
mk -c
cov-build --dir ~/result_coverity mk -a

cov-analyze --dir ~/result_coverity -all --security

cov-commit-defects --host 10.25.53.203 --dataport 9090 --stream $STREAM --user admin --password 654321 --dir ~/result_coverity

