#include "minishell.h"

static char		**find_env(const char *name, char **env)
{
	int 	i;
	char	**ret;

	i = -1;
	while(env[++i] != NULL)
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name)))
		{
			ret = ft_strsplit(env[i], '=');
			return (ret);
		}
		//LEAKS;
	}
	return (NULL);
}

void			minishell_getenv(int argc, char **argv, char ***env)
{
	char	**value;
	int		i;

	if (argc != 2)
		return ;
	value = find_env(argv[1], *env);
	ft_putendl(value[1]);
	i = -1;
	while (value[++i] != NULL)
		ft_strdel(&(value[i]));
	ft_memdel((void*)&value);
}
