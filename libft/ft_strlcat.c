/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:35:30 by ascatama          #+#    #+#             */
/*   Updated: 2022/11/23 15:47:14 by ascatama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;
	size_t		dest_len;
	size_t		src_len;

	if (dest == NULL && dstsize == 0)
		return (0);
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	i = 0;
	j = 0;
	if (dstsize < dest_len)
		return (dstsize + src_len);
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && dstsize > 1)
	{
		dest[i + j] = src[j];
		dstsize--;
		j++;
	}
	if (dstsize > 0)
		dest[i + j] = '\0';
	return (dest_len + src_len);
}
