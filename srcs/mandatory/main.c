/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:09:49 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/09 22:23:17 by mgamil           ###   ########.fr       */
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

void	exec(t_args *args, int boolean)
{
	char	*temp;
	char	**tab;
	int		i;

	i = -1;
	if (boolean)
		ft_printf("%Gdoesnt start with backslash%0\n");
	while (boolean && args->env[++i])
	{
		tab = ft_split(args->cmds[0], ' ');
		temp = ft_slash(args->env[i], tab[0]);
		execve(temp, tab, NULL);
		// ft_printf("access=%i\n", access(temp, F_OK));
		ft_freestr(1, 1, temp, tab);
	}
	if (!boolean)
	{
		ft_printf("%Mstart with backslash%0\n");
		tab = ft_split(args->cmds[0], ' ');
		execve(tab[0], tab, NULL);
		perror("slashback");
		ft_freetab((void **)tab);
	}
	// errno vaut 2 si tout est faux
}

void	forking(t_args *args)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) // gosse
	{
		ft_printf("%B\t\tGOSSE\t\t\n");
		ft_printf("PID:%d\n", getpid());
		ft_printf("%RDARON PID:%d%0\n", getppid());
		if (args->cmds[0][0] != '/')
			exec(args, 1);
		else
			exec(args, 0);
	}
	else // daron
	{
		waitpid(pid, NULL, 0);
		ft_printf("PID:%d\n%0", getpid());
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_args	*args;

	args = ft_calloc(sizeof(t_args), 1);
	if (!args)
		exit(1);
	if (!ft_getenv(ac, envp, args))
		return (1);
	init(args, av);
	ft_printstruct(args);
	forking(args);
	freestruct(args);
}
