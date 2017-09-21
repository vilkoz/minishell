#include "minishell.h"


static char		**add_to_env(char ***env, char *key, char *value)
{
	int		size;
	int		i;
	char	**new_env;
	char	*tmp_key;

	size = -1;
	while((*env)[++size])
		;
	new_env = (char **)malloc(sizeof(char*) * (size + 2));
	i = -1;
	while(++i < size)
	{
		new_env[i] = ft_strdup((*env)[i]);
	}
	tmp_key = ft_strjoin(key, "=");
	new_env[i++] = ft_strjoin(tmp_key, value);
	ft_strdel(&tmp_key);
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

	if (argc != 3)
		return ;
	key = argv[1];
	value = argv[2];
	env_set(key, value, env);
}

void			minishell_getenv(int argc, char **argv, char ***env)
{
	char	*value;

	if (argc != 2)
		return ;
	value = env_get(argv[1], *env);
	ft_putendl(value);
	ft_strdel(&value);
}

void			env_set(char *key, char *value, char ***env)
{
	char	*tmp_line;
	char	*tmp_key;
	int		i;

	tmp_key = env_get(key, *env);
	if (tmp_key == NULL)
		*env = add_to_env(env, key, value);
	else
	{
		ft_strdel(&tmp_key);
		i = -1;
		while ((*env)[++i] != NULL)
			if (!ft_strncmp(key, (*env)[i], ft_strlen(key)))
			{
				tmp_line = (*env)[i];
				tmp_key = ft_strjoin(key, "=");
				(*env)[i] = ft_strjoin(tmp_key, value);
				ft_strdel(&tmp_key);
				ft_strdel(&tmp_line);
				break ;
			}
	}
}

char		*env_get(const char *name, char **env)
{
	int 	i;
	char	*ret;
	char	*value;

	i = -1;
	while (env[++i] != NULL)
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name)) &&
			(value = ft_strchr(env[i], '=')) != NULL)
		{
			ret = ft_strdup(value + 1);
			return (ret);
		}
	}
	return (NULL);
}
