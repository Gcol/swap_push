
int		ft_isspace(char c)
{
	if ((c >= 8 && c <= 13) || c == 32)
		return (1);
	return (0);
}
