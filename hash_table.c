#include "hash_table.h"
#include <string.h>
#include <stdio.h>

struct Bucket {
  char *key;
  void *data;
  ValueType type;
  Bucket *next;
};

struct HashTable {
  size_t size;
  HashFunc hash;
  Bucket **buckets;
};

HashTable *hash_table_init(size_t size, HashFunc hash) {
  HashTable *ht = malloc(sizeof(HashTable));
  if (ht == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  ht->size = size;
  ht->hash = hash;
  ht->buckets = calloc(ht->size, sizeof(*ht->buckets));
  if (ht->buckets == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  return ht;
}

bool hash_table_insert(HashTable *ht, char *key, void *data, ValueType type) {
  if (!ht || !key || !data) {
    fprintf(stderr, "Received hash table, key or data as NULL.\n");
    exit(EXIT_FAILURE);
  }

  size_t index = ht->hash(key) % ht->size;

  if (hash_table_get(ht, key) != NULL) {
    fprintf(stderr, "Cannot have duplicate keys in hash table.\n");
    exit(EXIT_FAILURE);
  }

  Bucket *bucket = malloc(sizeof(Bucket));
  if (bucket == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  bucket->key = malloc(strlen(key) + 1);
  strcpy(bucket->key, key);
  bucket->data = data;
  bucket->type = type;

  bucket->next = ht->buckets[index];
  ht->buckets[index] = bucket;

  return true;
}

void *hash_table_get(HashTable *ht, char *key) {
  if (!ht || !key) {
    fprintf(stderr, "Received hash table, key or data as NULL.\n");
    exit(EXIT_FAILURE);
  }

  size_t index = ht->hash(key) % ht->size;

  Bucket *curr = ht->buckets[index];
  while (curr != NULL && strcmp(curr->key, key) != 0) {
    curr = curr->next;
  }

  if (curr == NULL) return NULL;

  return curr->data;
}

bool hash_table_delete(HashTable *ht, char *key) {
  if (!ht || !key) {
    fprintf(stderr, "Received hash table or key as NULL.\n");
    exit(EXIT_FAILURE);
  }

  size_t index = ht->hash(key) % ht->size;
  
  Bucket *prev = NULL;
  Bucket *curr = ht->buckets[index];
  while (curr) {
    if (strcmp(curr->key, key) == 0) {
      printf("Deleting a key '%s'\n", curr->key);

      if (prev) {
        prev->next = curr->next;
      } else {
        // deleting a head
        ht->buckets[index] = curr->next;
      }

      free(curr->key);
      free(curr);

      return true;
    }

    prev = curr;
    curr = curr->next;
  }

  return false;
}

void hash_table_destroy(HashTable *ht) {
  if (!ht) return;

  for (size_t i = 0; i < ht->size; i++) {
    if (ht->buckets[i] == NULL) continue;

    Bucket *curr = ht->buckets[i];
    while (curr) {
      Bucket *tmp = curr->next;

      free(curr->key);
      free(curr);

      curr = tmp;
    }
  }

  free(ht->buckets);
  free(ht);
}

void hash_table_print(HashTable *ht) {
  if (!ht) return;

  for (size_t i = 0; i < ht->size; i++) {
    if (ht->buckets[i] == NULL) continue;
    Bucket *curr = ht->buckets[i];
    while (curr) {
      if (curr->type == INT) {
        printf("[%zu] key=%s value=%d\n", i, curr->key, *(int*)curr->data);
      }

      if (curr->type == DOUBLE) {
        printf("[%zu] key=%s value=%.2f\n", i, curr->key, *(double*)curr->data);
      }

      if (curr->type == CHAR) {
        printf("[%zu] key=%s value=%s\n", i, curr->key, (char*)curr->data);
      }

      curr = curr->next;
    }
  }
}
