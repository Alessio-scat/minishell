/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:11:26 by ascatama          #+#    #+#             */
/*   Updated: 2023/02/20 10:27:48 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_special_nbr(unsigned int nbr, char *base, int *index)
{
	if (nbr > 0)
	{
		(*index)++;
		ft_special_nbr(nbr / 16, base, index);
		ft_putchar(base[nbr % 16]);
	}
}

size_t	ft_putnbr_base(int nbr, char *base)
{
	int	index;

	index = 0;
	if (nbr == 0)
	{
		ft_putchar(base[0]);
		index++;
	}
	ft_special_nbr(nbr, base, &index);
	return (index);
}
