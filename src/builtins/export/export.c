/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lveloso <lveloso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:07:15 by lveloso           #+#    #+#             */
/*   Updated: 2023/05/25 10:20:40 by lveloso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	ft_check_export(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == ' ' && input[i + 1] == '=')
			|| (input[i] == ' ' && input[i - 1] == '='))
			return (1);
		if (input[i] == '"')
			return (0);
		if (input[i] == ' ')
			return (0);
		i++;
	}
	return (0);
}

void	malloc_copy(char **variable, int sizevariable, t_export *export)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char) * sizevariable - 2);
	if (!copy)
		exit(-2);
	while (variable[1][i + 2])
	{
		copy[i] = variable[1][i + 1];
		i++;
	}
	export->content = copy;
}

void	malloc_copy_lst(char **variable, int sizevariable, t_export *export)
{
	char		*copy;
	int			i;
	t_export	*element;

	i = 0;
	copy = malloc(sizeof(char) * sizevariable - 2);
	if (!copy)
		exit (-2);
	while (variable[1][i + 2])
	{
		copy[i] = variable[1][i + 1];
		i++;
	}
	element = ft_lst_new(copy, variable[0]);
	ft_lst_add_back(&export, element);
}

int	variable_exist(t_export *ex, int sizevar, char **var, t_builtins *bu)
{
	ex = ex->next;
	while (ex)
	{
		sizevar = ft_strlen(var[0]);
		if (ft_strncmp(var[0], ex->variable, sizevar) == 0)
		{
			if (ft_strncmp(var[0], ex->variable, ft_strlen(ex->variable)) == 0)
			{
				verif_variable(ex, sizevar, var, bu);
				return (1);
			}
		}
		ex = ex->next;
	}
	return (0);
}

void	ft_builtin_export(char *maVariable, t_export *export, t_builtins *bu)
{
	char	**variable;
	int		i;

	bu->countspace = 0;
	bu->sizevariable = 0;
	i = 0;
	bu->j = 0;
	variable = ft_split(maVariable, '=');
	if (!variable)
		exit (-2);
	while (maVariable[i++])
	{
		if (maVariable[i] == '=')
			bu->countspace++;
	}
	bu->i = i;
	if (variable[1] != NULL || bu->countspace > 1)
	{
		if (variable[1] == NULL)
			bu->j = 1;
		if (add_export(export, bu, variable, maVariable) == 1)
			return ;
	}
	free_add_export(export, variable, bu);
}
