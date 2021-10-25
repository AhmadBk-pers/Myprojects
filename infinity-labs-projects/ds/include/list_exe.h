#ifndef __SL_EXR_H__
#define __SL_EXR_H__

#include <stddef.h> /* size_t  */

typedef struct node
{
    void *data;
    struct node *next;
    
} node_t;


node_t *FindIntersection(node_t *head_1, node_t *head_2);
int HasLoop(const node_t *head);
node_t *Flip(node_t *head);

#endif /* __SL_EXR_H__ */
