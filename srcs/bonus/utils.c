/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:32:41 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/15 23:03:34 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_slash(char *path, char *cmd)
{
	size_t	pathlen;
	size_t	cmdlen;
	char	*var;
	size_t	i;
	size_t	x;

	pathlen = ft_strlen(path);
	cmdlen = ft_strlen(cmd);
	var = ft_calloc(pathlen + cmdlen + 2, 1);
	if (!var)
		return (NULL);
	i = -1;
	while (path[++i])
		var[i] = path[i];
	var[i++] = '/';
	x = -1;
	while (cmd[++x])
		var[i + x] = cmd[x];
	var[i + x] = '\0';
	return (var);
}

void	dupnclose(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}

void	checkaccess(char *cmd, int boolean)
{
	if (access(cmd, F_OK) != 0 && boolean == 1)
	{
		ft_printf("%s: No such command\n", cmd);
		return ;
	}
	if (access(cmd, F_OK) != 0 && boolean == 0)
	{
		ft_printf("bash: %s: No such file or directory\n", cmd);
		return ;
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_printf("ici cmd=%s\n", cmd);
		ft_printf("bash: %s: Permission denied\n", cmd);
		exit (1);
		return ;
	}
}

void	ft_error_exit(char *s, int error, t_args *args)
{
	if (error == 0)
		ft_printf("bash: %s: Permission denied\n", s);
	if (error == -1)
		ft_printf("bash: %s: No such file or directory\n", s);
	close(args->fd[0]);
	close(args->fd[1]);
	freestruct(args);
	exit(1);
}
