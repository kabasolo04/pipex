/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:11:35 by kabasolo          #+#    #+#             */
/*   Updated: 2024/06/06 12:33:06 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
		i ++;
	}
	ft_dprintf(2, "Error: couldn't find the PATH in the environment.\n");
	return (NULL);
}

static char	*get_command_path(char	**paths, char *command)
{
	int		i;
	char	*path_part;
	char	*command_path;

	i = 0;
	while (paths[i])
	{
		path_part = ft_strjoin(paths[i], "/");
		if (!path_part)
			return (NULL);
		command_path = ft_strjoin(path_part, command);
		free(path_part);
		if (!command_path)
			return (NULL);
		if (access(command_path, F_OK | X_OK) == 0)
			return (command_path);
		free(command_path);
		i ++;
	}
	ft_dprintf(2, "Error: couldn't find the command.\n");
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	*command_path;
	char	*env_path;
	char	**paths;
	char	**command;

	env_path = get_env(envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	command = ft_split(cmd, ' ');
	if (!command)
		return (free_split(paths), NULL);
	command_path = get_command_path(paths, command[0]);
	free_split(paths);
	free_split(command);
	return (command_path);
}
