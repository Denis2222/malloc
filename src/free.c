/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:22:56 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/22 14:24:44 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		freemap(t_map *cmap, t_map *prev)
{
	if (prev)
	{
		if (cmap->available == BLOCK_MAX || (cmap->type > SMALL && cmap->available == 1))
		{
			prev->next = cmap->next;
			munmap(cmap->ptr, cmap->type);
			return (1);
		}
	}
	else
	{
		if (cmap->type > SMALL && cmap->available == 1)
		{
			staticmaps(cmap->next);
			munmap(cmap->ptr, cmap->type);
			return (1);
		}
	}
  return (0);
}

void	freeemptymap(t_map *gmap)
{
	t_map	*map;
	t_map	*prev;
	t_map	*next;
	int		tiny;
	int		small;

	map = gmap;
	prev = NULL;
	tiny = 0;
	small = 0;
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

void	freemyblock(t_map *map, t_block *block)
{
	block->content = 0;
	map->available++;
}

void	free(void *ptrblock)
{
	t_map	*map;
	t_map	*globalmap;
	t_block	*block;
	int		id;

	ft_putstr("F");
	if (ptrblock == NULL)
		return ;
	globalmap = staticmaps(NULL);
	map = findmapwithblock(globalmap, ptrblock);
	if (!map)
		return ;
	id = 0;
	while (id < BLOCK_MAX)
	{
		block = getblockbyid(map, id);
		if (block->ptr == ptrblock)
			freemyblock(map, block);
		id++;
	}
	freeemptymap(globalmap);
}
