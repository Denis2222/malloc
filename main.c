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
  int             content;
}                 t_chunk;

typedef struct    s_block
{
  int             total;
  int             size;
  struct s_block  *next;
}                 t_block;

t_block *getnewblock(int type)
{
  t_block *block;
  int     i;
  t_chunk *chunk;
  i = 0;
  block = (t_block*)mmap(0, type * 100 + (100*sizeof(t_chunk)) + sizeof(t_block) , PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1,0);
  if (block == MAP_FAILED)
  {
    perror("mmap");
    return (NULL);
  }
  block->total = type * 100 + (100*sizeof(t_chunk)) + sizeof(t_block);

  printf("block TOTAL:%#x", block->total);
  block->size = type;
  block->next = NULL;
  while (i < 100)
  {
    chunk = block + sizeof(t_block) + (sizeof(t_chunk) * i);
    printf("alloc:%p\n", chunk);
    chunk->content = 0;
    i++;
  }
  return (block);
}

void    *blockstorechunk(t_block *block, int type, int size)
{
  int i;
  t_chunk *chunk;
  void    *ptr;

  i = 0;
  while (i < 100)
  {
    chunk = (t_chunk*)(block + sizeof(t_block) + (sizeof(t_chunk) * i));
    if (chunk->content == 0)
      break;
    i++;
  }
  chunk->content = size;
  ptr = (void*) (block + sizeof(t_block) + (100 * sizeof(t_chunk)) + i * type);
  return (ptr);
}

bool    blockcanstore(t_block *block, int type)
{
  int  sizefree;
  t_chunk *chunk;
  int i;

  i = 0;
  if (block->size != type)
    return (false);

  while (i < 100)
  {
    chunk = (t_chunk*)(block + sizeof(t_block) + (sizeof(t_chunk) * i));
    if (chunk->content == 0)
      return (true);
    i++;
  }
  return (false);
}

t_block *blocksmanager(t_block *first)
{
  static t_block *blocks = NULL;

  if (first != NULL)
    blocks = first;
  return (blocks);
}


void *searchmapfor(int type, int size)
{
  t_block *blocks;
  t_block *currentblock;
  t_block *blockavailable;
  bool    blockfound;

  blockfound = false;
  //CREATE OR GET BLOCKS
  if(!(blocks = blocksmanager(NULL)))
    blocks = blocksmanager(getnewblock(type));

  //If can store in
  if (blockcanstore(blocks, type))
    return (blockstorechunk(blocks,type,size));

  currentblock = blocks;
  while (currentblock->next && !blockfound)
  {
    currentblock = currentblock->next;
    blockfound = blockcanstore(currentblock, size);
  }
  if (blockfound)
    return (blockstorechunk(currentblock,type,size));
  else
  {
    currentblock->next = getnewblock(type);
    if (blockcanstore(currentblock->next, size))
      return (blockstorechunk(currentblock->next,type,size));
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
  return (searchmapfor(msize(size), size));
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
  void *ptr;
  int i;

  i = 0;
  blocks = blocksmanager(NULL);
  current = blocks;
  while (current)
  {
    printf("\nblock:%d addr:%p s:%d ===================%#x======%p==========\n", current->total, current, sizeof(t_block), current->size, (current+current->total));

    while (i < 100)
    {
      chunk = (t_chunk*)(current + sizeof(t_block) + (sizeof(t_chunk) * i));
      ptr = (void*) (current + sizeof(t_block) + (100 * sizeof(t_chunk)) + (i * current->size));
      if (chunk->content > 0)
        printf("Chunk %d/%d %d %p\n", chunk->content, current->size, sizeof(t_chunk),ptr);
      i++;
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


  test = (char*)ft_malloc(1020);
  printf(" [ %p ] ", test);
  strcpy(test,"HelloWorld    3 SMALL\n");
  printf("%s\n", test);


  test = (char*)ft_malloc(1020);
  printf(" [ %p ] ", test);
  strcpy(test,"HelloWorld    3 SMALL\n");
  printf("%s\n", test);

  test = (char*)ft_malloc(1020);
  printf(" [ %p ] ", test);
  strcpy(test,"HelloWorld    3 SMALL\n");
  printf("%s\n", test);



  test = (char*)ft_malloc(1020);
  printf(" [ %p ] ", test);
  strcpy(test,"HelloWorld    3 SMALL\n");
  printf("%s\n", test);

  test = (char*)ft_malloc(1020);
  printf(" [ %p ] ", test);
  strcpy(test,"HelloWorld    3 SMALL\n");
  printf("%s\n", test);

  //
  //
  // test = (char*)ft_malloc(1020);
  // printf(" [ %p ] ", test);
  // strcpy(test,"HelloWorld    3 SMALL\n");
  // printf("%s\n", test);
  //
  // test = (char*)ft_malloc(1020);
  // printf(" [ %p ] ", test);
  // strcpy(test,"HelloWorld    3 SMALL\n");
  // printf("%s\n", test);
  //
  // show_alloc_mem();
  //
  // test = (char*)ft_malloc(100);
  // printf(" [ %p ] ", test);
  //
  // strcpy(test,"HelloWorld    3 SMALL\n");
  // printf("%s\n", test);

  // test = (char*)ft_malloc(2500);
  // printf(" [ %p ] ", test);
  //
  // strcpy(test,"HelloWorld    3 SMALL\n");
  // printf("%s\n", test);
  //
  //
  // test = (char*)ft_malloc(2500);
  // printf(" [ %p ] ", test);
  //
  // strcpy(test,"HelloWorld    5 SMALL\n");
  // printf("%s\n", test);
  //
  //
  // test = (char*)ft_malloc(2500);
  // printf(" [ %p ] ", test);
  //
  // strcpy(test,"HelloWorld    3 SMALL\n");
  // printf("%s\n", test);
  //
  //
  // test = (char*)ft_malloc(2500);
  // printf(" [ %p ] ", test);
  //
  // strcpy(test,"HelloWorld    5 SMALL\n");
  // printf("%s\n", test);
  //
  //
  //   test = (char*)ft_malloc(5500);
  //   printf(" [ %p ] ", test);
  //
  //   strcpy(test,"HelloWorld    5 SMALL\n");
  //   printf("%s\n", test);
  //
  //   test = (char*)ft_malloc(55000);
  //   printf(" [ %p ] ", test);
  //
  //   strcpy(test,"HelloWorld    5 SMALL\n");
  //   printf("%s\n", test);
  //

    printf("[%p    %p]", test, test + sizeof(t_block) + 100 * sizeof(t_chunk));

  show_alloc_mem();
  //while(42);

  return (0);
}
