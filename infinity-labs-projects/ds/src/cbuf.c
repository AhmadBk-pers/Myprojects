/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Circular buffer module
* Group         OL110
* Company       ILRD Ramat Gan
* *****************************************************************************/

#include <assert.h> /* assert()   */
#include <stdio.h>  /* printf()   */
#include <stdlib.h> /* malloc()   */
#include <stddef.h> /* offsetof() */
#include <string.h> /* memcpy() */

#include "cbuf.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

struct cb {
    size_t head;
    size_t size;
    size_t capacity;
    char buf[1];
};


cbuff_t *CBCreate(size_t capacity)
{
	cbuff_t *cbuff = (cbuff_t *)malloc(offsetof(cbuff_t, buf) + capacity);
	
	if (!(cbuff))
    {
        return NULL;
    }
    
    cbuff->head = 0;
    cbuff->size = 0;
    cbuff->capacity = capacity;
    
    return cbuff;
}

void CBDestroy(cbuff_t *cbuff)
{
	free(cbuff);
	cbuff = NULL;
}

size_t CBFreeSpace(const cbuff_t *cbuff)
{
	assert(cbuff);
	
	return ((cbuff->capacity) - (cbuff->size));
}

size_t CBBufsiz(const cbuff_t *cbuff)
{
	assert(cbuff);
	
	return (cbuff->capacity);
}

/* returns the number of bytes read */
ssize_t CBRead(cbuff_t *cbuff, void *buf, size_t count)
{
	char *original_buff = NULL;
	size_t bytes_to_read = 0, bytes_read = 0;
	
	assert(cbuff);
	assert(buf);

	if (count > cbuff->size)
    {
        count = cbuff->size;
        bytes_to_read = cbuff->size;
    }
	
	original_buff = cbuff->buf + cbuff->head;
	bytes_to_read = MIN((cbuff->capacity - cbuff->head), count);
	count -= bytes_to_read;
	bytes_read += bytes_to_read;
	
	memcpy(buf, original_buff, bytes_to_read);
	cbuff->size -= bytes_to_read;
	buf = (char *)buf + bytes_to_read;
	cbuff->head = (cbuff->head + bytes_to_read) % cbuff->capacity;
	
	if (count > 0)
	{
		original_buff = cbuff->buf + cbuff->head;
		bytes_to_read = count;
		bytes_read += count;
		
		memcpy(buf, original_buff, bytes_to_read);
		cbuff->size -= bytes_to_read;
		buf = (char *)buf + bytes_to_read;
		cbuff->head = (cbuff->head + bytes_to_read) % cbuff->capacity;
	}
	
	return bytes_read;
}

/* returns the number of bytes written */
ssize_t CBWrite(cbuff_t *cbuff, const void *buf, size_t count)
{
	char *original_buff = NULL;
	size_t bytes_to_write = 0, bytes_written = 0;
	
	assert(cbuff);
	assert(buf);

	if (count > CBFreeSpace(cbuff))
    {
        count = CBFreeSpace(cbuff);
        bytes_to_write = CBFreeSpace(cbuff);
    }
	
	original_buff = cbuff->buf + ((cbuff->head + cbuff->size) % cbuff->capacity);
	bytes_to_write = MIN(count, (cbuff->capacity - (cbuff->head + cbuff->size)));
	count -= bytes_to_write;
	bytes_written += bytes_to_write;
	
	memcpy(original_buff, buf, bytes_to_write);
	cbuff->size += bytes_to_write;
	buf = (char *)buf + bytes_to_write;
	
	if (count > 0)
	{
		original_buff = cbuff->buf + ((cbuff->head + cbuff->size) % cbuff->capacity);
		bytes_to_write = count;
		bytes_written += count;
		
		memcpy(original_buff, buf, bytes_to_write);
		cbuff->size += bytes_to_write;
		buf = (char *)buf + bytes_to_write;
	}
	
	return bytes_written;
}

int CBIsEmpty(const cbuff_t *cbuff)
{
	assert(cbuff);
	
	return (0 == cbuff->size);
}
