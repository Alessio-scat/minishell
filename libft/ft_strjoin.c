/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:57:27 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 10:31:29 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (0);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + (sizeof(char) * 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)s1, (ft_strlen(s1) + 1));
	ft_strlcat(str, (char *)s2, (ft_strlen(s1) + ft_strlen(s2) + 1));
	return (str);
}
