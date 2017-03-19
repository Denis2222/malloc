/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:24:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/20 00:46:19 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void getmapwords(t_map *map)
{
  char keyword[10] = "";

  if (map->type < TINY)
    strcpy(keyword, "TINY");
  else if (map->type < SMALL)
    strcpy(keyword, "SMALL");
  else if (map->type >= SMALL)
    strcpy(keyword, "LARGE");

  ft_printf("%s : %p (%d)\n",keyword,  map, map->empty);
}

void show_alloc_mem(void)
{
  t_map *maps;
  t_map *current;
  t_block *block;
  int i;

  maps = staticmaps(NULL);
  current = maps;
  while (current)
  {
    getmapwords(current);
    i = 0;
    while (i < BLOCK_MAX)
    {
      block = getblockbyid(current, i);
      if (block->content != 0)
        ft_printf("%p - %p : %d octets\n", block->ptr, block->ptr + block->content, block->content);
      if (current->type > SMALL)
        break;
      i++;
    }
    current = current->next;
  }
}

/*

TINY : 0xA0000
0xA0020 - 0xA004A : 42 octets
0xA006A - 0xA00BE : 84 octets
SMALL : 0xAD000
0xAD020 - 0xADEAD : 3725 octets
LARGE : 0xB0000
0xB0020 - 0xBBEEF : 48847 octets
Total : 52698 octets

*/
