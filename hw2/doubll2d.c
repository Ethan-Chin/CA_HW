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
     * If we set the macro CHECK_LIST, then perform the function to check if the cursor is surely there
     */
    #ifdef CHECK_LIST
        if (check_list(list, cursor) == false) return NULL;
    #endif

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
     * If we set the macro CHECK_LIST, then perform the function to check if the cursor is surely there
     */
    #ifdef CHECK_LIST
        if (check_list(list, cursor) == false) return NULL;
    #endif

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
doubll2d_elem *doubll2d_delete_row(doubll2d *list, doubll2d_elem *cursor);

/* Delete the column where the given `cursor` locates and returns the element
   before the given `cursor`. If the first column is deleted, then return the
   element after the given `cursor`. If the deleted column is the only column in
   the list, return NULL. Return NULL on error.

   If the marco CHECK_LIST is set, your code has to check if the element `cursor` is
   actually a member of the list. If not, abort and return NULL. This check is slow.
   If the marco CHECK_LIST is not set, your code shall not perform that check
   but rather run very fast. */
doubll2d_elem *doubll2d_delete_col(doubll2d *list, doubll2d_elem *cursor);

/*  Purge all items from the list. */
void doubll2d_purge(doubll2d *list);


/* Use the given `less` function to find the maximum element in the whole list.
   If there are multiple maximum elements, return any one of them.
   When the 2D linked list is empty, return NULL.
 */
doubll2d_elem *doubll2d_find_max(doubll2d *list, list_less_func *less);

/* Use the given `less` function to find the minimum element in the whole list.
   If there are multiple minimum elements, return any one of them.
   When the 2D linked list is empty, return NULL.
 */
doubll2d_elem *doubll2d_find_min(doubll2d *list, list_less_func *less);

static void print_list_for_int(doubll2d *list)
{
    int i, j;
    doubll2d_elem *row_flag, *col_flag;
    if (list == NULL) return;
    row_flag = list->head;

    for (i = 0; i < (int)list->dim_row; i++) {
        col_flag = row_flag;
        for (j = 0; j < (int)list->dim_col; j++) {
            printf("%d ", *(int*)(col_flag->data));
            col_flag = col_flag->right;
        }
        printf("\n");
        row_flag = row_flag->down;
    }
}
int main()
{

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

    return 0;
}
