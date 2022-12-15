/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:09:49 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/15 18:43:29 by mgamil           ###   ########.fr       */
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

void	checkaccess(char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		ft_printf("bash: %s: Noa such file or directory\n", cmd);
		return ;
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_printf("bash: %s: Permission denied\n", cmd);
		return ;
	}
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
		if (args->env[i + 1] == NULL)
			checkaccess(tab[0]);
		// ft_printf("(%d)about to exec\n", index);
		execve(temp, tab, NULL);
		// ft_printf("(%d)failed exec\n", index);
		free(temp);
	}
	if (!boolean)
	{
		checkaccess(tab[0]);
		execve(tab[0], tab, NULL);
		perror("slashback");
	}
	ft_freetab((void **)tab);
}

// void	forking(t_args *args, int index, char **av)
// {
// 	(void)av;
// 	// if (index == 0 || index == args->nbcmds - 1)
// 	if (index == 0)
// 	{
// 		// args->infile = open(av[index], O_RDONLY);
// 		// ft_printf("(%d)INFILE EEEE%i\n", index, args->infile);
// 		dup2(args->infile, STDIN_FILENO);
// 		close(args->infile);
// 	}
// 	else if (index == args->nbcmds - 1)
// 	{
// 		// args->outfile = open(av[args->nbcmds - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 		// ft_printf("(%d)OUTFILE EEE %i\n", index, args->outfile);
// 		dup2(args->outfile, STDOUT_FILENO);
// 		close(args->outfile);
// 	}
// 	if (index != args->nbcmds - 1)
// 		dup2(args->fd[1], STDOUT_FILENO);
// 	if (index != 0)
// 	{
// 		dup2(args->prev_pipes, STDIN_FILENO);
// 		close(args->prev_pipes);
// 	}
// 	close(args->fd[0]);
// }

void	forking(t_args *args, int index)
{
	if (index == 0) // cat
	{
		close(args->fd[0]);
		dup2(args->infile, STDIN_FILENO);
		dup2(args->fd[1], STDOUT_FILENO);
		close(args->infile);
	}
	else if (index == args->nbcmds - 1) // wc -l
	{
		dup2(args->prev_pipes, STDIN_FILENO);
		dup2(args->outfile, STDOUT_FILENO);
		close(args->outfile);
		close(args->prev_pipes);
		close(args->fd[0]);
	}
	else
	{
		dup2(args->prev_pipes, STDIN_FILENO);
		dup2(args->fd[1], STDOUT_FILENO);
		close(args->prev_pipes);
		close(args->fd[0]);
	}
}
void	preforking(t_args *args, char **av)
{
	int	i;

	i = -1;
	(void)av;
	while (++i < args->nbcmds)
	{
		pipe(args->fd);
		args->pid[i] = fork();
		if (args->pid[i] == 0)
		{
			forking(args, i);
			close(args->fd[1]);
			if (ft_strchr(args->cmds[i], '/'))
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

	if (!envp[0])
		return (1);
	args = ft_calloc(sizeof(t_args), 1);
	if (!args)
		exit(1);
	args->prev_pipes = -1;
	if (!ft_getenv(ac, envp, args))
		return (1);
	init(args, av, ac);
	// checkcmd(args);
	preforking(args, av);
	wait_pids(args);
	// ft_printstruct(args, ac);
	// while (wait(NULL) > 0)
	// ;
	close(args->outfile);
	close(args->fd[0]);
	close(args->infile);
	freestruct(args);
}
