#include "../../include/pipex.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**env_paths;
	char	*full_path;
	char	*half_path;
	int		i;

	while (*envp && strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (*envp == NULL)
		return (NULL);
	env_paths = ft_split(*envp + 5, ':');
	i = -1;
	while (env_paths[++i])
	{
		half_path = ft_strjoin(env_paths[i], "/");
		full_path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_tab(env_paths);
			return (full_path);
		}
		free(full_path);
	}
	free_tab(env_paths);
	return (NULL);
}

void	execute_cmd(char *cmd_string, char **envp)
{
	char	**argv;
	char	*path;

	argv = ft_split(cmd_string, ' ');
	if (argv[0] == NULL)
	{
		free_tab(argv);
		exit(EXIT_FAILURE);
	}
	path = find_cmd_path(argv[0], envp);
	if (!path)
	{
		fprintf(stderr, "%s: command not found\n", argv[0]);
		free_tab(argv);
		exit(NOT_FOUND);
	}
	execve(path, argv, envp);
	exit(EXIT_FAILURE);
}
