/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:21:07 by kabasolo          #+#    #+#             */
/*   Updated: 2024/06/06 13:35:17 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	files[4];

	if (argc != 5)
		return (ft_dprintf(2, "Error: non-valid argument number.\n"));
	files[0] = open(argv[1], O_RDONLY);
	if (files[0] == -1)
		return (ft_dprintf(2, "Error: infile\n"), 1);
	files[1] = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (files[1] == -1)
		return (close(files[0]), ft_dprintf(2, "Error: outfile\n"), 1);
	if (pipe(&files[2]) == -1)
	{
		close(files[0]);
		close(files[1]);
		return (ft_dprintf(2, "Error: pipe failed.\n"), 1);
	}
	daddy(argv, envp, files);
	close(files[0]);
	close(files[1]);
	close(files[2]);
	close(files[3]);
	return (0);
}
