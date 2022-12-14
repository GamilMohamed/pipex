/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:09:49 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/14 03:52:46 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_getenv(int ac, char **envp, t_args *args)
{
	int	i;

	if (ac < 5)
		return (0);
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
	return (1);
}

void	checkcmd(t_args *args)
{
	char	**tab;
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (++i < args->nbcmds)
	{
		if (args->cmds[i][0] == '/')
		{
			tab = ft_split(args->cmds[i], ' ');
			if (access(tab[0], F_OK) != 0)
			{
				// ft_printf("bash: %s: No such file or directory\n",
				// tab[0]);
				ft_freetab((void **)tab);
				freestruct(args);
				exit(1);
			}
			ft_freetab((void **)tab);
		}
		else
		{
			j = 0;
			while (args->env[j])
			{
				tab = ft_split(args->cmds[i], ' ');
				temp = ft_slash(args->env[j], tab[0]);
				access(temp, F_OK);
				if (access(temp, F_OK) != 0 && args->env[j + 1] == NULL)
				{
					ft_freestr(1, 1, temp, tab);
					freestruct(args);
					exit(1);
				}
				else if (access(temp, F_OK) == 0)
				{
					ft_freestr(1, 1, temp, tab);
					break ;
				}
				ft_freestr(1, 1, temp, tab);
				j++;
			}
		}
	}
}

void	exec(t_args *args, int boolean, int fathorchild)
{
	char	*temp;
	char	**tab;
	int		i;

	i = -1;
	while (boolean && args->env[++i])
	{
		tab = ft_split(args->cmds[fathorchild], ' ');
		temp = ft_slash(args->env[i], tab[0]);
		execve(temp, tab, NULL);
		ft_freestr(1, 1, temp, tab);
	}
	if (!boolean)
	{
		tab = ft_split(args->cmds[fathorchild], ' ');
		execve(tab[0], tab, NULL);
		perror("slashback");
		ft_freetab((void **)tab);
	}
}

void	forking(t_args *args, int index)
{
	if (index == 0 || index == args->nbcmds - 1)
		close(args->fd[0]);
	if (index == 0) // cat
	{
		dup2(args->infile, STDIN_FILENO);
		close(args->infile);
	}
	else if (index == args->nbcmds - 1)
	{
		dup2(args->outfile, STDOUT_FILENO);
		close(args->outfile);
	}
	if (index != args->nbcmds - 1)
		dup2(args->fd[1], STDOUT_FILENO);
	if (index != 0)
	{
		dup2(args->prev_pipes, STDIN_FILENO);
		close(args->prev_pipes);
	}
}

void	preforking(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nbcmds)
	{
		pipe(args->fd);
		args->pid[i] = fork();
		if (args->pid[i] == 0)
		{
			forking(args, i);
			close(args->fd[1]);
			if (args->cmds[i][0] == '/')
				exec(args, 0, i);
			else
				exec(args, 1, i);
		}
		else
		{
			close(args->fd[1]);
			if (args->prev_pipes != -1)
				close(args->prev_pipes);
			args->prev_pipes = args->fd[0];
		}
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_args	*args;

	args = ft_calloc(sizeof(t_args), 1);
	if (!args)
		exit(1);
	args->prev_pipes = -1;
	if (!ft_getenv(ac, envp, args))
		return (1);
	init(args, av, ac);
	checkcmd(args);
	ft_printstruct(args, ac);
	preforking(args);
	wait_pids(args);
	freestruct(args);
}
