# ifndef __SORTEDLIST_H__
# define __SORTEDLIST_H__

# include <stddef.h> /* size_t */
# include "dlist.h"


typedef struct sorted_list sr_list_t;

struct sorted_list_iter
{
    dl_iter_t dl_iter;
    
#ifndef NDEBUG
    const sr_list_t *origin_list;
#endif /* NDEBUG */
};

typedef struct sorted_list_iter sr_iter_t;

/* creates a new empty sorted list, returns it on allocation success,
    params: compare returns a positive integer if 'd1' should be after 'd2', 0 if their order is the same, and a negative number if 'd1' should be before 'd2'
    return: 
    		on Fail: NULL
    		on succes: srlist
*/
/* O(1) */
sr_list_t *SortedLCreate(int (*compare)(const void *d1, const void *d2));

/* frees the valid sorted list it gets */
/* O(n) */
void SortedLDestroy(sr_list_t *srlist);

/* returns the data inside the node, pointed by 'iter' */
/* O(1) */
void *SortedLGetData(sr_iter_t iter);

/* returns an iterator to the first valid element */
/* O(1) */
sr_iter_t SortedLBegin(const sr_list_t *srlist);

/* returns an iterator to the last valid element's next */
/* O(1) */
sr_iter_t SortedLEnd(const sr_list_t *srlist);

/* returns an iterator after the given one */
/* O(1) */
sr_iter_t SortedLNext(sr_iter_t iter);

/* returns an iterator to the node previous to the given node */
/* O(1) */
sr_iter_t SortedLPrev(sr_iter_t iter);

/* returns 0 if the specified iterators point to different nodes */
/* returns another number if both specified iterators point to
    the same node */
/* O(1) */
int SortedLIsIterEqual(sr_iter_t i1, sr_iter_t i2);

/* returns the size of the srlist */
/* O(n) */
/* use foreach function (in the dlist implementation) */
size_t SortedLSize(const sr_list_t *srlist);

/* returns 1 if srlist is empty, 0 otherwise */
/* O(1) */
int SortedLIsEmpty(const sr_list_t *srlist);

/* inserts a new node with the specified data in its sorted place*/
/* returns an iterator to the inserted node or to end on failure */
/* O(n) */
sr_iter_t SortedLInsert(sr_list_t *srlist, void *data);

/* Removes the given iter ator of srlist and returns the next iterator */
/* given iterator must be valid */
/* O(1) */
sr_iter_t SortedLRemove(sr_iter_t iter);

/* removes the last valid member and returns its data */
/* O(1) */
void *SortedLPopBack(sr_list_t *srlist);

/* removes the first valid member and returns its data*/
/* O(1) */
void *SortedLPopFront(sr_list_t *srlist);

/* Returns an iterator, pointing to a node between 'from' and 'to' */
/* whose value matches the specified data*/
/* if a match wasn't found, returns 'to' */
/* is_match = 0 on mismatch, non-zero otherwise */
/* O(n) */
/* assert that 'from' & 'to' are from the same list */
sr_iter_t SortedLFindIf(sr_iter_t from, sr_iter_t to,
    const void *data, int (*is_match)(const void *, const void *));

/* Returns an iterator, pointing to a node between 'from' and 'to' */
/* whose value matches the specified data*/
/* if a match wasn't found, returns 'to' */
/* comparison is done by the 'compare' function of the 'srlist',
    which returns 0 on match and none zero depending on the order */
/* O(n) */
/* assert that 'from' & 'to' are from the same list */
sr_iter_t SortedLFind(sr_iter_t from, sr_iter_t to,
    const void *data, sr_list_t *srlist);

/* performs the specified action on all elements in range */
/* returns 0 on success or another number otherwise */
/* halts execution on first failure of action and returns non-0 */
/* assert that 'from' & 'to' are from the same list */
/* O(n) */
int SortedLForEach(sr_iter_t from, sr_iter_t to,
    int (*action)(void *data, void *param), void *param);

/* incorporates all nodes in given range into the list in the
    correct order */
/* while removing them from their original place */
/* the 2 lists share the same compare function */
/* assert that 'from' & 'to' are from the same list */
/* O(n) */
void SortedLMerge(sr_list_t *dest, sr_list_t *src);


# endif /* __SORTEDLIST_H__ */
