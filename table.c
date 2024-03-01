#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

KeySpaceElem *new_key_space() {
  KeySpaceElem *ks = (KeySpaceElem *) calloc(1, sizeof(KeySpaceElem));
  ks->info = 0;
  ks->key = 0;
  ks->par = 0;
  ks->next = NULL;
  return ks;
}

Table *new_table() {
  Table *table = (Table *) calloc(1, sizeof(Table));
  table->ks = NULL;
  return table;
}

int load(char **name, Table* table) {
  FILE *file = fopen(*name, "r");
  if (file == NULL) {
    return 1;
  }
  KeyType key;
  KeyType par;
  InfoType info;
  int count = 0;
  while (fscanf(file, "%u\n%u\n%u\n", &key, &par, &info) == 3) {
    insert(table, key, par, info);
    count++;
  }
  if (!count) {
    fclose(file);
    return 1;
  }
  fclose(file);
  return 0;
}

int insert(Table *table, KeyType key, KeyType parent, InfoType info) {
  // Проверяем, что элемент с таким ключом не существует
  KeySpaceElem *curr = table->ks;
  while (curr != NULL) {
    if (curr->key == key) {
      return 1;
    }
    curr = curr->next;
  }
  // Выделяем память на новый узел
  KeySpaceElem *node = new_key_space();
  node->key = key;
  node->par = parent;
  node->info = info;
  node->next = NULL;
  // Вставляем новый узел
  node->next = table->ks;
  table->ks = node;
  return 0;
}

int erase(Table* table, int key) {
  // Проверка пустоты таблицы
  if (table->ks == NULL) {
    return 2;
  }
  KeySpaceElem *prev = NULL;
  KeySpaceElem *curr = table->ks;
  while (curr != NULL) {
    if (curr->key == key) {
      if (prev == NULL) {
        // Если удаляемый элемент первый в списке
        table->ks = curr->next;
      } else {
        // Если удаляемый элемент находится в середине или конце списка
        prev->next = curr->next;
      }

      free(curr);
      return 0;
    }
    prev = curr;
    curr = curr->next;
  }
  // Элемента с таким ключом не найдено
  return 1;
}

int search(Table *table, KeyType key, KeySpaceElem **elem) {
  // Проверка пустоты таблицы
  if (table->ks == NULL) {
    return 2;
  }
  KeySpaceElem *curr = table->ks;
  *elem = NULL;
  int found = 0;
  while (curr != NULL) {
    if (curr->key == key) {
      KeySpaceElem *node = new_key_space();
      node->key = curr->key;
      node->info = curr->info;
      node->par = curr->par;
      node->next = NULL;
      *elem = node;
      found = 1;
      break;
    }
    curr = curr->next;
  }
  if (!found) {
    return 1;
  } else {
    return 0;
  }
}

int printTable(Table *table) {
  if (table->ks == NULL) {
    return 1;
  }
  KeySpaceElem *curr = table->ks;
  while (curr != NULL) {
    printf("Key: %u, Parent: %u, Info: %u\n", curr->key, curr->par, curr->info);
    curr = curr->next;
  }
  return 0;
}

int clearTable(Table *table) {
  if (table->ks == NULL) {
    free(table);
    return 1;
  }
  KeySpaceElem *curr = table->ks;
  KeySpaceElem *next;
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  free(table);
  return 0;
}
