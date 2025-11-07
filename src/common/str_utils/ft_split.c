#include "str_utils.h"

static size_t	count_substrings(char const *s, char delimiter)
{
	size_t	count;

	while (*s == delimiter && delimiter != '\0')
		s++;
	if (*s == '\0')
		return (0);
	count = 1;
	while (*s)
	{
		if (*s == delimiter)
		{
			while (*s == delimiter)
				s++;
			if (*s != '\0')
				count++;
		}
		else
			s++;
	}
	return (count);
}

static size_t	substring_length(char const *s, char delimiter)
{
	size_t	count;

	while (*s == delimiter)
		s++;
	if (*s == '\0')
		return (0);
	count = 0;
	while (*s && (*s != delimiter))
	{
		count++;
		s++;
	}
	return (count);
}

static char	*substring_dup(char const *str, size_t len)
{
	char	*dup;
	char	*ptr;

	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	ptr = dup;
	while (len--)
		*ptr++ = *str++;
	*ptr = '\0';
	return (dup);
}

static void	free_all(char **res, size_t last_idx)
{
	while (last_idx > 0)
		free(res[--last_idx]);
	free(res);
}

char	**ft_split(char const *s, char c)
{
	size_t	substring_count;
	size_t	substring_len;
	size_t	i;
	char	**res;

	substring_count = count_substrings(s, c);
	res = malloc(sizeof(char *) * (substring_count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < substring_count)
	{
		while (*s == c)
			s++;
		substring_len = substring_length(s, c);
		res[i] = substring_dup(s, substring_len);
		if (!res[i])
			return (free_all(res, i), NULL);
		s += substring_len;
		i++;
	}
	res[i] = NULL;
	return (res);
}
