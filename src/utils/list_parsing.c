/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascatama <ascatama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:32:24 by ascatama          #+#    #+#             */
/*   Updated: 2023/04/18 17:33:35 by ascatama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_lst	*lst_last(t_lst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	lst_add_back(t_lst **lst, t_lst *new)
{
	t_lst	*end;

	if (lst == NULL)
		return (1);
	end = lst_last(*lst);
	if (end != NULL)
		end->next = new;
	else
		*lst = new;
	return (0);
}

t_lst	*lst_new(char **cmd)
{
	t_lst	*element;

	element = malloc(sizeof(t_lst));
	if (!element)
		return (NULL);
	element->cmd = cmd;
	element->next = NULL;
	return (element);
}

t_lst	*lst_new_redir(char **cmd, char file)
{
	t_lst	*element;

	element = malloc(sizeof(t_lst));
	if (!element)
		return (NULL);
	element->cmd = cmd;
	element->file = file;
	element->next = NULL;
	return (element);
}
