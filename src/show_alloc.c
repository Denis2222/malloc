/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:24:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/24 06:23:41 by dmoureu-         ###   ########.fr       */
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

void	show_alloc_mem(void)
{
	t_map			*maps;
	t_map			*current;
	t_block			*b;
	int				i;
	size_t			content;
	size_t			total;

	content = 0;
	total = 0;
	maps = staticmaps(NULL);
	current = maps;
	while (current)
	{
		getmapwords(current);
		i = 0;
		while (i < BLOCK_MAX)
		{
			b = getblockbyid(current, i);
			content += b->content;
			total += current->type;
			if (b->content != 0)
				print_block(current, b);
			if (current->type > SMALL)
				break ;
			i++;
		}
		current = current->next;
	}
	ft_putstr("Total : ");
	ft_putulongnbr(content);
	ft_putstr(" octets");
}

void	getmapwords_plus(t_map *map)
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
		ft_putstr(" use :");
		ft_putnbr(map->available);
		ft_putstr("\n");
	}
	else
	{
		ft_putstr(keyword);
		ft_putstr(" : ");
		ft_putptr(map);
		ft_putstr(" use : ");
		ft_putnbr((BLOCK_MAX - map->available));
		ft_putstr("  ");
		ft_putnbr(map->total);
		ft_putstr("  ");
		ft_putulongnbr(map->total / getpagesize());
		ft_putstr("\n");
	}
}

void	show_alloc_mem_plus(void)
{
	t_map			*maps;
	t_map			*current;
	t_block			*b;
	int				i;
	size_t			content;
	size_t			total;

	ft_putstr("sizeof(t_map):");
	ft_putulongnbr(sizeof(t_map));
	ft_putstr(" + sizeof(t_block):");
	ft_putulongnbr(sizeof(t_block));
	ft_putstr(" * ");
	ft_putulongnbr(BLOCK_MAX);
	ft_putstr(" = ");
	ft_putulongnbr(sizeof(t_map) + sizeof(t_block) * BLOCK_MAX);
	ft_putstr("\n");
	content = 0;
	total = 0;
	maps = staticmaps(NULL);
	current = maps;
	while (current)
	{
		getmapwords_plus(current);
		i = 0;
		while (i < BLOCK_MAX)
		{
			b = getblockbyid(current, i);
			content += b->content;
			total += current->type;
			if (b->content != 0)
				print_block(current, b);
			if (current->type > SMALL)
				break ;
			i++;
		}
		current = current->next;
	}
	ft_putstr("Total : ");
	ft_putulongnbr(content);
	ft_putstr(" / ");
	ft_putulongnbr(total);
	ft_putstr(" octets");
}
