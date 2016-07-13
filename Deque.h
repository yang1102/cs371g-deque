// --------------------------
// projects/c++/deque/Deque.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                           allocator_type;
        typedef typename allocator_type::value_type         value_type;

        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;

        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;

        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;

        typedef typename A::template rebind<pointer>::other B;

         //Size of inner row arrays.
        const size_type static INNER_SIZE = 5;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * @param lhs a const my_deque by reference
         * @param rhs a const my_deque by reference
         * @return bool 
         * 
         * output the whether the value of lhs is equal to rhs 
         */
        friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::equal()
            //check if nothing, zero
            if(lhs.size() == 0 && rhs.size() ==0)
                return true;
                    
             return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());}

        // ----------
        // operator <
        // ----------

        /**
         * @param lhs a const my_deque by reference
         * @param rhs a const my_deque by reference
         * @return bool 
         * 
         * output the whether the value of lhs is smaller than rhs 
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());}

    private:
        // ----
        // data
        // ----

        allocator_type _a;  //inner array allocator
        B _b;          //outer block allocator

        //The very beginning and end of each outer chunk
        pointer* outer_top;
        pointer* outer_bot;

        //The used begin and end of each outer chunk
        pointer* outer_begin;
        pointer* outer_end;

        //The begin and end of inner arrays
        pointer begin;
        pointer end;

        size_type size;
        size_type outer_size;

        //outer array capacity
        size_type capacity;



        // <your data>

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            return true;}

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef          std::bidirectional_iterator_tag iterator_category;
                typedef typename my_deque::value_type            value_type;
                typedef typename my_deque::difference_type       difference_type;
                typedef typename my_deque::pointer               pointer;
                typedef typename my_deque::reference             reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs a const iterator by reference
                 * @param rhs a const iterator by reference
                 * @return bool 
                 * 
                 * output the whether the value of lhs is equal to rhs 
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    // <your code>

                    return (lhs.index==rhs.index)&&(lhs.outer_index==rhs.outer_index)&&(lhs.x==rhs.x);
                }

                /**
                 * @param lhs a const iterator by reference
                 * @param rhs a const iterator by reference
                 * @return bool 
                 * 
                 * output the whether the value of lhs is not equal to rhs (true for not equal)
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs a const iterator by reference
                 * @param rhs a const iterator by reference
                 * @return iterator 
                 * 
                 * output the addition of two iterator 
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------
                
                /**
                 * @param lhs a const iterator by reference
                 * @param rhs a const iterator by reference
                 * @return iterator 
                 * 
                 * output the subtracion of two iterator 
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                size_type index;
                size_type outer_index;
                my_deque* x;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return outer_index > x->outer_size;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * Three arguments constructor
                 * @param q pointer to the my_deque
                 * @param s a size_type index represents index this iterator should point at 
                 * @param out a size_type index represents the outer index that this iterator is point at
                 * output an iterator 
                 */
                iterator (my_deque* q, size_type s, size_type out): x(q) {

                    // <your code>
                    this->index = s;
                    this->outer_index = out;
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * @return reference to value type 
                 */
                reference operator * () const {
                    // <your code>
                    // dummy is just to be able to compile the skeleton, remove it
                    return *(*(q->outer_begin+outer_index)+index);}

                // -----------
                // operator ->
                // -----------

                /**
                 * @return pointer to value type location 
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * pre increment
                 * @return iterator reference 
                 */
                iterator& operator ++ () {
                    if(index > INNER_SIZE-1){
                        ++outer_index;
                        index = 0;
                    }
                    else
                        ++index;
                    assert(valid());
                    return *this;}

                /**
                 * post increment
                 * @return iterator reference 
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * post decrement
                 * @return iterator reference 
                 */
                iterator& operator -- () {
                    if(index == 0){
                        --outer_index;
                        index = INNER_SIZE-1;
                    }
                    else
                        --index;
                    assert(valid());
                    return *this;}

                /**
                 * pre decrement
                 * @return iterator reference 
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * @param d is a difference_type 
                 * @return iterator by reference which increased by d
                 */
                iterator& operator += (difference_type d) {
                    while(d){
                        ++*this;
                        --d;
                    }
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * @param d is a difference_type 
                 * @return iterator by reference which decreased by d
                 */
                iterator& operator -= (difference_type d) {
                    while(d){
                        --*this;
                        --d;
                    }
                    assert(valid());
                    return *this;}};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef          std::bidirectional_iterator_tag iterator_category;
                typedef typename my_deque::value_type            value_type;
                typedef typename my_deque::difference_type       difference_type;
                typedef typename my_deque::const_pointer         pointer;
                typedef typename my_deque::const_reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs a const const_iterator by reference
                 * @param rhs a const const_iterator by reference
                 * @return bool 
                 * 
                 * output the whether the value of lhs is equal to rhs 
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    // <your code>
                    return lhs.i==rhs.i;}

                /**
                 * @param lhs a const const_iterator by reference
                 * @param rhs a const const_iterator by reference
                 * @return bool 
                 * 
                 * output the whether the value of lhs is not equal to rhs (true for not equal)
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs a const const_iterator by reference
                 * @param rhs a const const_iterator by reference
                 * @return const_iterator 
                 * 
                 * output the addition of two const_iterator 
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs a const const_iterator by reference
                 * @param rhs a const const_iterator by reference
                 * @return const_iterator 
                 * 
                 * output the subtraction of two const_iterator 
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
                my_deque::iterator i;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return true;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * Three arguments constructor
                 * @param q const pointer to my_deque t
                 * @param s a size_type index represents index this iterator should point at 
                 * @param out a size_type index represents the outer index that this iterator is point at
                 * output a const_iterator 
                 */
                const_iterator (const my_deque* q, size_type s, size_type out):i(const_case<my_deque*>(q),s,out) {
                    // <your code>
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * @return const_reference to value type 
                 */
                const_reference operator * () const {
                    // <your code>
                    // dummy is just to be able to compile the skeleton, remove it
                    return const_cast<const_reference>(*i);}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * pre increment
                 * @return const_iterator reference 
                 */
                const_iterator& operator ++ () {
                    // <your code>
                    ++i;
                    assert(valid());
                    return *this;}

                /**
                 * post increment
                 * @return const_iterator reference 
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * post decrement
                 * @return const_iterator reference 
                 */
                const_iterator& operator -- () {
                    --i;
                    assert(valid());
                    return *this;}

                /**
                 * pre decrement
                 * @return const_iterator reference 
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * @param d is a difference_type 
                 * @return const_iterator by reference which increased by d
                 */
                const_iterator& operator += (difference_type d) {
                    // <your code>
                    i += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * @param d is a difference_type 
                 * @return const_iterator by reference which decreased by d
                 */
                const_iterator& operator -= (difference_type d) {
                    // <your code>
                    i -= d;
                    assert(valid());
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
         * @param s is size_type by value
         * @param v is const_reference by value
         * @param a is allocator_type by reference
         */
        explicit my_deque (size_type s = 0, const_reference v = value_type(), const allocator_type& a = allocator_type()): _a(a),size(s)
            {

            outer_size = ( s==0 )? 0:(s-1)/INNER_SIZE+1;
            capacity = outer_size*INNER_SIZE;
            outer_top = _b.allocate(outer_size);

            //default size 0
            if(s == 0)
                begin = 0;

            for(int i = 0; i< s; ++i){
                if(i == 0){
                    begin = _a.allocate(INNER_SIZE);
                    outer_top[i] = begin;
                }
                else if(i == s-1){
                    outer_top[i]=_a.allocate(INNER_SIZE);
                    end = outer_top[i]+(size%INNER_SIZE);
                }
                else
                    outer_top[i]=_a.allocate(INNER_SIZE);
            }
            end = begin + s;
            outer_bot = outer_top + outer_size -1;
            outer_begin = outer_top;
            outer_end = outer_bot;
            uninitialized_fill (_a, begin(), end(), v);

            assert(valid());
            }

        /**
         * copy constructor
         * @param that is a my_deque passed by reference 
         */
        my_deque (const my_deque& that): _a(that._a),size(that.size),outer_size(that.outer_size),capacity(that.capacity){
            
            outer_top = _b.allocate(that.outer_size);
            outer_bot = outer_top + (that.outer_bot-that.outer_top);
            outer_begin = outer_top + (that.outer_begin-that.outer_top);
            outer_end =  outer_top + (that.outer_end-that.outer_top);

            for(int i = 0; i < that.size; ++i){
                    outer_top[i] = _a.allocate(INNER_SIZE);
            }

            begin = *outer_top + (that.begin - *(that.outer_top));
            end = *outer_end + (that.end - *(that.outer_end));


            uninitialized_copy(_a, that.begin(), that.end(), begin());

            assert(valid());}

        // ----------
        // destructor
        // ----------
        destroy (A& a, BI b, BI e) 
        /**
         * destructs and frees all memory
         */
        ~my_deque () {
            // <your code>
            clear();
            destory(_a,begin(),end());

            for(int i  = 0; i <outer_size; ++i){
                _a.deallocate(outer_top[i], INNER_SIZE);
            }    

            _b.deallocate(outer_top, outer_size);

            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * @param rhs is a my_deque by reference 
         * @return my_deque by reference
         * copy assignment
         */
        my_deque& operator = (const my_deque& rhs) {
            if (this == &rhs)
                return *this;
            if (rhs.size() == size())
                std::copy(rhs.begin(), rhs.end(), begin());

            else if (rhs.size() < size()) {
                std::copy(rhs.begin(), rhs.end(), begin());
                resize(rhs.size());
            }
            else {
                clear();
                resize(that.size());
                auto temp = std::copy(that.begin(), that.end(), begin());
                end = &(*temp);
            }

            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * @param index is a size_type
         * @return reference of that value at taht index
         * copy assignment
         */
        reference operator [] (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            size_type temp = index+ (begin - *outer_begin);
            size_type outer_index = temp/INNER_SIZE;
            size_type inner_index = temp%INNER_SIZE;

            return *(*(outer_begin+outer_index)+inner_index);
        }

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * <your documentation>
         * @throws out_of_range
         */
        reference at (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         * @throws out_of_range
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * <your documentation>
         */
        reference back () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;
        }

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * <your documentation>
         */
        iterator begin () {
            // <your code>
            return iterator(/* <your arguments> */);}

        /**
         * <your documentation>
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(/* <your arguments> */);}

        // -----
        // clear
        // -----

        /**
         * <your documentation>
         */
        void clear () {
            // <your code>
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * <your documentation>
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * <your documentation>
         */
        iterator end () {
            // <your code>
            return iterator(/* <your arguments> */);}

        /**
         * <your documentation>
         */
        const_iterator end () const {
            // <your code>
            return const_iterator(/* <your arguments> */);}

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         */
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();}

        // -----
        // front
        // -----

        /**
         * <your documentation>
         */
        reference front () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * <your documentation>
         */
        iterator insert (iterator, const_reference) {
            // <your code>
            assert(valid());
            return iterator();}

        // ---
        // pop
        // ---

        /**
         * <your documentation>
         */
        void pop_back () {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         */
        void pop_front () {
            // <your code>
            assert(valid());}

        // ----
        // push
        // ----

        /**
         * <your documentation>
         */
        void push_back (const_reference) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         */
        void push_front (const_reference) {
            // <your code>
            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            // <your code>
            assert(valid());}

        // ----
        // size
        // ----

        /**
         * <your documentation>
         */
        size_type size () const {
            // <your code>
            return 0;}

        // ----
        // swap
        // ----

        /**
         * <your documentation>
         */
        void swap (my_deque&) {
            // <your code>
            assert(valid());}};

#endif // Deque_h
