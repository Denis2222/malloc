/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 17:40:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/22 22:19:36 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*reallocblock(t_map *map, t_block *block, size_t size)
{
	void	*ptr;

	if (size < map->type)
	{
		block->content = size;
		return (block->ptr);
	}
	ptr = malloc(size);
	ft_memcpy(ptr, block->ptr, block->content);
	freemyblock(map, block);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_map	*globalmap;
	t_map	*map;
	t_block	*block;
	int		id;

	if (size == 0 && ptr)
	{
		//free(ptr);
		return (malloc(1024));
	}
	if (!ptr)
		return (malloc(size));
	globalmap = staticmaps(NULL);
	map = findmapwithblock(globalmap, ptr);
	if (!map)
		return (malloc(size));
	id = 0;
	while (id < BLOCK_MAX)
	{
		block = getblockbyid(map, id);
		if (block->ptr == ptr)
			if ((ptr = reallocblock(map, block, size)))
			{
				freeemptymap(globalmap);
				return (ptr);
			}
		id++;
	}
	return (NULL);
}
