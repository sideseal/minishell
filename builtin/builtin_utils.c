/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:28:31 by gychoi            #+#    #+#             */
/*   Updated: 2023/03/09 19:56:09 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	is_meta_builtin(char c)
{
	if (c == '!' || c == '@' || c == '$' || c == '^' || c == '%' || c == ':' \
	|| c == '*' || c == '[' || c == ']' || c == '/' || c == '{' || c == '}' \
	|| c == ',' || c == '.' || c == '?' || c == '+' || c == '~' || c == '-' \
	|| c == '=' || c == '\\' || c == '#' || c == '&' || c == '*' || c == '\'' \
	|| c == '\"' || c == '`' || c == '(' || c == ')' || c == '|' || c == ';' \
	|| c == '<' || c == '>')
		return (1);
	return (0);
}

void	free_strings(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int	xnor_by_status(int n1, int n2, int status)
{
	if (n1 == n2 && n2 == status)
		return (status);
	else
		return (!status);
}

void	export_identifier_error(char *command)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
