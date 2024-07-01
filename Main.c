
#include <stdio.h>
#include <stdlib.h>


// Taha Tüfekçi 150119050


struct Node {
    int val;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;

int depth_level(Node* node);
void sorting_array(int arr[], int n);
Node* array_to_tree(int arr[], int start, int end);
Node* new_node(int val);
void print_depth_levels(Node* root);
void print_node_numbers(Node* root, int level,int* node_counter);
void print_current_number(Node* root,int* key_value_ptr);
void print_node_level(Node* root, int level,int* node_counter,int* key_value_ptr,int *search,int node_level);


int main(){
    FILE *input_file;
    int count = 0;
    Node *root = NULL;
    input_file = fopen("C:\\Users\\TAHA\\Desktop\\input.txt", "r");
    if (input_file == NULL) { // Checking the input file
        printf("Error!");
        exit(0);
    }
    int i = 0;
    int tempArray[100];  // Creating a temporary array
    while (1) {
        fscanf(input_file, "%d", &tempArray[i++]);
        ++count;                                       // Counting the number of values in the input file
        if (feof(input_file)) {                 
            break;
        }
    }
    int numbers[count];            // Creating the main array with the count number
    for (i = 0; i < count; i++) {
        numbers[i] = tempArray[i];     // Taking the values from the temporary array to the main array
        if (numbers[i] <= 0) {
            printf("The BST should contain non-negative keys!");  // Checking the values of the input file
            exit(1);
        }
        int j;
        for (j = 0; j < i; j++) {
            if (numbers[j] == numbers[i]) {
                printf("The BST should have non-replicated keys!");// Checking the values of the input file
                exit(0);
            }
        }
    }
    if (count < 16) {
        printf("The BST should have at least 16 non-negative keys!");// Checking the values the of input file
        exit(0);
    }

    sorting_array(numbers, count);                // Sorting the array
    int size = sizeof(numbers) / sizeof(numbers[0]);
    root = array_to_tree(numbers, 0, size - 1);          //Constructing the tree
    printf("Depth level of BST is %d\n", depth_level(array_to_tree(numbers, 0, size - 1)) + 1);
    print_depth_levels(root);   // Printing the depth levels of the tree


    int key_value;
    int *key_value_ptr;
    key_value_ptr = &key_value;

    do {
        printf("Key value to be searched(Enter 0 to exit) : ");
        scanf("%d", &key_value);
        if (key_value == 0) {                 //Taking the inputs from the user
            printf("Exit");
            exit(1);
        }
        print_current_number(root, key_value_ptr);    //According to the key value printing the values depth level and element number properties
    } while (key_value != 0);


    fclose(input_file);
    return 0;

}

void print_current_number(Node *root, int *key_value_ptr) {  //This function prints the element number and the depth level of the key
    int height = depth_level(root);  
    int i, node_counter, search;   // Search value is used for whether the key is in the tree or not by using 1 or 0
    for (i = 0; i <= height; i++) {
        int *node_counter_ptr, *search_ptr;
        node_counter = 0, search = 0;
        search_ptr = &search;
        node_counter_ptr = &node_counter;
        print_node_level(root, i, node_counter_ptr, key_value_ptr, search_ptr, i);
        if (search == 1) {
            break;
        }
    }
    if (search == 0) {
        printf("%d is not found in BST\n", *key_value_ptr);
    }

}

void print_node_level(Node *root, int level, int *node_counter, int *key_value_ptr, int *search_ptr, int node_level) {//This function counts the element number of the key
    if (root == NULL) {
        return;
    }
    if (level == 0) {
        (*node_counter)++;
        if (*key_value_ptr == root->val) {
            *(search_ptr) = 1;
            if (*node_counter == 1) {
                printf("At Depth level %d, 1st element \n", node_level);
            } else if (*search_ptr == 1 && *node_counter == 2) {
                printf("At Depth level %d, 2nd element \n", node_level);
            } else if (*search_ptr == 1 && *node_counter == 3) {
                printf("At Depth level %d, 3rd element \n", node_level);
            } else if (*search_ptr == 1) {
                printf("At Depth level %d, %dth element \n", node_level, *node_counter);
            }
            return;
        }
    } else if (level > 0) {
        print_node_level(root->left, level - 1, node_counter, key_value_ptr, search_ptr, node_level);
        print_node_level(root->right, level - 1, node_counter, key_value_ptr, search_ptr, node_level);
    }
}

void print_depth_levels(Node *root) { // This function prints the depth levels of the tree
    int height = depth_level(root);
    int i;
    for (i = 0; i <= height; i++) {
        int *node_counter_ptr;
        int node_counter = 0;
        node_counter_ptr = &node_counter;
        print_node_numbers(root, i, node_counter_ptr);
        printf("Depth level %d->%d \n", i, node_counter);
    }
}

void print_node_numbers(Node *root, int level, int *node_counter) { // This function counts the number of nodes in a single depth level
    if (root == NULL) {
        return;
    }
    if (level == 0) {
        (*node_counter)++;
    } else if (level > 0) {
        print_node_numbers(root->left, level - 1, node_counter);
        print_node_numbers(root->right, level - 1, node_counter);
    }
}

int depth_level(Node *node) {   // This function is checking left and right subtrees and counting the depth levels of the tree
    int left_depth, right_depth;
    if (node == NULL)
        return -1;
    else {
        left_depth = depth_level(node->left);
        right_depth = depth_level(node->right);
        if (left_depth > right_depth) {
            return (left_depth + 1);
        } else {
            return (right_depth + 1);
        }
    }
}

Node *array_to_tree(int arr[], int start, int end) { // This function is constructing the tree by taking the middle of both sides of the tree
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    Node *root = new_node(arr[mid]);
    root->left = array_to_tree(arr, start, mid - 1);
    root->right = array_to_tree(arr, mid + 1, end);
    return root;
}

void sorting_array(int arr[], int a) { // This function written for sorting the array using the insertion sort
    if (a <= 1) {
        return;
    }
    sorting_array(arr, a - 1);

    int last = arr[a - 1];
    int t = a - 2;
    while (t >= 0 && arr[t] > last) {
        arr[t + 1] = arr[t];
        t--;
    }
    arr[t + 1] = last;
}

Node *new_node(int val) { // This function used for creating new nodes
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
