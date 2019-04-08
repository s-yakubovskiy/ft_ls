/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:00:53 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/05 15:20:46 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	arg_checker(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] != 'l' && argv[i][j] != 'R' && argv[i][j] != 'a'
				  && argv[i][j] != 'r' && argv[i][j] != 't' && argv[i][j] != '1')
			{
				ft_putstr("ls: illegal option -- ");
				ft_putchar(argv[i][j]);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	Check_On_Consist(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (-1);
}

static int ft_get_count_flags(int argc, char **argv)
{
	int a;
	int i;
	int j;

	i = 1;
	a = 0;
	while (i < argc && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			a++;
			j++;
		}
		i++;
	}
	return (a);
}

static char	*Ft_Get_Str_Options(int argc, char **argv)
{
	int		i;
	int		j;
	int 	a;
	char	*str;

	i = 1;
	a = ft_get_count_flags(argc, argv);
	str = (char *)malloc(sizeof(char) * a);
	str[a] = '\0';
	while (i < argc && argv[i][0] == '-')
	{
		j = 1;
		a = 0;
		while (argv[i][j])
		{
			if (Check_On_Consist(str, argv[i][j]) == -1)
			{
				str[a++] = argv[i][j];
				str[a] = '\0';
			}
			j++;
		}
		i++;
	}
	return (str);
}

static int	Ft_Bitwise_Shift(int flag, int a)
{
	flag = flag >> a;
	flag = flag + 1;
	flag = flag << a;
	return (flag);
}

static int	Ft_Get_Bit(int argc, char **argv)
{
	int		flag;
	char    *str;

	flag = 0;
	str = Ft_Get_Str_Options(argc, argv);
	if (Check_On_Consist(str, '1') == 1)
		flag = Ft_Bitwise_Shift(flag, 5);
	if (Check_On_Consist(str, 't') == 1)
		flag = Ft_Bitwise_Shift(flag, 4);
	if (Check_On_Consist(str, 'r') == 1)
		flag = Ft_Bitwise_Shift(flag, 3);
	if (Check_On_Consist(str, 'a') == 1)
		flag = Ft_Bitwise_Shift(flag, 2);
	if (Check_On_Consist(str, 'R') == 1)
		flag = Ft_Bitwise_Shift(flag, 1);
	if (Check_On_Consist(str, 'l') == 1)
		flag = Ft_Bitwise_Shift(flag, 0);
	return (flag);
}

void	f_strcpy(char *dst, const char *src)
{
	int		i;
	int     j;

	i = -1;
	j = 0;
	while(dst[j] != '\0')
	    j++;
	while (src[++i])
		dst[j++] = src[i];
	dst[j] = '\0';
}

static void	path_cpy(char *dst, const char *src, t_ls *ls)
{
	int		i;
	int 	j;

	i = -1;
	j = 0;
	while (dst[j] != '\0')
		j++;
	while (src[++i])
		dst[j++] = src[i];
	dst[j] = '\0';
	if (is_dir(dst) && dst[j - 1] != '/')
	{
		dst[j] = '/';
		dst[j + 1] = '\0';
	}
//
//	dst[j] = '/';
//	dst[j + 1] = '\0';
}

//static void	full_pathname(char *dst, char)

void	grab_ls(t_ls *ls, int i)
{
	int j;
	DIR				*d;
	struct dirent	*dir;
	j = 0;

	//ls->dir[i]->cont[0] = create_ls_item(0);
	d = opendir(ls->dir[i]->name);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if ((a_FLAG) == 0 && dir->d_name[0] != '.')
			{
				ls->dir[i]->cont[j] = create_ls_item(0);
				f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
				f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
				path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name, ls);
				//ls->dir[i]->cont[++j] = create_ls_item(0);
				j++;
			}
			else if (a_FLAG)
			{
				ls->dir[i]->cont[j] = create_ls_item(0);
				f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
				f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
				path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name, ls);
				//ls->dir[i]->cont[++j] = create_ls_item(0);
				j++;
			}
		}
		closedir(d);
	}
	ls->dir[i]->cont[j] = 0;
	//free_item_ls     надо последний елемент
}

static int ft_check_open_dir(char *tmp)
{
//	DIR				*d;
//	struct dirent	*dir;

	if (opendir(tmp) == NULL)
	{
		printf("%s: %s: No such file or directory\n", tmp, tmp);
		return (-1);
	}
	return (1);
}

static int ft_check_open_file(char *tmp)
{
	if (fopen(tmp, "r") == NULL)
	{
		printf("%s: %s: No such file or directory\n", tmp, tmp);
		return (-1);
	}
	return (1);
}

