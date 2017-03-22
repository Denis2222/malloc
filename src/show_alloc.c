/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:24:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/22 12:29:11 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	getmapwords(t_map *map)
{
	char	keyword[10];

	if (map->type <= TINY)
		strcpy(keyword, "TINY");
	else if (map->type <= SMALL)
		strcpy(keyword, "SMALL");
	else if (map->type >= SMALL)
		strcpy(keyword, "LARGE");
	if (map->type > SMALL)
		ft_printf("%s : %p (use:%d)\n",
					keyword, map, !map->available);
	else
		ft_printf("%s : %p (use:%d)\n",
					keyword, map, (BLOCK_MAX - map->available));
}

void	show_alloc_mem(void)
{
	t_map			*maps;
	t_map			*current;
	t_block			*b;
	int				i;

	maps = staticmaps(NULL);
	current = maps;
	while (current)
	{
		getmapwords(current);
		i = 0;
		while (i < BLOCK_MAX)
		{
			b = getblockbyid(current, i);
			if (b->content != 0)
				ft_printf("%p - %p : %lu octets\n", b->ptr,
					b->ptr + b->content, b->content);
			if (current->type > SMALL)
				break ;
			i++;
		}
		current = current->next;
	}
}
