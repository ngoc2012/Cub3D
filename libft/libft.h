/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:08:19 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/09/24 15:40:04 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_lstdelone(t_list *lst, void (*del)(void *));
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_isalpha(int c);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_isalnum(int c);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_back2(t_list **lst, t_list *new, int (*cmp)());
int		ft_isdigit(int c);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *begin_list);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
int		ft_isascii(int c);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(const char *str, char charset);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_putnbr_fd(int n, int fd);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strrchr(const char *s, int c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strdup(const char *src);
t_list	*ft_lstlast(t_list *lst);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	ft_lstremove_if(t_list **bg, void *dr, int (*c)(), void (*d)(void *));
int		free_array_str(char ***ss, int i);
char	**astr_copy(char **ss);
char	**astr_addback(char **ss, char *s);
void	astr_remove(char **ss, void *dr, int (*cmp)(), void (*del)(void *));
char	*ft_strndup(char *s, int len);
int	astr_len(char **ss);

#endif
