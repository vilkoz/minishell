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

void	clean_up(char *line, char **command)
{
	int	 i;

	i = -1;
	if (command != NULL)
	{
		while (command[++i])
			ft_strdel(&(command[i]));
	}
	ft_memdel(((void*)command));
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
	char	**command;

	envp = new_envp(envp);
	g_env = &envp;
	while (1)
	{
		put_prompt(envp);
		if ((line = read_line(0)) == NULL)
		{
			continue ;
		}
		if (ft_strlen(line) > 0)
		{
			command = parse_line(line);
			run_command(command, &envp);
		}
		clean_up(line, command);
	}
}

void	sigint(int sig)
{
	(void)sig;
	ft_putchar('\n');
	put_prompt(*g_env);
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	signal(SIGINT, sigint);
	minishell_loop(envp);
	return (0);
}
