/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 20:04:56 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 02:15:41 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define IS_FLAG(x) (x == 'R' || x == 'a' || x == 'l' || x == 'r' || x == 't')
# define ISNT_FLAG(x) (x != 'R' && x != 'a' && x != 'l' && x != 'r' && x != 't')
# define IF_BREAK(x) if(x) {break ;}

/*
**STRUCTURES
*/

typedef	struct		s_file
{
	int				index;
	char			*path;
	char			*name;
	char			*full_path;
	struct s_file	*next;
}					t_file;

char				get_flags(char **av, char mask, int i, int j);
t_file				*get_dirs(char **av, int i, int j);
t_file				*t_fileinit(char *param);
t_file				*t_filedel(t_file *file);

int					ft_ls(t_file *paths, char flags);

/*
**	MANDATORY FLAGS
**	-R	Recursively list subdirectories encountered.
**	-a	Include directory entries whose names begin with a dot (.).
**	-l	List in long format. If the output is to a terminal, a total sum
**		for all the file sizes is output on a line before the long listing.
**	-r	Reverse the order of the sort to get reverse lexicographical
**		order or the oldest entries first
**	-t	Sort by time modified (most recently modified first) before sorting
**		the operands by lexicographical order
**	OPTIONS FLAGS
**	-f	Output is not sorted. This option turns on the -a option.
*/

#endif
