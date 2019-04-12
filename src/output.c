#include "ft_ls.h"

void		print_ls_one_flag(t_ls *ls)
{
	int i;
	int j;

	i = -1;
	while (ls->dir[++i] != NULL)
	{
		j = 0;
		bubble_sort_ls(ls->dir[i]);
		if (FLAG_R)
			reverse_ls_output(ls->dir[j]);
		while (ls->dir[i]->cont[j] != NULL)
			ft_putendl(ls->dir[i]->cont[j++]->name);
	}
	i = -1;
	bubble_sort_ls(ls->file[0]);
	while (ls->file[++i] != NULL)
		ft_putendl(ls->file[i]->name);
}

static void	print_plus_sp(t_ls_item **ls, int i, int a)
{
	int	m;
	int	j;

	m = a - (int)ft_strlen(ls[i]->name);
	printf("%s", ls[i]->name);
	if (ls[i + 1] != NULL)
	{
		j = -1;
		while (++j < m)
			printf("%c", ' ');
	}
}

static void	ft_body_print(t_ls_item **ls, int a, int len, int row)
{
	int m[3];

	m[2] = 0;
	m[1] = 1;
	m[0] = 0;
	while (m[1] <= row)
	{
		if (m[2] == row)
		{
			print_plus_sp(ls, m[0], a);
			m[2] = 0;
		}
		else
			(ADD);
		if (m[0] == len)
		{
			printf("\n");
			m[0] = 0;
			m[0] += m[1];
			m[1]++;
			if (m[1] <= row)
				print_plus_sp(ls, m[0], a);
			m[2] = 0;
		}
	}
}

void		ft_print_dir_file(t_ls_item **ls, int a, int len)
{
	int	i;
	int	ws;
	int	col;
	int	row;

	i = 0;
	ws = get_terminal_width();
	ws == 0 ? ws = 100 : 0;
	col = ws / a;
	row = len / col;
	if (row * col < len)
		row++;
	print_plus_sp(ls, i, a);
	ft_body_print(ls, a, len, row);
}

int			ft_print_anti_l(t_ls *ls)
{
	int	a;
	int	j;
	int	len;

	j = 0;
	if (ls->file[j])
	{
		a = (ft_find_max_len(ls->file) / 8 + 1) * 8;
		ft_print_dir_file(ls->file, a, ls->num_file);
		if (ls->dir[0] != NULL)
			printf("\n");
	}
	j = -1;
	while (ls->dir[++j])
	{
		if (ls->num_dir != 1 || ls->num_file > 0)
			printf("%s:\n", ls->dir[j]->name);
		len = cont_len(ls->dir[j]);
		a = (ft_find_max_len(ls->dir[j]->cont) / 8 + 1) * 8;
		bubble_sort_ls(ls->dir[j]);
		if (FLAG_R)
			reverse_ls_output(ls->dir[j]);
		ft_print_dir_file(ls->dir[j]->cont, a, len);
	}
	return (0);
}

static void	cheack_attribut_dir(t_ls_item *ls, int *mas, int i, int j)
{
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
}

static void	cheack_attribut_file(t_ls *ls, int *mas, int i, int j)
{
	if (ft_strlen(ls->file[i]->perms) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->perms);
	j++;
	if (ft_strlen(ft_itoa(ls->file[i]->links)) > mas[j])
		mas[j] = (int)ft_strlen(ft_itoa(ls->file[i]->links));
	j++;
	if (ft_strlen(ls->file[i]->uid) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->uid);
	j++;
	if (ft_strlen(ls->file[i]->guid) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->guid);
	j++;
	if (ft_strlen(ft_itoa(ls->file[i]->file_size)) > mas[j])
		mas[j] = (int)ft_strlen(ft_itoa(ls->file[i]->file_size));
	j++;
	if (ft_strlen(ls->file[i]->month) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->month);
	j++;
	if (ft_strlen(ls->file[i]->day) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->day);
	j++;
	if (ft_strlen(ls->file[i]->time) > mas[j])
		mas[j] = (int)ft_strlen(ls->file[i]->time);
}

