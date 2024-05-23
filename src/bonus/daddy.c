/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daddy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:45:56 by kabasolo          #+#    #+#             */
/*   Updated: 2024/05/22 20:34:46 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(int fd_out, char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	
	cmd = ft_split(argv, ' ');
	if (!cmd)
		exit(1);
	path = get_path(cmd[0], envp);
	if (!path)
		exit(1);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	execve(path, cmd, envp);
	ft_dprintf(2, "Error: execve() failed.\n");
	free(path);
	mtrx_free(cmd);
	exit(1);
}

void	daddy(int i, char **argv, char **envp)
{
	int	fd[2];
	int	pid;
	
	if (pipe(fd) == -1)
	{
		ft_dprintf(2, "Error: pipe() failed.\n");
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		ft_dprintf(2, "Error: fork() failed.\n");
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	if (pid == 0)
		exec(fd[1], argv[0], envp);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	i --;
	if (i > 1)
		daddy(i, &argv[1], envp);
}
