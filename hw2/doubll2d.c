#include <stdio.h>
#include <stdlib.h>
#include "doubll2d.h"

#define LEFT 0x0
#define RIGHT 0x1
#define UP 0x2
#define DOWN 0x3

#define CHECK_LIST


/* Initialize a 2D doubly linked list. */
void doubll2d_init(doubll2d *list)
{
    /*
     * At the beginning, the list does not contain any element,
     * so the head and tail point to NULL, and the #rows and #cols
     * equal to 0
     */
    list->head = NULL;
    list->tail = NULL;
    list->dim_row = 0;
    list->dim_col = 0;
}

/* Return the upper-left most element of the list.
   Return NULL on error. */
doubll2d_elem *doubll2d_get_head(doubll2d *list)
{
    /*
     * In case the list is a NULL pointer
     */
    if (list == NULL) return NULL;
    return list->head;
}

/* Return the lower-right most element of the list.
   Return NULL on error. */
doubll2d_elem *doubll2d_get_tail(doubll2d *list)
{
    /*
     * In case the list is a NULL pointer
     */
    if (list == NULL) return NULL;
    return list->tail;
}
/* Return number of rows in a list.
   Return -1 on error. */
size_t doubll2d_dim_row(doubll2d *list)
{
    /*
     * In case the list is a NULL pointer
     */
    if (list == NULL) return -1;
    return list->dim_row;
}

/* Return number of columns in a list.
   Return -1 on error. */

size_t doubll2d_dim_col(doubll2d *list)
{
    /*
     * In case the list is a NULL pointer
     */
    if (list == NULL) return -1;
    return list->dim_col;
}

/*
 * Create a new elem with specific data, notice that it should be stored in the 'heap' region.
 */
static doubll2d_elem* doubll2d_elem_create(void* data, size_t size)
{
    /*
     * Create it by malloc;
     */
    doubll2d_elem* elem = (doubll2d_elem*) malloc(sizeof(doubll2d_elem));

    /*
     * Set all the connectors to NULL by default
     */
    elem->left = NULL;
    elem->right = NULL;
    elem->up = NULL;
    elem->down = NULL;

    /*
     * Set the data and its size by given prams
     */
    elem->data = data;
    elem->size = size;

    return elem;
}

/*
 * Link two elements, notice that we use double links.
 */
static void doubll2d_elem_link(doubll2d_elem* alpha, int alpha_direction, doubll2d_elem* beta)
{
    /*
     * This is actually my first time using 'switch' command
     */
    switch (alpha_direction)
    {

        /*
         * If we need to link beta to the left of alpha
         */
        case LEFT:
            alpha->left = beta;
            beta->right = alpha;
            break;

        /*
         * If we need to link beta to the right of alpha
         */
        case RIGHT:
            alpha->right = beta;
            beta->left = alpha;
            break;

        /*
         * If we need to link beta to the top of alpha
         */
        case UP:
            alpha->up = beta;
            beta->down = alpha;
            break;

        /*
         * If we need to link beta to the btm of alpha
         */
        case DOWN:
            alpha->down = beta;
            beta->up = alpha;
            break;

        /*
         * Execute abort() when the direction is invalid.
         */
        default:
            abort();
    }
}


/*
 * Check if the cursor is in the list. When CHECK_LIST is defined, it will be executed inside some functions
 */
static bool check_list(doubll2d *list, doubll2d_elem *cursor)
{
    /*
     * build a double traversal to check every element if it is cursor
     */
    size_t i, j;
    doubll2d_elem *row_flag, *col_flag;

    /*
     * make sure that the list is not empty
     */
    if (list == NULL) return false;

    row_flag = list->head;
    for (i = 0; i < list->dim_row; i++) {
        /*
         * From the left-up to right-down
         */
        col_flag = row_flag;
        for (j = 0; j < list->dim_col; j++) {
            if (cursor == col_flag) return true;
            col_flag = col_flag->right;
        }
        /*
         * everytime we check a row in the outer for-loop
         */
        row_flag = row_flag->down;
    }
    return false;
}

