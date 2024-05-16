/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:21:07 by kabasolo          #+#    #+#             */
/*   Updated: 2024/05/16 19:24:58 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	
	if (argc < 5)
		return (write(1, "tontopoia\n", 10), 1);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		return (1);
	daddy(argc - 3, &argv[2], envp, infile);
	return (0);
}
