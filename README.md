# aflk

## Overview

`aflk` is a command-line utility designed to handle advisory file locks on Unix-like systems using the `fcntl` system call. The tool offers functionalities to set and query locks on specified files, ensuring proper synchronization and coordination between processes when accessing shared resources.

### Example

Invoke the tool by stipulating the desired options followed by the target filename.

For instance, to set a write lock on a file named `example.txt`, execute:

```bash
./aflk -S -t write example.txt
```

## Options

- `-S` or `--setlk`: Apply a lock using `F_SETLK`. This will fail if the lock cannot be obtained.
- `-W` or `--setlkw`: Apply a lock using `F_SETLKW`. As for `F_SETLK`(`-S` or `--setlk`), but if a conflicting lock is held on the file, then wait for that lock to be released.
- `-G` or `--getlk`: Query the lock status of a file using `F_GETLK`.
- `-t` or `--type`: Define the lock type. Options are `read` for read locks (`F_RDLCK`) and `write` for write locks (`F_WRLCK`).
- `-s` or `--start`: Indicate the starting byte of the lock.
- `-w` or `--whence`: Determine how the `l_start` value is interpreted. Choices are `set` (file start), `cur` (current position), and `end` (file end).
- `-l` or `--len`: Specify the span (in bytes) to lock. A value of `0` locks up to the file's end.

## Features

- **Set Advisory Locks**: Use `F_SETLK` to set locks on files.
- **Set Advisory Locks by Waiting**: Use `F_SETLKW` if you want to wait for the lock to be established.
- **Query Lock Status**: Use `F_GETLK` to retrieve the lock status of files.

### To Set Advisory Locks

Set an advisory lock on a file. This can be a read (F_RDLCK) or write (F_WRLCK) lock.

Command:

```bash
aflk -S -t [read|write] [options] <filename>
```

For example, to set a write lock on file.txt:

```bash
aflk -S -t write file.txt
```

### To Set Advisory Locks by Waiting

For setting a lock that waits until it can obtain the lock:

Command:

```bash
aflk -W -t [read|write] [options] <filename>
```

For example:

```bash
aflk -W -t write file.txt
```

### To Query Lock Status

To check the current advisory lock status of a file:

Command:

```bash
aflk -G [options] <filename>
```

For example:

```bash
aflk -G file.txt
```

### Additional Options

Specify the starting byte with -s or --start.
Define the interpretation of the l_start value (set, cur, or end) with -w or --whence.
Indicate the span (in bytes) to lock with -l or --len. Using 0 will lock up to the file's end.
If you're unsure about any option, please refer to the tool's documentation or this guide for clarity.

## Installation

Follow these steps to install `aflk`:

1. **Download the Source and Installation Script**
   - Make sure you have `install.sh` in your current directory.

2. **Provide Execute Permissions**
   - Before running the installation script, you need to give it execute permissions. Use the following command:

     ```bash
     chmod +x install.sh
     ```

3. **Run the Installation Script**
   - Now, run the installation script. This will compile the source code and place the executable in the appropriate directory.

     ```bash
     ./install.sh
     ```

   - If everything goes smoothly, you should see a message indicating a successful installation.

## Uninstallation

If you wish to uninstall `aflk`, follow these steps:

1. **Download the Uninstallation Script**
   - Make sure you have `uninstall.sh` in your current directory.

2. **Provide Execute Permissions**
   - Give the uninstallation script execute permissions using:

     ```bash
     chmod +x uninstall.sh
     ```

3. **Run the Uninstallation Script**
   - Now, execute the uninstallation script to remove the tool from your system.

     ```bash
     ./uninstall.sh
     ```

   - Upon successful removal, you'll receive a confirmation message.
