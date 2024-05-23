/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:21:07 by kabasolo          #+#    #+#             */
/*   Updated: 2024/05/23 10:54:23 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define infile 0
#define outfile 1

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	bool;

	if (argc < 5)
		return (ft_dprintf(2, "Error: ./pipex infile cmd ... cmd outfile\n"));
	bool = (ft_strncmp("here_doc", argv[1], 8) == 0);
	if (bool == 1)
	{
		if (argc < 6)
			return (ft_dprintf(2, "Error: non-valid argument number\n"), -1);
		fd[infile] = here_doc(argv);
	}
	else
		fd[infile] = open(argv[1], O_RDONLY);
	if (fd[infile] == -1)
			return (ft_dprintf(2, "Error: infile failed.pitoss\n"), -1);
	fd[outfile] = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd[outfile] == -1)
		return (ft_dprintf(2, "Error: open() failed.\n"));
	dup2(fd[infile], STDIN_FILENO);
	close(fd[infile]);
	daddy(argc - 3 - bool, &argv[2 + bool], envp);
	exec(fd[outfile], argv[argc - 2], envp);
	return (0);
}
