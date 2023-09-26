/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:19:07 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/16 15:52:54 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	quotes(char *line, char *inquotes, int i)
{
	if (!(*inquotes) && (line[i] == '\'' || line[i] == '\"'))
		*inquotes = line[i];
	else if ((*inquotes) == '\'' && line[i] == '\'')
		*inquotes = 0;
	else if ((*inquotes) == '\"' && line[i] == '\"')
		*inquotes = 0;
	else
		return ;
}

void	err_msg(char *err)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\'\n", 2);
}

int	verif_syntax(char *line, int i)
{
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
			return (err_msg("|"), g_status = 2, 1);
		else if (line[i] == '>' && line[i + 1] == '>')
			return (err_msg(">>"), g_status = 2, 1);
		else if (line[i] == '<' && line[i + 1] == '<')
			return (err_msg("<<"), g_status = 2, 1);
		else if (line[i] == '>')
			return (err_msg(">"), g_status = 2, 1);
		else if (line[i] == '<')
			return (err_msg("<"), g_status = 2, 1);
		else
			return (0);
	}
	return (0);
}