static void	ft_max_len_attributes(t_ls_item *ls, int *mas)
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
		cheack_attribut_dir(ls, mas, i, j);
		i++;
	}
}

static void	ft_max_len_attrb_file(t_ls *ls, int *mas)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 10)
		mas[j++] = 0;
	while (ls->file[i])
	{
		j = 0;
		cheack_attribut_file(ls, mas, i, j);
		i++;
	}
}

static void	ft_output_ls_right_side(char *str, int max)
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

static void	ft_output_ls_left_side(char *str, int max)
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

static void	ft_output_field_struct(t_ls_item *ls, int *mas)
{
	int	i;

	i = 0;
	ft_output_ls_left_side(ls->perms, mas[i++]);
	if (mas[i - 1] != 11)
		ft_putchar(' ');
	ft_output_ls_right_side(ft_itoa(ls->links), mas[i++]);
	ft_output_ls_left_side(ls->uid, mas[i++]);
	ft_putchar(' ');
	ft_output_ls_left_side(ls->guid, mas[i++]);
	ft_putchar(' ');
	ft_output_ls_right_side(ft_itoa(ls->file_size), mas[i++]);
	ft_output_ls_left_side(ls->month, mas[i++]);
	ft_output_ls_right_side(ls->day, mas[i++]);
	ft_output_ls_right_side(ls->time, mas[i]);
	ft_putstr(ls->name);
	ft_putchar('\n');
}

void		ft_output_l(t_ls *ls)
{
	int	mas[10];
	int	i;
	int	j;

	if (ls->file[0])
	{
		ft_max_len_attrb_file(ls, mas);
		j = 0;
		while (ls->file[j])
			ft_output_field_struct(ls->file[j++], mas);
	}
	i = -1;
	while (ls->dir[++i])
	{
		if (ls->num_dir != 1 || ls->num_file > 0)
			printf("%s:\n", ls->dir[i]->name);
		ft_printf("total %lli\n", ls->dir[i]->st_blocks);
		ft_max_len_attributes(ls->dir[i], mas);
		j = 0;
		if (FLAG_R)
			reverse_ls_output(ls->dir[i]);
		while (ls->dir[i]->cont[j])
			ft_output_field_struct(ls->dir[i]->cont[j++], mas);
	}
}

void		ls_base(t_ls *ls)
{
	if (T_FLAG)
		ft_tsort(ls);
	if (L_FLAG)
	{
		perm_maker(ls);
		ft_output_l(ls);
	}
	else if (ONE_FLAG)
		print_ls_one_flag(ls);
	else
		ft_print_anti_l(ls);
}

void		ls_recoursive(char *path, int flag)
{
	t_ls		*ls;
	int			i;
	static int	fl;

	(INITILIZAZYA);
	ls->flag = flag;
	ls->dir[(ls->num_dir)] = create_ls_item(1);
	f_strcpy(ls->dir[ls->num_dir]->name, path);
	path_cpy(ls->dir[ls->num_dir]->path, path, ls);
	++(ls->num_dir);
	get_contents(ls);
	ft_sort_by_ascii_all_dir_file(ls);
	ls->dir[0]->name[ft_strlen(ls->dir[0]->name) - 1] = '\0';
	fl != 0 ? printf("\n%s:\n", ls->dir[0]->name) : fl++;
	if (ls->dir[0]->cont[0] == NULL)
		(FREE);
	ls_base(ls);
	while (ls->dir[0]->cont[i] != NULL)
	{
		if (is_dir(ls->dir[0]->cont[i]->path) == 1)
			ls_recoursive(ls->dir[0]->cont[i]->path, flag);
		i++;
	}
	ft_free_ls(&ls);
}
