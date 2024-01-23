/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 07:13:20 by codespace         #+#    #+#             */
/*   Updated: 2023/02/23 07:22:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_variable_name(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_valid_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	dollar_error(int *status)
{
	ft_putstr_fd("minishell: syntax error near unexpected token \'$\'\n", 2);
	*status = 1;
	return (1);
}

int	process_dollar(char *return_val, int *index, t_list **root, int *status)
{
	int		index_before;

	index_before = *index;
	(*index)++;
	if (return_val[*index] == '$')
		return (dollar_error(status));
	if (is_valid_variable_name(return_val[*index]))
	{
		while (is_valid_variable_char(return_val[*index]))
			(*index)++;
		ft_lstadd_back(root, ft_lstnew(ft_substr(return_val,
					index_before, *index - index_before), 0));
	}
	else if (return_val[*index] == '?')
	{
		ft_lstadd_back(root, ft_lstnew(ft_strdup("?"), 0));
		ft_lstlast(*root)->is_question_dollor = 1;
		(*index) += 1;
	}
	else
	{
		ft_lstadd_back(root, ft_lstnew(ft_strdup("$"), 0));
		ft_lstlast(*root)->is_single_quote = 1;
	}
	return (0);
}
