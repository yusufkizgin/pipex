/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykizgin <ykizgin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:00:07 by ykizgin           #+#    #+#             */
/*   Updated: 2025/01/22 10:49:16 by ykizgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

char	*whereis(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (paths[i++])
		free(paths[i]);
	free(paths);
	return (0);
}

void	exec_cmd(char *command, char **envp)
{
	char	**cmd_trunc;
	char	*path;
	int		i;

	cmd_trunc = ft_split(command, ' ');
	path = whereis(cmd_trunc[0], envp);
	i = 0;
	if (!path)
	{
		while (cmd_trunc[i]++)
			free(cmd_trunc[i]);
		free(cmd_trunc);
		error();
	}
	if (execve(path, cmd_trunc, envp) == -1)
		error();
}
