/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ------
* Description   Hash Table module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/


#include <assert.h>
#include <stdlib.h>

#include "s_list.h"		/*	single list API_File*/
#include "hash_t.h"    /* hash table API           */

static void HashTableDestroy(slist_t **hash_table, size_t size);
static int HashInsert(slist_t *hash, void *data);

struct h_table
{
	size_t hash_entries;
	slist_t **hash_table;
    hash_function_t hash_function;
    find_func_t compare;
};

h_table_t *HTCreate(size_t hash_entries, hash_function_t hash_function, find_func_t compare)
{
	h_table_t *h_table = (h_table_t *)malloc(sizeof(h_table_t));
	if (h_table == NULL)
	{
		return NULL;
	}
	
	h_table->hash_table = (slist_t **)calloc(hash_entries, sizeof(slist_t *));
	if (h_table->hash_table == NULL)
	{
		free(h_table);
		h_table = NULL;
		
		return NULL;
	}
	
	h_table->hash_entries = hash_entries;
	h_table->hash_function = hash_function;
	h_table->compare = compare;
	
	return h_table;
}

void HTDestroy(h_table_t *h_table)
{
	assert(h_table);
	
	HashTableDestroy(h_table->hash_table, h_table->hash_entries);
	h_table->hash_table = NULL;
	
	h_table->hash_function = NULL;
	h_table->compare = NULL;
	
	free(h_table);
	h_table = NULL;
}

size_t HTSize(const h_table_t *h_table)
{
	size_t i = 0, size = 0, hash_entries = 0;
	slist_t **hash_table = NULL;
	
	assert(h_table);
	
	hash_entries = h_table->hash_entries;
	hash_table = h_table->hash_table;
	
	for (i = 0; i < hash_entries; i++)
	{
		if (hash_table[i] != NULL)
		{
			size += SLCount(hash_table[i]);
		}
	}
	
	return size;
}

int HTIsEmpty(const h_table_t *h_table)
{
	assert(h_table);
	
	return !HTSize(h_table);
}

int HTInsert(h_table_t *h_table, void *data)
{
	int index = 0;
	slist_t **hash_table = NULL;

	assert(h_table);
	assert(data);

	hash_table = h_table->hash_table;
	index = h_table->hash_function(data);

	if (hash_table[index] == NULL)
	{
		hash_table[index] = SLCreate();
		return HashInsert(hash_table[index], data);
	}
	else
	{
		return HashInsert(hash_table[index], data);
	}
}

void *HTRemove(h_table_t *h_table, const void *data)
{
	int index = 0;
	slist_t **hash_table = NULL;
	sl_iter_t search_result = NULL;

	assert(h_table);
	assert(data);

	hash_table = h_table->hash_table;
	index = h_table->hash_function(data);

	if (hash_table[index] == NULL)
	{
		return NULL;
	}
	
	search_result = SLFind(hash_table[index], data, h_table->compare);

	if (SLIterIsEqual(SLEnd(hash_table[index]), search_result))
	{
		return NULL;
	}
	else
	{
		SLRemove(search_result);
		return (void *)data;
	}
}

void *HTFind(const h_table_t *h_table, const void *data)
{
	int index = 0;
	slist_t **hash_table = NULL;
	sl_iter_t search_result = NULL;

	assert(h_table);
	assert(data);

	hash_table = h_table->hash_table;
	index = h_table->hash_function(data);

	if (hash_table[index] == NULL)
	{
		return NULL;
	}
	
	search_result = SLFind(hash_table[index], data, h_table->compare);

	if (SLIterIsEqual(SLEnd(hash_table[index]), search_result))
	{
		return NULL;
	}
	else
	{
		return SLGetValue(search_result);
	}
}

int HTForEach(h_table_t *h_table, action_func_t action, void *param)
{
	size_t i = 0, status = 0, hash_entries = 0;
	slist_t **hash_table = NULL;
	
	assert(h_table);
	
	hash_entries = h_table->hash_entries;
	hash_table = h_table->hash_table;
	
	for (i = 0; i < hash_entries && !status; i++)
	{
		if (hash_table[i] != NULL)
		{
			status = SLForEach(SLBegin(hash_table[i]), SLEnd(hash_table[i]), action, param);
		}
	}
	
	return status;
}



static void HashTableDestroy(slist_t **hash_table, size_t size)
{
	size_t i = 0;
	
	assert(hash_table);	
		
	for (i = 0; i < size; i++)
	{
		if (hash_table[i] != NULL)
		{
			SLDestroy(hash_table[i]);
		}
	}
	
	free(hash_table);
	hash_table = NULL;
}

static int HashInsert(slist_t *hash, void *data)
{
	assert(hash);
	assert(data);

	return SLIterIsEqual(SLEnd(hash), SLAddBefore(SLEnd(hash), data));
}
