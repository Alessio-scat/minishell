/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_nbr_unsign.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:27:34 by ascatama          #+#    #+#             */
/*   Updated: 2023/02/20 10:28:42 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_number(long long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	while (n >= 10)
	{
		count++;
		n = n / 10;
	}
	return (count + 1);
}

size_t	ft_putnbr_unsigne(unsigned int n, int fd)
{
	size_t	len;

	len = ft_number(n);
	if (n == 4294967295)
		return (ft_putstr("4294967295", fd));
	else if (n < 10)
		ftt_putchar(n + 48, fd);
	else
	{
		ft_putnbr_unsigne(n / 10, fd);
		ft_putnbr_unsigne(n % 10, fd);
	}
	return (len);
}
