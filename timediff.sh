#!/bin/bash

# This script is to caculate how long a script takes

START=$(date +%s)

# do something
# start your script work here
ls -R /etc > /tmp/x
rm -f /tmp/x
sleep 5

# your logic ends here
END=$(date +%s)
DIFF=$(( $END - $START ))
MIN=$(( $DIFF / 60))
SEC=$(( $DIFF % 60)) 

echo "It took $MIN minutes and $SEC seconds"
