#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct block {
    size_t size;
    struct block *l, *r;
} block_t;

block_t **find_free_tree(block_t **root, block_t *target);
block_t *find_predecessor_free_tree(block_t **root, block_t *node);

/*
 * Structure representing a free memory block in the memory allocator.
 * The free tree is a binary search tree that organizes free blocks (of type block_t)
 * to efficiently locate a block of appropriate size during memory allocation.
 */
void remove_free_tree(block_t **root, block_t *target)
{
    /* Locate the pointer to the target node in the tree. */
    block_t **node_ptr = find_free_tree(root, target);

    /* If the target node has two children, we need to find a replacement. */
    if ((*node_ptr)->l && (*node_ptr)->r) {
        /* Find the in-order predecessor:
         * This is the rightmost node in the left subtree.
         */
        block_t **pred_ptr = &(*node_ptr)->l;
        while ((*pred_ptr)->r)
            pred_ptr = &(*pred_ptr)->r;

        /* Verify the found predecessor using a helper function (for debugging).
         */
        block_t *expected_pred = find_predecessor_free_tree(root, *node_ptr);
        assert(expected_pred == *pred_ptr);

        /* If the predecessor is the immediate left child. */
        if (*pred_ptr == (*node_ptr)->l) {
            block_t *old_right = (*node_ptr)->r;
            *node_ptr = *pred_ptr; /* Replace target with its left child. */
            (*node_ptr)->r = old_right; /* Attach the original right subtree. */
            assert(*node_ptr != (*node_ptr)->l);
            assert(*node_ptr != (*node_ptr)->r);
        } else {
            /* The predecessor is deeper in the left subtree. */
            block_t *old_left = (*node_ptr)->l;
            block_t *old_right = (*node_ptr)->r;
            block_t *pred_node = *pred_ptr;
            /* Remove the predecessor from its original location. */
            remove_free_tree(&old_left, *pred_ptr);
            /* Replace the target node with the predecessor. */
            *node_ptr = pred_node;
            (*node_ptr)->l = old_left;
            (*node_ptr)->r = old_right;
            assert(*node_ptr != (*node_ptr)->l);
            assert(*node_ptr != (*node_ptr)->r);
        }
    }
    /* If the target node has one child (or none), simply splice it out. */
    else if ((*node_ptr)->l || (*node_ptr)->r) {
        block_t *child = ((*node_ptr)->l) ? (*node_ptr)->l : (*node_ptr)->r;
        *node_ptr = child;
    } else {
        /* No children: remove the node. */
        *node_ptr = NULL;
    }

    /* Clear the removed node's child pointers to avoid dangling references. */
    target->l = NULL;
    target->r = NULL;
}

block_t **find_free_tree(block_t **root, block_t *target){
	/* basically, it is an binary searching problem with best-fit strategy in BST.*/
	block_t **best = NULL;
	block_t **indirect = root;
	
	while(*indirect){
		/* case 1: if current node is larger then target node,
			then save the current node 
			and keep traversing the subtree of current node(which should consists of nodes smaller then target node).
		*/
		if((*indirect)->size > target->size){
			best = indirect;
			indirect = &(*indirect)->l;
		}
		/* case 2: if size of current node is identical to size of target node,
				then return current node.
		*/
		else if((*indirect)->size == target->size){
			return indirect;
		}
		/* case 3: if size of current node is smaller then size of target node,
				then traversing the right subtree of current node(which should consists of nodes larger then target node).
		*/
		else if((*indirect)->size < target->size){
			indirect = &(*indirect)->r;
		}
	}
	return best;
}


block_t *find_predecessor_free_tree(block_t **root, block_t *node){
	/* 
	case 1: free node has no left subtree, then it definity has no predecessor.
	*/
	if(!node || !node->l){
		return NULL;
	}
	/*
	case 2: free node has left subtree, then keep traversing the right node of the left subtree.
	*/
	block_t *ptr = node->l;
	while(ptr->r){
		ptr = ptr->r;
	}
	return ptr;
}

void BST_insertion(block_t **root, int val){
	block_t **indirect = root;
	block_t *node = (block_t *)malloc(sizeof(block_t));
	node->size = val;
	node->l = NULL;
	node->r = NULL;
	while(*indirect){
		if((*indirect)->size > node->size){
			indirect = (&(*indirect)->l);
		}
		else if((*indirect)->size < node->size){
			indirect = (&(*indirect)->r);
		}
	}
	*indirect = node;
}

void **create_free_tree(block_t **root){
	/*create a BST.*/
	(*root) = (block_t *)malloc(sizeof(block_t));
	(*root)->size = 70;
	(*root)->l = NULL;
	(*root)->r = NULL;
	BST_insertion(root, 50);
	BST_insertion(root, 80);
	BST_insertion(root, 40);
	BST_insertion(root, 55);
	BST_insertion(root, 30);
	BST_insertion(root, 42);
	BST_insertion(root, 41);
	BST_insertion(root, 46);
}

void in_order_traversing(block_t **root){
	/* in order traversing in a BST is a sorting algorithm*/
	block_t **indirect = root;
	if(*indirect){
		in_order_traversing(&(*indirect)->l);
		printf("%ld, ", (*indirect)->size);
		in_order_traversing(&(*indirect)->r);
	}
	else{
		printf("nil,");
	}
}

int main(){
	block_t *root = NULL;
	create_free_tree(&root);

	printf("BST:[");
	in_order_traversing(&root);
	printf("]\n");


	long int num;
	printf("input target :");
	scanf("%ld", &num);

	block_t *target = (block_t *)malloc(sizeof(block_t));
	target->size = num;
	target->l = NULL;
	target->r = NULL;

	remove_free_tree(&root, target);

	printf("[");
	in_order_traversing(&root);
	printf("]\n");
	
	return 0;
}
