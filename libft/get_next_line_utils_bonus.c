/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:01:56 by ascatama          #+#    #+#             */
/*   Updated: 2023/01/19 10:43:31 by ascatama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_search(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*conca;
	size_t	i;
	size_t	k;

	k = 0;
	i = 0;
	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	conca = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (conca == NULL)
		return (NULL);
	while (s1[i])
		conca[i++] = s1[k++];
	free(s1);
	k = 0;
	while (s2[k])
		conca[i++] = s2[k++];
	conca[i] = '\0';
	return (conca);
}
