/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:21:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/20 21:13:54 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	multiplepagesize(size_t size)
{
	size_t	nb;
	size_t	result;

	if (size == 0)
		return (getpagesize());
	nb = size / getpagesize();
	if (nb * getpagesize() < size)
		result = getpagesize() * (nb + 1);
	else
		result = nb * getpagesize();
	return (result);
}

size_t	mapsize(size_t size)
{
	size_t	mapsize;

	if (size < TINY)
		mapsize = (SIZEMAP + (BLOCK_MAX * SIZEBLOCK) + (TINY * BLOCK_MAX));
	else if (size >= TINY && size < SMALL)
		mapsize = (SIZEMAP + (BLOCK_MAX * SIZEBLOCK) + (SMALL * BLOCK_MAX));
	else
		mapsize = (SIZEMAP + SIZEBLOCK + size);
	return (mapsize);
}

size_t	sizetype(size_t size)
{
	if (size < TINY)
		return (TINY);
	else if (size >= TINY && size < SMALL)
		return (SMALL);
	else
		return (size);
}
