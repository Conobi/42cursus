/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:32:40 by conobi            #+#    #+#             */
/*   Updated: 2022/05/17 14:47:33 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/**
 * @brief Gives you the size of the string, not including '\\0'.
 * Be aware using it with indexes!
 *
 * @param s Your string
 * @return size_t The size of the string
 */
size_t	ft_strlen(const char *s);

/**
 * @brief copies up to dstsize - 1 characters from the string src to dst,
 * NUL-terminating the result if dstsize is not 0.
 *
 * @param dst Your destination string
 * @param src Your source; Cannot be modified
 * @param dstsize The total size of the future string. You must include the '\\0'
 * @return size_t Returns the total length of the string they tried to create.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @brief Appends up to dstsize -  strlen(dst)
 * - 1 characters from the string src to dst,
 * NUL-terminating the result if dstsize is not 0.
 *
 * @param dst Your destination string
 * @param src Your source; Cannot be modified
 * @param dstsize The total size of the future string. You must include the '\\0'
 * @return size_t Returns the total length of the string they tried to create.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @brief Compares the string s1 to the string s2.
 * Returns an integer greater than, equal to, or less than 0,
 * according as the string s1 is lexicographically greater than,
 * equal to, or less than the string s2.
 *
 * @param s1 Your string
 * @param s2 Your string
 * @param n The size of the string
 * @return int Returns an integer.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Duplicates a string.
 *
 * @param s1 Your string
 * @return char* Returns a pointer to the new string.
 */
char	*ft_strdup(const char *s1);

/**
 * @brief Convert a string to an integer.
 *
 * @param str Your string
 * @return int Returns the integer.
 */
int		ft_atoi(const char *str);

/**
 * @brief Allocates (with malloc(3)) and returns an array
 * of strings obtained by splitting ’s’ using the
 * character ’c’ as a delimiter. The array must be
 * ended by a NULL pointer.
 *
 * @param s The string to split
 * @param c The delimiter character
 * @return char Returns an array of strings.
 */
char	**ft_split(char const *s, char c);

/**
 * @brief Allocates (with malloc(3)) and returns a new
 * string, which is the result of the concatenation
 * of ’s1’ and ’s2’.
 *
 * @param s1 The prefix string
 * @param s2 The suffix string
 * @return char* A pointer to the new string.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument.
 * Negative numbers must be handled.
 *
 * @param n The integer to convert
 * @return char* The string representing the integer. NULL if the
 * allocation fails
 */
char	*ft_itoa(int n);

/**
 * @brief This function tests if the character c is alphabetical.
 *
 * @param c The character to test
 * @return int Returns 1 if the character is alphabetical, 0 otherwise.
 */
int		ft_isalpha(int c);

/**
 * @brief This function tests if the character c is a digit.
 *
 * @param c The character to test
 * @return int Returns 1 if the character is a digit, 0 otherwise.
 */
int		ft_isdigit(int c);

/**
 * @brief This function tests if the character c is a letter or a digit.
 *
 * @param c The character to test
 * @return int Returns 1 if the character is alphanumeric, 0 otherwise.
 */
int		ft_isalnum(int c);

/**
 * @brief This function tests if the character c is between
 * 0 and octal 0177 inclusive.
 *
 * @param c The character to test
 * @return int Returns 1 if the character is in the ASCII table, 0 otherwise.
 */
int		ft_isascii(int c);

/**
 * @brief This function tests if the character c is a printable character.
 *
 * @param c The character to test
 * @return int Returns 1 if the character is printable, 0 otherwise.
 */
int		ft_isprint(int c);

/**
 * @brief Does lowercase to uppercase conversion.
 *
 * @param c The character to convert
 * @return int If conversion is possible, the converted character is returned,
 * otherwise the character itself is returned.
 */
int		ft_toupper(int c);

/**
 * @brief Does uppercase to lowercase conversion.
 *
 * @param c The character to convert
 * @return int If conversion is possible, the converted character is returned,
 * otherwise the character itself is returned.
 */
int		ft_tolower(int c);

