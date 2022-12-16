/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:30:42 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/15 21:38:56 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(t_args *args, char **av, int ac)
{
	int	i;

	args->nbcmds = 0;
	i = -1;
	while (++i < ac - 3)
	{
		args->nbcmds++;
		args->cmds[i] = av[i + 2];
	}
	args->cmds[i] = NULL;
}

int	freestruct(t_args *args)
{
	ft_freetab((void **)args->env);
	free(args->cmds);
	free(args);
	exit(1);
}

void	ft_freestr(int n, int ntab, ...)
{
	va_list	str;
	int		i;

	va_start(str, ntab);
	i = -1;
	while (++i < n)
		free(va_arg(str, void *));
	i = -1;
	while (++i < ntab)
		ft_freetab((void **)va_arg(str, void **));
	va_end(str);
}

void	wait_pids(t_args *args)
{
	int	i;
	int	r;

	i = -1;
	while (++i < args->nbcmds)
		waitpid(args->pid[i], &r, 0);
}
