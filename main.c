#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef enum { false, true } bool;

#define TINY 1024
#define SMALL 4096 //GETPAGESIZE

#define BLOCK_MAX 50

typedef struct    s_block
{
  long            id;
  long            content;
  void            *ptr;
}                 t_block;

typedef struct    s_map
{
  void            *ptr;
  long            total;
  long            type;
  int             empty;
  struct s_map    *next;
  t_block         *firstblock;
  t_block         *emptyblock;
}                 t_map;

#define SIZEBLOCK sizeof(t_block)
#define SIZEMAP sizeof(t_map)
// MMAP %P  T_BLOCK         T_CHUNK
//  0x0      0x0 ->  0x16   ->

long mapsize(long size)
{
  long mapsize;
  if (size < TINY)
    mapsize = (SIZEMAP + (BLOCK_MAX*SIZEBLOCK) + (TINY * BLOCK_MAX));
  else if (size >= TINY && size < SMALL)
    mapsize = (SIZEMAP + (BLOCK_MAX*SIZEBLOCK) + (SMALL * BLOCK_MAX));
  else
    mapsize = (SIZEMAP + SIZEBLOCK + size);
  return (mapsize);
}

long sizetype(long size)
{
  if (size < TINY)
    return (TINY);
  else if (size >= TINY && size < SMALL)
    return (SMALL);
  else
    return (size);
}

t_block *getblockptrbyid(t_map *map, int id)
{
  if (map->type == TINY)
  {
    return (t_block*)(map->ptr + SIZEMAP + (SIZEBLOCK * BLOCK_MAX) + (TINY * id));
  }
  else if(map->type == SMALL)
  {
    return (t_block*)(map->ptr + SIZEMAP + (SIZEBLOCK * BLOCK_MAX) + (SMALL * id));
  }
  else
    return ((t_block*)(map->ptr + SIZEMAP + SIZEBLOCK));
}

t_block *getblockbyid(t_map *map, int id)
{
  t_block *block;
  if (map->type == TINY)
  {
    block = (t_block*)(map->ptr + sizeof(t_map) + (sizeof(t_block) * id));
    return block;
  }
  else if(map->type == SMALL)
  {
    return (t_block*)(map->ptr + SIZEMAP + SIZEBLOCK * id);
  }
  else
    return ((t_block*)(map->ptr + SIZEMAP));
}

void initblockmap(t_map *map) {
  int id;
  t_block *block;

  id = 0;
  while (id < BLOCK_MAX)
  {
    block = getblockbyid(map, id);
    block->id = id;
    block->content = 0;
    block->ptr = getblockptrbyid(map, id);
    id++;
    if (map->type > SMALL)
      break;
  }
}


t_map *newmap(long size)
{
  t_map   *map;
  void *ptrmmap;

  ptrmmap = mmap(0, mapsize(size), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1,0);
  map = (t_map*)ptrmmap;
  if (ptrmmap == MAP_FAILED)
  {
    perror("mmap");
    return (NULL);
  }
  map->ptr = ptrmmap;
  map->total = mapsize(size);
  map->type = sizetype(size);
  map->next = NULL;
  map->empty = BLOCK_MAX;
  initblockmap(map);
  map->firstblock = getblockbyid(map, 0);
  map->emptyblock = getblockbyid(map, 0);
  return (map);
}

t_map *staticmaps(t_map *first)
{
  static t_map *maps = NULL;

  if (first != NULL)
    maps = first;
  return (maps);
}

bool  mapcanstore(t_map *map, long size)
{
  if (map->type == sizetype(size) && map->type <= SMALL)
  {
    if (map->empty > 0)
      return (1);
    else
      return (0);
  }
  else
    return (0);
}

t_block *findemptyblock(t_map *map)
{
  t_block *block;
  int id;

  id = 0;
  while (id < BLOCK_MAX)
  {
    block = getblockbyid(map, id);
    if (block->content == 0)
      return (block);
    id++;
  }
  return (NULL);
}

void  *mapstore(t_map *map, long size)
{
  t_block *block;
  void *ptr;

  block = findemptyblock(map);
  block->content = size;
  ptr = getblockptrbyid(map, block->id);
  map->empty--;
  return (ptr);
}