/* Insert a new row in the list below the row where the given `cursor` locates.
   The given `data` should be **copied** to the newly created elements.
   The `length` is the number of data pointers given to you.
   Return the pointer to the newly created element below the given `cursor`.
   Return NULL on error.

   Remember, our 2D doubly linked list should always be a rectangular. So if
   the `length` is shorter than it should be, abort immediately and return NULL.
   However, it is okay that the `length` is longer than needed. And in this case
   you should make use of the first `doubll.dim_col` items in `data` and leave
   alone the rest.

   If the marco CHECK_LIST is set, your code has to check if the element `cursor` is
   actually a member of the list. If not, abort and return NULL. This check is slow.
   If the marco CHECK_LIST is not set, your code shall not perform that check
   but rather run very fast. */
doubll2d_elem *doubll2d_insert_row(doubll2d *list, doubll2d_elem *cursor,
                                   void **data, size_t *size, size_t length)
{
    /*
     * Set two flags to let us know where is the beginning, used in traversals
     */
    doubll2d_elem* flag_elem1 = cursor;
    doubll2d_elem* flag_elem2;

    /*
     * A variable to temporarily store new generated elems
     */
    doubll2d_elem* temp_item;

    int i;

    /*
     * In case the list or the cursor is a NULL pointer
     */
    if ((list == NULL) | (cursor == NULL)) return NULL;


    /*
     * If we set the macro CHECK_LIST, then perform the function to check if the cursor is surely there
     */
    #ifdef CHECK_LIST
        if (check_list(list, cursor) == false) return NULL;
    #endif


    /*
     * To check if the length is large enough to form a row
     */
    if ((length < list->dim_col) | (length == 0)) return NULL;

    /*
     * Firstly, find the beginning element in the row that cursor located
     */
    while (flag_elem1->left != NULL) flag_elem1 = flag_elem1->left;
    flag_elem2 = flag_elem1;


    /*
     * From the beginning elem to the ending elem, dock a new elem to every elem in that row
     * if there is already another row below the new generated elems, then remember to dock it too
     */
    i = 0;
    while (flag_elem1 != NULL)
    {
        /*
         * Generate new elems
         */
        temp_item = doubll2d_elem_create(data[i], size[i]);


        if (flag_elem1->down != NULL) doubll2d_elem_link(flag_elem1->down, UP, temp_item);
        doubll2d_elem_link(flag_elem1, DOWN, temp_item);

        /*
         * move the flag
         */
        flag_elem1 = flag_elem1->right;
        i++;
    }

    /*
     * make sure the new row is tightly connected inside
     */
    while (flag_elem2->right != NULL)
    {
        doubll2d_elem_link(flag_elem2->down, RIGHT, flag_elem2->right->down);
        flag_elem2 = flag_elem2->right;
    }

    /*
     * To check if we need to update the tail
     */
    if (flag_elem2->down == NULL) list->tail = flag_elem2;


    /*
     * Remember to update dim_row
     */
    list->dim_row++;

    /*
     * return the elems downward the cursor
     */
    return cursor->down;
}

/* Insert a new column in the list after the column where the given `cursor`
   locates. The given `data` should be **copied** to the newly created elements.
   The `length` is the number of data pointers given to you.
   Return the pointer to the newly created element after the given `cursor`.
   Return NULL on error.

   Remember, our 2D doubly linked list should always be a rectangular. So if
   the `length` is shorter than it should be, abort immediately and return NULL.
   However, it is okay that the `length` is longer than needed. And in this case
   you should make use of the first `doubll.dim_row` items in `data` and leave
   alone the rest.

   If the marco CHECK_LIST is set, your code has to check if the element `cursor` is
   actually a member of the list. If not, abort and return NULL. This check is slow.
   If the marco CHECK_LIST is not set, your code shall not perform that check
   but rather run very fast. */
