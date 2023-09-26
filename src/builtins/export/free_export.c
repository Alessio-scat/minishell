/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:48:19 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:15:23 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	export_strjoin_tmp3(char *tmp3, char *tmp1, char *tmp_variable)
{
	if (tmp3 == NULL)
	{
		free (tmp1);
		free (tmp_variable);
		exit (-2);
	}
}

void	export_strjoin_tmp4(char *tmp4, char *tmp3, char *tmp1, \
char *tmp_variable)
{
	if (tmp4 == NULL)
	{
		free (tmp3);
		free (tmp1);
		free (tmp_variable);
		exit(-2);
	}
}

void	export_strjoin(char *export)
{
	if (export == NULL)
		exit (-2);
}

void	export_substr(char *var)
{
	if (var == NULL)
		exit (-2);
}

void	export_substr_2d(char **var, int *i)
{
	if (var[(*i)++] == NULL)
	{
		free_2d(var);
		exit (-2);
	}
}
