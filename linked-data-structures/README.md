# Linked list code from 3/24

To compile:

```
$ gcc -c ll.c
$ gcc ll_driver.c -o ll_driver ll.o
```

Run the driver program:

```
$ ./ll_driver
```

This is an interactive program to add elments to a list, print it, and free it.

```
$ ./ll_driver
i n0 n1 ...  insert values into list
g idx        get element at idx from the list
f            free list
p            print list
> i 10 20 1 3 7 8 6 9
insert 10...
    - [10]
insert 20...
    - [20, 10]
insert 1...
    - [1, 20, 10]
insert 3...
    - [3, 1, 20, 10]
insert 7...
    - [7, 3, 1, 20, 10]
insert 8...
    - [8, 7, 3, 1, 20, 10]
insert 6...
    - [6, 8, 7, 3, 1, 20, 10]
insert 9...
    - [9, 6, 8, 7, 3, 1, 20, 10]
inserted 8 values
> g 0
getting element at index 0
list[0] -> 9
> g 3
getting element at index 3
list[3] -> 7
> p
[9, 6, 8, 7, 3, 1, 20, 10]
> f
freeing list...
[]
```
