//
// Created by 陈昱聪 on 2021/5/31.
//

#ifndef HW7_DOUBLL2D_IMPL_HPP
#define HW7_DOUBLL2D_IMPL_HPP
/* the definitions of the .hpp file */
using namespace __detail;
/**********************list_row_elem_iter****************************/
/* return the reference of the inner */
template <typename T>
typename list_row_elem_iter<T>::reference list_row_elem_iter<T>::operator*() {return inner->data;}

/* return the inner(as a pointer) */
template <typename T>
typename list_row_elem_iter<T>::pointer list_row_elem_iter<T>::operator->() {return &(inner->data);}

/* prefix move to the right element */
template <typename T>
list_row_elem_iter<T>& list_row_elem_iter<T>::operator++() {inner = inner->right; return *this;}

/* postfix move to the right element */
template <typename T>
list_row_elem_iter<T> list_row_elem_iter<T>::operator++(int) {list_row_elem_iter<T> temp(*this); ++(*this); return temp;}

/* prefix move to the left element */
template <typename T>
list_row_elem_iter<T>& list_row_elem_iter<T>::operator--() {inner = inner->left; return *this;}

/* postfix move to the left element */
template <typename T>
list_row_elem_iter<T> list_row_elem_iter<T>::operator--(int) {list_row_elem_iter<T> temp = *this; --(*this); return temp;}

/* true if this inner and other inner are the same one */
template <typename T>
bool list_row_elem_iter<T>::operator==(const list_row_elem_iter &other) {return inner == other.inner;}

/* true if this inner and other inner are not the same one */
template <typename T>
bool list_row_elem_iter<T>::operator!=(const list_row_elem_iter &other) {return inner != other.inner;}
/**********************list_row_elem_iter****************************/



/***********************list_row_iter**********************************/


/* the leftmost iterator of this row */
template <typename T>
typename list_row_iter<T>::iterator list_row_iter<T>::begin() {return iterator(left);}

/* the iterator next to the rightmost element in this row */
template <typename T>
typename list_row_iter<T>::iterator list_row_iter<T>::end() {
    //in case it is empty
    if (!right) return this->begin();
    return iterator(right->right);
}

/* the `reverse_iterator` of the rightmost element in this row */
template <typename T>
typename list_row_iter<T>::reverse_iterator list_row_iter<T>::rbegin() {return reverse_iterator(iterator(right));}

/* the `reverse_iterator` before the leftmost element in this row */
template <typename T>
typename list_row_iter<T>::reverse_iterator list_row_iter<T>::rend() {
    //in case it is empty
    if (!left) return this->rbegin();
    return reverse_iterator(iterator(left->left));
}

/* reference operator */
template <typename T>
typename list_row_iter<T>::reference list_row_iter<T>::operator*() {return *this;}

/* pointer operator */
template <typename T>
typename list_row_iter<T>::pointer list_row_iter<T>::operator->() {return this;}

//self increment operator
//prefix move to the row below
template <typename T>
list_row_iter<T>& list_row_iter<T>::operator++() {left = left->down; right = right->down; return *this;}

//self increment operator
//postfix move to the row below
template <typename T>
list_row_iter<T> list_row_iter<T>::operator++(int) {list_row_iter<T> temp = *this; ++(*this); return temp;}

//self decrement operator
//prefix move to the row above
template <typename T>
list_row_iter<T>& list_row_iter<T>::operator--() {left = left->up; right = right->up; return *this;}

//self decrement operator
//postfix move to the row above
template <typename T>
list_row_iter<T> list_row_iter<T>::operator--(int) {list_row_iter<T> temp = *this; --(*this); return temp;}

/* true if this iter and other iter are the same one */
template <typename T>
bool list_row_iter<T>::operator==(const list_row_iter<T> &other)
    {return (this->left == other.left)&&(this->right == other.right);}

