# 42-formation-lvl1-6.pipex

### _Project 6: pipex - Sixth project for the formation of software engineers at school 42 São Paulo._

- This project aims to recreate the Unix pipe ( | ) command.

## _This project was like this:_

![so_long](https://user-images.githubusercontent.com/83036509/150965119-a96d5590-3971-43d0-959f-ee0d0f237d9e.gif)

## _How to test it_

For you to test this project, you should use the following way:

```c
./pipex file1 cmd1 cmd2 file2
```
Just in case: file1 and file2 are file names, cmd1 and cmd2 are shell commands with their parameters.

The execution of the pipex program should do the same as the next shell command:

```c
< file1 cmd1 | cmd2 > file2
```

Example 1:
```c
./pipex infile ``ls -l'' ``wc -l'' outfile
```
Should be the same as:
```c
< infile ls -l | wc -l > outfile
```

Example 2:
```c
 ./pipex infile ``grep a1'' ``wc -w'' outfile
```
Should be the same as:
```c
< infile grep a1 | wc -w > outfile
```

## _How i did (mandatory)_

-   [Makefile](https://github.com/Vinicius-Santoro/42-formation-lvl1-5.so-long/blob/main/READMES/01.makefile.md)
-   [pipex.c](https://github.com/Vinicius-Santoro/42-formation-lvl1-5.so-long/blob/main/READMES/02.so_long.md)
-   [errors.c](https://github.com/Vinicius-Santoro/42-formation-lvl1-5.so-long/blob/main/READMES/03.verify_error.md)
-   [cmd_parser.c](https://github.com/Vinicius-Santoro/42-formation-lvl1-5.so-long/blob/main/READMES/04.read_map.md)

