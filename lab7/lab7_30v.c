#include "lab7_30v.h"

int main() {
  char find_house[50], find_author[50], buf[500];
  int (*fptr_for_autrhor_sort)(lib_write * first_lib, lib_write * next_lib);
  int (*fptr_for_year_sort)(lib_write * first_lib, lib_write * next_lib);
  int rezjim = -1, find_year = 0, rezjim_of_sort = 0, num = 0;
  FILE *file = NULL;
  char file_name[50];

  lib_write *result = NULL;

  print_reajims();
  while (rezjim != 0) {
    for (; !result && rezjim;) {
      printf("Инициализируйте структуру\n");
      printf("выберите 0-выход 9-ручной ввод/11-считывание с файла: ");
      scanf("%d", &rezjim);
      if (rezjim == 11) {
        scanf("%s", file_name);
        file = fopen(file_name, "r");
        if (file) {
          result = scanf_new_struct(result, file);
          fclose(file);
        } else {
          printf("error!");
        }
      } else if (rezjim == 9)
        result = add_obj(result, 0);
      else if (!rezjim)
        break;
      print_reajims();
    }
    while ((rezjim && scanf("%d", &rezjim) != 1) ||
           !(rezjim >= 0 && rezjim < 14))
      ;
    switch (rezjim) {
    case 1:
      printf("Количесвто работ: %d\n", count_works(get_tail(result)));
      break;
    case 2:
      printf("Введите имя дома, работы которого хотите подсчитать: ");
      scanf("%s", find_house);
      printf("Количесвто работ:%d\n",
             count_works_of_isd(get_tail(result), find_house));
      break;
    case 3:
      printf("Количесвто объёма: %d\n", count_volume(get_tail(result)));
      break;
    case 4:
      printf("Введите имя автора, работы которого хотите найти:");
      scanf("%s", find_author);
      find_of_author(get_tail(result), find_author);
      break;
    case 5:
      printf("Введите год, работы которого хотите подсчитать: ");
      scanf("%d", &find_year);

      find_by_year(get_tail(result), find_year);

      break;

    case 6:
      printf("Введите режим сортировки:\n0-от меньшего к большему\n 1 - от "
             "большего к меньшему\n");

      while (scanf("%d", &rezjim_of_sort) != 1 ||
             !(rezjim_of_sort >= 0 && rezjim_of_sort < 2))
        ;
      fptr_for_year_sort =
          rezjim_of_sort ? sort_year_small_to_big : sort_year_big_to_small;
      result = get_tail(Sort_for_year(get_tail(result), fptr_for_year_sort));
      break;
    case 7:
      printf("Введите режим сортировки:\n0-от меньшего к большему\n 1 - от "
             "большего к меньшему\n");

      while (scanf("%d", &rezjim_of_sort) != 1 ||
             !(rezjim_of_sort >= 0 && rezjim_of_sort < 2))
        ;
      fptr_for_autrhor_sort = rezjim_of_sort ? comparison_str_small_to_big
                                             : comparison_str_big_to_small;
      result =
          get_tail(Sort_for_author(get_tail(result), fptr_for_autrhor_sort));
      break;
    case 8:
      printf("Введите номер эллемента которого хотите удалить\n");
      scanf("%d", &num);
      result = pop(get_tail(result), num);
      break;
    case 9:
      result = add_obj(result, 0);
      break;
    case 10:
      printf("Введите имя файла: ");
      scanf("%s", file_name);
      file = fopen(file_name, "w");
      if (file) {
        printf_struct(result, file);
        fclose(file);
      } else {
        printf("error!");
      }
      break;
    case 11:
    printf("Введите имя файла: ");
      scanf("%s", file_name);
      file = fopen(file_name, "r");
      if (file) {
        result = scanf_new_struct(result, file);
        fclose(file);
      } else {
        printf("error!");
      }
      break;
    case 12:
      free_libs(get_tail(result));
      result = NULL;
      break;
    default:
      fflush(stdin);
      scanf("%[^\n]s", buf);
      break;
    }
    if (rezjim >= 6) {
      output(result);
    }
    print_reajims();
  }
  free_libs(get_tail(result));
  return 0;
}

