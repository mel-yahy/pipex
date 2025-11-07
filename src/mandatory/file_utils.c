#include "../../include/pipex.h"

void	open_files(char *infile, char *outfile, int *fds)
{
	fds[IN_FD] = open(infile, O_RDONLY);
	if (fds[IN_FD] < 0)
		perror(infile);
	fds[OUT_FD] = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fds[OUT_FD] < 0)
		perror(outfile);
}
