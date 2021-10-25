/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Version       3                                          *
 ~ Author        OL110 Students                                  ~
 * Reviewer      Binyamin Hayman                                 *
 ~ Description   Hash_Table - API_File                           ~
 * Group         OL110                                           *
 ~ Company       ILRD Ramat Gan                                  ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __HASH_TABLE_OL_110_H__
#define __HASH_TABLE_OL_110_H__

#include <stddef.h> /* size_t */

typedef struct h_table h_table_t;
typedef int (*find_func_t)(const void *d1, const void *d2);
typedef int (*action_func_t)(void *data, void *param);
typedef size_t (*hash_function_t) (const void *data);

/* Input: the size of the hash table
      hash function - maps data to appropriately sized hash
      compare function - returns 0 if identical,
                a positive number if 'd1' should be after 'd2',
                and a negative number if 'd1' should be before 'd2'.
Return: hash_table_t pointer on success, NULL on failure. */
h_table_t *HTCreate(size_t hash_entries, hash_function_t hash_function, find_func_t compare);

void HTDestroy(h_table_t *h_table);

/* input: pointer to a valid hash table */
/* output: number of different keys inserted */
size_t HTSize(const h_table_t *h_table);

/* Return: non-zero if empty, 0 otherwise. */
int HTIsEmpty(const h_table_t *h_table);

/*  Return: 0 on success, non-zero on failure.
data is structure with key & value */
int HTInsert(h_table_t *h_table, void *data);

/*  Return: removed data or NULL if not found.
  data is structure with key & value */
void *HTRemove(h_table_t *h_table, const void *data);

/*  Return : found data or NULL if not found.
  data is structure with key & value */
void *HTFind(const h_table_t *h_table, const void *data);

/*  performs action on every entry.
  Return: 0 on success or action_failure_status otherwise,
  halts execution on first failure of action. */
int HTForEach(h_table_t *h_table, action_func_t action, void *param);

#endif /* __HASH_TABLE_OL_110_H__ */