/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 20:04:56 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/02 02:35:25 by rpapagna         ###   ########.fr       */
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
# include <time.h>
# include <pwd.h>
# include <grp.h>

/*
**STRUCTURES
*/

typedef	struct			s_file
{
	char				*path;
	char				*name;
	char				*full_path;
	struct s_file		*next;
}						t_file;

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
