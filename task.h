#ifndef TASk_H
#define TASK_H

#include "table.h"

int TaskSearch(Table* res, Table* table, KeyType parentKey);
int TaskErase(Table* table, KeyType key);

#endif
