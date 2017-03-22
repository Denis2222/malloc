/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:18:17 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/22 22:16:34 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	ft_putstr("M");
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
	pthread_mutex_lock(&g_lock);
	mapavailable = getmapavailable(maps, size);
	ptr = mapstore(mapavailable, size);
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}
