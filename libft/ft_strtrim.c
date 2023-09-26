/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:54:36 by ascatama          #+#    #+#             */
/*   Updated: 2022/11/23 15:47:42 by ascatama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_front(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_is_set(s1[i], set) == 1)
		i++;
	return (i);
}

static int	ft_back(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (j >= 0 && ft_is_set(s1[j], set) == 1)
	{
		i++;
		j--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		front;
	int		back;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	front = ft_front(s1, set);
	back = ft_back(s1, set);
	if (front == (int)ft_strlen(s1))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = ft_substr(s1, front, ft_strlen(s1) - front - back);
	if (!str)
		return (NULL);
	return (str);
}
