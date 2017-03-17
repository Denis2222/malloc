#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


typedef enum { false, true } bool;

#define TINY 1024
#define SMALL 4096 //GETPAGESIZE


typedef struct    s_chunk
{
  int          size;
  void            *ptr;
  struct s_chunk  *next;
}                 t_chunk;

typedef struct s_block
{
  int          size;
  int          type;
  t_chunk      *child;
  struct s_block  *next;
}                 t_block;


int chunk_count(t_chunk *chunk)
{
  t_chunk *current;
  int     nb;

  nb = 0;
  current = chunk;
  while (current)
  {
    nb++;
    current = current->next;
  }
  return (nb);
}



t_block *getnewblock(int size, int type)
{
  t_block *block;

  block = (t_block*)mmap(0, size , PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1,0);
  if (block == MAP_FAILED)
  {
    perror("mmap");
    return (NULL);
  }
  block->size = size;
  block->type = type;
  block->child = NULL;
  block->next = NULL;
  return (block);
}

void    *blockstorechunk(t_block *block, int size)
{
  t_chunk *chunk;
  t_chunk *lastchunk;
  void    *ptr;
  int     nbchunk;

  nbchunk = chunk_count(block->child);
  chunk = (t_chunk*)(block + sizeof(t_block) + nbchunk * sizeof(t_chunk));
  ptr =      (void*)(block + sizeof(t_block) + (100 * sizeof(t_chunk)) + nbchunk * size);
  chunk->size = size;
  chunk->ptr = ptr;

  if (block->child == NULL)
    block->child = chunk;
  else
  {
    lastchunk = block->child;
    while (lastchunk->next)
    {
      lastchunk = lastchunk->next;
    }
    lastchunk->next = chunk;
  }

  return (ptr);
}

bool    blockcanstore(t_block *block, int size)
{
  int  sizefree;
  if (block->type != size)
    return (false);

  sizefree = block->size - sizeof(t_block) - ((sizeof(t_chunk) + block->type) * chunk_count(block->child));
  if (sizefree > size + sizeof(t_chunk))
    return (true);
  return (false);
}

t_block *blocksmanager(t_block *first)
{
  static t_block *blocks = NULL;

  if (first != NULL)
    blocks = first;
  return (blocks);
}


void *searchmapfor(int size)
{
  t_block *blocks;
  t_block *currentblock;
  t_block *blockavailable;
  bool    blockfound;

  blockfound = false;
  //CREATE OR GET BLOCKS
  if(!(blocks = blocksmanager(NULL)))
    blocks = blocksmanager(getnewblock(size * 100, size));

  //If can store in
  if (blockcanstore(blocks, size))
    return (blockstorechunk(blocks,size));

  currentblock = blocks;
  while (currentblock->next && !blockfound)
  {
    currentblock = currentblock->next;
    blockfound = blockcanstore(currentblock, size);
  }
  if (blockfound)
    return (blockstorechunk(currentblock,size));
  else
  {
    currentblock->next = getnewblock(size * 100, size);
    if (blockcanstore(currentblock->next, size))
      return (blockstorechunk(currentblock->next,size));
  }

  return (NULL);
}

int msize(int size)
{
  if (size < TINY)
    return (TINY);
  else if (size >= TINY && size < SMALL)
    return (SMALL);
  else
    return (size);
}

void *getfreemap(int size)
{
  return (searchmapfor(msize(size)));
}

void *ft_malloc(int size)
{
  return (getfreemap(size));
}


void show_alloc_mem()
{
  t_block *blocks;
  t_block *current;
  t_chunk *chunk;

  blocks = blocksmanager(NULL);
  current = blocks;
  while (current)
  {
    printf("\nblock:%d addr:%p s:%d ===================%#x================\n", current->type, current, sizeof(t_block), current->size);
    chunk = current->child;
    while(chunk)
    {
      printf("struct chunk  p:%p s:%d \n   Zone memoire:%p s:%d\n", chunk, sizeof(t_chunk), chunk->ptr, chunk->size);
      chunk = chunk->next;
    }
    current = current->next;
  }
}
/*
void *realloc(void *ptr, int size)
{

}

void free(void *ptr)
{

}

void show_alloc_mem()
{

}*/

int main(void)
{
  char *test;


  test = (char*)ft_malloc(2500);
  printf(" [ %p ] ", test);
  bzero(test, 10);
  strcpy(test,"HelloWorld    3 SMALL\n");
  printf("%s\n", test);


  test = (char*)ft_malloc(2500);
  printf(" [ %p ] ", test);
  bzero(test, 10);
  strcpy(test,"HelloWorld    5 SMALL\n");
  printf("%s\n", test);


  test = (char*)ft_malloc(2500);
  printf(" [ %p ] ", test);
  bzero(test, 10);
  strcpy(test,"HelloWorld    3 SMALL\n");
  printf("%s\n", test);


  test = (char*)ft_malloc(2500);
  printf(" [ %p ] ", test);
  bzero(test, 10);
  strcpy(test,"HelloWorld    5 SMALL\n");
  printf("%s\n", test);

  show_alloc_mem();
  //while(42);

  return (0);
}
