/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GNL_BUF_SIZE 32
#define ABS(x) ((x) > 0 ? (x) : -(x))

/*
** GNL buffer pointer (after a newline character) for a saved FD
*/
typedef struct s_saved_fds
{
    int                 fd;
    char               *buf_ptr;
    struct s_saved_fds *next;
} t_saved_fds;

/*
** Linked list type declaration
*/
typedef struct s_list
{
    void          *content;
    size_t         content_size;
    struct s_list *next;
} t_list;

/*
** Memory functions
*/
void *ft_memset(void *s, int c, size_t n);
void  ft_bzero(void *s, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memccpy(void *dest, const void *src, int c, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);
void *ft_memchr(const void *s, int c, size_t n);
int   ft_memcmp(const void *s1, const void *s2, size_t n);
void *ft_memalloc(size_t size);
void *ft_realloc(void *ptr, size_t old_size, size_t new_size);
void  ft_memdel(void **ap);
void  ft_ptrswap(void **a, void **b);
void  ft_intswap(int *a, int *b);

/*
** String functions
*/
size_t ft_strlen(const char *s);
char  *ft_strdup(const char *s);
char  *ft_strcpy(char *dest, const char *src);
char  *ft_strncpy(char *dest, const char *src, size_t n);
char  *ft_strcat(char *dest, const char *src);
char  *ft_strncat(char *dest, const char *src, size_t n);
size_t ft_strlcat(char *dst, const char *src, size_t size);
char  *ft_strchr(const char *s, int c);
char  *ft_strrchr(const char *s, int c);
char  *ft_strstr(const char *big, const char *little);
char  *ft_strnstr(const char *big, const char *little, size_t len);
int    ft_strcmp(const char *s1, const char *s2);
int    ft_strncmp(const char *s1, const char *s2, size_t n);
int    ft_atoi(const char *nptr);
char  *ft_strnew(size_t size);
void   ft_strdel(char **as);
void   ft_strclr(char *s);
void   ft_striter(char *s, void (*f)(char *));
void   ft_striteri(char *s, void (*f)(unsigned int, char *));
char  *ft_strmap(const char *s, char (*f)(char));
char  *ft_strmapi(const char *s, char (*f)(unsigned int, char));
int    ft_strequ(const char *s1, const char *s2);
int    ft_strnequ(const char *s1, const char *s2, size_t n);
char  *ft_strsub(const char *s, unsigned int start, size_t len);
char  *ft_strjoin(const char *s1, const char *s2);
char  *ft_strtrim(const char *s);
int    ft_strcount(const char *s, const char *sub);
char  *ft_strrep(char *src, char *in, char *to);
char **ft_strsplit(const char *s, char c);
char **ft_split_whitespaces(const char *s);
char  *ft_itoa(int n);
char  *ft_itoa_base(int n, unsigned int base);
char  *ft_strtolower(char *s);
char  *ft_strtoupper(char *s);
int    ft_get_next_line(const int fd, char **line);

/*
** Printing functions
*/
void ft_putchar(char c);
void ft_putwchar(wchar_t wc);
void ft_putstr(const char *s);
void ft_putwstr(const wchar_t *s);
void ft_putendl(const char *s);
void ft_putwendl(const wchar_t *s);
void ft_putnbr(int n);
void ft_putchar_fd(char c, int fd);
void ft_putwchar_fd(wchar_t wc, int fd);
void ft_putstr_fd(const char *s, int fd);
void ft_putwstr_fd(const wchar_t *s, int fd);
void ft_putendl_fd(const char *s, int fd);
void ft_putwendl_fd(const wchar_t *s, int fd);
void ft_putnbr_fd(int n, int fd);

/*
** Character functions
*/
int     ft_wcsize(wchar_t wc);
int     ft_wctomb(unsigned char *s, unsigned int wchar);
wchar_t ft_utf8_encode(unsigned int wchar);
int     ft_isalpha(int c);
int     ft_islower(int c);
int     ft_isupper(int c);
int     ft_isdigit(int c);
int     ft_isalnum(int c);
int     ft_isascii(int c);
int     ft_isprint(int c);
int     ft_isblank(int c);
int     ft_toupper(int c);
int     ft_tolower(int c);
int     ft_is_whitespace(int c);

/*
** Math functions
*/
int      ft_sqrt(int x);
int      ft_max(int a, int b);
intmax_t ft_pow(int x, int power);

/*
** Linked list functions
*/
t_list *ft_lstnew(const void *content, size_t content_size);
void    ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void    ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void    ft_lstadd(t_list **alst, t_list *new);
void    ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list *ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

#endif
