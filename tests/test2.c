/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 09:01:16 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/23 23:57:04 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "malloc.h"

int main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 3)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		//if (i < 1020)
			free(addr);
		i++;
	}

	//ft_putptr(addr);
 	show_alloc_mem();
	return (0);
}
