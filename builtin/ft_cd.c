/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:49:01 by gychoi            #+#    #+#             */
/*   Updated: 2023/03/09 20:36:27 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static int	change_environ_oldpwd(t_env *environ)
{
	t_env	*cur;
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (EXIT_FAILURE);
	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, "OLDPWD", 7) == 0)
		{
			free(cur->val);
			cur->val = path;
			return (EXIT_SUCCESS);
		}
		cur = cur->next;
	}
	free(path);
	return (EXIT_SUCCESS);
}

static int	change_environ_pwd(t_env *environ)
{
	t_env	*cur;
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		perror("");
		return (EXIT_FAILURE);
	}
	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, "PWD", 4) == 0)
		{
			free(cur->val);
			cur->val = path;
			return (EXIT_SUCCESS);
		}
		cur = cur->next;
	}
	free(path);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmd *node, t_env *environ)
{
	int	status_pwd;
	int	status_oldpwd;

	if (node->args[1] == NULL)
	{
		if (chdir(get_env(environ, "HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	status_oldpwd = change_environ_oldpwd(environ);
	if (chdir(node->args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (EXIT_FAILURE);
	}
	status_pwd = change_environ_pwd(environ);
	return (xnor_by_status(status_pwd, status_oldpwd, EXIT_SUCCESS));
}
