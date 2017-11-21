/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:30:26 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 23:15:29 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

char	**new_envp(char **envp)
{
	char	**new;
	int		i;

	i = -1;
	while (envp[++i])
		;
	new = (char**)malloc(sizeof(char*) * (i + 1));
	i = -1;
	while (envp[++i])
		new[i] = ft_strdup(envp[i]);
	new[i] = NULL;
	return (new);
}

void	clean_up(char *line, char ***command)
{
	int		i;
	int		j;

	i = -1;
	if (command != NULL)
	{
		while (command[++i])
		{
			j = -1;
			while (command[i][++j])
				ft_strdel(&(command[i][j]));
			ft_memdel(((void*)&(command[i])));
		}
	}
	ft_memdel(((void*)&command));
	ft_strdel(&line);
}

void	put_prompt(char **env)
{
	char	*pwd;

	pwd = env_get("PWD", env);
	ft_putstr(pwd);
	ft_putstr(" $> ");
	ft_strdel(&pwd);
}

void	minishell_loop(char **envp)
{
	char	*line;
	char	***commands;
	int		i;

	envp = new_envp(envp);
	g_env = &envp;
	while (1)
	{
		commands = NULL;
		put_prompt(envp);
		if ((line = read_line(0)) == NULL)
			continue ;
		if (ft_strlen(line) > 0)
		{
			commands = parse_line(line);
			i = -1;
			while (commands[++i])
				run_command(commands[i], &envp);
		}
		clean_up(line, commands);
	}
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	signal(SIGINT, sigint);
	signal(SIGTSTP, sigint);
	signal(SIGQUIT, sigint);
	minishell_loop(envp);
	return (0);
}
