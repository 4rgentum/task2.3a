#ifndef TABLE_H
#define TABLE_H

typedef unsigned int KeyType;
typedef unsigned int IndexType;
typedef unsigned int InfoType;

typedef struct KeySpaceElem {
  KeyType key;
  KeyType par;
  InfoType info;
  struct KeySpaceElem *next;
} KeySpaceElem;

typedef struct Table {
  KeySpaceElem *ks;
} Table;

KeySpaceElem *new_key_space();
Table *new_table();
int load(char **file, Table* table);
int insert(Table *table, KeyType key, KeyType parent, InfoType info);
int erase(Table* table, int key);
int search(Table *table, KeyType key, KeySpaceElem **elem);
int printTable(Table *table);
int clearTable(Table *table);

#endif
