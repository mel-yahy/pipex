#include "../../include/pipex_bonus.h"

void	init_pipeline(t_pipeline *pipeline, char **argv, int argc, int here_doc)
{
	if (here_doc)
		pipeline->cmd_count = argc - 4;
	else
		pipeline->cmd_count = argc - 3;
	create_pipes(pipeline->pipes, pipeline->cmd_count);
	open_files(argc, argv, pipeline->fds, here_doc);
}

void	set_redirects(t_pipeline *pipeline, int i)
{
	if (i == 0)
	{
		close(pipeline->fds[OUT_FD]);
		if (pipeline->fds[IN_FD] == -1)
			exit(EXIT_FAILURE);
		dup2(pipeline->fds[IN_FD], STDIN_FILENO);
		close(pipeline->fds[IN_FD]);
	}
	else
		dup2(pipeline->pipes[i - 1][0], STDIN_FILENO);
	if (i == pipeline->cmd_count - 1)
	{
		close(pipeline->fds[IN_FD]);
		if (pipeline->fds[OUT_FD] == -1)
			exit(EXIT_FAILURE);
		dup2(pipeline->fds[OUT_FD], STDOUT_FILENO);
		close(pipeline->fds[OUT_FD]);
	}
	else
		dup2(pipeline->pipes[i][1], STDOUT_FILENO);
}

void	execute_cmds(t_pipeline *pipeline, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (i < pipeline->cmd_count)
	{
		create_fork(&pipeline->ids[i]);
		if (pipeline->ids[i] == 0)
		{
			set_redirects(pipeline, i);
			close_pipes(pipeline->pipes, pipeline->cmd_count - 1);
			execute_cmd(argv[i], envp);
		}
		i++;
	}
	close_pipes(pipeline->pipes, pipeline->cmd_count - 1);
	if (pipeline->fds[IN_FD] != STDIN_FILENO)
		close(pipeline->fds[IN_FD]);
	if (pipeline->fds[OUT_FD] != STDOUT_FILENO)
		close(pipeline->fds[OUT_FD]);
}