void  *getmapavailable(t_map *maps, long size)
{
  t_map *map;
  t_map *mapavailable;

  map = maps;
  mapavailable = NULL;
  while (map)
  {
    if (mapcanstore(map, size))
    {
      mapavailable = map;
      break;
    }
    if (map->next)
      map = map->next;
    else
      break;
  }
  if (!mapavailable)
  {
    mapavailable = newmap(size);
    map->next = mapavailable;
  }
  return (mapavailable);
}

void *getmemory(long size)
{
  t_map *maps;
  t_map *mapavailable;
  void  *ptr;
  //Get Maps list from static or create
  if(!(maps = staticmaps(NULL)))
  {
    maps = staticmaps(newmap(size));
  }
  mapavailable = getmapavailable(maps, size);
  ptr = mapstore(mapavailable, size);
  return (ptr);
}

void *ft_malloc(long size)
{
  return (getmemory(size));
}

int freemap(t_map *cmap, t_map *prev)
{
  if (prev)
  {
    if (cmap->empty == BLOCK_MAX || ((cmap->type > SMALL) && cmap->empty == BLOCK_MAX-1) )
    {
      prev->next = cmap->next;
      munmap(cmap->ptr, cmap->type);
      return (1);
    }
  }
  return (0);
}

void freeemptymap(t_map *gmap)
{
  t_map *map;
  t_map *prev;
  t_map *next;
  int   tiny;
  int   small;

  map = gmap;
  prev = NULL;
  while (map)
  {
    next = map->next;
    if (map->type == TINY)
    {
      tiny++;
      if (tiny > 1)
        if (freemap(map, prev))
          map = NULL;
    }
    if (map && map->type == SMALL)
    {
      small++;
      if (small > 1)
        if (freemap(map, prev))
          map = NULL;
    }
    if (map && map->type > SMALL)
      if (freemap(map, prev))
        map = NULL;

    if (map)
      prev = map;
    map = next;
  }
}

void freemyblock(t_map *map, t_block *block)
{
  block->content = 0;
  map->empty++;
}

void ft_free(void *ptr)
{
  t_map   *map;
  t_map   *globalmap;
  t_block *block;
  int     id;

  if (ptr == NULL)
    return;
  globalmap = staticmaps(NULL);
  map = globalmap;
  while (map)
  {
    if ((ptr > map->ptr) && (ptr < (map->ptr + map->total)))
      break;
    map = map->next;
  }
  if (!map)
    return;
  id = 0;
  while (id < BLOCK_MAX)
  {
    block = getblockbyid(map, id);
    if (block->ptr == ptr)
    {
      freemyblock(map, block);
    }
    id++;
  }
  freeemptymap(globalmap);
}

void show_alloc_mem(void)
{
  t_map *maps;
  t_map *current;
  t_block *block;
  long i;


  maps = staticmaps(NULL);
  current = maps;
  while (current)
  {
    printf("\nblock: [%p -> %p] (%ld)=====empty:%d=====\n", current, current + current->total,  current->total, current->empty);
    i = 0;
    while (i < BLOCK_MAX)
    {
      block = getblockbyid(current, i);
      if (block->content)
        printf("------->%p %p   s:%ld \n", block, block + SIZEBLOCK, block->content);
      if (current->type > SMALL)
        break;
      i++;
    }
    current = current->next;
  }
}

int main(int ac, char **av)
{
  (void)av;


  //printf("t_map:%lu t_block:%lu \n\n", sizeof(t_map), sizeof(t_block));

  if(ac>2)
  {
  char **tab;
  char **tab2;
  int i;
  int NB;

  NB = 30;
  tab = (char**)ft_malloc(NB);
  i = 0;
  while (i < NB)
  {
    tab[i] = ft_malloc(50 + (150*i));
    strcpy(tab[i],"STR IN TAB ");
    //printf("%s \n", tab[i]);
    i++;
  }
  //show_alloc_mem();

  tab2 = (char**)ft_malloc(NB);
  i = 0;
  while (i < NB)
  {
    tab2[i] = ft_malloc(50 + (150*i));
    strcpy(tab2[i],"STR IN TAB ");
    //printf("%s \n", tab2[i]);
    i++;
  }
  //show_alloc_mem();


  i = 0;
  while (i < NB)
  {
    ft_free(tab[i]);
    i++;
  }

  i = 0;
  while (i < NB)
  {
    ft_free(tab2[i]);
    i++;
  }

  //printf("FT_FREE\n\n");
  //show_alloc_mem();
  }
  return (0);
}
