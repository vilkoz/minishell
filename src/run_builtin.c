#include "minishell.h"

int		get_array_size(char **array)
{
	int		len;

	len = -1;
	while (array[++len] != NULL)
		;
	return (len);
}

void	(*check_builtin(char *name))(int, char **, char **)
{
	if (!strcmp("ehco", name))
		return minishell_echo;
	else if (!strcmp("cd", name))
		return minishell_cd;
	else if (!strcmp("env", name))
		return minishell_env;
	else if (!strcmp("exit", name))
		return minishell_exit;
	return NULL;
}

int		run_builtin(char **command, char **envp)
{
	void	*function;

	function = check_builtin(command[0]);
	if (function != NULL)
	{
		((void(*)(int, char **, char **))function)(get_array_size(command),
			command, envp);
		return (1);
	}
	return (0);
}
