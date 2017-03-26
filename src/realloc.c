/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 17:40:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/26 18:54:51 by dmoureu-         ###   ########.fr       */
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
	pthread_mutex_lock(&g_lock);
	ft_memcpy(ptr, block->ptr, block->content);
	freemyblock(map, block);
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_map	*globalmap;
	t_map	*map;
	t_block	*block;
	int		id;

	if (size == 0 && ptr)
		return (malloc(TINY));
	if (!ptr)
		return (malloc(size));
	globalmap = staticmaps(NULL);
	map = findmapwithblock(globalmap, ptr);
	if (!map)
		return (malloc(size));
	id = 0;
	while (id < BLOCK_MAX && (block = getblockbyid(map, id++)))
		if (block->ptr == ptr)
			if ((ptr = reallocblock(map, block, size)))
			{
				freeemptymap(globalmap);
				return (ptr);
			}
	return (NULL);
}
