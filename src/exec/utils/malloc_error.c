/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:21:17 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/24 16:13:33 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	shlvl_malloc(t_export *exp, t_cmd *cmd)
{
	if (!exp->content)
	{
		if (cmd->tmppwd)
			free(cmd->tmppwd);
		free_export(&exp);
		exit(-2);
	}
}

void	env_malloc(char *tmp_variable, char **tmp_env, t_cmd *cmd, char *tmp)
{
	if (!tmp)
	{
		free(tmp_variable);
		free_tmp_var(cmd, tmp_env);
	}
}

void	get_env_malloc(char **envtmp, t_cmd *cmd)
{
	if (envtmp[1] == NULL)
	{
		free(envtmp[0]);
		if (cmd->tmppwd)
			free(cmd->tmppwd);
		exit(-2);
	}
}

void	get_env_malloc2(char **envtmp, t_cmd *cmd)
{
	if (envtmp[0] == NULL)
	{
		if (cmd->tmppwd)
			free(cmd->tmppwd);
		exit(-2);
	}
}
