/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      Shahar
* Description   Binary search tree module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <stdlib.h>
#include <assert.h>

#include "bst.h"

typedef struct bst_node bst_node_t;

typedef enum
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
} children_t;

struct bst_node
{
    void *data;
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
};

struct bst
{
    bst_node_t end;
    int (*is_before)(const void *, const void *, void *param);
    void *param;
};

static bst_node_t *NodeCreate(void *data)
{
	bst_node_t *node = (bst_node_t *)malloc(sizeof(bst_node_t));
	
	if(!node)
	{
		return NULL;
	}
	
	node->data = data;
	
	return node;
}

static void *NodeFree(bst_iter_t iter)
{
	void *data = NULL;
	
	assert(iter);
	
	iter->parent = NULL;
	iter->children[LEFT] = NULL;
	iter->children[RIGHT] = NULL;
	data = iter->data;
	
	free(iter);
	iter = NULL;
	
	return data;
}

static void NodeConnect(bst_node_t *node, bst_node_t *parent, children_t position, bst_node_t *left_child, bst_node_t *right_child)
{
	assert(node);
	
	node->parent = parent;
	node->children[LEFT] = left_child;
	node->children[RIGHT] = right_child;
	
	parent->children[position] = node;
}

static bst_node_t *GetTreeRoot(const bst_t *bst)
{
	assert(bst);
	
	return bst->end.children[LEFT];
}

static bst_iter_t NodeFindFarthestLeaf(bst_iter_t iter, children_t child)
{
	assert(iter);
	
	while (iter->children[child])
	{
		iter = iter->children[child];
	}
	
	return iter;
}


bst_t *BSTCreate(find_func is_before, void *param)
{
	bst_t *tree = NULL;
	
	assert(is_before);
	
	tree = (bst_t *)malloc(sizeof(bst_t));
	
	if(!tree)
	{
		return NULL;
	}
	
	tree->is_before = is_before;
	tree->param = param;
	
	(tree->end).parent = NULL;
	tree->end.children[LEFT] = NULL;
	tree->end.children[RIGHT] = NULL;
	tree->end.data = NULL;
	
	return tree;
}

void BSTDestroy(bst_t *bst)
{
	bst_iter_t iter = NULL;
	
	assert(bst);
	
	iter = GetTreeRoot(bst);
	
	while (iter != NULL)
	{
		BSTRemove(iter);
		iter = GetTreeRoot(bst);
	}
	
	free(bst);
	bst = NULL;
}

size_t BSTSize(const bst_t *bst)
{
	size_t count = 0;
	bst_iter_t iter = NULL;
	
	assert(bst);
	
	for (iter = BSTBegin(bst); iter != BSTEnd(bst); iter = BSTNext(iter))
	{
		count ++;
	}
	
	return count;
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);
	
	return (GetTreeRoot(bst) == NULL);
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t inserted_node = NULL, current_iter = NULL;
	children_t position = 0;
	
	assert(bst);
	
	inserted_node = NodeCreate(data);
	
	if (!inserted_node)
	{
		return BSTEnd(bst);		
	}
	
	current_iter = BSTEnd(bst);
	position = LEFT;
	
	while (current_iter->children[position] != NULL)
	{
		current_iter = current_iter->children[position];
		position = !(bst->is_before(data, current_iter->data, bst->param));
	}
	
	NodeConnect(inserted_node, current_iter, position, NULL, NULL);
	
	return inserted_node;
}

void *BSTRemove(bst_iter_t iter)
{
	void *data = NULL;
	children_t iter_position = 0, child = 0;
	bst_iter_t insertion_point_iter = NULL;
	
	assert(iter);
	
	if (!(iter->children[LEFT] || iter->children[RIGHT]))
	{
		if (BSTIterIsEqual(iter->parent->children[RIGHT], iter))
		{
			iter_position = RIGHT;
		}
		else
		{
			iter_position = LEFT;
		}
		
		iter->parent->children[iter_position] = NULL;
		
		data = NodeFree(iter);
		iter = NULL;
		return data;
	}
	else if ((iter->children[LEFT] && !(iter->children[RIGHT])) || (!(iter->children[LEFT]) && iter->children[RIGHT]))
	{
		if (BSTIterIsEqual(iter->parent->children[RIGHT], iter))
		{
			iter_position = RIGHT;
		}
		else
		{
			iter_position = LEFT;
		}
		
		if (iter->children[RIGHT])
		{
			child = RIGHT;
		}
		else
		{
			child = LEFT;
		}
		
		iter->parent->children[iter_position] = iter->children[child];
		iter->children[child]->parent = iter->parent;
		
		
		data = NodeFree(iter);
		iter = NULL;
		return data;
	}
	else
	{
		if (BSTIterIsEqual(iter->parent->children[RIGHT], iter))
		{
			iter_position = RIGHT;
		}
		else
		{
			iter_position = LEFT;
		}
		
		insertion_point_iter = NodeFindFarthestLeaf(iter->children[RIGHT], LEFT);	
		insertion_point_iter->children[LEFT] = iter->children[LEFT];
		iter->children[LEFT]->parent = insertion_point_iter;
		
		iter->parent->children[iter_position] = iter->children[RIGHT];
		iter->children[RIGHT]->parent = iter->parent;
		
		data = NodeFree(iter);
		iter = NULL;
		return data;
	}
}

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_iter_t iter = NULL;
	
	assert(bst);
	
	iter = BSTEnd(bst);
	
	return NodeFindFarthestLeaf(iter, LEFT);
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	assert(bst);
	
	return (bst_iter_t)&(bst->end);	
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	assert(iter);
	
	
	if (!(iter->children[LEFT]))
	{
		if (iter == iter->parent->children[RIGHT])
		{
			return iter->parent;
		}
		else
		{
			return iter->parent->parent;
		}	
	}
	else 
	{
		return NodeFindFarthestLeaf(iter->children[LEFT], RIGHT);
	}
}

bst_iter_t BSTNext(bst_iter_t iter)
{
	assert(iter);
	
	if (!(iter->children[RIGHT]))
	{
		while (iter != iter->parent->children[LEFT])
		{
			iter = iter->parent;
		}
		
		return iter->parent;
	}
	else 
	{
		return NodeFindFarthestLeaf(iter->children[RIGHT], LEFT);
	}
}

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	return (iter1 == iter2);
}

void *BSTGetData(bst_iter_t iter)
{
	assert(iter);
	
	return iter->data;
}

bst_iter_t BSTFind(const bst_t *bst, void *data)
{
	bst_iter_t iter = NULL;
	
	assert(bst);
	
	for (iter = BSTBegin(bst); iter != BSTEnd(bst); iter = BSTNext(iter))
	{
		if (iter->data == data)
		{
			break;
		}
	}
	
	return iter;
}

int BSTForEach(bst_iter_t from, bst_iter_t to,
			   action_func action, void *param)
{
	bst_iter_t iter = NULL;
	int status = 0;
	
	assert(from);
	assert(to);
	assert(action);
	
	for (iter = from; iter != to; iter = BSTNext(iter))
	{
		status += action(iter->data, param);
	}
	
	return status;
}
