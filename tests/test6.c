/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 09:01:35 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/04/17 17:10:46 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "malloc.h"

int		main(void)
{

	srand(time(0));

	int i;
	for (i=0; i<5; i++)
	{
		malloc((rand()%1024));
	}
	for (i=0; i<10; i++)
	{
		malloc((rand()%4096));
	}
	for (i=0; i<5; i++)
	{
		malloc((rand()%999999));
	}

	show_alloc_mem();
	malloc(199999999999999);
	return (0);
}
