/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 05:55:43 by codespace         #+#    #+#             */
/*   Updated: 2023/02/12 08:51:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_list	*parse_data(char *str)
{
	t_list	*pre_parse;
	t_list	*return_val;
	int		index;

	index = 0;
	pre_parse = seperate_string(str);
	set_pipe_n(&pre_parse);
	set_env(&pre_parse);
	return_val = merge_string(&pre_parse);
	return (return_val);
}
//echo adf | cat -e | asdf

// 1.input command -- ended--
// 2. <<
// 3. seperate command and redirection part
