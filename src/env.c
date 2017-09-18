#include "minishell.h"

static char		*find_env(const char *name, char **env)
{
	int 	i;
	char	*ret;
	char	**value;

	i = -1;
	while(env[++i] != NULL)
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name)))
		{
			value = ft_strsplit(env[i], '=');
			ret = ft_strdup(value[1]);
			i = -1;
			while (value[++i] != NULL)
				ft_strdel(&(value[i]));
			ft_memdel((void*)&value);
			return (ret);
		}
	}
	return (NULL);
}

static char		**add_to_env(char ***env, char *key, char *value)
{
	int		size;
	int		i;
	char	**new_env;

	size = -1;
	while((*env)[++size])
		;
	new_env = (char **)malloc(sizeof(char*) * (size + 2));
	i = -1;
	while(++i < size)
	{
		new_env[i] = ft_strdup((*env)[i]);
	}
	new_env[i++] = ft_strjoin(ft_strjoin(key, "="), value);
	ft_strdel(&key);
	/* ft_strdel(&value); */
	new_env[i] = NULL;
	i = -1;
	while ((*env)[++i] != NULL)
		ft_strdel(&((*env)[i]));
	return (new_env);
}

void			minishell_setenv(int argc, char **argv, char ***env)
{
	char	*key;
	char	*value;
	char	*tmp;
	int		i;

	if (argc != 3)
		return ;
	key = argv[1];
	value = argv[2];
	if (find_env(key, *env) == NULL)
	{
		*env = add_to_env(env, key, value);
	}
	else
	{
		i = -1;
		while (env[++i] != NULL)
			if (!ft_strncmp(key, *(env)[i], ft_strlen(key)))
			{
				tmp = *(env)[i];
				*(env)[i] = ft_strjoin(ft_strjoin(key, "="), value);
				ft_strdel(&tmp);
				break ;
			}
	}
}

void			minishell_getenv(int argc, char **argv, char ***env)
{
	char	*value;

	if (argc != 2)
		return ;
	value = find_env(argv[1], *env);
	ft_putendl(value);
}
