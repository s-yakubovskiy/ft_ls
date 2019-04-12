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

static void	set_dir(t_ls *ls, int i, int j, struct dirent	*dir)
{
	ls->dir[i]->cont[j] = create_ls_item(0);
	f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
	f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
	path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name, ls);
}

static void	set_file(t_ls *ls, int i, int j, struct dirent	*dir)
{
	ls->dir[i]->cont[j] = create_ls_item(0);
	f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
	f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
	path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name, ls);
}

void		grab_ls(t_ls *ls, int i)
{
	int				j;
	DIR				*d;
	struct dirent	*dir;

	j = 0;
	d = opendir(ls->dir[i]->path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if ((A_FLAG) == 0 && dir->d_name[0] != '.')
			{
				set_dir(ls, i, j, dir);
				j++;
			}
			else if (A_FLAG)
			{
				set_file(ls, i, j, dir);
				j++;
			}
		}
		closedir(d);
	}
	ls->dir[i]->cont[j] = 0;
}

static void	no_args(t_ls *ls, int argc)
{
	if (argc == 1)
	{
		ls->dir[(ls->num_dir)] = create_ls_item(1);
		f_strcpy(ls->dir[ls->num_dir]->name, ".");
		path_cpy(ls->dir[ls->num_dir]->path, ".", ls);
		++(ls->num_dir);
	}
	else if (ls->dir[0] == NULL && ls->file[0] == NULL)
	{
		ls->dir[(ls->num_dir)] = create_ls_item(1);
		f_strcpy(ls->dir[ls->num_dir]->name, ".");
		path_cpy(ls->dir[ls->num_dir]->path, ".", ls);
		++(ls->num_dir);
	}
}

static int	ft_check_end_argument(t_ls *ls, char *tmp)
{
	f_strcpy(tmp, ".");
	if (ft_check_open_dir(tmp) == 1)
	{
		ls->dir[(ls->num_dir)] = create_ls_item(1);
		f_strcpy(ls->dir[ls->num_dir]->name, tmp);
		path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
		++(ls->num_dir);
	}
	else
		return (-1);
	return (1);
}

static void	ft_fill_dir(t_ls *ls, char *tmp)
{
	ls->dir[(ls->num_dir)] = create_ls_item(1);
	f_strcpy(ls->dir[ls->num_dir]->name, tmp);
	path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
	++(ls->num_dir);
}

static void	ft_fill_file(t_ls *ls, char *tmp)
{
	ls->file[(ls->num_file)] = create_ls_item(0);
	f_strcpy(ls->file[ls->num_file]->name, tmp);
	path_cpy(ls->file[ls->num_file]->path, tmp, ls);
	++(ls->num_file);
}

static int	ft_cheak_dir_or_file(t_ls *ls, char *tmp)
{
	if (is_dir(tmp) == 1)
	{
		if (ft_check_open_dir(tmp) == 1)
			ft_fill_dir(ls, tmp);
		else
			return (-1);
	}
	else
	{
		if (ft_check_open_file(tmp) == 1)
			ft_fill_file(ls, tmp);
		else
			return (-1);
	}
	return (1);
}

static int	func_copy(char *argv[], t_ls *ls, char *tmp, int *m)
{
	int	k;

	k = 0;
	while (argv[m[0]][m[1]] != '\0' && argv[m[0]][m[1]] != ' ')
	{
		tmp[k] = argv[m[0]][m[1]];
		m[1]++;
		k++;
	}
	tmp[k] = '\0';
	if (ft_cheak_dir_or_file(ls, tmp) == -1)
		return (-1);
	ft_bzero(tmp, (size_t)k);
	return (1);
}

static int	get_arguments(int argc, char *argv[], t_ls *ls)
{
	int		m[2];
	char	tmp[256];

	m[0] = 1;
	while (m[0] < argc)
	{
		if (argv[m[0]][0] == '-')
			m[0]++;
		else
		{
			m[1] = 0;
			while (ISSPACE(argv[m[0]][m[1]]))
				m[1]++;
			if (argv[m[0]][m[1]] == '\0')
				return (ft_check_end_argument(ls, tmp));
			if (func_copy(argv, ls, tmp, m) == -1)
				return (-1);
			m[0]++;
		}
	}
	no_args(ls, argc);
	return (1);
}

int			main(int argc, char **argv)
{
	t_ls	*ls;
	int		i;

	i = -1;
	if (arg_checker(argc, argv) == -1)
	{
		ft_putendl("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] "
			"[file ...]\n");
		return (0);
	}
	ls = create_ls_main();
	ls->flag = ft_get_bit(argc, argv);
	if (get_arguments(argc, argv, ls) != 1)
		return (ft_free_ls(&ls));
	get_contents(ls);
	ft_sort_by_ascii_all_dir_file(ls);
	if (R_FLAG)
	{
		while (ls->dir[++i] != NULL)
			ls_recoursive(ls->dir[i]->name, ls->flag);
	}
	else
		ls_base(ls);
	return (ft_free_ls(&ls));
}
