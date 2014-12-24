#!/bin/bash

# sudo ./st-flash write /home/anton/Source/Bootloader/Debug/Bootloader.hex 0x08000000

# lsusb
# ID 0483:3748 SGS Thomson Microelectronics ST-LINK/V2

STLINK_PATH=/home/anton/Distrib/stm32/stm32-tools/stlink/st-flash
BOOTLOADER_BIN=/home/anton/Source/Bootloader/Debug/Bootloader.bin
APP_BIN=/home/anton/Source/JumpAddressPrj/Debug/JumpAddressPrj.bin
IMS_BIN=/home/anton/Source/IMS/Debug/IMS.bin

BOOTLOADER_ADDR=0x08000000
APP_ADDR=0x08004000
IMS_ADDR=0x08004000

$STLINK_PATH write $BOOTLOADER_BIN $BOOTLOADER_ADDR > /dev/null
$STLINK_PATH write $IMS_BIN $IMS_ADDR > /dev/null