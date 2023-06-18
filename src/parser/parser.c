/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:08:18 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/18 11:41:36by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../gnl/get_next_line.h"

// ! debugging purposes
void	printSPLIT(char ** s)
{
    int i = 0;

	if (!s)
	{
		puts("(null)");
		return;
	}
    printf("<| ");
    while (s[i])
    {
		printf("%s", s[i]);
        printf(s[i+1]  ? " | " : " |");
        i++;
    }
    printf(">\n");
}


void	free_split(void *split)
{
	char	**head;

	head = (char **)split;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(*head);
	free(split);
}

void	parse_color(char *str, t_vect3d *pt)
{
	char		*comma_pos;
	char		**split;
	int			split_len;
	uint32_t	color;

	comma_pos = ft_strchr(str, ',');
	color = 0xFFFFFF;
	if (comma_pos && ft_strlen(str) > 1)
	{
		split = ft_split(str, ',');
		split_len = count_words(str, ',');
		if (split_len == 2 && ft_strlen(split[1]) > 2)
			color = ft_atoi_base((split[1] + 2), "0123456789abcdef");
		else if (split_len == 1 && comma_pos == str && ft_strlen(split[0]) > 2)
			color = ft_atoi_base((split[0] + 2), "0123456789abcdef");
		free_split(split);
	}
	pt->color = color;
}

void	split_map(t_vars *vars, t_list **map, int fd)
{
	char	*str;
	char	**split;

	// Split things
	str = "";
	while (str)
	{
		str = get_next_line(fd);
		if (str)
		{
			vars->rows++;
			if (ft_strchr(str, '\n'))
				str[ft_strlen(str) - 1] = '\0';
		}
		if (vars->cols < 0)
			vars->cols = count_words(str, ' ');
		else if (str && count_words(str, ' ') != vars->cols)
			return (ft_lstclear(map, free_split), exit(-1));
		split = ft_split(str, ' ');
		if (split)
			ft_lstadd_back(map, ft_lstnew(split));
		free(str);
	}
}

void	set_max_min(t_vars *vars, int val)
{
	if (val > vars->max)
		vars->max = val;
	if (val < vars->min)
		vars->min = val;
}

void	parse_map(t_vars *vars, t_list *map)
{
	int		i;
	int		j;
	char	**split;
	int		z;

	i = 0;
	while (map)
	{
		j = 0;
		vars->pts[i] = malloc(vars->cols * sizeof(t_vect3d));
		split = (char **)map->content;
		while (j < vars->cols)
		{
			z = ft_atoi(split[j]);
			vars->pts[i][j] = (t_vect3d){
				j - vars->cols / 2, i - vars->rows / 2, z, 0
			};
			parse_color(split[j], &vars->pts[i][j]);
			set_max_min(vars, z);
			// printf("Parsed point (%d, %d, %#X)\n", i, j, vars->pts[i][j].color);
			j++;
		}
		i++;
		map = map->next;
	}
}

//! Handle maps that are not Squared please or SEGS (Error String)
void	handle_map(char *file_path, t_vars *vars)
{
	int		fd;
	t_list	*map;

	vars->cols = -1;
	vars->rows = 0;
	map = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd < 3)
		return (perror("fdf"), exit(-1));
	// Spliting stuff
	split_map(vars, &map, fd);
	// Actual parsing
	vars->pts = malloc(vars->rows * sizeof(t_vect3d*));
	parse_map(vars, map);
	ft_lstclear(&map, free_split);
}