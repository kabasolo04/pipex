/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:21:07 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/31 17:25:22 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	get_files(char *n_in, char *n_out, t_pipex *data, int bool_hd)
{
	if (bool_hd)
	{
		if (data->argc < 6)
		{
			ft_dprintf(2, "Error: non-valid argument number\n");
			exit(1);
		}
		data->infile = here_doc(data->argv);
	}
	else
		data->infile = open(n_in, O_RDONLY);
	if (data->infile == -1)
	{
		ft_dprintf(2, "Error: infile\n");
		exit(1);
	}
	data->outfile = open(n_out, O_CREAT | O_APPEND | O_RDWR, 0644);
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
	int		here_doc;
	t_pipex	data;

	if (argc < 5)
		return (ft_dprintf(2, "Error: non-valid argument number\n"), -1);
	here_doc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	data.argc = argc;
	data.argv = &argv[here_doc + 1];
	data.envp = envp;
	get_files(argv[1], argv[argc - 1], &data, here_doc);
	data.argc = argc - (here_doc + 3);
	dup2(data.infile, STDIN_FILENO);
	close(data.infile);
	daddy(data, 0);
	i = 0;
	while (++i <= argc - (here_doc + 3))
		wait(NULL);
	close(data.outfile);
	return (0);
}
