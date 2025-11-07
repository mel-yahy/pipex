#include "../../include/pipex.h"

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

int	wait_for_children(int child_1, int child_2)
{
	int	status1;
	int	status2;

	waitpid(child_1, &status1, 0);
	waitpid(child_2, &status2, 0);
	if (WIFEXITED(status2))
	{
		return (WEXITSTATUS(status2));
	}
	return (EXIT_FAILURE);
}
