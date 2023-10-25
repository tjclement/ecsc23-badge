#!/usr/bin/env bash

WAIT_TIME=5

echo "This script will listen for new target devices, and copy ECSC23 firmware to it"
while :
do
  read -p "Press enter to flash"
  openocd -d0 -f openocd_flash.cfg && echo "Success" || echo "Flashing failed"
done
