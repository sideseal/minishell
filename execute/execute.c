/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 01:31:40 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/24 04:21:09 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/execute.h"

int	execute_builtin(t_cmd *node, t_env *environ, int process_type)
{
	int	ret;

	ret = -1;
	if (node->cmd == NULL)
		return (ret);
	if (ft_strncmp(node->cmd, "echo", 5) == 0)
		ret = ft_echo(node);
	else if (ft_strncmp(node->cmd, "cd", 3) == 0)
		ret = ft_cd(node, environ);
	else if (ft_strncmp(node->cmd, "pwd", 4) == 0)
		ret = ft_pwd(node);
	else if (ft_strncmp(node->cmd, "export", 7) == 0)
		ret = ft_export(node, environ);
	else if (ft_strncmp(node->cmd, "unset", 6) == 0)
		ret = ft_unset(node, environ);
	else if (ft_strncmp(node->cmd, "env", 4) == 0)
		ret = ft_env(node, environ);
	else if (ft_strncmp(node->cmd, "exit", 5) == 0)
		ret = ft_exit(node, process_type);
	return (ret);
}

int	execute_command_type(t_cmd *node, t_env *environ, int process_type)
{
	struct stat	sb;
	pid_t		pid;
	int			status;

	if (execute_builtin(node, environ, process_type) == -1)
	{
		pid = fork();
		if (pid == -1)
			execute_error("failed to fork", process_type);
		else if (pid == 0)
		{
			if (stat(node->cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
				is_a_directory(node->cmd);
			if (execute_command(node, get_environ(environ)) == 1)
				command_not_found(node->cmd);
		}
		if (waitpid(pid, &status, 0) == -1)
			execute_error("failed to waitpid", process_type);
	}
	return (WEXITSTATUS(status));
}

void	pipeline_child(t_cmd *node, t_env *environ)
{
	int		pfd[2];
	pid_t	pid;

	ft_pipe(pfd);
	pid = fork();
	if (pid == -1)
		execute_error("failed to fork", CHILD);
	else if (pid == 0)
	{
		if (node->fd_in != -2)
			ft_dup2(node->fd_in, STDIN_FILENO, CHILD);
		ft_close(pfd[READ_END], CHILD);
		ft_dup2(pfd[WRITE_END], STDOUT_FILENO, CHILD);
		if (node->fd_out != -2)
			ft_dup2(node->fd_out, STDOUT_FILENO, CHILD);
		if (execute_command_type(node, environ, CHILD) == 1)
			command_not_found(node->cmd);
		exit(0);
	}
	ft_close(pfd[WRITE_END], CHILD);
	ft_dup2(pfd[READ_END], STDIN_FILENO, CHILD);
}

int	pipeline(t_cmd *line, t_env *environ)
{
	t_cmd	*cur;
	pid_t	pid;

	cur = line;
	while (cur->next != NULL)
	{
		pipeline_child(cur, environ);
		cur = cur->next;
	}
	pid = fork();
	if (pid == 0)
	{
		if (cur->fd_in != -2)
			ft_dup2(cur->fd_in, STDIN_FILENO, PARENT);
		if (cur->fd_out != -2)
			ft_dup2(cur->fd_out, STDOUT_FILENO, PARENT);
		if (execute_command_type(cur, environ, PARENT) == 1)
			command_not_found(cur->cmd);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	execute(t_cmd *line, t_env *environ)
{
	int	ret;

	if (line->next == NULL)
	{
		set_simple_command_fd(line, PARENT);
		ret = execute_command_type(line, environ, PARENT);
		reset_simple_command_fd(line, PARENT);
		return (ret);
	}
	int	pid = fork();
	if (!pid)
		ret = pipeline(line, environ);
	wait(NULL);
	return (ret);
}
