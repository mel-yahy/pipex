#include "../../include/pipex_bonus.h"

void	create_fork(int *id)
{
	*id = fork();
	if (*id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	create_pipes(int (*pipes)[2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		create_pipe(pipes[i]);
		i++;
	}
}

void	close_pipes(int (*pipes)[2], int last_pipe)
{
	int	i;

	i = 0;
	while (i < last_pipe)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	wait_for_children(int *ids, int cmd_count)
{
	int	i;
	int	status;
	int	last_exit;

	i = 0;
	last_exit = 0;
	while (i < cmd_count)
	{
		waitpid(ids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
			else
				last_exit = 1;
		}
		i++;
	}
	return (last_exit);
}
