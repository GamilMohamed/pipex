/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:09:49 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/18 04:14:36 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	t_args	*args;

	if (ac != 5)
		exit(1);
	if (!envp[0])
		exit(1);
	args = ft_calloc(sizeof(t_args), 1);
	if (!args)
		exit(0);
	ft_getenv(ac, envp, args);
	init(args, av, ac);
	preforking(args);
	wait_pids(args);
	close(args->out);
	close(args->fd[0]);
	close(args->in);
	freestruct(args);
	return (1);
}
