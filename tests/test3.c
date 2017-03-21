/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:26:13 by jguyet            #+#    #+#             */
/*   Updated: 2017/03/21 10:44:14 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "malloc.h"

#define M (1024 * 1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{
	char	*addr1;
	char	*addr3;

	addr1 = (char *)malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char *)realloc(addr1, 128*M);
	addr3[127*M] = 42;
	print(addr3);

	addr1 = malloc(10);
	free(addr1);


	addr3 = malloc(30);
addr3 = malloc(30);
addr3 = malloc(30);
addr3 = malloc(-2);
	show_alloc_mem();
	return (0);
}
