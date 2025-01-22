/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykizgin <ykizgin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:59:59 by ykizgin           #+#    #+#             */
/*   Updated: 2025/01/22 13:36:37 by ykizgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	child_p(char **argv, int fd[], char **envp)
{
	int		infile_fd;
	char	*cmd1;

	cmd1 = argv[2];
	infile_fd = open(argv[1], O_RDWR);
	if (infile_fd == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(fd[0]);
	exec_cmd(cmd1, envp);
}

void	parent_p(char **argv, int fd[], char **envp)
{
	int		outfile_fd;
	char	*cmd2;

	cmd2 = argv[3];
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(cmd2, envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		printf("%d\n", pid);
		if (pid == 0)
			child_p(argv, fd, envp);
		waitpid(pid, NULL, 0);
		parent_p(argv, fd, envp);
	}
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
