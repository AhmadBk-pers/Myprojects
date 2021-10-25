
node_t *printMiddle(const node_t *head)
{
    const node_t *slow_ptr = head;
    const node_t *fast_ptr = head;
 
    assert(head);
    
    while (fast_ptr != NULL && fast_ptr->next != NULL)
    {
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
    }
	
	return slow_ptr;
}
