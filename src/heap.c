/**
 * @file heap.c
 * 
 * @author a.grunewald
 * 
 * @brief Define heap functions.
 */

#include "heap.h"


node *find_father_node(heap *current_heap, int node_number){
    // In case we're at the root of the heap
    if (node_number == 1){
        return NULL;
    }

    // Depth in base 2
    int depth = (int) log2(node_number);

    // Initializing the father_node with a pointer to the root of the tree
    node *father_node = current_heap->root;

    for (int i = depth - 1; i > 0; i--){
        if ((node_number >> i & 1) == 0){
            father_node = father_node->left;
        } else {
            father_node = father_node->right;
        }
    }

    return father_node;
}


node *find_last_node(heap *current_heap){
    int number_of_nodes = current_heap->number;

    if (number_of_nodes % 2 == 0){
        return find_father_node(current_heap, number_of_nodes)->left;
    } else {
        return find_father_node(current_heap, number_of_nodes)->right;
    }
}


heap *adding_new_node(heap *current_heap, int new_node_cost, int new_node_ID){
    // Allocating memory for the new node
    node *new_node = (node *) malloc(sizeof(node));

    int node_number = current_heap->number + 1;

    // Adding data to the new node
    new_node->cost = new_node_cost;
    new_node->ID = new_node_ID;

    // Checking if the heap already contains nodes, because if not, what's following won't work
    if (current_heap->number == 0){
        current_heap->root = new_node;
        return current_heap;
    }

    // Finding the father node of the new node
    node *father_node = find_father_node(current_heap, node_number);
    if (node_number % 2 == 0){
        father_node->left = new_node;
    } else {
        father_node->right = new_node;
    }

    new_node->parent = father_node;

    return current_heap;
}


heap *insert(heap *current_heap, int new_node_cost, int new_node_ID){
    // Adding a new node
    current_heap = adding_new_node(current_heap, new_node_cost, new_node_ID);
    current_heap->number += 1;

    // If we've only one node, nothing more than adding_new_node needs to be done
    if (current_heap->number == 1){
        return current_heap;
    }

    // Having access to the new node
    node *current_node = find_last_node(current_heap);

    // Initializing the parent_node_cost
    int parent_node_cost = current_node->parent->cost;
    int parent_node_ID = current_node->parent->ID;

    while (new_node_cost < parent_node_cost){
        // Exchanging the two nodes_costs
        current_node->parent->cost = current_node->cost;
        current_node->parent->ID = current_node->ID;
        current_node->cost = parent_node_cost;
        current_node->ID = parent_node_ID;

        // Going one time background in the heap
        current_node = current_node->parent;

        if (current_node->parent != NULL){
            // Updating the parent_node_cost if we're not a the root of the heap
            parent_node_cost = current_node->parent->cost;
            parent_node_ID = current_node->parent->ID;
        } else {
            break;
        }
    }

    return current_heap;
}


int extract_min(heap *current_heap){
    int min_cost = current_heap->root->ID;

    // In case we have only one node
    if (current_heap->number == 1){
        free(current_heap->root);
        current_heap->root = NULL;
        current_heap->number -= 1;
        //current_heap = NULL;
        return min_cost;

    } else {

        // The starting heap has at least 2 nodes
        // Having access to the last node
        node *last_node = find_last_node(current_heap);
        int last_node_cost = last_node->cost;
        int last_node_ID = last_node->ID;

        // Moving the last node in root position 
        current_heap->root->cost = last_node_cost;
        current_heap->root->ID = last_node_ID;

        if (current_heap->number % 2 == 0){
            last_node->parent->left =  NULL;
        } else {
            last_node->parent->right = NULL;
        }
        current_heap->number -= 1;
        free(last_node);

        // Having access to the last node
        node *current_node = current_heap->root;

        // In case we had only two nodes initially, there's just one node left
        if (current_node->left == NULL){
            return min_cost;
        } else {
            // Moving the root node
            // Initializing the left_child_node_cost and right_child_node_cost
            int left_child_node_cost = current_node->left->cost;
            int left_child_node_ID = current_node->left->ID;
            int right_child_node_cost = INT_MAX;
            int right_child_node_ID = -1;

            if (current_node->right != NULL){
                right_child_node_cost = current_node->right->cost;
                right_child_node_ID = current_node->right->ID;
            }

            while ((last_node_cost > left_child_node_cost) || (last_node_cost > right_child_node_cost)){
                
                // Only one cost is lower than last_node_cost
                if (last_node_cost < right_child_node_cost){
                    // Exchanging with left node
                    current_node->left->cost = current_node->cost;
                    current_node->left->ID = current_node->ID;
                    current_node->cost = left_child_node_cost;
                    current_node->ID = left_child_node_ID;

                    // Going one step further in the heap
                    current_node = current_node->left;

                } else if (last_node_cost < left_child_node_cost){
                    // Exchanging with right node
                    current_node->right->cost = current_node->cost;
                    current_node->right->ID = current_node->ID;
                    current_node->cost = right_child_node_cost;
                    current_node->ID = right_child_node_ID;

                    // Going one step further in the heap
                    current_node = current_node->right;
                } else {
                    // We have both inequalities that are true, we choose to exchange with the child with lowest value
                    if (left_child_node_cost < right_child_node_cost){
                        // Exchanging with left node
                        current_node->left->cost = current_node->cost;
                        current_node->left->ID = current_node->ID;
                        current_node->cost = left_child_node_cost;
                        current_node->ID = left_child_node_ID;

                        // Going one step further in the heap
                        current_node = current_node->left;
                    } else {
                        // Exchanging with right node
                        current_node->right->cost = current_node->cost;
                        current_node->right->ID = current_node->ID;
                        current_node->cost = right_child_node_cost;
                        current_node->ID = right_child_node_ID;

                        // Going one step further in the heap
                        current_node = current_node->right;                
                    }
                }

                // Updating left/right child node costs
                if (current_node->left != NULL){
                    left_child_node_cost = current_node->left->cost;
                    left_child_node_ID = current_node->left->ID;
                } else {
                    left_child_node_cost = INT_MAX;
                    left_child_node_ID = -1;
                }

                if (current_node->right != NULL){
                    right_child_node_cost = current_node->right->cost;
                    right_child_node_ID = current_node->right->ID;

                } else {
                    right_child_node_cost = INT_MAX;
                    right_child_node_ID = -1;
                }
            }

            return min_cost;
        }
    }
}


