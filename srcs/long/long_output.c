/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 17:56:07 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 04:22:55 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

static char		*block_char(t_file *paths, char *p, int *l, int type)
{
	char			*tmp;
	char			second[595];
	char			*date;
	struct passwd	*usr;
	struct group	*grp;

	usr = getpwuid(paths->info.st_uid);
	grp = getgrgid(paths->info.st_gid);
	date = get_time(paths->info.st_mtimespec, "");
	ft_bzero(second, 595);
	tmp = second;
	ft_sprintf(second, "%s ", p);
	ft_sprintf(&second[LEN(second)], "%-*s  ", l[1], usr->pw_name);
	ft_sprintf(&second[LEN(second)], "%-*s  ", l[2], grp->gr_name);
	ft_sprintf(&second[LEN(second)], "%3ld, ", major(paths->info.st_rdev));
	minor(paths->info.st_rdev) > 999 ? ft_sprintf(&second[LEN(second)], "%#.8x",
		minor(paths->info.st_rdev)) : ft_sprintf(&second[LEN(second)], "%3ld",
		minor(paths->info.st_rdev));
	if (!type)
		ft_sprintf(&second[LEN(second)], " %s %s", date, paths->name);
	else
		ft_sprintf(&second[LEN(second)], " %s %s%s%s", date,
			define_color(paths), paths->name, NOCOL);
	return (tmp);
}

static char		*links(t_file *paths, char *p, int *l, int type)
{
	char			*tmp;
	char			third[850];
	char			*date;
	struct passwd	*usr;
	struct group	*grp;

	usr = getpwuid(paths->info.st_uid);
	grp = getgrgid(paths->info.st_gid);
	date = get_time(paths->info.st_mtimespec, "");
	ft_bzero(third, 850);
	tmp = third;
	ft_sprintf(third, "%s ", p);
	ft_sprintf(&third[LEN(third)], "%-*s  ", l[1], usr->pw_name);
	ft_sprintf(&third[LEN(third)], "%-*s  ", l[2], grp->gr_name);
	ft_sprintf(&third[LEN(third)], "%*ld", l[3], paths->info.st_size);
	if (!type)
		ft_sprintf(&third[LEN(third)], " %s %s -> ", date, paths->name);
	else
		ft_sprintf(&third[LEN(third)], " %s %s%s%s -> ", date,
			define_color(paths), paths->name, NOCOL);
	readlink(paths->full_path, &third[596], 255);
	ft_sprintf(&third[LEN(third)], "%s", &third[596]);
	return (tmp);
}

static char		*reg_dir(t_file *paths, char *p, int *l, int type)
{
	char			*tmp;
	char			second[595];
	char			*date;
	struct passwd	*usr;
	struct group	*grp;

	usr = getpwuid(paths->info.st_uid);
	grp = getgrgid(paths->info.st_gid);
	date = get_time(paths->info.st_mtimespec, "");
	ft_bzero(second, 595);
	tmp = second;
	ft_sprintf(second, "%s ", p);
	ft_sprintf(&second[LEN(second)], "%-*s  ", l[1], usr->pw_name);
	ft_sprintf(&second[LEN(second)], "%-*s  ", l[2], grp->gr_name);
	ft_sprintf(&second[LEN(second)], "%*ld", l[3], paths->info.st_size);
	if (!type)
		ft_sprintf(&second[LEN(second)], " %s %s", date, paths->name);
	else
		ft_sprintf(&second[LEN(second)], " %s %s%s%s", date,
			define_color(paths), paths->name, WHT);
	return (tmp);
}

static char		*first(char *p, int link_len, t_file *paths, mode_t st_mode)
{
	char	*tmp;
	char	first[16];
	char	*link;

	ft_bzero(first, 16);
	first[0] = get_type(st_mode);
	first[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	first[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	first[3] = get_x1(paths, paths->info.st_mode);
	first[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	first[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	first[6] = get_x2(paths, paths->info.st_mode);
	first[7] = (st_mode & S_IROTH) ? 'r' : '-';
	first[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	first[9] = get_x3(paths, paths->info.st_mode);
	link = ft_itoa(paths->info.st_nlink);
	ft_sprintf(&first[10], "%c %*s", listxattr(paths->name, p, 0,
		XATTR_NOFOLLOW) > 0 ? '@' : ' ', link_len, link);
	free(link);
	tmp = ft_strdup(first);
	p = ft_strcpy(p, tmp);
	free(tmp);
	return (p);
}

char			*long_out(int *li, t_file *paths, char *p, int type)
{
	char	buf[1024];

	ft_bzero(buf, 1024);
	p = buf;
	p = first(p, li[0], paths, paths->info.st_mode);
	if (p[0] == '-' || p[0] == 'd')
		p = reg_dir(paths, p, li, type);
	else if (p[0] == 'l')
		p = links(paths, p, li, type);
	else if (p[0] == 'b' || p[0] == 'c')
		p = block_char(paths, p, li, type);
	return (p);
}