/* true if this iter and other iter are not the same one */
template <typename T>
bool list_row_iter<T>::operator!=(const list_row_iter<T> &other)
    {return (this->left != other.left)||(this->right != other.right);}
/***********************list_row_iter*********************************/


/**********************list_col_elem_iter****************************/
/* return the reference of the inner */
template <typename T>
typename list_col_elem_iter<T>::reference list_col_elem_iter<T>::operator*() {return inner->data;}

/* return the inner(as a pointer) */
template <typename T>
typename list_col_elem_iter<T>::pointer list_col_elem_iter<T>::operator->() {return &(inner->data);}

/* prefix move to the down element */
template <typename T>
list_col_elem_iter<T>& list_col_elem_iter<T>::operator++() {inner = inner->down; return *this;}

/* postfix move to the down element */
template <typename T>
list_col_elem_iter<T> list_col_elem_iter<T>::operator++(int) {list_col_elem_iter<T> temp = *this; ++(*this); return temp;}

/* prefix move to the up element */
template <typename T>
list_col_elem_iter<T>& list_col_elem_iter<T>::operator--() {inner = inner->up; return *this;}

/* postfix move to the up element */
template <typename T>
list_col_elem_iter<T> list_col_elem_iter<T>::operator--(int) {list_col_elem_iter<T> temp = *this; --(*this); return temp;}

/* true if this inner and other inner are the same one */
template <typename T>
bool list_col_elem_iter<T>::operator==(const list_col_elem_iter &other) {return inner == other.inner;}

/* true if this inner and other inner are not the same one */
template <typename T>
bool list_col_elem_iter<T>::operator!=(const list_col_elem_iter &other) {return inner != other.inner;}
/**********************list_col_elem_iter****************************/



/***********************list_col_iter**********************************/
/* the top iterator of this col */
template <typename T>
typename list_col_iter<T>::iterator list_col_iter<T>::begin() {return iterator(up);}

/* the iterator below to the bottom element in this col */
template <typename T>
typename list_col_iter<T>::iterator list_col_iter<T>::end() {
    //in case it is empty
    if (!down) return this->begin();
    return iterator(down->down);
}

/* the `reverse_iterator` of the bottom element in this col */
template <typename T>
typename list_col_iter<T>::reverse_iterator list_col_iter<T>::rbegin() {return reverse_iterator(iterator(down));}

/* the `reverse_iterator` above the up element in this col */
template <typename T>
typename list_col_iter<T>::reverse_iterator list_col_iter<T>::rend() {
    //in case it is empty
    if (!up) return this->rbegin();
    return reverse_iterator(iterator(up->up));
}

/* reference operator */
template <typename T>
typename list_col_iter<T>::reference list_col_iter<T>::operator*() {return *this;}

/* pointer operator */
template <typename T>
typename list_col_iter<T>::pointer list_col_iter<T>::operator->() {return this;}

//self increment operator
//prefix move to the col right
template <typename T>
list_col_iter<T>& list_col_iter<T>::operator++() {up = up->right; down = down->right; return *this;}

//self increment operator
//postfix move to the col right
template <typename T>
list_col_iter<T> list_col_iter<T>::operator++(int) {list_col_iter<T> temp = *this; ++(*this); return temp;}

//self decrement operator
//prefix move to the col left
template <typename T>
list_col_iter<T>& list_col_iter<T>::operator--() {up = up->left; down = down->left; return *this;}

//self decrement operator
//postfix move to the col left
template <typename T>
list_col_iter<T> list_col_iter<T>::operator--(int) {list_col_iter<T> temp = *this; --(*this); return temp;}

/* true if this iter and other iter are the same one */
template <typename T>
bool list_col_iter<T>::operator==(const list_col_iter<T> &other)
{return (this->up == other.up)&&(this->down == other.down);}

/* true if this iter and other iter are not the same one */
template <typename T>
bool list_col_iter<T>::operator!=(const list_col_iter<T> &other)
{return (this->up != other.up)||(this->down != other.down);}
/***********************list_col_iter*********************************/



