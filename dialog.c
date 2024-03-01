#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialog.h"

int D_load(Table* table) {
  const char* errmsgs[]={"Table Is Loaded", "File Can't Be Open"}; 
  printf("Input File Name:\n");
  char *name = readline();
  if (!name) {
    printf("End");
    return 1;
  }
  int rc = load(&name, table);
  printf("\n");
  printf("%s %s\n", errmsgs[rc], name);
  free(name);
  return 1;
}

int D_Insert(Table* table) {
  int rc;
  const char* errmsgs[] = {"Ok", "Duplicate"};
  printf("Input Key:\n");
  KeyType key = get_unsigned_int();
  if (key == -1){ 
    printf("End Of File\n");
    return 0; 
  }
  printf("Input Parent:\n");
  KeyType par = get_unsigned_int();
  if (par == -1){ 
    printf("End Of File\n");
    return 0;
  }
  printf("Input Info:\n");
  InfoType info = get_unsigned_int();
  if (info == -1){ 
    printf("End Of File\n");
    return 0;
  }
  rc = insert(table, key, par, info);
  printf("\n");
  printf("%s: %u\n",errmsgs[rc], key);
  return 1;
}

int D_Erase(Table* table) {
  int rc;
  printf("Input Key:\n");
  KeyType key = get_unsigned_int();
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist", "Table Is Empty"};
  if (key == -1){ 
    printf("End Of File\n");
    return 0; 
  }
  rc = erase(table, key);
  printf("\n");
  printf("%s \n",errmsgs[rc]);
  return 1;
}

int D_Search(Table *table){
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist", "Table Is Empty"};
  printf("Input Key:\n");
  KeyType key = get_unsigned_int();
  if (key == -1){ 
    printf("End Of File\n");
    return 0; 
  }
  KeySpaceElem *elem = new_key_space();
  int rc = search(table, key, &elem);
  if (!rc) {
    printf("Key: %u, Parent: %u, Info: %u\n", elem->key, elem->par, elem->info);
  }
  printf("\n");
  printf("%s \n",errmsgs[rc]);
  free(elem);
  return 1;
}

int D_Print(Table* table) {
  int rc;
  const char* errmsgs[] = {"Ok", "Table Is Empty"};
  rc = printTable(table);
  printf("\n");
  printf("%s \n",errmsgs[rc]);
  return 1;
}

int D_TaskSearch(Table* table) {
  int rc;
  printf("Input Parent:\n");
  KeyType par = get_unsigned_int();
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist", "Table Is Empty"};
  if (par == -1) { 
    printf("End Of File\n");
    return 0; 
  }
  Table *res = new_table();
  rc = TaskSearch(res, table, par);
  if (!rc) {
    printTable(res);
    clearTable(res);
    return 1;
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  clearTable(res);
  return 1;
}

int D_TaskErase(Table* table) {
  int rc;
  printf("Input Key:\n");
  KeyType key = get_unsigned_int();
  const char* errmsgs[] = {"Ok", "This Element Doesn't Exist", "Table Is Empty"};
  if (key == -1) { 
    printf("End Of File\n");
    return 0; 
  }
  rc = TaskErase(table, key);
  if (rc != 1 || rc != 2) {
    printf("\n");
    printf("%s \n", errmsgs[0]);
    return 1;
  }
  printf("\n");
  printf("%s \n", errmsgs[rc]);
  return 1;
}

int dialog(const char* msgs[], int flag){
  char* errmsg = "";
  int rc;
  do {
    puts(errmsg);
    errmsg = "Invalid Input, Repeat\n";
    for (int i = 0; i < flag; i++) {
      puts(msgs[i]);
    }
    puts("Enter:\n");
    rc = get_int();
    printf("\n");
    
  } while (rc < 0 || rc >= flag);
  return rc;
}
