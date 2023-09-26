/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:47:47 by ascatama          #+#    #+#             */
/*   Updated: 2023/04/21 09:58:18 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_is_char(char str, char c)
{
	if (str == c)
		return (1);
	return (0);
}

static int	ft_number_tab(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (ft_char_is_char(str[i], c) && str[i] != '\0')
			i++;
		if (!ft_char_is_char(str[i], c) && str[i] != '\0')
		{
			count++;
			while (!ft_char_is_char(str[i], c) && str[i] != '\0')
				i++;
		}
	}
	return (count);
}

char	*ft_to_fill_tab(char const *str, int *index, char c)
{
	char	*fill;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (ft_char_is_char(str[*index], c) && str[*index])
		(*index)++;
	while (!ft_char_is_char(str[*index + len], c) && str[*index + len])
		len++;
	fill = malloc(sizeof(char) * (len + 1));
	if (fill == NULL)
		return (NULL);
	while (len-- > 0)
	{
		fill[i] = str[*index];
		i++;
		(*index)++;
	}
	fill[i] = '\0';
	return (fill);
}

char	**ft_str_free(char **str)
{
	size_t	index;

	index = 0;
	while (str[index] == NULL)
	{
		free(str[index]);
		index++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	count;
	size_t	i;
	int		index;

	if (!s)
		return (NULL);
	i = 0;
	index = 0;
	count = ft_number_tab(s, c);
	str = malloc(sizeof(char *) * (count + 1));
	if (str == NULL)
		return (NULL);
	while (i < count)
	{
		str[i] = ft_to_fill_tab(s, &index, c);
		if (!str[i])
			return (ft_str_free(str));
		i++;
	}
	str[i] = 0;
	return (str);
}
