/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:41:55 by ascatama          #+#    #+#             */
/*   Updated: 2023/05/25 09:54:27 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ms_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ms_handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_status = 131;
	}
}

void	ms_handle_fork(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 0);
}

void	ms_handle_mini(int sig)
{
	(void)sig;
	rl_replace_line("\n", 0);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ms_handle_hdoc(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
