/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_no_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:21:31 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/16 09:26:57 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_word(char *str, t_s *s, int start, int end)
{
	char	*word;
	int		len;

	word = NULL;
	len = end - start + 1;
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		exit(1);
	ft_strncpy(word, str + start, len);
	word[len] = '\0';
	s->result[s->index] = word;
	s->index += 1;
}

static void	incrementation(char *quote, char c)
{
	if (!*quote || *quote == c)
	{
		if (*quote)
			*quote = 0;
		else
			*quote = c;
	}
}

static void	split_string(char *str, char del, t_s *s)
{
	int		i;
	int		j;
	char	quote;
	int		len;

	i = 0;
	j = 0;
	quote = 0;
	len = ft_strlen(str);
	s->index = 0;
	while (i < len)
	{
		if (ft_is_quote(str[i]))
			incrementation(&quote, str[i]);
		else if (str[i] == del && !quote)
		{
			if (i > j)
				fill_word(str, s, j, i - 1);
			j = i + 1;
		}
		i++;
	}
	if (j < len)
		fill_word(str, s, j, len - 1);
	s->result[s->index] = NULL;
}

static int	count_word(char *str, char del)
{
	int		count;
	int		i;
	char	quote;

	count = 0;
	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (ft_is_quote(str[i]))
			incrementation(&quote, str[i]);
		else if (str[i] == del && !quote)
			count++;
		i++;
	}
	return (count + 1);
}

char	**ft_split_no_quote(char *str, char del)
{
	t_s		s;
	int		count;

	s.result = NULL;
	count = 0;
	count = count_word(str, del);
	s.result = malloc((count + 1) * sizeof(char *));
	if (!s.result)
		exit(1);
	split_string(str, del, &s);
	s.result[count] = NULL;
	return (s.result);
}