doubll2d_elem *doubll2d_insert_col(doubll2d *list, doubll2d_elem *cursor,
                                   void **data, size_t *size, size_t length)
{
    /*
 * Set two flags to let us know where is the beginning, used in traversals
 */
    doubll2d_elem* flag_elem1 = cursor;
    doubll2d_elem* flag_elem2;

    /*
     * A variable to temporarily store new generated elems
     */
    doubll2d_elem* temp_item;

    int i;

    /*
     * In case the list or the cursor is a NULL pointer
     */
    if ((list == NULL) | (cursor == NULL)) return NULL;

    /*
     * If we set the macro CHECK_LIST, then perform the function to check if the cursor is surely there
     */
    #ifdef CHECK_LIST
        if (check_list(list, cursor) == false) return NULL;
    #endif

    /*
     * To check if the length is large enough to form a row
     */
    if ((length < list->dim_row) | (length == 0)) return NULL;

    /*
     * Firstly, find the beginning element in the col that cursor located
     */
    while (flag_elem1->up != NULL) flag_elem1 = flag_elem1->up;
    flag_elem2 = flag_elem1;


    /*
     * From the beginning elem to the ending elem, dock a new elem to every elem in that col
     * if there is already another col besides the new generated elems, then remember to dock it too
     */
    i = 0;
    while (flag_elem1 != NULL)
    {
        /*
         * Generate new elems
         */
        temp_item = doubll2d_elem_create(data[i], size[i]);


        if (flag_elem1->right != NULL) doubll2d_elem_link(flag_elem1->right, LEFT, temp_item);
        doubll2d_elem_link(flag_elem1, RIGHT, temp_item);

        /*
         * move the flag
         */
        flag_elem1 = flag_elem1->down;
        i++;
    }

    /*
     * make sure the new col is tightly connected inside
     */
    while (flag_elem2->down != NULL)
    {
    doubll2d_elem_link(flag_elem2->right, DOWN, flag_elem2->down->right);
        flag_elem2 = flag_elem2->down;
    }

    /*
     * To check if we need to update the tail
     */
    if (flag_elem2->right == NULL) list->tail = flag_elem2;


    /*
     * Remember to update dim_col
     */
    list->dim_col++;

    /*
     * return the elems downward the cursor
     */
    return cursor->right;
}

/* Delete the row where the given `cursor` locates and returns the element above
   the given `cursor`. If the first row is deleted, then return the element
   below the given `cursor`. If the deleted row is the only row in the list,
   return NULL. Return NULL on error.

   If the marco CHECK_LIST is set, your code has to check if the element `cursor` is
   actually a member of the list. If not, abort and return NULL. This check is slow.
   If the marco CHECK_LIST is not set, your code shall not perform that check
   but rather run very fast. */
