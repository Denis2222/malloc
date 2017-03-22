/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:20:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/22 11:53:25 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_map	*staticmaps(t_map *first)
{
	static t_map	*maps = NULL;

	if (first != NULL)
	{
		pthread_mutex_init(&g_lock, NULL);
		maps = first;
	}
	return (maps);
}

t_map	*newmap(size_t size)
{
	t_map	*map;
	void	*ptrmmap;

	//printf("newmap(%lu)\n", size);
	//ft_putstr("newmap(");ft_putnbr(size);ft_putstr(")\n");
	ptrmmap = mmap(0, multiplepagesize(mapsize(size)),
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	map = (t_map*)ptrmmap;
	if (ptrmmap == MAP_FAILED)
	{
		return (NULL);
	}
	map->ptr = ptrmmap;
	map->total = mapsize(size);
	map->type = sizetype(size);
	map->next = NULL;
	if (map->type <= SMALL)
		map->available = BLOCK_MAX;
	else
		map->available = 1;
	initblockmap(map);
	return (map);
}

bool	mapcanstore(t_map *map, size_t size)
{
	if (map->type == sizetype(size) && map->available > 0)
		return (1);
	else
		return (0);
}

void	*mapstore(t_map *map, size_t size)
{
	t_block	*block;
	void	*ptr;

	block = findemptyblock(map);
	block->content = size;
	ptr = getblockptrbyid(map, block->id);
	map->available--;
	return (ptr);
}

void	*getmapavailable(t_map *maps, size_t size)
{
	t_map	*map;
	t_map	*mapavailable;

	map = maps;
	mapavailable = NULL;
	while (map)
	{
		if (mapcanstore(map, size))
		{
			mapavailable = map;
			break ;
		}
		if (map->next)
			map = map->next;
		else
			break ;
	}
	if (!mapavailable)
	{
		mapavailable = newmap(size);
		map->next = mapavailable;
	}
	return (mapavailable);
}
