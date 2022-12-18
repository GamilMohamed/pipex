/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:09:49 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/18 05:27:48 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_here_doc(t_args *args)
{
	char	*s;

	s = NULL;
	args->heredocfd = open("tmpipex.txt", O_RDWR | O_CREAT, 0644);
	while (1)
	{
		s = get_next_line(0, 0);
		if (!s || !ft_strcmp(s, args->delimiter))
			break ;
		ft_putstr_fd(s, args->heredocfd);
		free(s);
	}
	free(s);
	get_next_line(0, 1);
	close(args->heredocfd);
	return (0);
}

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
