# malloc
Memory allocator implementation in C: implement malloc(), calloc(), free(), realloc()


<h2>Build the library</h2>
Open a terminal and just compile the library by tapping: 
```c
make libmalloc.so
```
Then, you can use some commands by loading the library:
```c
LD_PRELOAD=./libmalloc.so tree /
```