doubll2d_elem *doubll2d_delete_row(doubll2d *list, doubll2d_elem *cursor)
{
    /*
     * Set two flags to let us know where is the beginning, used in traversals
     */
    doubll2d_elem* flag_elem1 = cursor;
    doubll2d_elem* flag_elem2;


    /*
     * A variable to temporarily store return elems
     */
    doubll2d_elem* return_target;


    /*
     * In case the list or the cursor is a NULL pointer
     */
    if ((list == NULL) | (cursor == NULL)) return NULL;

    /*
     * If we set the macro CHECK_LIST, then perform the function to check if the cursor is surely there
     */
    #ifdef CHECK_LIST
        if (check_list(list, cursor) == false) return NULL;
    #endif


    /*
     * Firstly, find the beginning element in the row that cursor located
     */
    while (flag_elem1->left != NULL) flag_elem1 = flag_elem1->left;
    flag_elem2 = flag_elem1;


    /*
     * Classify several cases
     */
    if (cursor->up != NULL && cursor->down != NULL)
    {
        /*
         * If the above elems exists, then we should return it
         */
        return_target = cursor->up;
    }
    else if (cursor->up != NULL && cursor->down == NULL)
    {
        /*
         * If the above elems exists, then we should return it
         * And if the below is NULL, then update the tail
         */
        return_target = cursor->up;
        list->tail = list->tail->up;
    }
    else if (cursor->up == NULL && cursor->down != NULL)
    {
        /*
         * If the above elems does not exist, but the below, then we should return the below elems
         * And if the above is NULL, then update the head
         */
        return_target = cursor->down;
        list->head = list->head->down;
    }
    else
    {
        /*
         * If both do not exist, then we should return NULL and update head and tail to be NULL
         */
        return_target = NULL;
        list->head = NULL;
        list->tail = NULL;
    }

    /*
     * From the beginning elem to the ending elem, delete every element in that row
     * in different cases, do different operations such that the list can keep a connected inside
     */
    while (flag_elem1 != NULL)
    {
        /*
         * move the 1st flag first so we won't loss the target
         */
        flag_elem1 = flag_elem1->right;

        if (flag_elem2->up != NULL && flag_elem2->down != NULL) doubll2d_elem_link(flag_elem2->up, DOWN, flag_elem2->down);
        else if (flag_elem2->up != NULL && flag_elem2->down == NULL) flag_elem2->up->down = NULL;
        else if (flag_elem2->up == NULL && flag_elem2->down != NULL) flag_elem2->down->up = NULL;

        /*
         * noticed that we need to free the data also
         */
        free(flag_elem2->data);
        free(flag_elem2);

        /*
         * move the 2nd flag so that we can do further deletion
         */
        flag_elem2 = flag_elem1;
    }


    /*
     * Remember to update dim_row
     */
    list->dim_row--;

    /*
     * Check if the list is empty
     */
    if (list->head == NULL) list->dim_col = 0;

    /*
     * return the elems properly
     */
    return return_target;
}

/* Delete the column where the given `cursor` locates and returns the element
   before the given `cursor`. If the first column is deleted, then return the
   element after the given `cursor`. If the deleted column is the only column in
   the list, return NULL. Return NULL on error.

   If the marco CHECK_LIST is set, your code has to check if the element `cursor` is
   actually a member of the list. If not, abort and return NULL. This check is slow.
   If the marco CHECK_LIST is not set, your code shall not perform that check
   but rather run very fast. */
doubll2d_elem *doubll2d_delete_col(doubll2d *list, doubll2d_elem *cursor)
{
    /*
     * Set two flags to let us know where is the beginning, used in traversals
     */
    doubll2d_elem* flag_elem1 = cursor;
    doubll2d_elem* flag_elem2;


    /*
     * A variable to temporarily store return elems
     */
    doubll2d_elem* return_target;


    /*
     * In case the list or the cursor is a NULL pointer
     */
    if ((list == NULL) | (cursor == NULL)) return NULL;

    /*
     * If we set the macro CHECK_LIST, then perform the function to check if the cursor is surely there
     */
    #ifdef CHECK_LIST
        if (check_list(list, cursor) == false) return NULL;
    #endif


    /*
     * Firstly, find the beginning element in the col that cursor located
     */
    while (flag_elem1->up != NULL) flag_elem1 = flag_elem1->up;
    flag_elem2 = flag_elem1;


    /*
     * Classify several cases
     */
    if (cursor->left != NULL && cursor->right != NULL)
    {
        /*
         * If the left elems exists, then we should return it
         */
        return_target = cursor->left;
    }
    else if (cursor->left != NULL && cursor->right == NULL)
    {
        /*
         * If the left elems exists, then we should return it
         * And if the right is NULL, then update the tail
         */
        return_target = cursor->left;
        list->tail = list->tail->left;
    }
    else if (cursor->left == NULL && cursor->right != NULL)
    {
        /*
         * If the left elems does not exist, but the right, then we should return the right elems
         * And if the left is NULL, then update the head
         */
        return_target = cursor->right;
        list->head = list->head->right;
    }
    else
    {
        /*
         * If both do not exist, then we should return NULL and update head and tail to be NULL
         */
        return_target = NULL;
        list->head = NULL;
        list->tail = NULL;
    }

    /*
     * From the beginning elem to the ending elem, delete every element in that col
     * in different cases, do different operations such that the list can keep a connected inside
     */
    while (flag_elem1 != NULL)
    {
        /*
         * move the 1st flag first so we won't loss the target
         */
        flag_elem1 = flag_elem1->down;

        if (flag_elem2->left != NULL && flag_elem2->right != NULL) doubll2d_elem_link(flag_elem2->left, RIGHT, flag_elem2->right);
        else if (flag_elem2->left != NULL && flag_elem2->right == NULL) flag_elem2->left->right = NULL;
        else if (flag_elem2->left == NULL && flag_elem2->right != NULL) flag_elem2->right->left = NULL;

        /*
         * noticed that we need to free the data also
         */
        free(flag_elem2->data);
        free(flag_elem2);

        /*
         * move the 2nd flag so that we can do further deletion
         */
        flag_elem2 = flag_elem1;
    }


    /*
     * Remember to update dim_col
     */
    list->dim_col--;

    /*
     * Check if the list is empty
     */
    if (list->head == NULL) list->dim_row = 0;

    /*
     * return the elems properly
     */
    return return_target;
}


