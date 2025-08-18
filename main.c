#include "hash_table.h"
#include <string.h>

/** 
 * FNV-1a hash function implementation
 *
 * @see https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 */
size_t hash_fnv1a(const char *key) {
  uint64_t hash_value = FNV_OFFSET_BASIS;
  for (size_t i = 0; i < strlen(key); i++) {
    hash_value ^= (unsigned char)key[i];
    hash_value *= FNV_PRIME;
  }
  return hash_value;
}

int main() {
  const uint32_t table_size = (1 << 16);
  HashTable *ht = hash_table_init(table_size, hash_fnv1);

  int age = 42;

  hash_table_insert(ht, "name", "John", CHAR);
  hash_table_insert(ht, "age", &age, INT);

  hash_table_print(ht);

  hash_table_delete(ht, "age");

  hash_table_print(ht);

  hash_table_destroy(ht);

  return EXIT_SUCCESS;
}
