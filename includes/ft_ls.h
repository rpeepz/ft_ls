/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 20:04:56 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/06 15:37:15 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <sys/xattr.h>
# include <sys/ioctl.h>
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
# define IS_FLAG2(x) (x == 'G' || x == 'l' || x == 'r' || x == 't')
# define NOT_FLAG(x) (x != '1' && x != 'R' && x != 'a' && x != 'f')
# define NOT_FLAG2(x) (x != 'G' && x != 'l' && x != 'r' && x != 't')
# define CURRENT_DIR(x) (x[0] == '.' && x[1] == '\0')
# define PARENT_DIR(x) (x[0] == '.' && x[1] == '.' && x[2] == '\0')
# define IF_BREAK(x) if(x) {break ;}
# define IF_THEN_CONTINUE(x, y) if(x) {(y); continue ;}
# define G_PATH(buf, path, name) ft_strncpy(buf, path, LEN(path) - LEN(name) -1)
# define Y_DIR(t_file) S_ISDIR(t_file->info.st_mode)
# define N_DIR(t_file) !S_ISDIR(t_file->info.st_mode)
# define Y_USX(m) (m->info.st_mode & S_IXUSR)

/*
**	(COLORS)
*/

# define NOCOL "\e[;37m"

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"

# define URED "\e[4;31m"
# define UGRN "\e[4;32m"
# define UYEL "\e[4;33m"
# define UMAG "\e[4;35m"
# define UCYN "\e[4;36m"
# define UWHT "\e[4;37m"

/*
**	(PERMISSIONS)
*/

# define U_EXE(m) (((m) & S_IRWXU) == S_IXUSR)
# define G_EXE(m) (((m) & S_IRWXG) == S_IXGRP)
# define O_EXE(m) (((m) & S_IRWXO) == S_IXOTH)
# define Y_EXE(m) U_EXE(m) || G_EXE(m) || O_EXE(m)

/*
**	--------------------------------
**				STRUCTS
**	---------------------------------
*/

typedef	struct		s_file
{
	int				index;
	char			*name;
	char			*full_path;
	struct stat		info;
	struct s_file	*next;
}					t_file;

/*
**	--------------------------------
**				GETTERS
**	--------------------------------
*/

char				get_flags(char **av, char mask, int i, int j);
t_file				*get_dirs(char **av, int i, int j);
int					get_contents(t_file **apath, t_file *path, DIR **dir);
int					get_longest(t_file *paths, int type);

/*
**	--------------------------------
**				T_FILE
**	--------------------------------
*/

t_file				*t_fileinit(char *param, char *fullpath, int type);
t_file				*t_filedel(t_file **apath);
int					t_fileadd(t_file **apath, char *param, char *full, int typ);
void				t_filedelone(t_file **apath, int index);

/*
**	--------------------------------
**				DISPLAY
**	--------------------------------
*/

int					ft_ls(t_file *paths, char flags);
int					print_contents(t_file *paths, char flags, int type);
int					recurse(t_file *paths, char flags);
int					print_first_files(t_file **apath, char flags, int longest);

/*
**	(COLOR)
*/

int					ls_color(t_file *paths, char flags);
int					color_contents(t_file *paths, char flags, int type);
int					recurse_color(t_file *paths, char flags);
int					color_first_files(t_file **apath, char flags, int length);

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
