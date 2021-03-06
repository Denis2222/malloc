/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:25:23 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/24 07:07:17 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <pthread.h>

# include "../libft/libft.h"

# define TINY 1024
# define SMALL 4096
# define BLOCK_MAX 100

typedef struct		s_block
{
	size_t			id;
	size_t			content;
	void			*ptr;
}					t_block;

typedef struct		s_map
{
	void			*ptr;
	size_t			total;
	size_t			type;
	int				available;
	struct s_map	*next;
}					t_map;

# define SIZEBLOCK sizeof(t_block)
# define SIZEMAP sizeof(t_map)

pthread_mutex_t		g_lock;

t_block				*getblockptrbyid(t_map *map, int id);
t_block				*getblockbyid(t_map *map, int id);

void				initblockmap(t_map *map);
t_block				*findemptyblock(t_map *map);
t_map				*findmapwithblock(t_map *globalmap, void*ptr);

int					freemap(t_map *cmap, t_map *prev);
void				freeemptymap(t_map *gmap);
void				freemyblock(t_map *map, t_block *block);
void				free(void *ptr);

void				*malloc(size_t size);
void				*getmemory(size_t size);

t_map				*staticmaps(t_map *first);
t_map				*newmap(size_t size);
int					mapcanstore(t_map *map, size_t size);
void				*mapstore(t_map *map, size_t size);
void				*getmapavailable(t_map *maps, size_t size);

size_t				mapsize(size_t size);
size_t				sizetype(size_t size);
size_t				multiplepagesize(size_t size);

void				*realloc(void *ptr, size_t size);

void				show_alloc_mem(void);

#endif
