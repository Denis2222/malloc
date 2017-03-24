/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:22:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/24 06:22:14 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*getblockptrbyid(t_map *map, int id)
{
	if (map->type == TINY)
		return (t_block*)(map->ptr + SIZEMAP + (SIZEBLOCK * BLOCK_MAX) +
			(TINY * id));
	else if (map->type == SMALL)
		return (t_block*)(map->ptr + SIZEMAP + (SIZEBLOCK * BLOCK_MAX) +
			(SMALL * id));
	else
		return ((t_block*)(map->ptr + SIZEMAP + SIZEBLOCK));
}

t_block	*getblockbyid(t_map *map, int id)
{
	if (map->type == TINY || map->type == SMALL)
		return (t_block*)(map->ptr + SIZEMAP + (SIZEBLOCK * id));
	else
		return ((t_block*)(map->ptr + SIZEMAP));
}

void	initblockmap(t_map *map)
{
	int		id;
	t_block	*block;

	id = 0;
	while (id < BLOCK_MAX)
	{
		block = getblockbyid(map, id);
		block->id = id;
		block->content = 0;
		block->ptr = getblockptrbyid(map, id);
		id++;
		if (map->type > SMALL)
			break ;
	}
}

t_block	*findemptyblock(t_map *map)
{
	t_block	*block;
	int		id;

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

t_map	*findmapwithblock(t_map *globalmap, void *ptr)
{
	t_map	*map;
	t_map	*found;

	found = NULL;
	map = globalmap;
	while (map)
	{
		if ((ptr > map->ptr) && (ptr < (map->ptr + map->total)))
		{
			found = map;
			break ;
		}
		map = map->next;
	}
	return (found);
}
