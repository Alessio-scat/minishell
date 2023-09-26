/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:14:40 by ascatama          #+#    #+#             */
/*   Updated: 2023/01/17 11:54:29 by ascatama         ###   ########lyon.fr   */
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

size_t	ft_putnbr(int n, int fd)
{
	size_t	len;

	len = ft_number(n);
	if (n == -2147483648)
		ft_putstr("-2147483648", fd);
	else if (n >= 0 && n < 10)
		ftt_putchar(n + 48, fd);
	else if (n < 0)
	{
		ftt_putchar('-', fd);
		ft_putnbr(n * -1, fd);
	}
	else
	{
		ft_putnbr(n / 10, fd);
		ft_putnbr(n % 10, fd);
	}
	return (len);
}
