#!/bin/bash

while :
do
    echo "Starting IQRF DAEMON application..."
    /usr/bin/iqrf_startup /etc/iqrf-daemon/config.json
    echo "IQRF DAEMON applications has ended, wait for 60 seconds and start it again..."
    sleep 60
done
