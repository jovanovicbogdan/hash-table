#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define FNV_OFFSET_BASIS 0xcbf29ce484222325
#define FNV_PRIME 0x100000001b3

typedef size_t (*HashFunc)(const char *key);

typedef enum {
  INT,
  DOUBLE,
  CHAR
} ValueType;
typedef struct Bucket Bucket;
typedef struct HashTable HashTable;

HashTable *hash_table_init(size_t size, HashFunc hash);
bool hash_table_insert(HashTable *ht, char *key, void *data, ValueType type);
void *hash_table_get(HashTable *ht, char *key);
bool hash_table_delete(HashTable *ht, char *key);
void hash_table_destroy(HashTable *ht);
void hash_table_print(HashTable *ht);
