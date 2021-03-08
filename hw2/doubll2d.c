#include <stdio.h>
#include <stdlib.h>
#include "doubll2d.h"

#define LEFT 0x0
#define RIGHT 0x1
#define UP 0x2
#define DOWN 0x3


/*
   You can imagine that our 2D linked list is a matrix, which MUST have
   a shape of rectangular at all time.

   The 2D doubly linked list with 4 elements (2 by 2) is like this:

    head -----------+   NULL              NULL
                    |    ^                 ^
                    |    |                 |
                    v    |                 |
                  +---------+         +---------+
    NULL <--------|    1    |<------->|    2    |------> NULL
                  +---------+         +---------+
                       ^                   ^
                       |                   |
                       v                   v
                  +---------+         +---------+
    NULL <--------|    3    |<------->|    4    |------> NULL
                  +---------+         +---------+
                       |                 |    ^
                       |                 |    |
                       v                 v    +--------- tail
                      NULL              NULL

    An empty list looks like this:

    head ------> NULL
    NULL <------ tail

    (If not empty) The head pointer of a list should always point to the
    upper-left most element, and the tail pointer should always point to the
    lower-right most element.

    The dim_row and dim_col stores the dimension of the rows and columns (i.e.
    the number of rows and columns).
*/

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
     * Set a flag used to traversal
     */
    doubll2d_elem* flag_elem = cursor;
    int i = 0;

    /*
     * In case the list or the cursor is a NULL pointer
     */
    if ((list == NULL) | (cursor == NULL)) return NULL;

    /*
     * To check if the length is large enough to form a row
     */
    if ((length < list->dim_col) | (length == 0)) return NULL;

    /*
     * Firstly, find the start element in the row that cursor located
     */
    while (flag_elem->left != NULL) flag_elem = flag_elem->left;

    /*
     * From the start elem to the end elem, dock a new elem to every elem in that row
     */
    while (flag_elem != NULL)
    {
        doubll2d_elem_link(flag_elem, DOWN, doubll2d_elem_create(data[i], size[i]));
        /*
         * move the flag
         */
        flag_elem = flag_elem->right;
        i++;
    }

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
                                   void **data, size_t *size, size_t length);

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


int main()
{
    return 0;
}
