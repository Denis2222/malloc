# malloc

Make malloc great again !  

42 C project. 

Remake basic malloc-realloc-free function with mmap-munmap.

Test on linux(debian 8-9) and osx.

Compile
```
make
```


Try
```
./run.sh ls -lR /
```


```
# define TINY 1024
# define SMALL 4096

typedef struct  s_block
{
        size_t  id;
        size_t  content;
        void    *ptr;
}               t_block;

typedef struct  s_map
{
        void          *ptr;
        size_t        total;
        size_t        type;
        int           available;
        struct s_map  *next;
}                     t_map;
```

How that work ?

mmap, munmap - map or unmap files or devices into memory.
syscall to os for memory, size is % PAGESIZE (debian and osx have 4096 octets) 

can be ~slow for 100 zone of 1000 octets. (because 100 syscall)

malloc can prevent a huge call number to syscall.

t_map represent an mmap region ( can contain 100 * TINY or 100 * SMALL or 1 * >SMALL)
t_block represent a malloc(x) memory zone of size (x) (type TINY or type SMALL or Bigger).
