#include "minishell.h"

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
	while (command[++i])
		ft_strdel(&(command[i]));
	ft_memdel(((void*)command));
	ft_strdel(&line);
}

void	minishell_loop(char **envp)
{
	char	*line;
	char	**command;

	envp = new_envp(envp);
	while (1)
	{
		ft_putstr("$> ");
		if ((line = read_line(0)) == NULL)
		{
			ft_putstr_fd("shell: input error\n", 2);
			continue ;
		}
		if (ft_strlen(line) > 0)
		{
			command = parse_line(line);
			run_command(command, &envp);
		}
		else
		{
			ft_strdel(&line);
			exit(write(1, "\n", 1));
		}
		clean_up(line, command);
	}
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	minishell_loop(envp);
	return (0);
}
