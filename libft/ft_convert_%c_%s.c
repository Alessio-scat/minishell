/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_%c_%s.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:08:10 by ascatama          #+#    #+#             */
/*   Updated: 2023/01/17 11:49:34 by ascatama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ftt_putchar(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}

size_t	ft_putstr(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (s[i])
		write(fd, &s[i++], 1);
	return (i);
}
