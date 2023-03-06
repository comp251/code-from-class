
To run the `malloc`/`realloc` example from class the past few days, you can run
`dynamic_array` either using standard input (keyboard) or from a file.

To run using standard input:

```
$ ./dynamic_array
```

You can enter numbers, separated by whitespace. When you are done entering data,
use `ctrl-d` to indicate end-of-file and the program will stop reading.

To run the program with a file input, you can generate a set of random numbers
using the `rand_file` program. The program takes two arguments: the number of
values to generate, and the output filename:

```
$ ./rand_file 128 temps.txt
$ ./dynamic_array nums.txt
```
