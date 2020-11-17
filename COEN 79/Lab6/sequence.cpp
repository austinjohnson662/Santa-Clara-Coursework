//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }

    //uses the clear function then sets the member variables to initial values
    sequence::~sequence() {
        list_clear(head_ptr);
        init();
    }

    //sets cursor to the head
    void sequence::start() {
        cursor = head_ptr;
        precursor = NULL;
    }

    //sets cursor to the last item in the sequence
    void sequence::end() {
        if (many_nodes == 0) {
            cursor = NULL;
            precursor = NULL;
            return;
        }
        if (head_ptr == tail_ptr) {
            cursor = head_ptr;
            precursor = NULL;
            return;
        }
        cursor = tail_ptr;
        precursor = list_locate(head_ptr, many_nodes - 1);
    }

    //moves the cursor and precursor one item down the list. Can set cursor to NULL.
    void sequence::advance() {
        assert(is_item());        
        precursor = cursor;
        cursor = cursor->link();
    }

    //checks if cursor is a real item. if it is real it uses list_insert. If cursor does not point to an item or precursor doesnt point to an item uses list_head_insert.
    void sequence::insert(const value_type& entry) {
        if (!is_item()||precursor == NULL) {
            list_head_insert(head_ptr, entry);
            if (tail_ptr == NULL)
                tail_ptr = head_ptr;
            cursor = head_ptr;
            precursor = NULL;
            many_nodes++;
        }
        else {
            list_insert(precursor, entry);
            cursor = precursor->link();
            many_nodes++;
        }
    }

    //uses three cases: empty, cursor is NULL, and all else. Inserts the entry after the cursor. Calls list_head_insert for case 1 and list_insert for 2,3.
    void sequence::attach(const value_type& entry) {
        if (head_ptr == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
            many_nodes++;
        }
        else if (cursor == NULL) {
            list_insert(tail_ptr, entry);
            precursor = tail_ptr;
            tail_ptr = tail_ptr->link();
            cursor = tail_ptr;
            many_nodes++;
        }
        else {
            list_insert(cursor, entry);
            precursor = cursor;
            if (cursor == tail_ptr)
                tail_ptr = tail_ptr->link();
            cursor = cursor->link();
            many_nodes++;
        }
    }

    //uses list_copy to create the new sequence. loops through the sequence until the cursor is correct.
    void sequence::operator =(const sequence& source) {
        if (this == &source)  //checks if the item is itself
            return;
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;
        start();
        node* cur = source.head_ptr;
        while (cur != source.cursor) {
            advance();
            cur = cur->link();
        }
    }

    //If it is a single item sequence use list_head_remove. otherwise use list_remove.
    void sequence::remove_current() {
        assert(is_item());
        if (head_ptr == cursor) {
            if (head_ptr == tail_ptr) {
                list_head_remove(head_ptr);
                head_ptr = NULL;
                tail_ptr = NULL;
                cursor = NULL;
                precursor = NULL;
            }
            else {
                list_head_remove(head_ptr);
                precursor = NULL;
                cursor = head_ptr;
            }
        }
        else if (cursor == tail_ptr) {
            list_remove(precursor);
            tail_ptr = precursor;
            cursor = NULL;
        }
        else {
            list_remove(precursor);
            cursor = precursor->link();
        }
        many_nodes--;
    }

    //returns many_nodes
    sequence::size_type sequence::size() const {
        return many_nodes;
    }

    //true is cursor points to a non-NULL item. False otherwise.
    bool sequence::is_item() const {
        return (cursor != NULL);
    }

    //returns the pointed to item.
    sequence::value_type sequence::current() const {
        assert(is_item());
        return cursor->data();
    }
}
