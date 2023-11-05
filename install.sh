#!/bin/bash

# インストール先のディレクトリ
INSTALL_DIR="/usr/local/bin"
# 実行可能ファイルの名前
EXEC_NAME="aflk"

# コンパイル
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

# 実行可能ファイルをインストールディレクトリにコピー
cp ./output/$EXEC_NAME $INSTALL_DIR/
if [ $? -ne 0 ]; then
    echo "Failed to copy the executable to $INSTALL_DIR."
    exit 1
fi

echo "$EXEC_NAME has been installed successfully to $INSTALL_DIR."

exit 0
