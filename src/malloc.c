/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:18:17 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/20 00:14:06 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *malloc(size_t size)
{
  return (getmemory(size));
}

void *getmemory(size_t size)
{
  t_map *maps;
  t_map *mapavailable;
  void  *ptr;
  //Get Maps list from static or create
  if(!(maps = staticmaps(NULL)))
  {
    maps = staticmaps(newmap(size));
  }
  mapavailable = getmapavailable(maps, size);
  ptr = mapstore(mapavailable, size);
  return (ptr);
}