/***************************doubll2d**************************************/
// Iterator to the first (top) row
template <typename T>
typename doubll2d<T>::row_iter doubll2d<T>::row_begin() {return row_iter(up_left, up_right);}

// Iterator below the last (bottom) row
template <typename T>
typename doubll2d<T>::row_iter doubll2d<T>::row_end() {
    //in case it is empty
    if (!down_left || !down_right) return this->row_begin();
    return row_iter(down_left->down, down_right->down);
}

// `reverse_iterator` to the last (bottom) row
template <typename T>
typename doubll2d<T>::row_riter doubll2d<T>::row_rbegin()
    {return row_riter(row_iter(down_left, down_right));}

// `reverse_iterator` above the first (top) row
template <typename T>
typename doubll2d<T>::row_riter doubll2d<T>::row_rend()
    {
        //in case it is empty
        if (!up_left || !up_right) return this->row_rbegin();
        return row_riter(row_iter(up_left->up, up_right->up));
    }


// Iterator to the first (leftmost) col
template <typename T>
typename doubll2d<T>::col_iter doubll2d<T>::col_begin() {return col_iter(up_left, down_left);}

// Iterator below the last (rightmost) col
template <typename T>
typename doubll2d<T>::col_iter doubll2d<T>::col_end() {
    //in case it is empty
    if (!up_right || !down_right) return this->col_begin();
    return col_iter(up_right->right, down_right->right);
}

// `reverse_iterator` to the last (rightmost) col
template <typename T>
typename doubll2d<T>::col_riter doubll2d<T>::col_rbegin()
    {return col_riter(col_iter(up_right, down_right));}

// `reverse_iterator` above the first (leftmost) col
template <typename T>
typename doubll2d<T>::col_riter doubll2d<T>::col_rend(){
        //in case it is empty
        if (!up_left || !down_left) return this->col_rbegin();
        return col_riter(col_iter(up_left->left, down_left->left));
    }


// connect the right-left nodes
template <typename T>
void right_left(list_node<T>* first, list_node<T>* second)
{
    //in case it is nullptr
    if (first) first->right = second;
    if (second) second->left = first;
}

// connect the down_up nodes
template <typename T>
void down_up(list_node<T>* first, list_node<T>* second)
{
    //in case it is nullptr
    if (first) first->down = second;
    if (second) second->up = first;
}


//doubll2d
template <typename T>
template<typename input_iter>
typename doubll2d<T>::row_iter doubll2d<T>::insert_row(row_iter cursor, input_iter begin, input_iter end)
{
    //in case the input data in empty
    if (begin == end) return this->row_end();
    //if it is empty
    if (!dim_row)
    {
        auto node = new list_node<T>(*begin);
        // top-left element
        up_left = node;
        // bottom-left element
        down_left = node;
        //increase the dim_col
        dim_col++;

        auto iter = make_iterable(++begin, end);
        //build a iter


        for (auto &data: iter)
        {
            auto new_node = new list_node<T>(data);
            right_left(node, new_node);
            dim_col++;
            //increase the dim_col
            node = new_node;
        }
        // construct a row and make each node connected
        // top-right element
        up_right = node;
        // bottom-right element
        down_right = node;

        //dim_row=1
        dim_row++;
        //return the new row
        return row_iter(up_left, up_right);
    }

    list_node<T>* node;

    //if the cursor is the row_end(), then insert at the begin
    if (cursor == row_end())
    {
        auto i = begin;
        //connect the new nodes into the doubll2d
        for (auto item = row_begin().begin(); item != row_begin().end(); ++item)
        {
            if (i != end) {node = new list_node<T>(*i); i++;}
            else {node = new list_node<T>(T());}
            //if the data is used out
            down_up(node, item.inner);
            //connect it into the list
        }
        //make the new row connected
        for (auto item = row_begin().begin(); item != row_begin().end(); ++item)
        {
            if (!(item.inner->right)) break;
            right_left(item.inner->up, item.inner->right->up);
        }

        //move the up flag
        up_left = up_left->up;
        up_right = up_right->up;

        dim_row++;
        //increase dim_row

        return row_begin();
    }
    else
    {
        //if it is not the end, do it normally
        auto i = begin;
        //connect the new nodes into the doubll2d
        for (auto item = cursor.begin(); item != cursor.end(); ++item)
        {
            if (i != end) {node = new list_node<T>(*i); i++;}
            else {node = new list_node<T>(T());}
            //if the data is used out
            down_up(node, item.inner->down);
            down_up(item.inner, node);
            //connect it into the list
        }
        //make the new row connected
        for (auto item = cursor.begin(); item != cursor.end(); ++item)
        {
            if (!(item.inner->right)) break;
            right_left(item.inner->down, item.inner->right->down);
        }
        if (down_left == cursor.begin().inner)
        {
            //move the up flag
            down_left = down_left->down;
            down_right = down_right->down;
        }
        dim_row++;
        //increase dim_row
        return row_iter(cursor.begin().inner->down, node);
    }
}

