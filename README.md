# Repository for "pipex" - project at 42 school Hive.

The objective of this project was to mimic the shell command pipe ("|"). to develop an understanding of especially the following C functions:
- pipe()
- fork()
- exec()
- exit()
- access()
- dup()

The format of the execute command for the pipex program is:

__./pipex file1 cmd1 cmd2 file2__

which mimics the following shell command:

__$> < file1 cmd1 | cmd2 > file2__

file1 is the **infile**, cmd1 is the **first command**, cmd2 is the **second command** and file2 is the **outfile**
