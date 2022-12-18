/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:32:41 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/18 04:33:44 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_slash(char *path, char *cmd)
{
	char	*var;
	size_t	i;
	size_t	x;

	var = ft_calloc(ft_strlen(path) + ft_strlen(cmd) + 2, 1);
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

void	checkaccess(char *cmd, int boolean)
{
	if (access(cmd, F_OK) != 0 && boolean == 1)
		ft_printf("%s: No such command\n", cmd);
	else if (access(cmd, F_OK) != 0 && boolean == 0)
		ft_printf("bash: %s: No such file or directory\n", cmd);
}

void	ft_getenv(int ac, char **envp, t_args *args)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			args->env = ft_split(envp[i], ':');
			if (!args->env)
			{
				free(args);
				exit(1);
			}
		}
	}
	args->cmds = ft_calloc(sizeof(char *), ac - 2);
	if (!args->cmds)
	{
		ft_freetab((void **)args->env);
		free(args);
		exit(1);
	}
}