/**
 * @brief Locates the first occurrence of the character c
 * (converted to a char) in the string s.
 *
 * @param s The string to search
 * @param c The character to find
 * @return char* Returns a pointer to the
 * first occurrence of the character c.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Locates in a reverse way
 * the first occurrence of the character c
 * (converted to a char) in the string s.
 *
 * @param s The string to search
 * @param c The character to find
 * @return char* Returns a pointer to the first occurrence of the character c.
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief locates the first occurrence
 * of c (converted to an unsigned char) in string s.
 *
 * @param s The content to search
 * @param c The character to find
 * @param n The size of the string
 * @return void*
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares byte string s1
 * against byte string s2.  Both strings are assumed
 * to be n bytes long.
 *
 * @param s1 The first string
 * @param s2 The second string
 * @param n The size of the string
 * @return int The memcmp() function returns zero if the two
 * strings are identical, otherwise returns the difference
 * between the first two differing bytes
 * (treated as unsigned char values, so that '\\200'
 * is greater than '\\0', for example).  Zero-length
 * strings are always identical.  This behavior is
 * not required by C and portable code should only
 * depend on the sign of the returned value.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Fill a byte string with a byte value
 *
 * @param b The byte string to fill
 * @param c The byte value
 * @param len The size of the string
 * @return void* Returns a pointer to the byte string.
 */
void	*ft_memset(void *b, int c, size_t len);

/**
 * @brief Same as memset, but filling the string
 * with zeroes
 *
 * @param s The string to fill
 * @param n The size of the string
 * @return void
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief Copies n bytes from memory
 * area src to memory area dst.  If dst and src overlap,
 * behavior is undefined.  Applications in which
 * dst and src might overlap should use memmove(3)
 * instead.
 * @param dst The destination memory
 * @param src The source memory
 * @param n The size of the memory
 * @return void*
 */
void	*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @brief The memmove() function copies len bytes from
 * string src to string dst.  The two strings may
 * overlap; the copy is always done in a
 * non-destructive manner.
 *
 * @param dst The destination memory
 * @param src The source memory
 * @param len The size of the memory
 * @return void* Returns the original value of dst.
 */