void print_reajims() {
  printf(
      "Выберете режим вывода:\n1 - Количесвто работ\n2 - кол-во работ определённого дома\n\
3 - количесвто сумарного объёма \n4 - найти по автору \n5 - найти по году\n6 - сортировка по году\n\
7 - сортировка по автору.\n8 - удаление\n9 - вставка\n10-вывод в файл\n11-считывание с файла\n 12 - удаление структуры\n0 - выход\n");
}

lib_write *add_obj(lib_write *result, int num) {
  printf("Введите номер эллемента перед которым хотите доабвить\n");
  scanf("%d", &num);
  lib_write *new_lib = malloc(sizeof(lib_write));
  input(new_lib);
  result = push(get_tail(result), new_lib, num);
  return result;
}

int input(lib_write *lib) {
  int year_of_publishing = 0;
  int volume = 0;
  printf("Введите наименование: ");
  scanf("%s", lib->name);
  printf("Введите имя автора: ");
  scanf("%s", lib->author);
  printf("Введите место публикации: ");
  scanf("%s", lib->place);
  printf("Введите пуб: ");
  scanf("%s", lib->publishing_house);
  printf("Введите год публикации: ");
  while (scanf("%d", &year_of_publishing) != 1 || year_of_publishing > 2024) {
    printf("Неверный ввод");
    printf("Введите год публикации: ");
    fflush(stdin);
    scanf("%*[^\r\n]");
  }
  printf("Введите объём: ");
  while (scanf("%d", &volume) != 1 || volume < 0) {
    printf("Неверный ввод");
    printf("Введите объём: ");
    fflush(stdin);
    scanf("%*[^\r\n]");
  }
  lib->year_of_publishing = year_of_publishing;
  lib->volume = volume;
  return 0;
}

int count_works(lib_write *first_lib) {
  int result = 1;
  lib_write *next_lib = first_lib->next;
  while (next_lib != NULL) {
    result++;
    next_lib = next_lib->next;
  }
  return result;
}

int count_works_of_isd(lib_write *first_lib, char *publishing_house) {
  int result = !strcmp(first_lib->publishing_house, publishing_house);
  lib_write *next_lib = first_lib->next;
  while (next_lib != NULL &&
         !strcmp(next_lib->publishing_house, publishing_house)) {
    result++;
    next_lib = next_lib->next;
  }
  return result;
}

int count_volume(lib_write *first_lib) {
  int result = first_lib->volume;
  lib_write *next_lib = first_lib->next;
  while (next_lib != NULL) {
    result += next_lib->volume;
    next_lib = next_lib->next;
  }
  return result;
}

void find_of_author(lib_write *first_lib, char *author_phind) {
  int result = !!strcmp(first_lib->author, author_phind);
  lib_write tmp = {0};
  if (!result) {
    tmp = *first_lib;
    tmp.next = NULL;
    tmp.prev = NULL;
    output(&tmp);
    return;
  }

  lib_write *next_lib = first_lib->next;
  while (next_lib != NULL && result) {
    result = !!strcmp(next_lib->author, author_phind);
    if (!result)
      break;
    next_lib = next_lib->next;
  }
  if (result) {
    return;
  }
  tmp = *next_lib;
  tmp.next = NULL;
  tmp.prev = NULL;
  output(&tmp);
}

