/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 20:04:56 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/02 19:12:08 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

/*
**	--------------------------------
**				MACROS
**	--------------------------------
*/

# define USAGE "usage: ./ft_ls [-1Raflrt] [file ...]\n"
# define MALLOC_ERR "malloc error, yo\n"
# define IS_FLAG(x) (x == '1' || x == 'R' || x == 'a' || x == 'f')
# define IS_FLAG2(x) (x == 'l' || x == 'r' || x == 't')
# define NOT_FLAG(x) (x != '1' && x != 'R' && x != 'a' && x != 'f')
# define NOT_FLAG2(x) (x != 'l' && x != 'r' && x != 't')
# define CURRENT_DIR(x) (x[0] == '.' && x[1] == '\0')
# define PARENT_DIR(x) (x[0] == '.' && x[1] == '.' && x[2] == '\0')
# define IF_BREAK(x) if(x) {break ;}
# define IF_THEN_CONTINUE(x, y) if(x) {(y); continue ;}
# define Y_DIR(t_file) S_ISDIR(t_file->info.st_mode)
# define N_DIR(t_file) !S_ISDIR(t_file->info.st_mode)

/*
**	--------------------------------
**				STRUCTS
**	---------------------------------
*/

typedef	struct		s_file
{
	int				index;
	char			*path;
	char			*name;
	char			*full_path;
	struct stat		info;
	struct dirent	*entry;
	struct s_file	*next;
}					t_file;

/*
**	--------------------------------
**				GETTERS
**	--------------------------------
*/

char				get_flags(char **av, char mask, int i, int j);
t_file				*get_dirs(char **av, int i, int j);

/*
**	--------------------------------
**				T_FILE
**	--------------------------------
*/

t_file				*t_fileinit(char *param);
t_file				*t_filedel(t_file *file);
int					t_fileadd(t_file **apath, char *dir);
void				t_filedelone(t_file **apath, int index);

/*
**	--------------------------------
**				DISPLAY
**	--------------------------------
*/

int					ft_ls(t_file *paths, char flags);

/*
**	--------------------------------
**				SORT
**	--------------------------------
*/

void				t_file_mergesort(t_file **apath, char flags, int type);

/*
**	--------------------------------
**			MANDATORY FLAGS
**	--------------------------------
**	-R	Recursively list subdirectories encountered.
**	-a	Include directory entries whose names begin with a dot (.).
**	-l	List in long format. If the output is to a terminal, a total sum
**		for all the file sizes is output on a line before the long listing.
**	-r	Reverse the order of the sort to get reverse lexicographical
**		order or the oldest entries first
**	-t	Sort by time modified (most recently modified first) before sorting
**		the operands by lexicographical order
**	OPTIONAL FLAGS
**	-f	Output is not sorted. This option turns on the -a option.
**	-1	(The numeric digit 'one'.) Force output to be one entry per line.
**		This is the default when output is not to a terminal.
*/

/*
**	-----------------------
**			ARCHIVED
**	-----------------------
*/

void				sort_paths(t_file **paths);
int					dash_onef(t_file *paths);
t_file				*t_filepushfront(t_file **apath, int index);
#endif
