/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:32:09 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:51:23 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	verif_strdup(char **env, char **envtmp);

void	free_tmp_var(t_cmd *cmd, char **tmp_env)
{
	free(tmp_env);
	shlvl(cmd->ex, 'a', cmd);
	free_export(&cmd->ex);
	if (cmd->tmppwd)
		free(cmd->tmppwd);
	if (cmd->s_builtins)
		free(cmd->s_builtins);
	if (cmd->old_stdout >= 0)
		close(cmd->old_stdout);
	exit (-2);
}

char	**ft_create_env(t_export *e, int size, t_cmd *cmd)
{
	char	**tmp_env;
	char	*tmp_variable;
	char	*tmp;

	cmd->i = 0;
	tmp_env = malloc(sizeof(char *) * (size + 1));
	if (!tmp_env)
		exit(-2);
	while (e)
	{
		if (e->content && e->variable[0] != '\0' )
		{
			tmp_variable = ft_substr(e->variable, 0, ft_strlen(e->variable));
			if (!tmp_variable)
				free_tmp_var(cmd, tmp_env);
			tmp = ft_strjoin(tmp_variable, "=");
			env_malloc(tmp_variable, tmp_env, cmd, tmp);
			free(tmp_variable);
			tmp_env[cmd->i++] = ft_strjoin(tmp, e->content);
			free(tmp);
		}
		e = e->next;
	}
	tmp_env[cmd->i] = NULL;
	return (tmp_env);
}

static char	**fill_env(char *env[], t_cmd *cmd, char **envtmp)
{
	env = malloc(sizeof(char *) * 4);
	if (!env)
		exit(-2);
	env[0] = ft_strdup("SHLVL=1");
	if (!env[0])
		exit (-2);
	env[1] = ft_strdup("OLDPWD");
	if (env[1] == NULL)
	{
		free(env[0]);
		exit(-2);
	}
	envtmp[0] = ft_strjoin("PWD", "=");
	if (!envtmp[0])
		exit (-2);
	envtmp[1] = ft_strjoin(envtmp[0], cmd->tmppwd);
	if (envtmp[1] == NULL)
	{
		free(envtmp[0]);
		exit(-2);
	}
	env[2] = ft_strdup(envtmp[1]);
	verif_strdup(env, envtmp);
	env[3] = 0;
	return (env);
}

void	get_env(t_export **envp, char *env[], t_cmd *cmd)
{
	int			j;
	int			start;
	char		*envtmp[2];
	t_export	*element;

	cmd->i = -1;
	if (env[0] == NULL)
	{
		env = fill_env(env, cmd, envtmp);
	}
	while (env[++cmd->i])
	{
		j = 0;
		while (env[cmd->i][j] && env[cmd->i][j] != '=')
			j++;
		start = j + 1;
		envtmp[0] = ft_substr(env[cmd->i], 0, start - 1);
		get_env_malloc2(envtmp, cmd);
		envtmp[1] = ft_substr(env[cmd->i], start, j - start);
		get_env_malloc(envtmp, cmd);
		element = ft_lst_new(envtmp[1], envtmp[0]);
		ft_lst_add_back(envp, element);
	}
}

void	shlvl(t_export *exp, char a, t_cmd *cmd)
{
	int			shlvl;
	t_export	*tmp;

	shlvl = 0;
	tmp = exp;
	while (exp)
	{
		if (ft_strncmp(exp->variable, "SHLVL", ft_strlen(exp->variable)) == 0)
		{
			if (ft_strncmp(exp->variable, "SHLVL", 5) == 0)
			{
				shlvl = ft_atoi(exp->content);
				break ;
			}
		}
		exp = exp->next;
	}
	shlvl = modif_shlvl(shlvl, a);
	free(exp->content);
	exp->content = ft_itoa(shlvl);
	exp = tmp;
	shlvl_malloc(exp, cmd);
}
