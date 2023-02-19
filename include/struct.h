/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:24:16 by codespace         #+#    #+#             */
/*   Updated: 2023/02/19 21:07:27 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_list
{
	char			*content;
	int				pipe_n;
	int				is_meta;
	int				is_single_quote;
	int				is_here_word;
	int				is_here_quote_word;
	int				is_fd_new;
	int				is_fd_add;
	int				is_fd_input;
	int				fd;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				fd_out;
	int				fd_in;
	int				pipe_n;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

#endif