void	*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @brief Locates the first occurrence
 * of the null-terminated string needle in the
 * string haystack, where not more than len characters
 * are searched.  Characters that appear after a
 * `\0' character are not searched.
 *
 * @param haystack The string to search into
 * @param needle The string to find
 * @param len The limit in which we search
 * @return char* If needle is an empty string, haystack is
 * returned; if needle occurs nowhere in haystack,
 * NULL is returned; otherwise a pointer to the first
 * character of the first occurrence of needle is
 * returned.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/**
 * @brief Contiguously allocates enough space for count objects
 * that are size bytes of memory each and
 * returns a pointer to the allocated memory.
 * The allocated memory is filled with bytes of value zero.
 *
 * @param count The number of elements to allocate
 * @param size The size of each element. Use sizeof(type) to get the exact
 * size of an element of a given type.
 * @return void* Returns a pointer to the allocated memory.
 */
void	*ft_calloc(size_t count, size_t size);

/**
 * @brief Allocates (with malloc(3)) and returns a substring
 * from the string ’s’.
 * The substring begins at index ’start’ and is of maximum size ’len’.
 *
 * @param s The string to cut
 * @param start The index of the first character of the substring
 * @param len The maximum size of the substring
 * @return char* Returns a pointer to the allocated memory.
 * NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Allocates (with malloc(3)) and returns a copy of
 * ’s1’ with the characters specified in ’set’ removed
 * from the beginning and the end of the string.
 *
 * @param s1 The string to be trimmed
 * @param set The reference set of characters to trim
 * @return char* The trimmed string. NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Outputs the character ’c’ to the given file
 * descriptor.
 *
 * @param c The character to print
 * @param fd The file descriptor
 * @return void
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string ’s’ to the given file
 * descriptor.
 *
 * @param s The string to print
 * @param fd The file descriptor
 * @return void
 */
void	ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs the string ’s’ to the given file
 * descriptor. The string is followed by a new line.
 *
 * @param s The string to print
 * @param fd The file descriptor
 * @return void
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Outputs the integer ’n’ to the given file
 * descriptor.
 *
 * @param n The integer to print
 * @param fd The file descriptor
 * @return void
 */
void	ft_putnbr_fd(int n, int fd);

/**
 * @brief Applies the function ’f’ to each character of
 * the string ’s’ , and passing its index as first
 * argument to create a new string (with malloc(3))
 * resulting from successive applications of ’f’.
 *
 * @param s The string on which to iterate
 * @param f The function to apply to each character.
 * @return char* The string created from the successive applications
 * of ’f’. Returns NULL if the allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies the function f to each character of the
 * string passed as argument, and passing its index
 * as first argument. Each character is passed by
 * address to f to be modified if necessary
 *
 * @param s The string on which to iterate.
 * @param f The function to apply to each character
 * @return void
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* BONUS PART */

/**
 * @brief Here is a description of the fields of the t_list struct:
 * - content : The data contained in the element.
 * The void * allows to store any kind of data.
 * - next : The next element’s address or NULL if it’s the last element.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/**
 * @brief Allocates (with malloc(3)) and returns a new
 * element. The variable ’content’ is initialized
 * with the value of the parameter ’content’. The
 * variable ’next’ is initialized to NULL.
 *
 * @param content The content to create the new element with
 * @return t_list* The new element.
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Adds the element ’new’ at the beginning of the
 * list.
 *
 * @param alst The address of a pointer to the first link of
 * a list.
 * @param new The address of a pointer to the first link of
 * a list.
 * @return void
 */
void	ft_lstadd_front(t_list **alst, t_list *new);

/**
 * @brief Counts the number of elements in a list.
 *
 * @param lst The beginning of the list.
 * @return int Length of the list.
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Returns the last element of the list.
 *
 * @param lst The beginning of the list.
 * @return t_list* Last element of the list.
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Adds the element ’new’ at the end of the list.
 *
 * @param alst The address of a pointer to the first link of
 * a list.
 * @param new The address of a pointer to the element to be
 * added to the list.
 * @return void
 */
void	ft_lstadd_back(t_list **alst, t_list *new);

/**
 * @brief Takes as a parameter an element and frees the
 * memory of the element’s content using the function
 * ’del’ given as a parameter and free the element.
 * The memory of ’next’ must not be freed
 *
 * @param lst The element to free.
 * @param del The address of the function used to delete the
 * content.
 * @return void
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Iterates the list ’lst’ and applies the function
 * ’f’ to the content of each element
 *
 * @param lst The adress of a pointer to an element.
 * @param f The adress of the function used to iterate on
 * the list.
 * @return void
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Deletes and frees the given element and every
 * successor of that element, using the function ’del’
 * and free(3).
 * Finally, the pointer to the list must be set to
 * NULL.
 *
 * @param lst The address of a pointer to an element.
 * @param del The address of the function used to delete the
 * content of the element.
 * @return void
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Iterates the list ’lst’ and applies the function
 * ’f’ to the content of each element. Creates a new
 * list resulting of the successive applications of
 * the function ’f’. The ’del’ function is used to
 * delete the content of an element if needed.
 *
 * @param lst The adress of a pointer to an element.
 * @param f The adress of the function used to iterate on
 * the list.
 * @param del The adress of the function used to delete the
 * content of an element if needed
 * @return t_list* The new list. NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * @brief Concatenates the number of arguments sent to the function
 *
 * @param argc Number of arguments to concat
 * @param ... all strings to concat
 * @return char* returns a string in all arguments have been concatenated,
 * or NULL on allocation failure.
 */
char	*ft_aconcat(int argc, ...);

/* GARBAGE COLLECTOR */

/**
 * @brief The list of allocated items, that we can clean or keep
 * depending on the type.
 */
typedef struct s_garbc
{
	void			*content;
	char			type;
	struct s_garbc	*next;
}	t_garbc;

/**
 * @brief A function to create the first element of the garbage collector.
 *
 * @return t_garbc* Create the first element of the list, nulled on every
 * parameter.
 */
t_garbc	*gb_init(void);

/**
 * @brief Add an allocated memory pointer to the garbage collector linked-list.
 *
 * @param ptr The allocated memory
 * @param garbcl A pointer to the linked-list, headed to the top of the list.
 * @param type The type of element allocated
 * @return void* Returns a pointer to the allocated memory.
 */
void	*gb_add(void *ptr, t_garbc **garbcl, const char type);

/**
 * @brief Works similarly as the ft_calloc function, but saves the allocated
 * pointer to a linked-list, that can be cleaned up.
 *
 * @param count The number of elements to allocate
 * @param size The size of each element. Use sizeof(type) to get the exact
 * size of an element of a given type.
 * @param type The type of element allocated.
 * This parameter is used to be able to choose
 * which element delete when this kind of element is not used
 * @param last A pointer to the linked-list, headed to the top of the list.
 * @return void* Returns a pointer to the allocated memory.
 */
void	*gb_calloc(size_t count, size_t size, const char type, t_garbc **last);

/**
 * @brief Deletes every element of type x in the garbage collector linked-list.
 *
 * @param garbcl A pointer to the linked-list, headed to the top of the list.
 * @param type The kind of element to delete. Can be between -128 and 127.
 * @return void
 */
void	gb_delete(t_garbc **garbcl, const char type);

/**
 * @brief Deallocates all the elements in the linked-list
 * created by `gb_calloc`, and sets it to NULL.
 * Should be used at the end of the program.
 *
 * @param garbcl The list, headed to the top of the list.
 * @return void
 */
void	gb_clear(t_garbc **garbcl);

/* ft_gnl.c */
char	*ft_gnl(int fd);

#endif
