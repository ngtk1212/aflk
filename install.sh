#!/bin/bash

# installation directory
INSTALL_DIR="/usr/local/bin"
# command name
EXEC_NAME="aflk"

# build
make $EXEC_NAME
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# check already installed
if [ -f $INSTALL_DIR/$EXEC_NAME ]; then
    echo "$EXEC_NAME has already installed."
    exit 1
fi

# install
cp ./output/$EXEC_NAME $INSTALL_DIR/
if [ $? -ne 0 ]; then
    echo "Failed to copy the executable to $INSTALL_DIR."
    exit 1
fi

echo "$EXEC_NAME has been installed successfully to $INSTALL_DIR."

exit 0
