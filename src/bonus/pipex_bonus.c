#include "../../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipeline	pipeline;
	char		**cmd_strings;
	int			here_doc;

	if (argc < 5)
	{
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "\t ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
		fprintf(stderr, "\t ./pipex heredoc LIMITER cmd cmd1 ... cmdn file2\n");
		return (1);
	}
	here_doc = (argc >= 6 && strcmp(argv[1], "here_doc") == 0);
	if (here_doc)
		cmd_strings = argv + 3;
	else
		cmd_strings = argv + 2;
	init_pipeline(&pipeline, argv, argc, here_doc);
	execute_cmds(&pipeline, cmd_strings, envp);
	return (wait_for_children(pipeline.ids, pipeline.cmd_count));
}
