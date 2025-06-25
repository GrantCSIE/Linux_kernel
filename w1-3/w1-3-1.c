# include <stdio.h>
# include <stdlib.h>

typedef struct __node {
    struct __node *left, *right;
    struct __node *next;
    long value;
} node_t;

int list_length(node_t **list);
node_t* list_tail(node_t **list);
void list_add(node_t **list, node_t *node);

void quick_sort(node_t **list)
{
    int n = list_length(list);
    int value;
    int i = 0;
    int max_level = 2 * n;
    node_t *begin[max_level], *end[max_level];
    node_t *result = NULL, *left = NULL, *right = NULL;
    
    begin[0] = *list;
    end[0] = list_tail(list);
            
    while (i >= 0) {
        node_t *L = begin[i], *R = end[i];
        if (L != R) {
            node_t *pivot = L;
            value = pivot->value;
            node_t *p = pivot->next;
            pivot->next = NULL;
    
            while (p) {
                node_t *n = p;
                p = p->next; // move to next item
                list_add(n->value > value ? &right : &left, n);
            }

            begin[i] = left;
            end[i] = list_tail(&left); // store end pointer of left list consisted of smaller item than pivot
            begin[i + 1] = pivot;
            end[i + 1] = pivot;
            begin[i + 2] = right;
            end[i + 2] = list_tail(&right); // store end pointer right of right list consisted of larger item than pivot

            left = right = NULL;
            i += 2;
        } else {
            if (L)
                list_add(&result, L);
            i--;
        }
    }
    *list = result;
}


int list_length(node_t **list){
	int length = 0;
	node_t *p = *list;
	while(p != NULL){
		length++;
		p = p->next;
	}
	return length;
}

node_t* list_tail(node_t **list){
    if(*list == NULL){
        return NULL;
    }
    else{
        node_t *tail = *list;
        while(tail->next != NULL){
            tail = tail->next;
        }
        return tail;
    }
}
void list_add(node_t **list, node_t *node){
    node->next = NULL;
    if (*list == NULL){
        *list = node;
    }
    else{
    	node_t *tail = list_tail(list);
	    tail->next = node;
	    node->next = NULL;
    }
        
}

void list_traverse(node_t **list){
	node_t *p = *list;
	while(p != NULL){
		printf("%ld,", p->value);
		p = p->next;
	}
    printf("\n");
}


int main(){
	node_t **list = NULL;
	node_t **new_node = (node_t **)malloc(5 * sizeof(node_t*));
    for(int i = 0; i < 5; i++){
        new_node[i] = (node_t *)malloc(sizeof(node_t));
    }
    new_node[0]->value = 3; new_node[0]->left = NULL; new_node[0]->right = NULL; new_node[0]->next = NULL;
    list = &(new_node[0]);

    new_node[1]->value = 1; new_node[1]->left = NULL; new_node[1]->right = NULL; new_node[1]->next = NULL;
    list_add(list, new_node[1]);

    new_node[2]->value = 0; new_node[2]->left = NULL; new_node[2]->right = NULL; new_node[2]->next = NULL;
    list_add(list, new_node[2]);

    new_node[3]->value = 2; new_node[3]->left = NULL; new_node[3]->right = NULL; new_node[3]->next = NULL;
    list_add(list, new_node[3]);

    new_node[4]->value = 4; new_node[4]->left = NULL; new_node[4]->right = NULL; new_node[4]->next = NULL;
    list_add(list, new_node[4]);

    printf("before sorting:\n");
	list_traverse(list);
    printf("%d\n", list_length(list));

    quick_sort(list);
    printf("after sorting:\n");
    list_traverse(list);
	return 0;
}
