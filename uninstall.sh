#!/bin/bash

# インストール先のディレクトリ
INSTALL_DIR="/usr/local/bin"
# 実行可能ファイルの名前
EXEC_NAME="aflk"

# 実行可能ファイルが存在するか確認
if [ ! -f $INSTALL_DIR/$EXEC_NAME ]; then
    echo "Error: $EXEC_NAME not found in $INSTALL_DIR!"
    exit 1
fi

# 実行可能ファイルをインストールディレクトリから削除
rm $INSTALL_DIR/$EXEC_NAME
if [ $? -ne 0 ]; then
    echo "Failed to remove the executable from $INSTALL_DIR!"
    exit 1
fi

echo "$EXEC_NAME has been successfully uninstalled from $INSTALL_DIR!"

