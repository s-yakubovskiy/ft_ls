/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:00:53 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/02 14:27:37 by yharwyn-         ###   ########.fr       */
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
				  && argv[i][j] != 'r' && argv[i][j] != 't')
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

static char	*Ft_Get_Str_Options(int argc, char **argv)
{
	int		i;
	int		j;
	char	*str;

	i = 1;
	str = (char *)malloc(sizeof(char) * 21);
	str[21] = '\0';
	while (i < argc && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (Check_On_Consist(str, argv[i][j]) == -1)
			{
				str[i - 1] = argv[i][j];
				str[i] = '\0';
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

void	print_ls(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
}


static void	f_strcpy(char *dst, const char *src)
{
	int		i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
}

void 	get_arguments(int argc, char *argv[], t_ls *arg_ls)
{
	int i;
	int j;
	int k;
	char *tmp;

	i = 1;
	tmp = malloc(sizeof(char) * 256);
	arg_ls->dir[arg_ls->num_dir] = create_ls_item(1);
	arg_ls->file[arg_ls->num_file] = create_ls_item(0);
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
			while (argv[i][j] != '\0' && argv[i][j] != ' ')
			{
				tmp[k] = argv[i][j];
				j++;
				k++;
			}
			tmp[k] = '\0';
			if (is_dir(tmp) == 1)
			{
				f_strcpy(arg_ls->dir[arg_ls->num_dir]->path, tmp);
				arg_ls->dir[++(arg_ls->num_dir)] = create_ls_item(1);
			}
			else
			{
				f_strcpy(arg_ls->file[arg_ls->num_file]->path, tmp);
				arg_ls->file[++(arg_ls->num_file)] = create_ls_item(0);
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
			print_ls(ls->dir[i]->path);
			i++;
		}
	}
}

int		main(int argc, char **argv)
{
	int			bit;
	int			flag;
	t_ls	*arg_ls;
	int			size;

	if (arg_checker(argc, argv) == -1)
		{
			ft_putendl("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] "
					   "[file ...]\n");
			return (0);
	}
	size = 0;
	flag = Ft_Get_Bit(argc, argv);

	arg_ls = create_ls_main();
	if (l_FLAG)
	{
		get_arguments(argc, argv, arg_ls);
		printf("%s\n", arg_ls->file[0]->path);
		printf("%s\n", arg_ls->dir[0]->path);
		get_contents(arg_ls);
//		if (is_dir(ls_list->path) == 1)
//			print_ls(ls_list);
//		else
//			printf("%s\n", ls_list->path);
	}
}
