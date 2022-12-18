/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:30:42 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/18 05:28:19 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	dupnclose(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}

void	ft_error_exit(char *s, t_args *args, int last)
{
	if (errno == 13)
		ft_printf("bash: %s: Permission denied\n", s);
	else
		ft_printf("bash: %s: No such file or directory\n", s);
	if (last)
		close(args->prev_pipes);
	close(args->fd[0]);
	close(args->fd[1]);
	freestruct(args);
	exit(1);
}

void	wait_pids(t_args *args)
{
	int	i;
	int	r;

	i = -1;
	while (++i < args->nbcmds)
		waitpid(args->pid[i], &r, 0);
}