template <typename T>
template<typename input_iter>
typename doubll2d<T>::col_iter doubll2d<T>::insert_col(col_iter cursor, input_iter begin, input_iter end)
{
    //in case the input data in empty
    if (begin == end) return this->col_end();
    //if it is empty
    if (!dim_col)
    {
        auto node = new list_node<T>(*begin);
        // top-left element
        up_left = node;
        // top-right element
        up_right = node;
        //increase the dim_row
        dim_row++;

        auto iter = make_iterable(++begin, end);
        //build a iter


        for (auto &data: iter)
        {
            auto new_node = new list_node<T>(data);
            down_up(node, new_node);
            dim_row++;
            //increase the dim_row
            node = new_node;
        }
        // top-right element
        down_left = node;
        // bottom-right element
        down_right = node;

        //dim_row=1
        dim_col++;
        //return the new row
        return col_iter(up_left, down_left);
    }

    list_node<T>* node;

    //if the cursor is the row_end(), then insert at the begin
    if (cursor == col_end())
    {
        auto i = begin;
        //connect the new nodes into the doubll2d
        for (auto item = col_begin().begin(); item != col_begin().end(); ++item)
        {
            if (i != end) {node = new list_node<T>(*i); i++;}
            else {node = new list_node<T>(T());}
            //if the data is used out
            right_left(node, item.inner);
            //connect it into the list
        }
        //make the new row connected
        for (auto item = col_begin().begin(); item != col_begin().end(); ++item)
        {
            if (!(item.inner->down)) break;
            down_up(item.inner->left, item.inner->down->left);
        }
        //move the up flag
        up_left = up_left->left;
        down_left = down_left->left;

        dim_col++;
        //increase dim_col

        return col_begin();
    }
    else
    {
        //if it is not the end, do it normally
        auto i = begin;
        //connect the new nodes into the doubll2d
        for (auto item = cursor.begin(); item != cursor.end(); ++item)
        {
            if (i != end) {node = new list_node<T>(*i); i++;}
            else {node = new list_node<T>(T());}
            //if the data is used out
            right_left(node, item.inner->right);
            right_left(item.inner, node);
            //connect it into the list
        }
        //make the new row connected
        for (auto item = cursor.begin(); item != cursor.end(); ++item)
        {
            if (!(item.inner->down)) break;
            down_up(item.inner->right, item.inner->down->right);
        }
        if (up_right == cursor.begin().inner)
        {
            //move the up flag
            up_right = up_right->right;
            down_right = down_right->right;
        }
        dim_col++;
        //increase dim_row
        return col_iter(cursor.begin().inner->right, node);
    }
}

