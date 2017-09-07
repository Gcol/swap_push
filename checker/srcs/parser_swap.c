#include <checker.h>

long **parsing_to_longlong(char **format, long taille)
{
	long index;
	long **result;

 	index = 0;
	result = ft_memalloc_exit((sizeof(long *) * 2));
	result[0] = ft_memalloc_exit((taille + 1) * sizeof(long));
	result[1] = ft_memalloc_exit(1);
	while(index < taille)
	{
		result[0][index] = ft_atoll(format[index]);
		index++;
	}
	result[1][0] = taille;
	return(result);
}

int longlong_check_rep(long *src, int len)
{
	long	*tmp;
	char	diff;
	long	i;
	long	j;

	i = 0;
	diff = 1;
	tmp = ft_memalloc_exit(len * sizeof(long));
	while(i < len && diff == 1)
	{
		j = 1;
		while(j < i)
		{
			if (tmp[j] == src[i])
				diff = 0;
			j++;
		}
		tmp[i] = src[i];
		i++;
	}
	free(tmp);
	return (diff);
}

int str_is_valid(char **format, char *str, char *first_carac)
{
	long	index_f;
	long	index_format;

	index_f = 0;
	index_format = 0;
	while (format[index_format])
	{
		while (format[index_format][index_f])
		{
			if (ft_c_in_str(format[index_format][index_f], first_carac))
				index_f++;
			if (!ft_c_in_str(format[index_format][index_f], str))
      {
        write(1, "Usage Error : Argument Invalid(not only number)\n", 49);
				return (0);
      }
			index_f++;
		}
		index_f = 0;
		index_format++;
	}
	return (1);
}

long ***parser_swap(char **argv, int argc)
{
  long ***tab;

  tab = ft_memalloc_exit(sizeof(long **) * 2);
  tab[0] = parsing_to_longlong(argv, argc);
  if (!longlong_check_rep(*tab[0], argc))
  {
    write(1, "Usage incorrect : similary number\n", 34);
    exit(3);
  }
  tab[1] = ft_memalloc_exit(sizeof(long *) * 2);
  tab[1][0] = ft_memalloc_exit(1 * sizeof(long));
  tab[1][1] = ft_memalloc_exit(1 * sizeof(long));
  return(tab);
}
