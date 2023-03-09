/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:28:00 by codespace         #+#    #+#             */
/*   Updated: 2023/02/24 22:05:12 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ignore_blank_inside(t_list **pre_lst, t_list *temp)
{
	t_list	*curr;
	int		pipe_n;

	pipe_n = temp->pipe_n;
	curr = *pre_lst;
	while (curr && curr->pipe_n != pipe_n)
		curr = curr->next;
	while (curr)
	{
		if (pipe_n != curr->pipe_n)
			return ;
		free(temp->content);
		temp->content = ft_strdup(" ");
		temp->is_meta = 1;
		curr = curr->next;
	}
}

void	lst_del_cmd(t_cmd **return_val, int pipe_n)
{
	t_cmd	*curr;

	curr = *return_val;
	while (curr && curr->pipe_n != pipe_n)
		curr = curr->next;
	curr->is_ignore = 1;
}

void	ignore_cmd(t_list **pre_lst, t_cmd **return_val)
{
	t_list	*curr;
	int		pipe_n;

	curr = *pre_lst;
	pipe_n = curr->pipe_n;
	if (is_ignore_f(curr, pre_lst))
		lst_del_cmd(return_val, curr->pipe_n);
	while (curr)
	{
		if (curr->pipe_n != pipe_n)
		{
			if (is_ignore_f(curr, pre_lst))
				lst_del_cmd(return_val, curr->pipe_n);
			pipe_n = curr->pipe_n;
		}
		curr = curr->next;
	}
}
