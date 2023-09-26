/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:55:08 by ascatama          #+#    #+#             */
/*   Updated: 2022/11/23 15:44:59 by ascatama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_reverse(char *s)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = ft_strlen(s) - 1;
	while (i < len)
	{
		c = s[i];
		s[i] = s[len];
		s[len] = c;
		i++;
		len--;
	}
}

static	int	ft_number_malloc(long long int n)
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

char	*ft_itoa(int n)
{
	long long int		i;
	long long int		sign;
	char				*str;
	long long int		nb;

	i = 0;
	sign = n;
	nb = ft_number_malloc(n);
	str = malloc((nb + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (sign < 0)
		sign = -sign;
	str[i++] = sign % 10 + 48;
	while (sign >= 10)
	{
		sign /= 10;
		str[i] = (sign % 10) + 48;
		i++;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	ft_reverse(str);
	return (str);
}
