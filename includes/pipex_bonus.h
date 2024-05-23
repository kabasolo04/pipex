/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:24:54 by kabasolo          #+#    #+#             */
/*   Updated: 2024/05/23 11:06:04 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <wait.h>

int		here_doc(char **argv);
char	*get_path(char *cmd, char **envp);
void	exec(int fd_out, char *argv, char **envp);
void	daddy(int argc, char **argv, char **envp);

#endif //PIPEX_BONUS_H