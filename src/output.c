//
// Created by Yoshiko Harwyn hoare on 2019-04-04.
//

#include "ft_ls.h"

void	print_ls_one_flag(t_ls *ls)
{
	int i;
	int j;

	i = 0;
	while (ls->dir[i] != NULL)
	{
		j = 0;
		bubble_sort_ls(ls->dir[i]);
		while (ls->dir[i]->cont[j] != NULL)
		{
			ft_putendl(ls->dir[i]->cont[j]->name);
			j++;
		}
		i++;
	}
	i = 0;
	bubble_sort_ls(ls->file[i]);
	while (ls->file[i] != NULL)
	{
//        bubble_sort_ls(ls->file[i]);
	    ft_putendl(ls->file[i]->name);
		i++;
	}
}



void    display_contents(t_ls_item *ls)
{
	struct stat fileStat;
	char link_read[255];
	ssize_t bytes_read;

    if (lstat(ls->path, &fileStat) == -1)
    {  /* validate stat of file */
//        perror("stat");
        return ;
    }
//	lstat(ls->path, &fileStat);
	if(S_ISLNK(fileStat.st_mode))
	{
//		printf("%s ",ls->path );
		bytes_read = readlink(ls->path, link_read, 254);
		link_read[bytes_read] = '\0';
		f_strcpy(ls->path, " -> ");
		f_strcpy(ls->path, link_read);
//		printf("-> %s\n", link_read);
	}
}

static void print_plus_sp(t_ls_item **ls, int i, int a)
{
    int m;
    int j;

    m = a - (int)ft_strlen(ls[i]->name);
    printf("%s", ls[i]->name);
    if (ls[i + 1] != NULL)
    {
        j = -1;
        while (++j < m)
            printf("%c", ' ');
    }
}

void	ft_print_dir_file(t_ls_item **ls, int a, int len)
{
    int i;
    int j;
    int ws;
    int col;
    int x;
    int row;

    i = 0;
    ws = get_terminal_width();
    ws == 0 ? ws = 100 : 0;
    col = ws / a;
    row = len / col;
    if (row * col < len)
        row++;
    x = 0;
    j = 1;

//	printf("\nbreaker %d len: %d ws: %d a: %d column: %d row: %d\n ", br, len, ws, a, col, row);
    print_plus_sp(ls, i, a);
    while (j <= row)
    {
        if (x == row)
        {
            print_plus_sp(ls, i, a);
            x = 0;
        } else
        {
            i++;
            x++;
        }
        if (i == len)
        {
            printf("\n");
            i = 0;
            i += j;
            j++;
            if (j <= row)
                print_plus_sp(ls, i, a);
            x = 0;
        }
    }
//    printf("\n");
}

int     ft_print_anti_l(t_ls *ls)
{
    int a;
    int j;
    int len;

    j = 0;
    while (ls->dir[j])
    {
        len = cont_len(ls->dir[j]);
        a = (ft_find_max_len(ls->dir[j]->cont) / 8 + 1) * 8;
        bubble_sort_ls(ls->dir[j]);
        ft_print_dir_file(ls->dir[j]->cont, a, len);
        j++;
    }
    return (0);
}

void    body_ls(t_ls *ls)
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

static void ft_max_len_attributes(t_ls_item *ls, int *mas)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < 10)
		mas[j++] = 0;
	while (ls->cont[i])
	{
		j = 0;
		if (ft_strlen(ls->cont[i]->perms) > mas[j])
			mas[j] = (int)ft_strlen(ls->cont[i]->perms);
		j++;
		if (ft_strlen(ft_itoa(ls->cont[i]->links)) > mas[j])
			mas[j] = (int)ft_strlen(ft_itoa(ls->cont[i]->links));
		j++;
		if (ft_strlen(ls->cont[i]->uid) > mas[j])
			mas[j] = (int)ft_strlen(ls->cont[i]->uid);
		j++;
		if (ft_strlen(ls->cont[i]->guid) > mas[j])
			mas[j] = (int)ft_strlen(ls->cont[i]->guid);
		j++;
		if (ft_strlen(ft_itoa(ls->cont[i]->file_size)) > mas[j])
			mas[j] = (int)ft_strlen(ft_itoa(ls->cont[i]->file_size));
		j++;
		if (ft_strlen(ls->cont[i]->month) > mas[j])
			mas[j] = (int)ft_strlen(ls->cont[i]->month);
		j++;
		if (ft_strlen(ls->cont[i]->day) > mas[j])
			mas[j] = (int)ft_strlen(ls->cont[i]->day);
		j++;
		if (ft_strlen(ls->cont[i]->time) > mas[j])
			mas[j] = (int)ft_strlen(ls->cont[i]->time);
		i++;
	}
}

static void ft_output_ls_right_side(char *str, int max)
{
	int i;

	i = (int)ft_strlen(str);
	while (i < max)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(str);
	ft_putchar(' ');
}

static void ft_output_ls_left_side(char *str, int max)
{
	int i;

	ft_putstr(str);
	i = (int)ft_strlen(str);
	while (i < max)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putchar(' ');
}

static void ft_output_field_struct(t_ls_item *ls, int *mas)
{
	int i;

	i = 0;
	ft_output_ls_left_side(ls->perms, mas[i++]);
	ft_output_ls_right_side(ft_itoa(ls->links), mas[i++]);
	ft_output_ls_left_side(ls->uid, mas[i++]);
	ft_output_ls_left_side(ls->guid, mas[i++]);
	ft_output_ls_right_side(ft_itoa(ls->file_size), mas[i++]);
	ft_output_ls_left_side(ls->month, mas[i++]);
	ft_output_ls_right_side(ls->day, mas[i++]);
	ft_output_ls_right_side(ls->time, mas[i]);
	ft_putstr(ls->name);
	ft_putchar('\n');
}

void ft_output_l(t_ls *ls)
{
	int	mas[10];
	int i;
	int j;

	i = 0;
	while (ls->dir[i])
	{
		ft_printf("total %lli\n", ls->dir[i]->st_blocks);
		ft_max_len_attributes(ls->dir[i], mas);
		j = 0;
		while (ls->dir[i]->cont[j])
		{
			ft_output_field_struct(ls->dir[i]->cont[j], mas);
			j++;
		}
		i++;
	}
}