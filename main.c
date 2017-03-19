

int main(int ac, char **av)
{
  (void)av;

  char **tab;
  char **tab2;
  int i;
  int NB;

  NB = 30;

  //printf("t_map:%lu t_block:%lu \n\n", sizeof(t_map), sizeof(t_block));
  if(ac == 2)
  {

    tab = (char**)ft_malloc(NB);
    i = 0;
    while (i < NB)
    {
    tab[i] = ft_malloc(50 + (150*i));
    strcpy(tab[i],"STR IN TAB ");
    printf("%s \n", tab[i]);
    i++;
    }
    show_alloc_mem();

    tab2 = (char**)ft_malloc(NB);
    i = 0;
    while (i < NB)
    {
    tab2[i] = ft_malloc(50 + (150*i));
    strcpy(tab2[i],"STR IN TAB ");
    printf("%s \n", tab2[i]);
    i++;
    }
    show_alloc_mem();

    i = 0;
    while (i < NB)
    {
    ft_free(tab[i]);
    i++;
    }

    i = 0;
    while (i < NB)
    {
    ft_free(tab2[i]);
    i++;
    }

    tab = (char**)malloc(NB);

    for ( i = 0 ; i < 3 ; i ++ )
    {
    tab[i] = 0;
    }
    for ( i = 0 ; i < 3 ; i ++ )
    {
    tab[i] = ft_malloc(50);
    printf("%p, %d\n", tab[i], i);
    }
    show_alloc_mem();
    for(i = 0 ; i < 3 ; i ++)
    {
    printf("%p, %d\n", tab[i], i);
    ft_free(tab[i]);
    }
    show_alloc_mem();
    //printf("FT_FREE\n\n");
  }
  else
  {
    tab = (char**)malloc(NB);
    i = 0;
    while (i < NB)
    {
    tab[i] = malloc(50 + (150*i));
    strcpy(tab[i],"STR IN TAB ");
    printf("%s \n", tab[i]);
    i++;
    }
    show_alloc_mem();

    i = 0;
    while (i < NB)
    {
    free(tab[i]);
    i++;
    }
  }
  return (0);
}
