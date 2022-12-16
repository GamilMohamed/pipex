/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:09:49 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/16 23:37:01 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_getenv(int ac, char **envp, t_args *args)
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
		ft_freestr(1, 1, args, (void **)args->env);
		exit(1);
	}
	return (0);
}

void	exec(t_args *args, int boolean, int index)
{
	char	*temp;
	char	**tab;
	int		i;

	i = -1;
	tab = ft_split(args->cmds[index], ' ');
	while (boolean && args->env[++i])
	{
		temp = ft_slash(args->env[i], tab[0]);
		if (access(temp, F_OK | X_OK) != -1)
			execve(temp, tab, NULL);
		free(temp);
	}
	if (!boolean)
		if (access(tab[0], F_OK | X_OK) == 0)
			execve(tab[0], tab, NULL);
	if (boolean)
		ft_printf("%s: command not found\n", tab[0]);
	else
		ft_printf("bash: %s: No such file or directory\n", tab[0]);
	ft_freetab((void **)tab);
	freestruct(args);
}

void	forking(t_args *args, int index)
{
	if (index == 0)
	{
		args->in = open(args->av[1], O_RDONLY);
		if (args->in == -1)
			ft_error_exit(args->av[1], args, 0);
		dupnclose(args->in, STDIN_FILENO);
	}
	else if (index == args->nbcmds - 1)
	{
		args->out = open(args->av[args->ac - 1],
				O_WRONLY | args->heredoc | O_CREAT, 0666);
		if (args->out == -1)
			ft_error_exit(args->av[args->ac - 1], args, 1);
		dupnclose(args->out, STDOUT_FILENO);
	}
	if (index != args->nbcmds - 1)
		dup2(args->fd[1], STDOUT_FILENO);
	if (index != 0)
		dupnclose(args->prev_pipes, STDIN_FILENO);
	close(args->fd[1]);
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
			close(args->fd[0]);
			if (ft_strchr(args->cmds[i], '/'))
				exec(args, 0, i);
			else
				exec(args, 1, i);
			exit(1);
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

	if (ac != 5)
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
	freestruct(args);
	return (1);
}

// ft_printstruct(args, ac);