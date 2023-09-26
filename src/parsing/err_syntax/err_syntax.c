/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:14:27 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 09:52:04 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	err_msg(char *err);
int		verif_syntax(char *line, int i);
void	quotes(char *line, char *inquotes, int index);

int	pipeline_err(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
			return (err_msg("|"), g_status = 2, 1);
		else
			return (0);
	}
	return (0);
}

int	redir_err(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (!quote && line[i] == '>')
		{
			if (line[i + 1] == '>')
				i++;
			if (verif_syntax(line, i + 1) == 1)
				return (1);
		}
		else if (!quote && line[i] == '<')
		{
			if (line[i + 1] == '<')
				i++;
			if (verif_syntax(line, i + 1) == 1)
				return (1);
		}
		quotes(line, &quote, i);
		i++;
	}
	return (0);
}

int	redir_err_newline(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (ft_isspace(line[i]))
			i--;
		else if (line[i] == '>' || line[i] == '<')
			return (err_msg("newline"), g_status = 2, 1);
		else
			return (0);
	}
	return (0);
}

int	pipeline_multiple(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			if (ft_isspace(line[i]))
				i++;
			if (line[i] == '|')
				i++;
			if (ft_isspace(line[i]))
				i++;
			if (line[i] == '|')
				return (err_msg("||"), g_status = 2, 1);
		}
		if (line[i])
			i++;
	}
	return (0);
}

int	simple_op(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == '\n' || line[i] == ' ' || line[i] == '	' \
			|| line[i] == ':' || line[i] == '!'))
	{
		if (line[i] == ' ')
			g_status = 0;
		else if (line[i] == '!')
			g_status = 1;
		if ((line[i] == ':' || line[i] == '!') \
			&& (line[i + 1] == ':' || line[i + 1] == '!'))
			return (0);
		i++;
	}
	if (line[i] == '\0')
		return (1);
	return (0);
}
