/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhammouc <hhammouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:45:46 by hhammouc          #+#    #+#             */
/*   Updated: 2025/01/18 15:26:01 by hhammouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


size_t	        ft_strlen(const char *s);
char	        *ft_substr(char const *s, unsigned int start, size_t len);
char	        *ft_strdup(const char *str);
char	        *ft_strjoin(char const *s1, char const *s2);
char            *get_next_line(int fd); 

#endif
