/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 07:31:30 by codespace         #+#    #+#             */
/*   Updated: 2023/03/02 14:57:27 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_to_list(t_list **root, char *return_val)
{
	if (!return_val[0])
	{
		free(return_val);
		return_val = ft_strdup("");
	}
	ft_lstadd_back(root, ft_lstnew(ft_strdup(return_val), 0));
	ft_lstlast(*root)->is_single_quote = 1;
}

void	process_plain_text(char *return_val, int *index, t_list **root)
{
	int		index_before;
	char	*text;

	index_before = *index;
	while (return_val[*index] && return_val[*index] != '$')
		(*index)++;
	text = ft_substr(return_val, index_before, *index - index_before);
	ft_lstadd_back(root, ft_lstnew(text, 0));
}

int	double_quote_task(char *return_val, t_list **root, int *status)
{
	int		index;
	char	*temp;

	temp = ft_strdup("");
	index = 0;
	if (!return_val[0])
	{
		ft_lstadd_back(root, ft_lstnew(temp, 0));
		return (0);
	}
	while (return_val[index])
	{
		if (return_val[index] == '$')
		{
			if (process_dollar(return_val, &index, root, status))
			{
				free(temp);
				return (1);
			}
		}
		else
			process_plain_text(return_val, &index, root);
	}
	free(temp);
	return (0);
}
