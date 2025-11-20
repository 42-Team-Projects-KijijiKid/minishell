/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:26:51 by mandre            #+#    #+#             */
/*   Updated: 2025/11/20 17:56:14 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//GNL Read Buffer Size
# define BUFFER_SIZE 10

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

long	ft_atol(const char *str);
int		ft_atoi(const char *str);
void	ft_bzero(void *str, size_t size);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int arg);
int		ft_isalpha(int arg);
int		ft_isascii(int arg);
int		ft_isdigit(int a);
int		ft_isprint(int arg);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, int n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, void *src, size_t n);
void	*ft_memset(void *dst, int c, size_t range);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strjoin(char const *s1, char const *s2);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		print_str(char *str);

//Libft Extensions
void	free2d(char **arr);
int		wrd_count(char const *s, char c);
double	atodl(char *s);

//Printf Prototypes
int		ft_printf(const char *str, ...);
int		print_stft_putcharr(char *str);
int		print_ptr(unsigned long ptr);
int		hexa_lowercase(unsigned long val, int rtn_val);
int		hexa_uppercase(unsigned long val, int rtn_val);
int		print_int(int val, int rtn_val);
int		print_usigned(unsigned int val, int rtn_val);
int		*get_error(void);
void	set_error(int new_status);
int		ft_putchar(char c);

// Fprintf
int		ft_fprintf(int fd, const char *str, ...);
int		fprint_usigned(int fd, unsigned int val, int rtn_val);
int		fprint_ptr(int fd, unsigned long ptr);
int		fhexa_uppercase(int fd, unsigned long val, int rtn_val);
int		fhexa_lowercase(int fd, unsigned long val, int rtn_val);
int		fprint_int(int fd, int val, int rtn_val);
int		ft_fputchar(int fd, char c);
int		fprint_str(int fd, char *str);

//GNL Prototypes
char	*get_next_line(int fd);
bool	ft_find_occurence(const char *s, int c);
size_t	strlen_special(const char *str);
char	*ft_strdup_gnl(const char *s);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
void	ft_memmove_gnl(char *dest, char *src, size_t n);


#endif