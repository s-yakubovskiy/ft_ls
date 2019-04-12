/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:41:22 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/05 15:20:46 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../lib/printf/ft_printf.h"
# include "../lib/printf/libft/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <time.h>
# include <sys/ioctl.h>

# define L_FLAG ((ls->flag >> 0u) & 1u)
# define R_FLAG ((ls->flag >> 1u) & 1u)
# define A_FLAG ((ls->flag >> 2u) & 1u)
# define FLAG_R ((ls->flag >> 3u) & 1u)
# define T_FLAG ((ls->flag >> 4u) & 1u)
# define ONE_FLAG ((ls->flag >> 5u) & 1u)
# define MAXC 64
# define FREE {ft_free_ls(&ls); return ;}
# define INITILIZAZYA {	i = 0; fl = 0; ls = create_ls_main();}
# define ADD {m[0]++; m[2]++;}

# define ISNUM(x) (x >= '0' && x <= '9')
# define ISSPACE(x) (x == ' ' || x == '\n')
# define _MIN(a,b) (((a)<(b))?(a):(b))
# define _MAX(a,b) (((a)>(b))?(a):(b))
# define EVEN(a) (((a)%(2) == 0) ? (1):(0))

# define _C_ "\033[1;96m"
# define _G_ "\033[1;92m"
# define _R_ "\x1b[0m"
# define _RD_ "\033[0;105m"
# define _M_ "\033[1;33m"

typedef struct			s_ls
{
	unsigned int		flag;
	int 				num_dir;
	int 				num_file;
	char				path[1024];
	struct s_ls_item	**dir;
	struct s_ls_item	**file;
}						t_ls;

typedef struct			s_ls_item
{
	char				time[6];
	char				day[6];
	char 				month[6];
	char				name[1024];
	char				path[4096];
	char				perms[16];
	char 				uid[64];
	char 				guid[64];
	int					file_size;
	int 				links;
	long long int		st_blocks;
	struct s_ls_item	*next;
	struct s_ls_item	**cont;
}						t_ls_item;

int						is_dir(char *path);
t_ls_item				*create_ls_item(int flag);
t_ls					*create_ls_main(void);
void					free_ls_item(t_ls_item	*ls);
int						ft_free_ls(t_ls **ls);
void					swap_ls_item(t_ls_item *a, t_ls_item *b);
int						time_getter(t_ls_item *ls);
int						perm_maker(t_ls *ls);
int						arg_checker(int argc, char **argv);
char					*ft_get_str_options(int argc, char **argv);
int						check_on_consist(char *str, char c);
int						ft_check_open_file(char *tmp);
int						ft_check_open_dir(char *tmp);
void					print_ls_one_flag(t_ls *ls);
void					grab_ls(t_ls *ls, int i);
void					ft_print_dir_file(t_ls_item **ls, int a, int len);
int						ft_print_anti_l(t_ls *ls);
void					ft_output_l(t_ls *ls);
void					ls_recoursive(char *path, int flag);
void					ls_base(t_ls *ls);
char					extended_param(char *filename);
int						uid_guid_getter(t_ls_item *ls);
long int				total(t_ls_item *ls);
void					bubble_sort_ls(t_ls_item *ls);
void					ft_tsort(t_ls	*ls);
void					reverse_ls_output(t_ls_item *ls);
void					ft_sort_by_ascii_all_dir_file(t_ls *ls);
int						get_terminal_width(void);
int						cont_len(t_ls_item *ls);
int						ft_bitwise_shift(unsigned int flag, unsigned int a);
int						ft_get_bit(int argc, char **argv);
void					path_cpy(char *dst, const char *src, t_ls *ls);
void					f_strcpy(char *dst, const char *src);
int						perm_getter(t_ls_item *ls);
int						ft_find_max_len(t_ls_item **ls);
void					get_contents(t_ls *ls);

#endif
