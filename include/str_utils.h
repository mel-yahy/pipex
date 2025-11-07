#ifndef STR_UTILS_H
# define STR_UTILS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif // !STR_UTILS_H
