/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:27:53 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 11:07:27 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	exit_to_many_arg(t_cmd *cmd)
{
	ft_putstr("exit\n", cmd->old_stdout);
	ft_putstr("bash: exit: too many arguments\n", cmd->old_stdout);
	g_status = 1;
}

long long	return_number(double long nb, int sign)
{
	if ((nb * sign) > LLONG_MIN && (nb * sign) < LLONG_MAX)
		return (nb * sign);
	if ((nb * sign) < LLONG_MIN)
		return (-1);
	if ((nb * sign) > LLONG_MAX)
		return (-1);
	return (nb * sign);
}

long long	ft_atoi_exit(const char *str)
{
	int			sign;
	long long	nb;
	int			i;

	sign = 1;
	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (((nb * 10) + str[i] - '0') * sign / 10 != nb * sign)
			return (-1);
		nb = (nb * 10) + str[i] - '0';
		if (!str[i + 1])
			return (nb * sign);
		i++;
	}
	return (0);
}

void	ft_exit(t_cmd *cmd, char **args)
{
	ft_putstr_fd("exit\n", cmd->old_stdout);
	g_status = ft_atoi(args[1]);
	exit_free(cmd);
	exit(g_status);
}
