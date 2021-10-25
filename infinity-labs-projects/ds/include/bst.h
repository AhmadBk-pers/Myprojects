/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Version       5.0.0                                           *
 ~ Author        OL110 Students                                  ~
 * Reviewer      Yinon Yishay                                    *
 ~ Description   Binary Search Tree - Source_File                ~
 * Group         OL110                                           *
 ~ Company       ILRD Ramat Gan                                  ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __BST_OL_110_H__
#define __BST_OL_110_H__

#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct bst_node *bst_iter_t;

typedef int (*find_func)(const void *d1, const void *d2, void *param);
typedef int (*action_func)(void *data, void *param);


/* O(1) */
/* returns a pointer to bst, on success, or NULL on failure */
/* is_before returns 1 if first argument is before the second, and
	0 otherwise (even if are equal) */
bst_t *BSTCreate(find_func is_before, void *param); 

/* input: tree pointer */
/* destroys associated tree */
void BSTDestroy(bst_t *bst); 

/* input: tree pointer */
/* return: num of valid members in the tree */
size_t BSTSize(const bst_t *bst);

/* O(1) */
/* input: tree pointer */
/* return:                    */
/*      tree is empty -> 1    */
/*      tree isn't empty -> 0 */
int BSTIsEmpty(const bst_t *bst); 

/* returns an iterator to the new node holding 'data', on success,
	or "end" iterator on failure */
/* input:                       */
/*      tree pointer            */
/*      data                    */
/* creates a node with given data */
/* inserts node in appropriate place */
/* returns an iterator to the node */				
bst_iter_t BSTInsert(bst_t *bst, void *data); 

/* removes the node iter is pointing to,
	and returns removed iter's data */
void *BSTRemove(bst_iter_t iter); 

/* find the smallest member of the tree */
bst_iter_t BSTBegin(const bst_t *bst);

/* O(1) */
/* returns end (invalid) */
bst_iter_t BSTEnd(const bst_t *bst);

/* returns the previous node according to the hierarchy of the tree */
/* prev of begin is undefined behavior */
bst_iter_t BSTPrev(bst_iter_t iter);

/* returns the next node according to the hierarchy of the tree */
/* next of end is undefined behavior */
bst_iter_t BSTNext(bst_iter_t iter);

/* O(1) */
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);

/* O(1) */
void *BSTGetData(bst_iter_t iter);

/* return value: */
/*		if find: the iterator holding the data.
		if doesn't find: "end" iterator
*/
bst_iter_t BSTFind(const bst_t *bst, void *data);

/* inclusive of "from" and exclusive of "to" */
int BSTForEach(bst_iter_t from, bst_iter_t to,
			   action_func action, void *param);

#endif /* __BST_OL_110_H__ */