template <typename T>
typename doubll2d<T>::row_iter doubll2d<T>::delete_row(row_iter cursor)
{
    // if the cursor is end
    if (cursor == row_end()) return row_end();
    // if the the list is empty
    if (!dim_row) return row_begin();
    // if it is the only row to be deleted
    if (dim_row == 1)
    {
        //make two targets to traverse
        auto dptr = cursor.begin().inner;
        auto fptr = cursor.begin();

        //traverse to delete
        while(dptr)
        {
            fptr++;
            delete(dptr);
            dptr = fptr.inner;
        }

        //make sure the four corners are set to nullptr
        up_left = nullptr;
        up_right = nullptr;
        down_left = nullptr;
        down_right = nullptr;

        //make sure the dims are correct
        dim_row = 0; dim_col = 0;
        return row_end();
    }
    // if we want to delete the first row
    if (cursor == row_begin())
    {
        auto temp = cursor;
        ++temp;
        auto iter = temp.begin();
        //set a iter
        up_left = iter.inner;
        //traverse
        do
        {
            delete(iter.inner->up);
            iter.inner->up = nullptr;
            //make sure set to nullptr
            up_right = iter.inner;
        } while ((++iter).inner);

        dim_row--;
        return row_begin();
    }

    //normal case
    auto temp = cursor;

    //identify whether it is the last to move the flag
    if (++cursor == row_end())
    {
        down_left = down_left->up;
        down_right = down_right->up;
    }

    --temp;
    auto iter = temp.begin();
    //traverse to delete
    do
    {
        auto target = iter.inner->down;
        //make sure to reconnect
        down_up(iter.inner, iter.inner->down->down);
        delete(target);
    } while((++iter).inner);

    dim_row--;
    //decrease it
    return temp;
}

template <typename T>
typename doubll2d<T>::col_iter doubll2d<T>::delete_col(col_iter cursor)
{
    // if the cursor is end
    if (cursor == col_end()) return col_end();
    // if the the list is empty
    if (!dim_col) return col_begin();
    // if it is the only row to be deleted
    if (dim_col == 1)
    {
        //make two targets to traverse
        auto dptr = cursor.begin().inner;
        auto fptr = cursor.begin();

        //traverse to delete
        while(dptr)
        {
            fptr++;
            delete(dptr);
            dptr = fptr.inner;
        }

        //make sure the four corners are set to nullptr
        up_left = nullptr;
        up_right = nullptr;
        down_left = nullptr;
        down_right = nullptr;

        //make sure the dims are correct
        dim_row = 0; dim_col = 0;
        return col_end();
    }
    // if we want to delete the first row
    if (cursor == col_begin())
    {
        auto temp = cursor;
        ++temp;
        //set a iter
        auto iter = temp.begin();
        up_left = iter.inner;
        //traverse
        do
        {
            delete(iter.inner->left);
            iter.inner->left = nullptr;
            //make sure set to nullptr
            down_left = iter.inner;
        } while ((++iter).inner);

        dim_col--;
        return col_begin();
    }
    //normal case
    auto temp = cursor;

    //identify whether it is the last to move the flag
    if (++cursor == col_end())
    {
        up_right = up_right->left;
        down_right = down_right->left;
    }

    --temp;
    auto iter = temp.begin();
    //traverse to delete
    do
    {
        auto target = iter.inner->right;
        right_left(iter.inner, iter.inner->right->right);
        //make sure to reconnect
        delete(target);
    } while((++iter).inner);

    dim_col--;
    //decrease it
    return temp;
}

//clear the list
template <typename T>
void doubll2d<T>::clear() {while(dim_row) this->delete_row(this->row_begin());}




//reduce method
template <typename T>
template<class R>
R doubll2d<T>::reduce(std::function<R(R, const T &)> fn, R init)
{
    //traverse the whole list
    for (auto &row: this->row_iterable())
        for (auto &data: row)
            init = fn(init, data);

    //return the final results
    return init;
}

/***************************doubll2d**************************************/

#endif //HW7_DOUBLL2D_IMPL_HPP
