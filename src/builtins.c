#include "minishell.h"

void	minishell_echo(int argc, char **argv, char ***env)
{
	int i;

	i = 0;
	(void)env;
	while(++i < argc)
		ft_putstr(argv[i]);
}

void	minishell_cd(int argc, char **argv, char ***env)
{
	(void)env;
	if (argc != 2)
	{
		ft_putstr_fd("shell: cd: wrong number of arguments\n", 2);
		return ;
	}
	if (chdir(argv[1]) == -1)
	{
		ft_putstr_fd("shell: cd:", 2);
		if (access(argv[1], F_OK) == -1)
			ft_putstr_fd("no such file or directory:", 2);
		else if (access(argv[1], R_OK) == -1)
			ft_putstr_fd("no such file or directory:", 2);
		else
			ft_putstr_fd("not a directory", 2);
		ft_putendl_fd(argv[1], 2);
	}
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
	exit(1);
}
