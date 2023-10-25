#!/usr/bin/env bash

MOUNT_POINT="/Volumes/RPI-RP2"
FW_FILE="glitcher.uf2"
WAIT_TIME=5

echo "This script will listen for new RP2040 devices in UF2 mode, and copy Bolt firmware to it"
while :
do
  if [ -d "${MOUNT_POINT}" ]; then
    echo "Copying firmware to new Bolt device"
    sleep 2
    cp $FW_FILE $MOUNT_POINT
    echo "Waiting ${WAIT_TIME} seconds to allow device to reboot"
    sleep $WAIT_TIME
  fi
done
