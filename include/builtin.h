/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:13:04 by gychoi            #+#    #+#             */
/*   Updated: 2023/03/09 19:56:21 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environ.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

int		ft_echo(t_cmd *node);
int		ft_cd(t_cmd *node, t_env *environ);
int		ft_pwd(t_cmd *node);
int		ft_export(t_cmd *node, t_env *environ);
int		ft_unset(t_cmd *node, t_env *environ);
int		ft_env(t_cmd *node, t_env *environ);
int		ft_exit(t_cmd *node, int process_type);

int		is_meta_builtin(char c);
void	free_strings(char *s1, char *s2);
int		xnor_by_status(int n1, int n2, int status);
void	export_identifier_error(char *command);

int		check_export_type(char *cmd);
char	*get_key(char *command);
int		get_value_len(char *command);
char	*get_value(char *command);
void	print_export_value(char *value);

#endif