void find_by_year(lib_write *first_lib, int year_phind) {
  int result = first_lib->year_of_publishing == year_phind ? 1 : 0;
  lib_write tmp = {0};
  if (result) {
    tmp = *first_lib;
    tmp.next = NULL;
    tmp.prev = NULL;
    output(&tmp);
    return;
  }
  lib_write *next_lib = first_lib->next;
  while (next_lib != NULL) {
    result = next_lib->year_of_publishing == year_phind ? 1 : 0;
    if (result)
      break;
    next_lib = next_lib->next;
  }
  if (!result) {
    return;
  }
  tmp = *next_lib;
  tmp.next = NULL;
  tmp.prev = NULL;
  output(&tmp);
}

int get_all_adress(lib_write *tail) {
  while (tail != NULL) {
    printf("%p %p = %p\n", tail->prev, tail->next, tail);
    tail = tail->next;
  }
  return 0;
}

lib_write *Sort_for_year(lib_write *first_lib,
                         int(fptr)(lib_write *first_lib, lib_write *next_lib)) {
  int i, j, high = get_size(get_tail(first_lib));
  lib_write *next_lib = first_lib->next, *next_lib2 = first_lib;

  for (i = 1; i < high; i++, next_lib = get_num_lib(get_tail(next_lib), i)) {
    next_lib2 = get_num_lib(get_tail(next_lib), 0);
    for (j = 0; j < i; j++, next_lib2 = get_num_lib(get_tail(next_lib), j)) {
      if (!fptr(next_lib2, next_lib))
        swap(next_lib2, next_lib);
      next_lib = get_num_lib(get_tail(next_lib), i);
    }
  }
  return first_lib;
}

int get_size(lib_write *tail) {
  int res = 0;
  for (; tail; res++, tail = tail->next)
    ;
  return res;
}

lib_write *Sort_for_author(lib_write *first_lib,
                           int(fptr)(lib_write *first_lib,
                                     lib_write *next_lib)) {
  int i, j, high = get_size(get_tail(first_lib));
  lib_write *next_lib = first_lib->next, *next_lib2 = first_lib,
            *result = first_lib;
  for (i = 1; i < high; i++, next_lib = get_num_lib(get_tail(next_lib), i)) {
    next_lib2 = get_num_lib(get_tail(next_lib2), 0);
    for (j = 0; j < i; j++, next_lib2 = get_num_lib(get_tail(next_lib2), j)) {
      if (!fptr(next_lib2, next_lib))
        swap(next_lib2, next_lib);
      next_lib = get_num_lib(get_tail(next_lib), i);
    }
  }
  return result;
}

int sort_year_small_to_big(lib_write *first_lib, lib_write *next_lib) {
  int result = 1;
  if (first_lib->year_of_publishing < next_lib->year_of_publishing) {
    result = 0;
  }
  return result;
}

int sort_year_big_to_small(lib_write *first_lib, lib_write *next_lib) {
  int result = 1;
  if (first_lib->year_of_publishing > next_lib->year_of_publishing) {
    result = 0;
  }
  return result;
}

lib_write *get_end_lib(lib_write *first_lib) {
  while (first_lib->next != NULL) {
    first_lib = first_lib->next;
  }
  return first_lib;
}

int comparison_str_small_to_big(lib_write *lib1, lib_write *lib2) {
  int res = 1;
  if (strcmp(lib1->author, lib2->author) > 0) {
    res = 0;
  }
  return res;
}

int comparison_str_big_to_small(lib_write *lib1, lib_write *lib2) {
  int res = 1;
  if (strcmp(lib1->author, lib2->author) < 0) {
    res = 0;
  }
  return res;
}

