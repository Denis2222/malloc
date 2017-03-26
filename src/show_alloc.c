/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:24:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/26 19:12:18 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	getmapwords(t_map *map)
{
	char	keyword[10];

	if (map->type <= TINY)
		ft_strcpy(keyword, "TINY");
	else if (map->type <= SMALL)
		ft_strcpy(keyword, "SMALL");
	else if (map->type >= SMALL)
		ft_strcpy(keyword, "LARGE");
	if (map->type > SMALL)
	{
		ft_putstr(keyword);
		ft_putstr(" : ");
		ft_putptr(map);
		ft_putstr("\n");
	}
	else
	{
		ft_putstr(keyword);
		ft_putstr(" : ");
		ft_putptr(map);
		ft_putstr("\n");
	}
}

void	print_block(t_map *map, t_block *block)
{
	(void)map;
	ft_putptr(block->ptr);
	ft_putstr(" - ");
	ft_putptr(block->ptr + block->content);
	ft_putstr(" : ");
	ft_putulongnbr(block->content);
	ft_putstr(" octets\n");
}

void	show_alloc_mem_block(t_map *current, size_t *content, size_t *total)
{
	int		i;
	t_block	*b;

	while (current)
	{
		getmapwords(current);
		i = 0;
		while (i < BLOCK_MAX)
		{
			b = getblockbyid(current, i);
			*content += b->content;
			*total += current->type;
			if (b->content != 0)
				print_block(current, b);
			if (current->type > SMALL)
				break ;
			i++;
		}
		current = current->next;
	}
}

void	show_alloc_mem(void)
{
	t_map			*maps;
	t_map			*current;
	size_t			content;
	size_t			total;

	content = 0;
	total = 0;
	maps = staticmaps(NULL);
	current = maps;
	pthread_mutex_lock(&g_lock);
	show_alloc_mem_block(current, &content, &total);
	pthread_mutex_unlock(&g_lock);
	ft_putstr("Total : ");
	ft_putulongnbr(content);
	ft_putstr(" octets");
}
