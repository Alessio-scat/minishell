/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:57:24 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:15:05 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	export_strjoin_tmp3(char *tmp3, char *tmp1, char *tmp_variable);
void	export_strjoin_tmp4(char *tmp4, char *tmp3, char *tmp1, \
char *tmp_variable);
void	export_strjoin(char *export);
void	export_substr(char *var);
void	export_substr_2d(char **var, int *i);

void	join_export(t_export *tmp, int *i, char **export)
{
	char		*tmp1;
	char		*tmp3;
	char		*tmp4;
	char		*tmp_variable;

	tmp_variable = ft_substr(tmp->variable, 0, ft_strlen(tmp->variable));
	if (tmp_variable == NULL)
		exit (-2);
	tmp1 = ft_strjoin(tmp_variable, "=");
	if (tmp1 == NULL)
	{
		free (tmp_variable);
		exit (-2);
	}
	tmp3 = ft_strjoin(tmp1, "\"");
	export_strjoin_tmp3(tmp3, tmp1, tmp_variable);
	tmp4 = ft_strjoin(tmp3, tmp->content);
	export_strjoin_tmp4(tmp4, tmp3, tmp1, tmp_variable);
	export[*i] = ft_strjoin(tmp4, "\"");
	free(tmp1);
	free(tmp3);
	free(tmp4);
	free(tmp_variable);
	export_strjoin(export[*i]);
	(*i)++;
}

void	print_export(t_export *exp)
{	
	t_export	*tmp;
	int			size;
	char		**export;
	int			i;

	size = 0;
	tmp = exp;
	size = ft_lst_size_export(exp);
	export = malloc(sizeof(char *) * (size + 1));
	if (!export)
		exit(-2);
	i = 0;
	while (tmp)
	{
		if (tmp->content && tmp->variable[0] != '\0' && tmp->content[0] != '\0')
			join_export(tmp, &i, export);
		else if (tmp->variable[0] != '\0')
		{
			export[i] = ft_substr(tmp->variable, 0, ft_strlen(tmp->variable));
			export_substr_2d(export, &i);
		}
		tmp = tmp->next;
	}
	export[i] = 0;
	print_list_exp(export);
}

int	export_verif_cote(t_export *export, int sizevar, char **variable)
{
	if (variable[1][0] == '"' && variable[1][sizevar - 1] == '"')
	{
		malloc_copy(variable, sizevar, export);
		return (1);
	}
	return (0);
}

void	free_add_export(t_export *export, char **variable, t_builtins *bu)
{
	t_export	*element;
	char		*tmp[2];

	if (variable_exist(export, 0, variable, bu) == 1)
		return ;
	tmp[0] = ft_substr(variable[0], 0, ft_strlen(variable[0]));
	export_substr(tmp[0]);
	if (variable[1])
		tmp[1] = ft_substr(variable[1], 0, ft_strlen(variable[1]));
	else if (bu->countspace == 0)
		tmp[1] = NULL;
	else
		tmp[1] = ft_strdup("\0");
	element = ft_lst_new(tmp[1], tmp[0]);
	ft_lst_add_back(&export, element);
	if (bu->j == 0)
		free_2d(variable);
	else
	{
		if (variable[0])
			free(variable[0]);
		if (variable[1])
			free(variable[1]);
		free(variable);
	}
}

int	add_export(t_export *ex, t_builtins *bu, char **variable, char *maVariable)
{
	int	i;

	if (variable[2] != NULL || bu->countspace > 1)
	{
		i = 0;
		while (maVariable[i] && maVariable[i] != '=')
			i++;
		bu->start = i + 1;
		if (variable[1])
			free(variable[1]);
		variable[1] = ft_substr(maVariable, bu->start, bu->i - bu->start);
	}
	bu->sizevariable = ft_strlen(variable[1]);
	if (ex->next)
	{
		if (variable_exist(ex, bu->sizevariable, variable, bu) == 1)
			return (1);
	}
	if (variable[1][0] == '"' && variable[1][bu->sizevariable - 1] == '"')
	{	
		malloc_copy_lst(variable, bu->sizevariable, ex);
		return (1);
	}
	return (0);
}