/*  Purge all items from the list. */
void doubll2d_purge(doubll2d *list)
{
    /*
     * Check if it is NULL
     */
    if (list == NULL) return;

    /*
     * Call multiple times of 'doubll2d_delete_row', until the dim_row == 0
     */
    while (list->dim_row != 0) doubll2d_delete_row(list, list->head);
}


/* Use the given `less` function to find the maximum element in the whole list.
   If there are multiple maximum elements, return any one of them.
   When the 2D linked list is empty, return NULL.
 */
doubll2d_elem *doubll2d_find_max(doubll2d *list, list_less_func *less)
{
    size_t i, j;
    doubll2d_elem *row_flag, *col_flag, *max;

    if (list == NULL) return NULL;

    /*
     * Initialize the max value with the head value
     */
    row_flag = list->head;
    max = list->head;

    /*
     * From the left-up to right-down
     */

    for (i = 0; i < list->dim_row; i++) {
        col_flag = row_flag;
        for (j = 0; j < list->dim_col; j++) {
            /*
             * Make use of the *less function (function pointer)
             */
            if ((*less)(max, col_flag)) max = col_flag;
            col_flag = col_flag->right;
        }
        row_flag = row_flag->down;
    }
    /*
     * This contains the situation that it is empty then return NULL
     */
    return max;
}

/* Use the given `less` function to find the minimum element in the whole list.
   If there are multiple minimum elements, return any one of them.
   When the 2D linked list is empty, return NULL.
 */
doubll2d_elem *doubll2d_find_min(doubll2d *list, list_less_func *less)
{
    size_t i, j;
    doubll2d_elem *row_flag, *col_flag, *min;

    if (list == NULL) return NULL;

    /*
     * Initialize the min value with the head value
     */
    row_flag = list->head;
    min = list->head;

    /*
     * From the left-up to right-down
     */

    for (i = 0; i < list->dim_row; i++) {
        col_flag = row_flag;
        for (j = 0; j < list->dim_col; j++) {
            /*
             * Make use of the *less function (function pointer)
             */
            if ((*less)(col_flag, min)) min = col_flag;
            col_flag = col_flag->right;
        }
        row_flag = row_flag->down;
    }
    /*
     * This contains the situation that it is empty then return NULL
     */
    return min;
}

static void print_list_for_int(doubll2d *list)
{
    size_t i, j;
    doubll2d_elem *row_flag, *col_flag;
    if (list == NULL) return;
    row_flag = list->head;

    for (i = 0; i < list->dim_row; i++) {
        col_flag = row_flag;
        for (j = 0; j < list->dim_col; j++) {
            printf("%d ", *(int*)(col_flag->data));
            col_flag = col_flag->right;
        }
        printf("\n");
        row_flag = row_flag->down;
    }
}

