/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 17:40:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/21 13:26:09 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*reallocblock(t_map *map, t_block *block, size_t size)
{
	void	*ptr;

	if (size < map->type)
	{
		write(1, "reblsize", 13);
		block->content = size;
		return (block->ptr);
	}
	ptr = malloc(size);
	write(1, "reallocblock", 13);
	memcpy(ptr, block->ptr, block->content);
	freemyblock(map, block);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_map	*globalmap;
	t_map	*map;
	t_block	*block;
	int		id;

	write(1, "REA", 3);
	if (size == 0 && ptr)
		return (malloc(1024));
	if (!ptr)
		return (malloc(size));
	globalmap = staticmaps(NULL);
	write(1, "realloc l 42", 13);
	map = findmapwithblock(globalmap, ptr);
	write(1, "realloc l 44", 13);
	if (!map)
		return (malloc(size));
	write(1, "realloc l 47", 13);
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
