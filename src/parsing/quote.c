/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:43:22 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 10:53:14 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*remove_quote(char *line, int l)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (i < l)
	{
		c = line[i];
		if (c == '"' || c == '\'')
		{
			i++;
			while (i < l && line[i] != c)
			{
				line[j] = line[i];
				i++;
				j++;
			}
		}
		else
			line[j++] = c;
		i++;
	}
	line[j] = '\0';
	return (line);
}
