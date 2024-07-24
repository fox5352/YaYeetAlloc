# YaYeetAlloc
A basic memory allocator

## prerequisites:
- gcc compiler
- cmake isntalled

``` bash
    sudo apt install cmake
```

### how to build
``` bash
    mkdir build
    cd build

    cmake ..

    make
```


### to run tests

in the build directory run:
``` bash
    ctest
```
to include on you c project

``` c
#include "yayeet_alloc.h"// include header file in c project

int main() {
    int *ptr1 = NULL;// initialize a pointer

    ptr1 = rent_free(<size you want>);// can return NULL if allocator failed

    *ptr1 = 12412;// use point by dereferencing the pointer


    yeet(ptr1)// free the memory allocated
}

```
