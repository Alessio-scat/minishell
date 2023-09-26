/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:03:57 by ascatama          #+#    #+#             */
/*   Updated: 2023/01/17 11:50:56 by ascatama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_search_arg(va_list ap, char c)
{
	size_t	len;

	len = 0;
	if (c == 'c')
		len += ftt_putchar(va_arg(ap, int), 1);
	else if (c == 's')
		len += ft_putstr(va_arg(ap, char *), 1);
	else if (c == 'p')
		len += ft_convert_p(va_arg(ap, unsigned long int), "0123456789abcdef");
	else if (c == 'd' || c == 'i')
		len += ft_putnbr(va_arg(ap, int), 1);
	else if (c == 'u')
		len += ft_putnbr_unsigne(va_arg(ap, unsigned int), 1);
	else if (c == 'x')
		len += ft_putnbr_base(va_arg(ap, int), "0123456789abcdef");
	else if (c == 'X')
		len += ft_putnbr_base(va_arg(ap, int), "0123456789ABCDEF");
	else if (c == '%')
		len += ftt_putchar('%', 1);
	else
		len += ftt_putchar(c, 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (write(1, 0, 0) != 0)
		return (-1);
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			return (len);
		else if (str[i] == '%')
		{
			len += ft_search_arg(ap, str[i + 1]);
			i += 2;
		}
		else
			len += ftt_putchar(str[i++], 1);
	}
	va_end(ap);
	return (len);
}
