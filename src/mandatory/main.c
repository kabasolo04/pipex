/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:21:07 by kabasolo          #+#    #+#             */
/*   Updated: 2024/06/13 12:20:26 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_files(char *n_in, char *n_out, t_pipex *data)
{
	data->infile = open(n_in, O_RDONLY);
	if (data->infile == -1)
	{
		ft_dprintf(2, "Error: infile\n");
		exit(1);
	}
	data->outfile = open(n_out, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->outfile == -1)
	{
		close(data->infile);
		ft_dprintf(2, "Error: outfile\n");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	data;

	if (argc != 5)
		return (ft_dprintf(2, "Error: non-valid argument number\n"), -1);
	get_files(argv[1], argv[argc - 1], &data);
	data.argc = argc - 3;
	data.argv = &argv[1];
	data.envp = envp;
	dup2(data.infile, STDIN_FILENO);
	close(data.infile);
	daddy(data, 0);
	i = 0;
	while (++i <= 2)
		wait(NULL);
	close(data.outfile);
	return (0);
}