void swap(lib_write *lib1, lib_write *lib2) {
  lib_write *tmp;
  if (!lib2->prev) {
    tmp = lib1;
    lib1 = lib2;
    lib2 = tmp;
  }
  if (!lib1->next) {
    tmp = lib1;
    lib1 = lib2;
    lib2 = tmp;
  }

  if (lib1->prev == lib2 || lib2->prev == lib1) {
    if (lib2->prev == lib1)
      swap_neigborn(lib1, lib2);
    else
      swap_neigborn(lib2, lib1);
  } else if (lib1->prev && lib2->prev && lib1->next && lib2->next) {
    lib1->prev->next = lib2;
    lib2->prev->next = lib1;
    lib2->next->prev = lib1;
    lib1->next->prev = lib2;

    tmp = lib1->prev;
    lib1->prev = lib2->prev;
    lib2->prev = tmp;

    tmp = lib1->next;
    lib1->next = lib2->next;
    lib2->next = tmp;
  } else if ((!lib1->prev) && (!lib2->next)) {
    lib2->next = lib1->next;
    lib1->next->prev = lib2;
    lib1->next = NULL;
    lib1->prev = lib2->prev;
    lib2->prev->next = lib1;
    lib2->prev = NULL;
  } else if (!lib1->prev) {
    lib2->next->prev = lib1;
    lib1->next->prev = lib2;
    lib2->prev->next = lib1;

    lib1->prev = lib2->prev;
    lib2->prev = NULL;

    tmp = lib1->next;
    lib1->next = lib2->next;
    lib2->next = tmp;
  } else if (!lib2->next) {
    lib1->prev->next = lib2;
    lib2->prev->next = lib1;
    lib1->next->prev = lib2;

    lib2->next = lib1->next;
    lib1->next = NULL;

    tmp = lib2->prev;
    lib2->prev = lib1->prev;
    lib1->prev = tmp;
  }
}
int swap_neigborn(lib_write *lib1, lib_write *lib2) {
  if (lib1->prev && lib2->prev && lib1->next && lib2->next) {
    lib1->prev->next = lib2;
    lib2->next->prev = lib1;
    lib2->prev = lib1->prev;
    lib1->prev = lib2;
    lib1->next = lib2->next;
    lib2->next = lib1;
  } else if (!lib1->prev) {
    lib2->next->prev = lib1;
    lib1->next = lib2->next;
    lib1->prev = lib2;
    lib2->prev = NULL;
    lib2->next = lib1;
  } else if (!lib2->next) {
    lib1->prev->next = lib2;
    lib2->prev = lib1->prev;
    lib2->next = lib1;
    lib1->next = NULL;
    lib1->prev = lib2;
  }
  return 0;
}

lib_write *get_tail(lib_write *lib1) {
  if (!lib1)
    return NULL;
  for (; lib1->prev != NULL; lib1 = lib1->prev)
    ;
  return lib1;
}
lib_write *get_num_lib(lib_write *tail, int num) {
  for (; num > 0 && tail != NULL; num--, tail = tail->next)
    ;
  return tail;
}

int output(lib_write *first_lib) {
  lib_write *next_lib = first_lib;
  while (next_lib != NULL) {
    printf("name: %s\n", next_lib->name);
    printf("author: %s\n", next_lib->author);
    printf("place: %s\n", next_lib->place);
    printf("publishing_house: %s\n", next_lib->publishing_house);
    printf("year_of_publishing: %d\n", next_lib->year_of_publishing);
    printf("volume: %d\n", next_lib->volume);
    printf("\n");
    next_lib = next_lib->next;
  }
  printf("Вывод закончен!\n");
  return 0;
}

lib_write *pop(lib_write *tail, int num) {
  lib_write *del_elem = get_num_lib(tail, num);

  if(del_elem == tail) { 
    free_libs(tail);
    tail = NULL;
    del_elem =NULL;
  }

  if (del_elem) {
    lib_write *next, *prev;
    next = del_elem->next;
    prev = del_elem->prev;
    if (prev) {
      prev->next = next;
      tail = prev;
    }
    if (next) {
      next->prev = prev;
      tail = next;
    }
    free(del_elem);
    del_elem = NULL;
  }
  return tail;
}

