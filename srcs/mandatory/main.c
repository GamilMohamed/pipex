/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:09:49 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/13 00:24:48 by mgamil           ###   ########.fr       */
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

void	exec(t_args *args, int boolean, int fathorchild)
{
	char	*temp;
	char	**tab;
	int		i;

	i = -1;
	if (boolean)
		ft_printf("%Gdoesnt start with backslash%0\n");
	while (boolean && args->env[++i])
	{
		tab = ft_split(args->cmds[fathorchild], ' ');
		temp = ft_slash(args->env[i], tab[0]);
		execve(temp, tab, NULL);
		// ft_printf("access=%i\n", access(temp, F_OK));
		ft_freestr(1, 1, temp, tab);
	}
	if (!boolean)
	{
		ft_printf("%Mstart with backslash%0\n");
		tab = ft_split(args->cmds[fathorchild], ' ');
		execve(tab[0], tab, NULL);
		perror("slashback");
		ft_freetab((void **)tab);
	}
	// errno vaut 2 si tout est faux
}

void	forking(t_args *args)
{
	pid_t	pid;
	pid_t	newpid;

	pipe(args->fd);
	pid = fork();
	if (pid == -1) // gosse
	{
		ft_printf("failed\n");
		exit(1);
	}
	if (pid == 0) // gosse
	{
		ft_printf("%B\t\tGOSSE\t\t\n");
		ft_printf("PID:%d\n", getpid());
		ft_printf("%RDARON PID:%d%0\n", getppid());
		dup2(args->fd[1], STDOUT_FILENO);
		close(args->fd[0]);
		close(args->fd[1]);
		if (args->cmds[0][0] != '/')
			exec(args, 1, 0);
		else
			exec(args, 0, 0);
	}
	newpid = fork();
	if (newpid == -1) // gosse
	{
		ft_printf("failed\n");
		exit(1);
	}
	if (newpid == 0) // daron
	{
		ft_printf("PID:%d\n%0", getpid());
		dup2(args->fd[0], STDIN_FILENO);
		close(args->fd[0]);
		close(args->fd[1]);
		if (args->cmds[1][0] != '/')
			exec(args, 1, 1);
		else
			exec(args, 0, 1);
	}
	close(args->fd[0]);
	close(args->fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(newpid, NULL, 0);
}

// void forking(t_args *args)
// {

// }

void	checkcmd(t_args *args)
{
	char	**tab;
	char	*temp;
	int		i;
	int		j;
	int		ok;

	i = -1;
	ok = 1;
	while (++i < args->nbcmds)
	{
		if (args->cmds[i][0] == '/')
		{
			tab = ft_split(args->cmds[i], ' ');
			if (access(tab[0], F_OK) != 0)
			{
				ft_printf("bash: %s: No such file or directory\n",
							tab[0]);
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
	// if (args->cmdss[1][0] != '/')
	// {
	// 	exec(args, 1, 1);
	// }
	// else
	// {
	// 	while (access() != -1)
	// 	{
	// 		tab = ft_split(args->cmds[i], ' ');
	// 		temp = ft_slash(args->env[i], tab[0]);
	// 	}
	// 	exec(args, 0, 1);
	// }
}

int	main(int ac, char *av[], char *envp[])
{
	t_args	*args;

	args = ft_calloc(sizeof(t_args), 1);
	if (!args)
		exit(1);
	args->nbcmds = ac - 3;
	if (!ft_getenv(ac, envp, args))
		return (1);
	init(args, av, ac);
	checkcmd(args);
	ft_printstruct(args);
	forking(args);
	freestruct(args);
}
