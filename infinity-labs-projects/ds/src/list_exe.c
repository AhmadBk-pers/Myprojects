#include <stdlib.h>	/*malloc free*/
#include <assert.h> /* assert*/

#include "list_exe.h"

size_t NCount(const node_t *head)
{
	size_t count = 0;
    assert(head);
    
    while (head->next != NULL)
    {
        head = head->next;
        count++;
    }

	return count;
}

node_t *Flip(node_t *head)
{
	node_t *reversed_head = NULL;
	node_t *reversed_node = NULL;
	node_t *end_of_reversed_list = NULL;
    assert(head);
    
    end_of_reversed_list = head;
	reversed_head = head;
	head = head->next;
	
    while (head != NULL)
    {
        reversed_node = head;
    	head = head->next;
    	
    	reversed_node->next = reversed_head;
    	reversed_head = reversed_node;
    }
    
    end_of_reversed_list->next = head;
    
    return reversed_head;
}

int HasLoop(const node_t *head)
{
	node_t *iter1step = NULL;
	node_t *iter2step = NULL;
	
	assert(head);
	
	iter1step = head->next;
	iter2step = head->next->next;
	
	while(iter2step->next && iter2step->next->next)
	{
		iter1step = iter1step->next;
		iter2step = iter2step->next->next;
		
		if(iter1step == iter2step)
		{
			return 1;		
		}
	}

	return 0;
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	size_t size1 = 0, size2 = 0;
	
	assert(head_1 && head_2);
	
	size1 = NCount(head_1);
	size2 = NCount(head_2);
	
	while (size1 > size2)
	{
		head_1 = head_1->next;
		size1--;
	}
	
	while (size1 < size2)
	{
		head_2 = head_2->next;
		size2--;
	}
	
	while (head_1 && head_2)
	{
		if (head_1 == head_2)
		{
			return head_1;
		}
		head_1 = head_1->next;
		head_2 = head_2->next;
		
	}
	
	return head_1;
}
