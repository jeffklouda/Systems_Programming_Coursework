#!/bin/sh 

EXITCODE="0"

if [ "${#}" = "0" ] ;  then
    echo "Usage: extract.sh archive1 archive2..."
    exit 1
else
    while [ "${#}" -gt "0" ] 
    do
        case ${1} in
            *.tgz) 
                echo ".tgz found"
                tar -xzf ${1}
                ;;
            *.tar.gz) 
                echo ".tar.gz found: ${1}"
                tar -xzf ${1}
                ;;

            *.tbz) 
                echo ".tbz found"
                tar -xjf ${1}
                ;;
            *.tar.bz2) 
                echo ".tar.bz2 found"
                tar -xjf ${1}
                ;;

            *.txz) 
                echo ".txz found"
                tar -Jxf ${1}
                ;;
            *.tar.xz) 
                echo ".tar.xz found"
                tar -Jxf ${1}
                ;;

            *.zip) 
                echo ".zip found"
                unzip ${1}
                ;;
            *.jar) 
                echo ".jar found"
                jar -xf ${1}
                ;;

            *) 
                echo "Unsupported file extension: ${1}" 
                EXITCODE=1
                ;;
        esac
        shift
    done
fi

exit ${EXITCODE}
