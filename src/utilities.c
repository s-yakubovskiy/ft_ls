/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:43:41 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/05 15:20:46 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int is_dir(char *path)
{
	if (path == NULL)
		return (-1);
	struct stat fileStat;
	if (lstat(path,&fileStat) < 0)
		return (-1);
	return ((S_ISDIR(fileStat.st_mode)) ? 1 : 0);
}

void	swap_ls_item(t_ls_item *a, t_ls_item *b)
{
    t_ls_item c;

    c = *a;
    *a = *b;
    *b = c;
}

void print_all_cont(t_ls *ls)
{
	int i;
	int j;

	i = 0;
	while (ls->dir[i] != NULL)
	{
		j = 0;
		while (ls->dir[i]->cont[j] != NULL)
		{
			printf("%s\n", ls->dir[i]->cont[j]->name);
			j++;
		}
		i++;
	}
}

char	extended_param(char *filename)
{
	acl_t acl = NULL;
	acl_entry_t dummy;
	ssize_t xattr = 0;
	char chr;

	acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;

	if (xattr > 0)
		chr = '@';
	else if (acl != NULL)
		chr = '+';
	else
		chr = ' ';
	return (chr);
}

void	f_strcpy_time(t_ls_item *ls, const char *src)
{
	int		i;
	int 	j;

	i = 0;
	j = 0;
	while (src[i] && src[i] != ' ')
		ls->month[j++] = src[i++];
	ls->month[j] = '\0';
	while (src[i] && src[i] == ' ')
		i++;
	j = 0;
	while (src[i] && src[i] != ' ')
		ls->day[j++] = src[i++];
	ls->day[j] = '\0';
	while (src[i] && src[i] == ' ')
		i++;
	j = 0;
	while (src[i])
		ls->time[j++] = src[i++];
	ls->time[j] = '\0';
}

int		time_getter(t_ls_item *ls)
{
	char time_str[MAXC] = "";
	time_t now = time (NULL);
	struct stat sb;
	struct tm tmfile, tmnow;

	if (lstat(ls->path, &sb) == -1)
	{  /* validate stat of file */
		perror("stat");
		return 1;
	}

	localtime_r (&sb.st_mtime, &tmfile);    /* get struct tm for file */
	localtime_r (&now, &tmnow);             /* and now */

	if (tmfile.tm_year == tmnow.tm_year)
	{    /* compare year values  */
		strftime (time_str, sizeof (time_str), "%b %e %H:%M",
				  &tmfile);   /* if year is current output date/time  */
		f_strcpy_time(ls, time_str);
		/*printf ("permission 1 user group 12345 %s %s\n",
				time_str, ls->path);*/
	}
	else
	{ /* if year is not current, output time/year */
		strftime (time_str, sizeof (time_str), "%b %e  %Y",
				  &tmfile);
		f_strcpy_time(ls, time_str);
//		f_strcpy_time(ls->time, time_str);
		/*printf ("permission 1 user group 12345 %s %s\n",
				time_str, ls->path);*/
	}
	return (0);
}

int uid_guid_getter(t_ls_item *ls)
{
	struct stat sb;

	if (lstat(ls->path, &sb) == -1)
	{  /* validate stat of file */
		perror("stat");
		return 1;
	}
	struct passwd *pw = getpwuid(sb.st_uid);
	struct group  *gr = getgrgid(sb.st_gid);
	f_strcpy(ls->uid, pw->pw_name);
	f_strcpy(ls->guid, gr->gr_name);
	return (0);
}

long int total(t_ls_item *ls)
{
	struct stat sb;
	long long int a;

	if (lstat(ls->path, &sb) == -1)
	{
		perror("stat");
		return (1);
	}
	a = (long)sb.st_blocks;
	return (a);
}

int     get_terminal_width(void)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return (w.ws_col);
}
