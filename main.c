/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:03:19 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/03/10 14:47:30 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_is_ended;

void	free_parsed_data(t_cmd **line_root)
{
	t_cmd	*curr;
	int		index;

	while (*line_root)
	{
		if ((*line_root)->fd_in > 0)
			ft_close((*line_root)->fd_in, PARENT);
		if ((*line_root)->fd_out > 0)
			ft_close((*line_root)->fd_out, PARENT);
		curr = (*line_root)->next;
		free((*line_root)->cmd);
		index = 0;
		while ((*line_root)->args[index])
		{
			free((*line_root)->args[index]);
			index++;
		}
		free((*line_root)->args);
		free(*line_root);
		(*line_root) = curr;
	}
}

void	sigint_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		if (g_is_ended == -1)
		{
			write(1, "\n", 1);
			close(0);
		}
		else
			write(1, "\nminishell$ ", 12);
		g_is_ended = 1;
	}
}

int	see_global_rest_handle(char *line, int *tmp_fd, int *status)
{
	if (g_is_ended > 0)
	{
		dup2(*tmp_fd, 0);
		close(*tmp_fd);
		*status = 1;
		return (1);
	}
	if (g_is_ended == -1)
		g_is_ended = 0;
	if (!line)
	{
		write(1, "\n", 1);
		exit(0);
	}
	if (line[0] != '\0')
		add_history(line);
	return (0);
}

void	readline_loop(t_env *environ, int *status)
{
	char	*line;
	t_cmd	*line_root;
	int		tmp_fd;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	tmp_fd = dup(0);
	g_is_ended = -1;
	line = readline("minishell$ ");
	if (see_global_rest_handle(line, &tmp_fd, status))
		return ;
	line_root = parse_data(line, status, environ);
	if (!line_root)
	{
		free(line);
		free_parsed_data(&line_root);
		*status = 127;
		return ;
	}
	close(tmp_fd);
	*status = execute(line_root, environ);
	free(line);
	free_parsed_data(&line_root);
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*environ;
	int				status;

	if (argv[1] || argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell", 2);
		exit(1);
	}
	ft_putstr_fd("Welcome to minishell!\n\n", 1);
	status = 0;
	environ = set_environ(envp);
	while (1)
	{
		g_is_ended = 0;
		readline_loop(environ, &status);
	}
	env_lstclear(environ);
	return (0);
}
