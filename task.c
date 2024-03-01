#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

int TaskSearch(Table* res, Table* table, KeyType parentKey) {
  if (table->ks == NULL) {
    return 2;
  }

  KeySpaceElem* current = table->ks;
  KeySpaceElem* resultCurrent = NULL;
  int flag = 0;
  
  while (current != NULL) {
    if (current->par == parentKey) {
      // Создаем новый элемент для найденного элемента
      KeySpaceElem* newElement = (KeySpaceElem*)malloc(sizeof(KeySpaceElem));
      newElement->key = current->key;
      newElement->par = current->par;
      newElement->info = current->info;
      newElement->next = NULL;
      flag = 1;
      // Добавляем новый элемент в результатирующую таблицу
      if (res->ks == NULL) {
        res->ks = newElement;
        resultCurrent = newElement;
      } else {
        resultCurrent->next = newElement;
        resultCurrent = resultCurrent->next;
      }
    }
    current = current->next;
  }
  if (!flag) {
    return 1;
  }
  return 0;  // Успешное выполнение
}

int TaskErase(Table* table, KeyType key) {
  if (table->ks == NULL) {
    return 2;
  }
  
  KeySpaceElem* current = table->ks;
  KeySpaceElem* previous = NULL;

  // Поиск элемента с заданным ключом
  while (current != NULL && current->key != key) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    // Элемент с заданным ключом не найден
    return 1;
  }

  // Удаление элемента
  if (previous == NULL) {
    // Удаляемый элемент - первый в списке
    table->ks = current->next;
  } else {
    previous->next = current->next;
  }

  // Рекурсивное удаление элементов, ссылающихся на удаляемый
  TaskErase(table, current->par);

  // Освобождение памяти
  free(current);

  return 0;
}
