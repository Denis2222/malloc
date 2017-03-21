/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:24:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/21 09:18:08 by dmoureu-         ###   ########.fr       */
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
	ft_printf("%s : %p (%d)\n", keyword, map, map->empty);
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
				ft_printf("%p - %p : %d octets\n", b->ptr,
					b->ptr + b->content, b->content);
			if (current->type > SMALL)
				break ;
			i++;
		}
		current = current->next;
	}
}