void 	get_arguments(int argc, char *argv[], t_ls *ls)
{
	int i;
	int j;
	int k;
	char *tmp;

	i = 1;
	tmp = malloc(sizeof(char) * 256);
//	ls->dir[ls->num_dir] = create_ls_item(1);
//	ls->file[ls->num_file] = create_ls_item(0);
    if (argc == 1)
    {
        f_strcpy(tmp, ".");
        if (ft_check_open_dir(tmp) == 1)
        {
            ls->dir[(ls->num_dir)] = create_ls_item(1);
            f_strcpy(ls->dir[ls->num_dir]->name, tmp);
            path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
            //ls->dir[++(ls->num_dir)] = create_ls_item(1);
            ++(ls->num_dir);
        }
        return ;
    }
	while (i < argc)
	{
		if (argv[i][0] == '-')
			i++;
		else
		{
			j = 0;
			while(ISSPACE(argv[i][j]))
				j++;
			k = 0;
			if (argv[i][j] == '\0')
            {
                f_strcpy(tmp, ".");
                if (ft_check_open_dir(tmp) == 1)
                {
                    ls->dir[(ls->num_dir)] = create_ls_item(1);
                    f_strcpy(ls->dir[ls->num_dir]->name, tmp);
                    path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
                    //ls->dir[++(ls->num_dir)] = create_ls_item(1);
                    ++(ls->num_dir);
                }
                return ;
            }

			while (argv[i][j] != '\0' && argv[i][j] != ' ')
			{
				tmp[k] = argv[i][j];
				j++;
				k++;
			}
			tmp[k] = '\0';
			if (is_dir(tmp) == 1)
			{
				if (ft_check_open_dir(tmp) == 1)
				{
					ls->dir[(ls->num_dir)] = create_ls_item(1);
					f_strcpy(ls->dir[ls->num_dir]->name, tmp);
					path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
					//ls->dir[++(ls->num_dir)] = create_ls_item(1);
					++(ls->num_dir);
				}
			}
			else
			{
				if (ft_check_open_file(tmp) == 1)
				{
					ls->file[(ls->num_file)] = create_ls_item(0);
					f_strcpy(ls->file[ls->num_file]->name, tmp);
					path_cpy(ls->file[ls->num_file]->path, tmp, ls);
					//ls->file[++(ls->num_file)] = create_ls_item(0);
					++(ls->num_file);
				}
			}
			ft_bzero(tmp, (size_t)k);
			i++;
		}
	}
}

void	get_contents(t_ls *ls)
{
	int i;

	i = 0;
	if (ls->dir[0] != NULL)
	{
		while (ls->dir[i] != NULL)
		{
            grab_ls(ls, i);
			i++;
		}
	}
}

static void body_ls(t_ls *ls)
{
	int i;
	int j;

	i = 0;
	if (ls->file[0] != 0)
	{
		while (ls->file[i] != 0)
		{
			printf("%s\n", ls->file[i++]->name);
		}
	}
	if (ls->dir[0] != 0)
	{
		i = 0;
		while(ls->dir[i])
		{
			j = 0;
			while (ls->dir[i]->cont[j])
			{
				printf("%-16s", ls->dir[i]->cont[j]->name);
				j++;
			}
			i++;
		}

	}
}

static	int perm_getter(t_ls_item *ls)
{
	struct stat fileStat;
    char link_read[255];
    ssize_t bytes_read;

	if (lstat(ls->path, &fileStat) < 0)
		return (1);

	ls->perms[0] = (char)((S_ISDIR(fileStat.st_mode)) ? 'd' : '-');
	ls->perms[1] = (char)((fileStat.st_mode & S_IRUSR) ? 'r' : '-');
	ls->perms[2] = (char)((fileStat.st_mode & S_IWUSR) ? 'w' : '-');
	ls->perms[3] = (char)((fileStat.st_mode & S_IXUSR) ? 'x' : '-');
	ls->perms[4] = (char)((fileStat.st_mode & S_IRGRP) ? 'r' : '-');
	ls->perms[5] = (char)((fileStat.st_mode & S_IWGRP) ? 'w' : '-');
	ls->perms[6] = (char)((fileStat.st_mode & S_IXGRP) ? 'x' : '-');
	ls->perms[7] = (char)((fileStat.st_mode & S_IROTH) ? 'r' : '-');
	ls->perms[8] = (char)((fileStat.st_mode & S_IWOTH) ? 'w' : '-');
	ls->perms[9] = (char)((fileStat.st_mode & S_ISVTX) ? 't' : '-');
	if (ls->perms[9] == '-')
		ls->perms[9] = (char)((fileStat.st_mode & S_IXOTH) ? 'x' : '-');
	ls->perms[10] = extended_param(ls->path);
	if (ls->perms[10] != '@' && ls->perms[10] != '+')
		ls->perms[10] = '\0';
	ls->perms[11] = '\0';
    if(S_ISLNK(fileStat.st_mode))
    {
//		printf("%s ",ls->path );
        bytes_read = readlink(ls->path, link_read, 254);
        link_read[bytes_read] = '\0';
        f_strcpy(ls->name, " -> ");
        f_strcpy(ls->name, link_read);
//		printf("-> %s\n", link_read);
    }
//	display_contents(ls);
	return (0);
}

