#include "minishell.h"

static char		is_input_valid(int argc, char **argv, char ***env)
{
	int		i;

	if (argc != 2)
	{
		ft_putendl_fd("shell: unsetenv: wrong number of arguments", 2);
		return (0);
	}
	i = -1;
	while ((*env)[++i])
		if (!ft_strncmp(argv[1], (*env)[i], ft_strlen(argv[1])))
			return (1);
	return (0);
}

static char		**copy_array_without_key(const char *key, const char **env)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char**)malloc(sizeof(char*) * (get_array_size(env) + 1 - 1));
	i = -1;
	j = -1;
	while ((env)[++i] != NULL)
	{
		if (ft_strncmp((env)[i], key, ft_strlen(key)))
			new_env[++j] = ft_strdup((env)[i]);
	}
	new_env[++j] = NULL;
	return (new_env);
}

static void		clean_env(char ***env)
{
	int		i;

	i = -1;
	while ((*env)[++i])
		ft_strdel(&((*env)[i]));
	ft_memdel((void*)env);
}

void			minishell_unsetenv(int argc, char **argv, char ***env)
{
	char	*key;
	char	**new_env;

	if (!is_input_valid(argc, argv, env))
		return ;
	key = argv[1];
	new_env = copy_array_without_key(key, (const char**)(*env));
	clean_env(env);
	*env = new_env;
}