static bool less_int123(const doubll2d_elem* alpha, const doubll2d_elem* beta)
{
    return (*(int*)(alpha->data) < *(int*)(beta->data));
}

int main()
{
/*
    int** data_line1 = (int**) malloc(0x12*sizeof(int*));
    doubll2d_elem* line1[12];
    doubll2d_elem* ser;
    int** data_line2 = (int**) malloc(0x14*sizeof(int*));
    size_t size[14] = {sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int)};
    int i;
    doubll2d* list = (doubll2d*) malloc(sizeof(doubll2d));

    for (i = 0; i < 12; i++) {
        data_line1[i] = (int*) malloc(sizeof(int));
    }
    for (i = 0; i < 12; i++) {
        *data_line1[i] = i*i;
        line1[i] = doubll2d_elem_create(data_line1[i], sizeof(int));
    }
    for (i = 0; i < 11 ; i++) {
        doubll2d_elem_link(line1[i], RIGHT, line1[i+1]);
    }
    doubll2d_init(list);
    list->head = line1[0];
    list->tail = line1[11];
    list->dim_col = 12;
    list->dim_row = 1;

    for (i = 0; i < 14; i++) {
        data_line2[i] = (int*) malloc(sizeof(int));
    }
    for (i = 0; i < 14; i++) {
        *data_line2[i] = 10000+i*i;
    }

    ser = doubll2d_insert_row(list, line1[2], (void**)data_line2, size, 14);

    print_list_for_int(list);
    printf("%d\n", *(int*)ser->data);
******************************************************************************************/


    int** data_line1 = (int**) malloc(0x12*sizeof(int*));
    doubll2d_elem* line1[12];
    doubll2d_elem* ser;
    doubll2d_elem* ser1;
    doubll2d_elem* ser2;
    int** data_line2 = (int**) malloc(0x14*sizeof(int*));
    size_t size[14] = {sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int), sizeof(int)};
    int i;

    int** data_col = (int**) malloc(0x14*sizeof(int*));

    doubll2d* list = (doubll2d*) malloc(sizeof(doubll2d));



    for (i = 0; i < 12; i++) {
        data_line1[i] = (int*) malloc(sizeof(int));
    }
    for (i = 0; i < 12; i++) {
        *data_line1[i] = i*i;
        line1[i] = doubll2d_elem_create(data_line1[i], sizeof(int));
    }
    for (i = 0; i < 11 ; i++) {
        doubll2d_elem_link(line1[i], RIGHT, line1[i+1]);
    }
    doubll2d_init(list);
    list->head = line1[0];
    list->tail = line1[11];
    list->dim_col = 12;
    list->dim_row = 1;

    for (i = 0; i < 14; i++) {
        data_line2[i] = (int*) malloc(sizeof(int));
        data_col[i] = (int*) malloc(sizeof(int));
    }
    for (i = 0; i < 14; i++) {
        *data_line2[i] = 10000+i*i;
        *data_col[i] = 998+i;
    }


    ser = doubll2d_insert_row(list, line1[2], (void**)data_line2, size, 14);
    ser1 = doubll2d_insert_col(list, line1[11]->down, (void**)data_col, size, 14);

    print_list_for_int(list);
    printf("%d\n", *(int*)ser->data);
    printf("%d\n", *(int*)ser1->data);
/*
    ser2 = doubll2d_delete_col(list, line1[3]->down);
    print_list_for_int(list);
    printf("%d\n", *(int*)ser2->data);

    doubll2d_purge(list);
    print_list_for_int(list);

    printf("%d\n", list->head==NULL);
    printf("%d\n", list->tail==NULL);
    printf("%d\n", list->dim_row==0);
    printf("%d\n", list->dim_col==0);
*/
    ser2 = doubll2d_find_min(list, less_int123);

    printf("%d\n", *(int*)ser2->data);


    return 0;
}
