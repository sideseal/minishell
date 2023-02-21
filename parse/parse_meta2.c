/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 07:31:30 by codespace         #+#    #+#             */
/*   Updated: 2023/02/21 05:45:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	double_quote_task(char *return_val, t_list **root)
{
	int		index;
	int		index_before;

	index = 0;
	index_before = 0;
	if (!return_val[index])
	{
		ft_lstadd_back(root, ft_lstnew(ft_strdup(""), 0));
		return ;
	}
	while (return_val[index])
	{
		while (return_val[index] && return_val[index] != '$')
			index++;
		ft_lstadd_back(root, ft_lstnew(ft_substr(return_val, index_before, index - index_before), 0));
		index_before = index;
		if (return_val[index] && return_val[index] == '$' && (ft_isalpha(return_val[index + 1]) || return_val[index + 1] == '_'))
		{
			while (return_val[index] && (ft_isalnum(return_val[index + 1]) || return_val[index + 1] == '_'))
				index++;
			index++;
			ft_lstadd_back(root, ft_lstnew(ft_substr(return_val, index_before, index - index_before), 0));
			index_before = index;
		}
		else if (!ft_isalpha(return_val[index + 1]) || return_val[index + 1] != '_')
		{
			ft_lstadd_back(root, ft_lstnew(ft_substr(return_val, index, 2), 0));
			ft_lstlast(*root)->is_single_quote = 1;
			index += 2;
			index_before = index;
		}
	}
}

char	*read_string_before_redirection(char *str, t_list **root)
{
	char	*return_val;

	if (*(str + 1) && *(str + 1) == *(str))
	{
		return_val = (char *)malloc(sizeof(char) * 3);
		return_val[0] = *str;
		return_val[1] = *str;
		return_val[2] = 0;
		ft_lstadd_back(root, ft_lstnew(return_val, 1));
		return (str + 2);
	}
	return_val = (char *)malloc(sizeof(char) * 2);
	return_val[0] = *str;
	return_val[1] = '\0';
	ft_lstadd_back(root, ft_lstnew(return_val, 1));
	return (str + 1);
}


char	*read_string_before_dollar(char *str, t_list **root, int *status)
{
	int		index;
	char	*return_val;
	
	index = 1;
	if (str[index] == '?')
	{
		ft_lstadd_back(root, ft_lstnew(ft_strdup("?"), 0));
		return (str + 2);
	}
	if (ft_isalpha(str[index]) || str[index] == '_')
		index++;
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token \'$\'\n", 2);
		*status = 1;
		return (0);
	}
	while (str[index] && (ft_isalnum(str[index]) || str[index] == '_'))
		index++;
	return_val = ft_substr(str, 0, index);
	ft_lstadd_back(root, ft_lstnew(return_val, 0));
	return (str + index);
}