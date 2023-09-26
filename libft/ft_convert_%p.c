/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_%p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:22:24 by ascatama          #+#    #+#             */
/*   Updated: 2023/02/20 10:27:38 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_special_nbr(unsigned long int nbr, char *base, size_t *index)
{
	if (nbr > 0)
	{
		(*index)++;
		ft_special_nbr(nbr / 16, base, index);
		ft_putchar(base[nbr % 16]);
	}
}

size_t	ft_convert_p(unsigned long int nbr, char *base)
{
	size_t	index;

	index = 0;
	ft_putchar('0');
	ft_putchar('x');
	index = 2;
	if (nbr == 0)
	{
		ft_putchar(base[0]);
		index++;
	}
	ft_special_nbr(nbr, base, &index);
	return (index);
}
