/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:46:46 by kabasolo          #+#    #+#             */
/*   Updated: 2024/05/23 11:59:58 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	read_the_terminal(int fd, char *limit)
{
	char	*input;
	int		len;

	len = ft_strlen(limit);
	limit[len] = '\n';
	while (1)
	{
		ft_dprintf(1, " heredoc> ");
		input = get_next_line(0);
		if (ft_strncmp(input, limit, len) == 0)
			return (free(input));
		ft_dprintf(fd, input);
		free(input);
	}
}

int	here_doc(char **argv)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (ft_dprintf(2, "Error: pipe() failed.\n"), -1);
	read_the_terminal(fd[1], argv[2]);
	close(fd[1]);
	dup2(fd[0], 0);
	return (fd[0]);
}