/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_redi_read_here.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:40:31 by codespace         #+#    #+#             */
/*   Updated: 2023/03/04 20:41:53 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*redi_append(t_list *temp, int *status, t_list **merged_lst)
{
	temp = temp->next;
	while (temp && temp->is_meta && ft_iswhite(temp->content[0]))
		temp = temp->next;
	if (temp->is_ignore == 0 && !is_ignore_f(temp, merged_lst))
		temp->fd = open(temp->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	temp->is_fd_add = 1;
	if (temp->fd == -1)
		minishell_error(temp->content, status);
	return (temp);
}

t_list	*redi_new(t_list *temp, int *status, t_list **merged_lst)
{
	temp = temp->next;
	while (temp && temp->is_meta && ft_iswhite(temp->content[0]))
		temp = temp->next;
	if (temp->is_ignore == 0 && !is_ignore_f(temp, merged_lst))
		temp->fd = open(temp->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	temp->is_fd_new = 1;
	if (temp->fd == -1)
		minishell_error(temp->content, status);
	return (temp);
}

t_list	*redi_input(t_list *temp, int *status, t_list **merged_lst)
{
	temp = temp->next;
	while (temp && temp->is_meta && ft_iswhite(temp->content[0]))
		temp = temp->next;
	if (temp->is_ignore == 0 && !is_ignore_f(temp, merged_lst))
		temp->fd = open(temp->content, O_RDONLY);
	temp->is_fd_input = 1;
	if (temp->fd == -1)
		minishell_error(temp->content, status);
	return (temp);
}

t_list	*redi_heredoc(t_list *temp, int *status)
{
	while (temp && temp->is_here_word == 0)
		temp = temp->next;
	if (temp)
	{
		temp->fd = read_heredoc_infile(temp->content, status);
		if (temp->fd == -2)
			return (0);
	}
	return (temp);
}

int	del_redi_read_here(t_list **merged_lst, int *status)
{
	t_list	*temp;

	temp = *merged_lst;
	while (temp)
	{
		if (ft_strncmp(temp->content, "<<", 2) == 0 && temp->is_meta)
			temp = redi_heredoc(temp, status);
		if (!temp)
			return (1);
		temp = temp->next;
	}
	temp = *merged_lst;
	while (temp)
	{
		if (ft_strncmp(temp->content, ">>", 2) == 0 && temp->is_meta)
			temp = redi_append(temp, status, merged_lst);
		else if (ft_strncmp(temp->content, ">", 2) == 0 && temp->is_meta)
			temp = redi_new(temp, status, merged_lst);
		else if (ft_strncmp(temp->content, "<", 2) == 0 && temp->is_meta)
			temp = redi_input(temp, status, merged_lst);
		temp = temp->next;
	}
	return (0);
}
