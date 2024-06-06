/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daddy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:45:56 by kabasolo          #+#    #+#             */
/*   Updated: 2024/06/06 14:51:18 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	exec(char *path, char **cmd, char **envp, int fd_out)
{
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	execve(path, cmd, envp);
	ft_dprintf(2, "Error: execve() failed.\n");
	exit(1);
}

static void	child(t_pipex data, char *path, char **cmd, int i)
{
	close(data.fd[0]);
	if (i == 0)
	{
		close(data.fd[1]);
		exec(path, cmd, data.envp, data.outfile);
	}
	exec(path, cmd, data.envp, data.fd[1]);
}

void	daddy(t_pipex data, int i)
{
	int		pid;
	char	*path;
	char	**split_comand;

	while (++i <= data.argc)
	{
		if (pipe(data.fd) == -1)
			return ;
		split_comand = ft_split(data.argv[i], ' ');
		if (!split_comand)
			return ;
		path = get_path(split_comand[0], data.envp);
		if (!path)
			return (free_split(split_comand));
		pid = fork();
		if (pid < 0)
			return (free(path), free_split(split_comand));
		if (pid == 0)
			child(data, path, split_comand, i * (i < data.argc));
		free_split(split_comand);
		free(path);
		close(data.fd[1]);
		dup2(data.fd[0], STDIN_FILENO);
		close(data.fd[0]);
	}
}
