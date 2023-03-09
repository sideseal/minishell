/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:22:00 by gychoi            #+#    #+#             */
/*   Updated: 2023/03/09 20:03:15 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	meta_and_number_exist(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (i == 0 && ('0' <= cmd[i] && cmd[i] <= '9'))
			return (1);
		if (is_meta_builtin(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(t_cmd *node, t_env *environ)
{
	int	i;
	int	status;

	i = 1;
	status = EXIT_SUCCESS;
	while (node->args[i] != NULL)
	{
		if (meta_and_number_exist(node->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(node->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = EXIT_FAILURE;
		}
		delete_environ(environ, node->args[i]);
		i++;
	}
	return (status);
}