lib_write *push(lib_write *tail, lib_write *new_elem, int num) {
  if (!new_elem)
    return tail;
  lib_write *next_elem = get_num_lib(tail, num);
  if (!next_elem)
    next_elem = push_tail(tail, new_elem);
  else {
    lib_write *prev = next_elem->prev;
    if (prev) {
      new_elem->prev = prev;
      prev->next = new_elem;
    }
    new_elem->next = next_elem;
    next_elem->prev = new_elem;
  }
  return next_elem;
}
lib_write *push_tail(lib_write *tail, lib_write *new_elem) {
  if (!tail) {
    new_elem->next = NULL;
    new_elem->prev = NULL;
    return new_elem;
  }
  lib_write *last_elem = get_end_lib(tail);
  if (last_elem) {
    last_elem->next = new_elem;
    new_elem->prev = last_elem;
    new_elem->next = NULL;
  } else {
    new_elem->next = NULL;
    new_elem->prev = NULL;
    tail = new_elem;
  }
  return tail;
}

int printf_struct(lib_write *tail, FILE *dst) {
  lib_write *next_lib = tail;
  while (next_lib != NULL) {
    fprintf(dst, "%s\n", next_lib->name);
    fprintf(dst, "%s\n", next_lib->author);
    fprintf(dst, "%s\n", next_lib->place);
    fprintf(dst, "%s\n", next_lib->publishing_house);
    fprintf(dst, "%d\n", next_lib->year_of_publishing);
    fprintf(dst, "%d\n", next_lib->volume);
    next_lib = next_lib->next;
  }
  return 0;
}

lib_write *scanf_new_struct(lib_write *tail, FILE *src) {
  int err = 0, len = 0;
  char *str = malloc(50 * sizeof(char));
  if (!str) {
    printf("Ошибка выделения!");
    return tail;
  }
  while (!err && fgets(str, 50, src) != NULL) {
    while (!strcmp(str, "\n") && fgets(str, 50, src) != NULL)
      ;
    str[strlen(str) - 1] = 0;
    lib_write *lib = malloc(sizeof(lib_write));
    if (!lib) {
      free(str);
      printf("Ошибка выделения!");
      return tail;
    }
    strcpy(lib->name, str);

    if (!err && fgets(str, 50, src) == NULL) {
      err = 1;
    }
    if (!err) {
      while (!strcmp(str, "\n") && fgets(str, 50, src) != NULL)
        ;
      str[strlen(str) - 1] = 0;
      strcpy(lib->author, str);
    }

    if (!err && fgets(str, 50, src) == NULL) {
      err = 1;
    }
    if (!err) {
      while (!strcmp(str, "\n") && fgets(str, 50, src) != NULL)
        ;
      len = strlen(str);
      if (str[len - 1] == '\n')
        str[len - 1] = 0;
      strcpy(lib->place, str);
    }

    if (!err && fgets(str, 50, src) == NULL) {
      err = 1;
    }
    if (!err) {
      while (!strcmp(str, "\n") && fgets(str, 50, src) != NULL)
        ;
      str[strlen(str) - 1] = 0;
      strcpy(lib->publishing_house, str);
    }

    if (!err && fgets(str, 50, src) == NULL) {
      err = 1;
    }
    if (!err) {
      while (!strcmp(str, "\n") && fgets(str, 50, src) != NULL)
        ;

      if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = 0;
      lib->year_of_publishing = atoi(str);
    }

    if (!err && fgets(str, 50, src) == NULL) {
      err = 1;
    }
    if (!err) {
      while (!strcmp(str, "\n") && fgets(str, 50, src) != NULL)
        ;
      if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = 0;
      lib->volume = atoi(str);
    }
    if(lib && !err)
      tail = push_tail(tail, lib);
  }
  if (feof(src)) {
    printf("File is read");
  }
  if (str)
    free(str);
  return tail;
}

int free_libs(lib_write *tail) {
  if (!tail)
    return 1;
  lib_write *next = tail->next;
  for (free(tail); next;) {
    tail = next->next;
    free(next);
    next = tail;
  }
  tail = NULL;
  return 0;
}