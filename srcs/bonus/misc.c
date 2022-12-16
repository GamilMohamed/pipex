/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:30:42 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/16 22:39:43 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_here_doc(t_args *args)
{
	char	*s;
	int		fd;

	s = NULL;
	fd = open("tmpipex.txt", O_RDWR | O_CREAT, 0644);
	ft_printf("fd la la la =%i\n", fd);
	while (1)
	{
		s = get_next_line(0, 0);
		if (!s || !ft_strcmp(s, args->delimiter))
			break ;
		ft_putstr_fd(s, fd);
		free(s);
	}
	free(s);
	get_next_line(0, 1);
	// close(fd);
	args->in = fd;
	return (0);
}
void	init(t_args *args, char **av, int ac)
{
	int	i;

	args->nbcmds = 0;
	args->prev_pipes = -1;
	args->av = av;
	args->ac = ac;
	args->heredoc = 0000100;
	i = -1;
	if (!ft_strcmp(av[1], "here_doc"))
	{
		args->delimiter = ft_strjoin(av[2], "\n");
		args->heredoc = 00002000;
		i++;
		get_here_doc(args);
	}
	free(args->delimiter);
	while (++i < ac - 3)
		args->cmds[args->nbcmds++] = av[i + 2];
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
