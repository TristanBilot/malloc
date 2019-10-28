# malloc
Memory allocator implementation in C: implement malloc(), calloc(), free(), realloc().
This program supports multi-thread applications and use fragmentation to free memory and improve the speed of each allocation.

<h3>Core features</h3>

```c
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t number, size_t size);
void *realloc(void *ptr, size_t size);
```

<h3>Build and run the library</h3>
Open a terminal and just compile the library by tapping: 

```
make libmalloc.so
```

Then, you can use some commands by loading the library:
<h4>Linux</h4>

```
LD_PRELOAD=./libmalloc.so tree /
LD_PRELOAD=./libmalloc.so git status
LD_PRELOAD=./libmalloc.so ls -la
```
<h4>MacOS</h4>

```
DYLD_INSERT_LIBRARIES=./libmalloc.so DYLD_FORCE_FLAT_NAMESPACE=y tree /
...
```

<h3>Debug</h3>
If you want to modify and test your own version of code, you can debug it by using GDB after loading the .so file:

```
gdb ls -la
set exec-wrapper env 'LD_PRELOAD=./libmalloc.so'
start
```
