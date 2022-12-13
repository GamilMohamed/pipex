/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:10:35 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/13 00:01:51 by mgamil           ###   ########.fr       */
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
	char	*infile;
	char	**cmds;
	char	*outfile;
	char	**env;
	int		nbcmds;
	int		fd[2];
}			t_args;

/*	PRINT.C				*/
char		*ft_firstword(char *s);
void		ft_printstruct(t_args *args);
/*	MISC.C				*/
void		init(t_args *args, char **av, int ac);
int			freestruct(t_args *args);
void		ft_freestr(int n, int ntab, ...);
/*	UTILS.C				*/
char		*ft_slash(char *path, char *cmd);

#endif