#include "minishell.h"

char	**get_path(char ***envp)
{
	size_t	i;

	i = -1;
	while ((*envp)[++i] != NULL)
	{
		if (ft_strncmp("PATH=", (*envp)[i], 5) == 0)
			return (ft_strsplit(&((*envp)[i][5]), ':'));
	}
	return (NULL);
}

void	run_single(char **command, char ***envp)
{
	if (execve(command[0], command, *envp) == -1)
	{
		ft_putstr_fd("shell: execve single error\n", 2);
		exit(1);
	}
}


void	run_with_path(char **command, char **path, char ***envp)
{
	size_t	i;
	char	*executable_name;

	if (command[0][0] == '/' || command[0][0] == '.' || path == NULL)
	{
		run_single(command, envp);
		return ;
	}
	i = 0;
	executable_name = ft_strdup(command[0]);
	while (execve(command[0], command, *envp) == -1 && path[i] != NULL)
	{
		ft_strdel(&(command[0]));
		command[0] = ft_strjoin(ft_strjoin(path[i], "/"), executable_name);
		i++;
	}
	if (path[i] == NULL)
	{
		ft_putstr_fd("shell: command not found: ", 2);
		ft_putendl_fd(executable_name, 2);
		exit(1);
	}
	ft_strdel(&executable_name);
	exit(1);
}

void	run_command(char **command, char ***envp)
{
	pid_t	pid;
	int		status;

	if (run_builtin(command, envp))
		return ;
	pid = fork();
	if (pid == 0)
		run_with_path(command, get_path(envp), envp);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		while (!WIFEXITED(status) && !WIFSTOPPED(status))
			waitpid(pid, &status, 0);
	}
	else
		ft_putstr_fd("shell: fork error\n", 2);
}

