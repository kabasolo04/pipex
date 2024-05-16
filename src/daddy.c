/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daddy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:45:56 by kabasolo          #+#    #+#             */
/*   Updated: 2024/05/16 18:36:23 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(int fdin, int fdout, char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		exit(1);
	path = get_path(cmd[0], envp);
	if (!path)
		exit(1);
	if (execve(path, cmd, envp) == -1)
		perror("execve");
	exit(1);
}

void	daddy(int i, char **argv, char **envp, int fdin)
{
	int	fd[2];
	int	pid;
	
	if (pipe(fd) == -1)
		return (perror("pipe"));
	if (i == 1)
	{
		close(fd[1]);
		fd[1] = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	pid = fork();
	if (pid < 0)
		return (close(fd[0]), close(fd[1]), perror("fork"));
	if (pid == 0)
		child(fdin, fd[1], argv[0], envp);
	wait(NULL);
	close(fdin);
	close(fd[1]);
	if (i > 1)
		daddy(i - 1, &argv[1], envp, fd[0]);
}
