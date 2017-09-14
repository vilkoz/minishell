#include "minishell.h"

void	minishell_loop(char **envp)
{
	char	*line;
	char	**command;

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
			run_command(command, envp);
		}
		else
			exit(write(1, "\n", 1));
		ft_strdel(&line);
	}
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	minishell_loop(envp);
	return (0);
}
