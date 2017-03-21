/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:18:17 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/21 12:29:56 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	write(1, "MAL", 3);
	return (getmemory(size));
}

void	*getmemory(size_t size)
{
	t_map	*maps;
	t_map	*mapavailable;
	void	*ptr;

	if(!(maps = staticmaps(NULL)))
	{
		maps = staticmaps(newmap(size));
	}
	mapavailable = getmapavailable(maps, size);
	ptr = mapstore(mapavailable, size);
	return (ptr);
}
