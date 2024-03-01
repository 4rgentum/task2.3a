#ifndef DIALOG_H
#define DIALOG_H

#include "table.h"
#include "get.h"
#include "task.h"

int D_load(Table* table);
int D_Insert(Table *table);
int D_Erase(Table *table);
int D_Search(Table *table);
int D_Print(Table *table);
int D_TaskSearch(Table* table);
int D_TaskErase(Table* table);
int dialog(const char* msgs[], int flag);

#endif
