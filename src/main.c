/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:21:07 by kabasolo          #+#    #+#             */
/*   Updated: 2024/04/30 17:40:47 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd1;
	int		fd2[2];
	char	**comand;
	char	*path;
	int		i;
	int		pid;

	if (argc != 5)
		return (write(2, "./pipex <file1> <cmd1> <cmd2> <file2>\n", 38), 1);
	i = 2;
	while (i <= argc)
	{
		if (pipe(fd2) == -1)
			return (perror("pipe"), 2);
		if (pid > 0)
			pid = fork();
		if (pid < 0)
			return (perror("fork"), 3);
		if (pid == 0)
		{
			comand = ft_split(argv[i], ' ');
			if (!comand)
				return (write(2, "alaburguer\n", 11), 1);
			path = get_path(comand[0], envp);
			if(i == 2)
				fd1 = open(argv[1],O_RDONLY);
			dup2(fd1, STDIN_FILENO);
			close(fd1);
			if(i == argc)
				fd2[1] = open(argv[i],O_WRONLY | O_CREAT);
			dup2(fd2[1], STDOUT_FILENO);
			close(fd2[1]);
			if (execve(path, comand, NULL) == -1)
				perror("execve");
			exit(1);
		}
		if(fd1)
			close(fd1); 
		fd1 = fd2[1];
		i ++;
	}
	close(fd2[0]);
	close(fd2[1]);
	return (0);
}


/*
	int		fd[2];
	char	*comand1;
	char	*comand2;
	int		pid1;
	int		pid2;

	if (argc != 5)
		return (write(2, "./pipex <file1> <cmd1> <cmd2> <file2>\n", 38), 1);
	comand1 = get_path(argv[2], envp);
	comand2 = get_path(argv[3], envp);
	if (!comand1 || !comand2)
		return (write(2, "loh comandos no van carakaka\n", 29), 1);
	if (pipe(fd) == -1)
		return (perror("pipe"), 2);
	pid1 = fork();
	if (pid1 < 0)
		return (perror("fork"), 3);
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(comand1, &argv[2], NULL) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	pid2 = fork();
	if (pid2 < 0)
		return (perror("fork"), 4);
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (execve(comand2, &argv[3], envp) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
*/