/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:43:48 by nikita            #+#    #+#             */
/*   Updated: 2020/12/25 12:45:27 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

# define ROTATE_LEFT	65361
# define ROTATE_RIGHT	65363
# define FORWARD_W_Z	119
# define BACK_S_S		115
# define RIGHT_D_D		100
# define LEFT_A_Q		97
# define BUFFER_SIZE	4096

typedef struct		s_sprxy
{
	double			x;
	double			y;
}					t_sprxy;

typedef struct		s_sprite
{
	int				nbspr;
	int				*order;
	double			*dist;
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstartx;
	int				drawstarty;
	int				drawendy;
	int				drawendx;
	int				spritewidth;
	double			*zbuffer;
}					t_sprite;

typedef struct		s_texture
{
	int				texdir;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
}					t_texture;

typedef struct		s_ray
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			raydirx;
	double			raydiry;
	double			camerax;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;

	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			movespeed;
	double			rotspeed;
	int				x;
	int				texture;
}					t_ray;

typedef struct		s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				forward;
	int				back;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
	int				minimapechelle;
	int				width;
	int				height;
	void			*img2;
	int				*addr2;
}					t_data;

typedef struct		s_params
{
	int				rx;
	int				ry;
	int				i;
	int				f;
	int				c;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
	int				nblines;
	int				sizeline;
	char			**map;
	char			depart;
	int				dx;
	int				dy;
	int				indicateur;
	int				indicateur2;
	int				indicateur3;
	int				save;
	int				screenx;
	int				screeny;
	int				error;
	int				multijoueurs;
	int				check_tabulation;
	int				insidemap;
	int				count;
	int				count2;
	int				sum;
	int				wrongcharmap;
	t_data			texture[5];
	t_data			data;
	t_ray			ray;
	t_texture		t;
	t_sprite		s;
	t_sprxy			*sxy;
}					t_params;

int					is_whitespace(int c);
int					ft_cub(char *str, t_params *params);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strchr(char *s, int c);
char				*ft_strdup(char *s1);
int					checker(char *save, char **line, int *flag, char **p);
int					get_line(int fd, char **line, char **save);
int					ft_get_line2(int fd, char *buffer,
						char **line, char **save);
int					ft_get_line3(int *flag, char **save, char **p);
void				ft_parsing(char *fichier, t_params *params);
int					ft_parsing_map(char *fichier, t_params *params);
void				ft_get_texture(t_params *params);
void				ft_imprime_map(t_params *params);
void				ft_get_texture_adress(t_params *params);
int					ft_strlen2(char *str);
int					ft_charinstr(char *str, char c);
int					ft_murs_util(char *str);
int					ft_depart(char c, t_params *params, int i, int j);
void				ft_color_resolution(char **str, t_params *params, int i);
int					ft_atoi2(const char *str, t_params *params);
int					ft_atoi3(const char *str, t_params *params);
void				ft_texture(char *str, t_params *params);
int					ft_path_texture(char *str, char **texture,
						t_params *params, int j);
void				ft_initialisation(t_params *params);
int					ft_murs(t_params *params);
int					ft_is_map(char *str, t_params *params);
void				ft_map(char *str, t_params *params);
int					ft_copy_map(char *str, t_params *params);
void				ft_init_sprite(t_params *params);
int					ft_raycasting(t_params *params);
int					ft_mlx(t_params *params);
int					ft_mlx2(t_params *params);
int					ft_key_press(int keycode, t_params *params);
int					ft_key_release(int keycode, t_params *params);
int					ft_color_column(t_params *params);
void				ft_draw_texture(t_params *params, int x, int y);
void				ft_initialisation2(t_params *params);
void				ft_initialisation3(t_params *params);
void				ft_init_texture(t_params *params);
void				ft_init_sprite2(t_params *params, int i, int j, int v);
void				ft_stepsidedist(t_params *params);
void				ft_incrementray(t_params *params);
void				ft_drawstartend(t_params *params);
void				ft_swap(t_params *params);
void				ft_forward_back(t_params *params);
void				ft_left_right(t_params *params);
void				ft_rotate_right_left(t_params *params);
void				ft_error(t_params *params, char *str);
int					ft_exit(t_params *params);
void				ft_verify_errors(t_params *params);
void				ft_header(t_params *params, int fd);
void				ft_save(t_params *params);
void				ft_sprite(t_params *params);
int					ft_minimap(t_params *params);
void				my_color_cube(t_data *data, int x, int y, int color);
void				my_color_perso(t_data *data, int x, int y, int color);
void				ft_hitpoints(t_params *params);
void				ft_init_more(t_params *params);
int					get_next_line(int fd, char **line, t_params *params);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_subbuff(char *buff, int start, int len);
void				ft_init_dir(t_params *params);
void				ft_init_more3(t_params *params);
void				ft_rotate_left(t_params *params, double olddirx);
void				ft_atoi3_check(const char *str, t_params *params);
int					ft_check_tabulation(char *str);
int					ft_check_save(char *str);
int					ft_number_rows(const char *str);

#endif
