#include "str_utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*res;
	size_t				s_len;

	if (!s)
		return (NULL);
	s_len = strlen(s);
	if (start >= s_len)
		return (strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	memcpy(res, s + start, len);
	res[len] = '\0';
	return (res);
}
