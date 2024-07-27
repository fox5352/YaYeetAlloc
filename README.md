# YaYeetAlloc

A basic memory allocator for the memes, it only works in linux

## prerequisites:
- gcc compiler
- cmake isntalled


### how to install Cmake
``` bash
    sudo apt install cmake
```

## how to build

``` bash
    mkdir build
    cd build

    cmake ..

    make
```

## how to install

In the build directory
```bash
    sudo make install
```

## to run tests

in the build directory run:
``` bash
    ctest
```

to include on you c project

``` c
#include "<yayeet_alloc.h>"// include header file in c project

int main() {
    int *ptr1 = NULL;// initialize a pointer

    ptr1 = rent_free(<size you want>);// malloc equivalent can return NULL if allocator failed

    *ptr1 = 12412;// use point by dereferencing the pointer

    int *ptr2 = tribe_rent_free(4, 100);// alloc equivalent

    ptr1 = run_it_back_rent_free(ptr1, 100)// reallocate copies current pointer and paste's data then free's' pointer and returns new block

    yeet(ptr1)// free the memory allocated
}

```
