/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daddy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:45:56 by kabasolo          #+#    #+#             */
/*   Updated: 2024/06/06 14:52:18 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_first(int files[], char *path, char **cmd, char **envp)
{
	dup2(files[0], STDIN_FILENO);
	close(files[0]);
	dup2(files[3], STDOUT_FILENO);
	close(files[3]);
	execve(path, cmd, envp);
	ft_dprintf(2, "Error: execve() failed.\n");
	exit(1);
}

static void	exec_second(int files[], char *path, char **cmd, char **envp)
{
	dup2(files[2], STDIN_FILENO);
	close(files[2]);
	dup2(files[1], STDOUT_FILENO);
	close(files[1]);
	execve(path, cmd, envp);
	ft_dprintf(2, "Error: execve() failed.\n");
	exit(1);
}

void	daddy(char **argv, char **envp, int files[])
{
	int		i;
	int		pid;
	char	**cmd;
	char	*path;

	i = 0;
	while (++i <= 2)
	{
		cmd = ft_split(argv[i + 1], ' ');
		if (!cmd)
			return ;
		path = get_path(cmd[0], envp);
		if (!path)
			return ;
		pid = fork();
		if (pid < 0)
			return ((void)ft_dprintf(2, "Error: fork.\n"));
		if (pid == 0 && i == 1)
			exec_first(files, path, cmd, envp);
		if (pid == 0 && i == 2)
			exec_second(files, path, cmd, envp);
		free_split(cmd);
		free(path);
	}
	wait(NULL);
}
