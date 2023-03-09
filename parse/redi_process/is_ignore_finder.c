/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ignore_finder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 07:30:16 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 07:30:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_ignore_f(t_list *temp, t_list **merged_lst)
{
	t_list	*curr;

	curr = *merged_lst;
	while (curr && curr->pipe_n != temp->pipe_n)
		curr = curr->next;
	while (curr && curr->pipe_n == temp->pipe_n)
	{
		if (curr->is_ignore)
			return (1);
		curr = curr->next;
	}
	return (0);
}

t_list	*confirm_input(t_list *temp, int *status, t_list **merged_lst)
{
	temp = temp->next;
	while (temp && temp->is_meta && ft_iswhite(temp->content[0]))
		temp = temp->next;
	if (temp && temp->is_meta && !ft_iswhite(temp->content[0])
		&& !is_ignore_f(temp, merged_lst))
	{
		unexpected_token_error(temp->content, status);
		temp->is_ignore = 1;
	}
	if (!temp)
	{
		unexpected_token_newline(status);
		return (0);
	}
	if (access(temp->content, R_OK) && !is_ignore_f(temp, merged_lst))
	{
		temp->is_ignore = 1;
		minishell_error(temp->content, status);
	}
	return (temp);
}

t_list	*confirm_new(t_list *temp, int *status, t_list **merged_lst)
{
	temp = temp->next;
	while (temp && temp->is_meta && ft_iswhite(temp->content[0]))
		temp = temp->next;
	if (temp && temp->is_meta && !ft_iswhite(temp->content[0])
		&& !is_ignore_f(temp, merged_lst))
	{
		unexpected_token_error(temp->content, status);
		temp->is_ignore = 1;
	}
	if (!temp)
	{
		unexpected_token_newline(status);
		return (0);
	}
	if (access(temp->content, F_OK) == 0 && !is_ignore_f(temp, merged_lst)
		&& access(temp->content, W_OK))
	{
		temp->is_ignore = 1;
		minishell_error(temp->content, status);
	}
	return (temp);
}

t_list	*confirm_heredoc(t_list *temp, int *status)
{
	while (temp && temp->is_here_word == 0)
		temp = temp->next;
	if (!temp)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline\'\n", 2);
		*status = 2;
		return (0);
	}
	return (temp);
}

int	is_ignore_finder(t_list **merged_lst, int *status)
{
	t_list	*temp;

	temp = *merged_lst;
	while (temp)
	{
		if (ft_strncmp(temp->content, "<<", 2) == 0 && temp->is_meta)
			temp = confirm_heredoc(temp, status);
		if (!temp)
			return (1);
		temp = temp->next;
	}
	temp = *merged_lst;
	while (temp)
	{
		if ((ft_strncmp(temp->content, ">>", 2) == 0
				|| ft_strncmp(temp->content, ">", 2) == 0) && temp->is_meta)
			temp = confirm_new(temp, status, merged_lst);
		else if (ft_strncmp(temp->content, "<", 2) == 0 && temp->is_meta)
			temp = confirm_input(temp, status, merged_lst);
		if (!temp)
			return (1);
		temp = temp->next;
	}
	return (0);
}
