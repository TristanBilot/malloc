# malloc
Memory allocator implementation in C: implement malloc(), calloc(), free(), realloc().
This program supports multi-thread applications and use fragmentation to free memory and improve the speed of each allocation.


<h3>Build and run the library</h3>
Open a terminal and just compile the library by tapping: 

```
make libmalloc.so
```

Then, you can use some commands by loading the library:
```
LD_PRELOAD=./libmalloc.so tree /
LD_PRELOAD=./libmalloc.so git status
LD_PRELOAD=./libmalloc.so ls -la
```

<h3>Debug</h3>
If you want to modify and test your own version of code, you can debug it by using GDB after loading the .so file:

```
gdb ls -la
set exec-wrapper env 'LD_PRELOAD=./libmalloc.so'
start
```
