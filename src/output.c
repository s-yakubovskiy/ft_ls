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