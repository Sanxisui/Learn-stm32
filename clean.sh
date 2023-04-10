#!/bin/bash
# **********************************************************
# Author        : lancz
# Email         : chengzhang.lan@jointligthing.com
# Create time   : 2023-01-29 16:48:04
# Last modified : 2023-01-29 16:48:04
# Filename      : clean.sh
# Description   : 
# **********************************************************
shopt -s extglob
RM_BIN_DIR_X64=`pwd`/dist/opt/bin/x64/
RM_BIN_DIR_ARM32=`pwd`/dist/opt/bin/arm32/
rm -rf $RM_BIN_DIR_X64/!(*.json|*.ko|*.sh|*.txt|*.md)
rm -rf $RM_BIN_DIR_ARM32/!(*.json|*.ko|*.sh|*.txt|*.md)

RM_LIB_DIR_X64=`pwd`/dist/opt/lib/x64/
RM_LIB_DIR_ARM32=`pwd`/dist/opt/lib/arm32/
rm -rf $RM_LIB_DIR_X64/!(*.json|*.ko|*.sh|*.txt|*.md)
rm -rf $RM_LIB_DIR_ARM32/!(*.json|*.ko|*.sh|*.txt|*.md)

rm -rf build