int	perm_maker(t_ls *ls)
{
	int i;
	int j;
	struct stat fileStat;


	i = 0;
	while(ls->dir[i] != NULL)
	{
		ls->dir[i]->st_blocks = 0;
		if (lstat(ls->dir[i]->path, &fileStat) < 0)
			return (1);
		perm_getter(ls->dir[i]);
		ls->dir[i]->links = fileStat.st_nlink;
		ls->dir[i]->file_size = fileStat.st_size;
		j = 0;
		while (ls->dir[i]->cont[j] != NULL)
		{
			if (lstat(ls->dir[i]->cont[j]->path, &fileStat) < 0)
				return (1);
			perm_getter(ls->dir[i]->cont[j]);
			ls->dir[i]->cont[j]->links = fileStat.st_nlink;
			ls->dir[i]->cont[j]->file_size = fileStat.st_size;
			time_getter(ls->dir[i]->cont[j]);
			uid_guid_getter(ls->dir[i]->cont[j]);
			if (is_dir(ls->dir[i]->cont[j]->path) == 0)
				ls->dir[i]->st_blocks += total(ls->dir[i]->cont[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while(ls->file[i] != NULL)
	{
		ls->file[i]->st_blocks = 0;
		if (lstat(ls->file[i]->path, &fileStat) < 0)
			return (1);
		perm_getter(ls->file[i]);
		ls->file[i]->links = fileStat.st_nlink;
		ls->file[i]->file_size = fileStat.st_size;
		time_getter(ls->file[i]);
		uid_guid_getter(ls->file[i]);
		ls->file[i]->st_blocks = total(ls->file[i]);
		i++;
	}
	return (0);
}

static int ft_find_max_len(t_ls_item **ls)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (ls[i])
	{
		if (ft_strlen(ls[i]->name) > a)
			a = ft_strlen(ls[i]->name);
		i++;
	}
	return (a);
}

static void	ft_print_dir_file(t_ls_item **ls, int a, int len)
{
	int i;
	int j;
	int m;
	int br;
	int ws;

	i = 0;
	br = 0;
	ws = get_terminal_width();
	if (a * len > ws)
    {
	    len % 2 != 0 ? len += 1 : len;
	    br = len / 2;
//	    printf("\nbr %d ws: %d \n", br, ws);
    }
//	printf("\nbreaker %d len: %d ws: %d a: %d\n ", br, len, ws, a);
	while (ls[i])
	{
		m = a - (int)ft_strlen(ls[i]->name);
		printf("%s", ls[i]->name);
		if (ls[i + 1] != NULL)
		{
			j = -1;
			while (++j < m)
				printf("%c", ' ');
		}
		i++;
		if (br != 0 && ws != 0 && i % br == 0)
		    printf("\n");
	}
    printf("\n");
}

static int ft_print_anti_l(t_ls	*ls)
{
	int a;
	int j;
	int len;

	j = 0;
	while (ls->dir[j])
	{
        len = cont_len(ls->dir[j]);
	    a = (ft_find_max_len(ls->dir[j]->cont) / 8 + 1) * 8;
		ft_print_dir_file(ls->dir[j]->cont, a, len);
		j++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_ls		*ls;

	if (arg_checker(argc, argv) == -1)
	{
			ft_putendl("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] "
					   "[file ...]\n");
			return (0);
	}
	ls = create_ls_main();
	ls->flag = Ft_Get_Bit(argc, argv);
	get_arguments(argc, argv, ls);
	get_contents(ls);
	if (l_FLAG)
	{
		perm_maker(ls);
	}
	else if (one_FLAG)
	{
		print_ls_one_flag(ls);
	}
	else
	{
//		ft_find_max_len(ls->dir);
        ft_print_anti_l(ls);
//        printf ("cont len: %d\n", cont_len(ls->dir[0]));
	}
	get_terminal_width();


//	printf("%s\n", ls->dir[0]->cont[0]->name);
//	printf("%s\n", ls->dir[0]->cont[1]->name);
//	printf("%s\n", ls->dir[0]->cont[15]->name);
//	printf("%s\n", ls->dir[0]->cont[16]->name);
//	printf("%s\n", ls->dir[0]->cont[17]->name);
//	printf("%s\n", ls->dir[0]->cont[18]->name);
//	printf("%s\n", ls->dir[0]->cont[19]->name);
//	display_contents("/sbin/mount_ftp");

}



