/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:11:35 by kabasolo          #+#    #+#             */
/*   Updated: 2024/05/16 11:55:03 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(int *fd, char *cmd, char **envp)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve("/usr/bin/which", (char *[]){"which", cmd, 0}, envp) == -1)
		perror("execve");
	exit(1);
}

/*
static char	*parent(int *fd)
{
	char	buff[2];
	char	*path;
	int		bytes_read;

	path = ft_calloc(1, sizeof(char));
	if (!path)
		return(NULL);
	buff[0] = '\0';
	buff[1] = '\0';
	bytes_read = 1;
	close(fd[1]);
	while (bytes_read > 0)
	{
		path = ft_strjoin(path, buff);
		if (!path)
			return(NULL);
		buff[0] = '\0';
		bytes_read = read(fd[0], buff, 1);
	}
	if (bytes_read == -1)
		return (perror("read"), free(path), NULL);
	close(fd[0]);
	return (path);
}

*/

static char	*parent(int *fd)
{
	char	buf[4096];
	int		bytes_read;

	close(fd[1]);
	bytes_read = read(fd[0], buf, sizeof(buf));
	close(fd[0]);
	if (bytes_read == -1)
		return (perror("read"), NULL);
	buf[bytes_read - 1] = '\0';
	return (ft_strdup(buf));
}


char	*get_path(char *cmd, char **envp)
{
	int		fd[2];
	int		pid;
	char	*path;

	if (pipe(fd) == -1)
		return (perror("pipe"), NULL);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd[0]), close(fd[1]), NULL);
	if (pid == 0)
		child(fd, cmd, envp);
	wait(NULL);
	path = parent(fd);
	close(fd[0]);
	close(fd[1]);
	if (!path)
		return (NULL);
	return (path);
}
