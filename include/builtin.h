/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:13:04 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/21 16:52:15 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environ.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

int	ft_echo(t_cmd *node);
int	ft_cd(t_cmd *node, t_env *environ);

#endif