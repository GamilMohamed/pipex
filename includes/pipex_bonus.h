/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:10:35 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/18 05:27:58 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <sys/fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_args
{
	int		ac;
	char	**av;
	int		in;
	char	**cmds;
	int		out;
	char	**env;
	int		nbcmds;
	int		prev_pipes;
	int		fd[2];
	pid_t	pid[1024];
	int		heredoc;
	char	*delimiter;
	int		heredocfd;
}			t_args;

/*	MAIN.C				*/
void		ft_getenv(int ac, char **envp, t_args *args);
int			get_here_doc(t_args *args);
/*	FORK.C				*/
void		exec(t_args *args, int boolean, int index);
void		forking(t_args *args, int index);
void		preforking(t_args *args);
/*	MISC.C				*/
void		init(t_args *args, char **av, int ac);
int			freestruct(t_args *args);
void		dupnclose(int fd, int std);
void		ft_error_exit(char *s, t_args *args, int last);
void		wait_pids(t_args *args);
/*	UTILS.C				*/
char		*ft_slash(char *path, char *cmd);
void		checkaccess(char *cmd, int boolean);

#endif