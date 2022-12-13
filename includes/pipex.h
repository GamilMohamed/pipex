/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:10:35 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/13 22:38:20 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line.h"
# include "libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_args
{
	int		infile;
	char	**cmds;
	int		outfile;
	char	**env;
	int		nbcmds;
	int		prev_pipes;
	int		fd[2];
	pid_t	pid[1024];
}			t_args;

/*	PRINT.C				*/
void		ft_printstruct(t_args *args, int ac);
/*	MISC.C				*/
void		init(t_args *args, char **av, int ac);
int			freestruct(t_args *args);
void		ft_freestr(int n, int ntab, ...);
/*	UTILS.C				*/
char		*ft_slash(char *path, char *cmd);

#endif