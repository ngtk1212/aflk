#!/bin/bash

# installation directory
INSTALL_DIR="/usr/local/bin"
# command name
EXEC_NAME="aflk"

# check command installed
if [ ! -f $INSTALL_DIR/$EXEC_NAME ]; then
    echo "Error: $EXEC_NAME not found in $INSTALL_DIR!"
    exit 1
fi

# uninstall
rm $INSTALL_DIR/$EXEC_NAME
if [ $? -ne 0 ]; then
    echo "Failed to remove the executable from $INSTALL_DIR!"
    exit 1
fi

echo "$EXEC_NAME has been successfully uninstalled from $INSTALL_DIR!"

