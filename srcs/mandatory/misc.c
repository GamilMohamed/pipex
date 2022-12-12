/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:30:42 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/09 20:40:08 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(t_args *args, char **av)
{
	args->infile = av[1];
	args->cmds[0] = av[2];
	args->cmds[1] = av[3];
	args->cmds[2] = NULL;
	args->outfile = av[4];
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
