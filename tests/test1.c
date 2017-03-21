/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:25:51 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/21 11:25:13 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 10)
	{
		addr = (char *)malloc(10);
		addr[0] = 42;
		i++;
	}

	show_alloc_mem();

	i = 0;
	while (i < 10)
	{
		free(addr);
		i++;
	}
	show_alloc_mem();

	return (0);
}
