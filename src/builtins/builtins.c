/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 13:59:42 by vrybalko          #+#    #+#             */
/*   Updated: 2017/09/22 14:49:22 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_echo(int argc, char **argv, char ***env)
{
	int i;

	i = 0;
	(void)env;
	while (++i < argc)
		ft_putstr(argv[i]);
}

void	minishell_env(int argc, char **argv, char ***env)
{
	(void)argc;
	(void)argv;
	ft_print_array(*env);
}

void	minishell_exit(int argc, char **argv, char ***env)
{
	(void)argc;
	(void)argv;
	(void)env;
	exit(0);
}
