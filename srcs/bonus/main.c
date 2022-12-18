/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:09:49 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/18 04:27:33 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char *av[], char *envp[])
{
	t_args	*args;

	if (ac < 6)
		exit(1);
	if (!envp[0])
		return (0);
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
	if (args->heredoc == 00002000)
		unlink("tmpipex.txt");
	freestruct(args);
	return (1);
}
