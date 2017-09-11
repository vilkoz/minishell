#include "minishell.h"

void	run_command(char **command, char **envp)
{
	pid_t	pid;
	/* pid_t	wait_pid; */
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(command[0], command, envp) == -1)
		{
			ft_putstr_fd("shell: execve error\n", 2);
			exit(1);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		while (!WIFEXITED(status) && !WIFSTOPPED(status))
			waitpid(pid, &status, 0);
	}
	else
		ft_putstr_fd("shell: fork error\n", 2);
}

