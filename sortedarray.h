#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H

#include <ostream> // std::ostream
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <iterator> // std::iterator_category
#include <cstddef>  // std::ptrdiff_t
#include "utils.h"

/**
@file sortedarray.h 
@brief sortedarray class declaration
**/

/**
@brief Templated sorted array

This class implements a templated sorted array.
The sorting is done by a generic comparation functor F.

**/

template <
    typename T,
    typename F=a_less_b<T>>
class sortedarray {
    friend class iterator;
    friend class const_interator;
    typedef unsigned int size_type;

public: //Iterators

    class const_iterator {
        const T* const* ptr;

    public:
    	typedef std::random_access_iterator_tag iterator_category;
		typedef T                               value_type;
		typedef ptrdiff_t                       difference_type;
		typedef const T*                        pointer;
		typedef const T&                        reference;

        const_iterator() : ptr(0) {}
        const_iterator(const const_iterator &other) : ptr(other.ptr) {}
        ~const_iterator() {}

        const_iterator& operator=(const const_iterator &other) {
            ptr = other.ptr;
            return *this;
        }

        // Returns dereferenced value
        reference operator*() const {
            return **ptr;
        }

        // Returns pointed value
        pointer operator->() const {
            return (*ptr);
        }
        
        // Returns value at pointed index
        reference operator[](int index) {
	        return *ptr[index];
	    }

        // Post-increment
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++ptr;
            return tmp;
        }

        // Pre-increment
        const_iterator& operator++() {
            ++ptr;
            return *this;
        }
        
        // Post-decrement
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --ptr;
            return tmp;
        }

        // Pre-decrement
        const_iterator &operator--() {
            --ptr;
            return *this;
        }

        // Addition
        const_iterator operator+(int offset) {
            ptr = (ptr + offset);
            return *this;
        }

        // Subtraction
        const_iterator operator-(int offset) {
            ptr = (ptr - offset);
            return *this;
        }

        // Shorthand addition
        const_iterator& operator+=(int offset) {
            ptr = (ptr + offset);
            return *this;
        }

        // Shorthand subtraction
        const_iterator& operator-=(int offset) {
            ptr = (ptr - offset);
            return *this;
        }

        // Pointer difference
        difference_type operator-(const const_iterator &other) {
            if((ptr - other.ptr) < 0)
            return other.ptr - ptr;
            else
            return ptr - other.ptr;
        }

        // Equality
        bool operator==(const const_iterator &other) const {
            return ptr == other.ptr;
        }

        // Inequality
        bool operator!=(const const_iterator &other) const {
            return ptr != other.ptr;
        }

        // Greater than
        bool operator>(const const_iterator &other) const {
	        return ptr > other.ptr;
        }

        // Greater or equal than
        bool operator>=(const const_iterator &other) const {
            return ptr >= other.ptr;
        }

        // Less than
        bool operator<(const const_iterator &other) const {
            return ptr < other.ptr;
        }

        // Less or equal than
        bool operator<=(const const_iterator &other) const {
            return ptr <= other.ptr;
        }


    private:
        friend class sortedarray;
        const_iterator(const T * const *p) : ptr(p) {}
    }; //const_iterator class

    const_iterator begin() const{
        #ifndef NDEBUG
		    std::cout << "const_iterator::begin() - addr: " << static_cast<const void*>(_sortedarray) << std::endl;
		#endif
        return const_iterator(_sortedarray);
    }

    const_iterator end() const{
       #ifndef NDEBUG
		    std::cout << "const_iterator::end() - addr: " << static_cast<const void*>(_sortedarray+_filled) << std::endl;
		#endif
        
        return const_iterator(_sortedarray+_filled);
    }
        
    class unsorted_const_iterator {
        const T *ptr;

    public:
    	typedef std::random_access_iterator_tag iterator_category;
		typedef T                               value_type;
		typedef ptrdiff_t                       difference_type;
		typedef const T*                        pointer;
		typedef const T&                        reference;

        unsorted_const_iterator() : ptr(0) {}
        unsorted_const_iterator(const unsorted_const_iterator &other) : ptr(other.ptr) {}
        ~unsorted_const_iterator() {}

        unsorted_const_iterator& operator=(const unsorted_const_iterator &other) {
            ptr = other.ptr;
            return *this;
        }

        // Returns dereferenced value
        reference operator*() const {
            return *ptr;
        }

        // Returns pointed value
        pointer operator->() const {
            return ptr;
        }
        
        // Returns value at pointed index
        reference operator[](int index) {
	        return ptr[index];
	    }

        // Post-increment
        unsorted_const_iterator operator++(int) {
            unsorted_const_iterator tmp(*this);
            ++ptr;
            return tmp;
        }

        // Pre-increment
        unsorted_const_iterator& operator++() {
            ++ptr;
            return *this;
        }
        
        // Post-decrement
        unsorted_const_iterator operator--(int) {
            unsorted_const_iterator tmp(*this);
            --ptr;
            return tmp;
        }

        // Pre-decrement
        unsorted_const_iterator &operator--() {
            --ptr;
            return *this;
        }

        // Addition
        unsorted_const_iterator operator+(int offset) {
            ptr = (ptr + offset);
            return *this;
        }

        // Subtraction
        unsorted_const_iterator operator-(int offset) {
            ptr = (ptr - offset);
            return *this;
        }

        // Shorthand addition
        unsorted_const_iterator& operator+=(int offset) {
            ptr = (ptr + offset);
            return *this;
        }

        // Shorthand subtraction
        unsorted_const_iterator& operator-=(int offset) {
            ptr = (ptr - offset);
            return *this;
        }

        // Pointer difference
        difference_type operator-(const unsorted_const_iterator &other) {
            if((ptr - other.ptr) < 0)
                return other.ptr - ptr;
            else
                return ptr - other.ptr;
        }

        // Equality
        bool operator==(const unsorted_const_iterator &other) const {
            return ptr == other.ptr;
        }

        // Inequality
        bool operator!=(const unsorted_const_iterator &other) const {
            return ptr != other.ptr;
        }

        // Greater than
        bool operator>(const unsorted_const_iterator &other) const {
	        return ptr > other.ptr;
        }

        // Greater or equal than
        bool operator>=(const unsorted_const_iterator &other) const {
            return ptr >= other.ptr;
        }

        // Less than
        bool operator<(const unsorted_const_iterator &other) const {
            return ptr < other.ptr;
        }

        // Less or equal than
        bool operator<=(const unsorted_const_iterator &other) const {
            return ptr <= other.ptr;
        }


    private:
        friend class sortedarray;
        unsorted_const_iterator(const T *p) : ptr(p) {}
    }; //unsorted_const_iterator class

    unsorted_const_iterator ubegin() const{
        #ifndef NDEBUG
		    std::cout << "unsorted_const_iterator::ubegin() - addr: " << static_cast<const void*>(_unsortedarray) << std::endl;
		#endif
        return unsorted_const_iterator(_unsortedarray);
    }

    unsorted_const_iterator uend() const{
        #ifndef NDEBUG
		    std::cout << "unsorted_const_iterator::uend() - addr: " << static_cast<const void*>(_unsortedarray+_filled) << std::endl;
		#endif
        return unsorted_const_iterator(_unsortedarray+_filled);
    }

private:
    T* _unsortedarray;
    T** _sortedarray;
    size_type _size;
    size_type _filled;
    F _funct;

public:
	/**
		@brief Default constructor

		Instantiates an empty sortedarray
	**/
	sortedarray(): _unsortedarray(0), _sortedarray(0), _size(0), _filled(0) { 
		#ifndef NDEBUG
		std::cout << "sortedarray::sortedarray()" << std::endl;
		#endif
	}

    /**
		@brief Secondary constructor

		Instantiates an sortedarray with a given size
        @param size Dimension of sortedarray to instantiate
	**/
	explicit sortedarray(size_type size): _unsortedarray(0), _sortedarray(0), _size(size), _filled(0) {
        _unsortedarray = new T[size];
        _sortedarray = new T*[size];
        
		#ifndef NDEBUG
		std::cout << "sortedarray::sortedarray(size_type)" << std::endl;
		#endif
	}

    /**
		@brief Secondary constructor

        Instantiates an sortedarray with a given size, allowing to initialize the cells
        of the sortedarray with a given value.
		@param size Dimension of the sortedarray to instantiate
		@param value Value for the initialization of the cells
	**/
	sortedarray(size_type size, const T &value) : _unsortedarray(0), _sortedarray(0), _size(size), _filled(0) {
		_unsortedarray = new T[size];
        _sortedarray = new T*[size];
        
		try {
			for(size_type i=0 ; i < _size; ++i){
				insert(value);
            }
		}
		catch(...) {
			clear();
			throw;
		}
		#ifndef NDEBUG
		std::cout << "sortedarray::sortedarray(size_type, T)" << std::endl;
		#endif
	}

    /**
		@brief Copy constructor 

        Copy constructor. Instantiates a sortedarray with the values taken from another sortedarray
		@param other sortedarray to use to create the current one
	**/
	sortedarray(const sortedarray &other) :  _unsortedarray(0), _sortedarray(0), _size(0), _filled(0) {
		_unsortedarray = new T[other._size];
        _sortedarray = new T*[other._size];
		_size = other._size;
        _filled = other._filled;

		try {
			for(size_type i=0; i<_size; ++i) {
				_unsortedarray[i] = other._unsortedarray[i];
                _sortedarray[i] = other._sortedarray[i];
            }
		}
		catch(...) {
			clear();
			throw;
		}

		#ifndef NDEBUG
		std::cout << "sortedarray::sortedarray(const sortedarray&)" << std::endl;
		#endif
	}

    /**
    @brief Method to clear the sortedarray
    Clears the sortedarray to leave the mmeory in a consistent state
    **/

    void clear() { 
        delete[] _unsortedarray;
        delete[] _sortedarray;
        _filled = 0;
        _unsortedarray = 0;
        _sortedarray = 0;

        #ifndef NDEBUG
		std::cout << "sortedarray::clear" << std::endl;
		#endif
    }

    /**
    @brief Method to clean the sortedarray
    Empties the sortedarray by swapping it with a new one (the old one gets automatically deleted)
    **/

    void clean() {
        _filled = 0;

        #ifndef NDEBUG
		std::cout << "sortedarray::clean" << std::endl;
		#endif
    }

    /**
		@brief Assignment operator

		Assignement operator, permits the copy between sortedarray
		@param other Source sortedarray
		@return Reference to this
	**/
	sortedarray &operator=(const sortedarray &other) {

		if (this != &other) {
			sortedarray tmp(other);
			this->swap(tmp);
		}

		#ifndef NDEBUG
		std::cout << "sortedarray::operator=(const sortedarray&)" << std::endl;
		#endif

		return *this;
	}

    /**
		@brief Distructor

		Distructor, removes the allocated memory
	    **/
	~sortedarray() {
		clear();
        _size = 0;

		#ifndef NDEBUG
		std::cout << "sortedarray::~sortedarray()" << std::endl;
		#endif
	}

    /**
		@brief Data access for the sorted array (read only)

		@pre index < filled
		@param index Index of the cell to read
	**/
	const T &operator[](size_type index) const {
		assert(index < _filled && "Index exceeds filled capacity"); 
		return *_sortedarray[index];
	}

    /**
		@brief Data access for the unsorted array (read only)

		@pre index < filled
		@param index Index of the cell to read
	**/
	const T &operator()(size_type index) const {
		assert(index < _filled && "Index exceeds filled capacity"); 
		return _unsortedarray[index];
	}

	/**
		@brief Swaps the content of two sortedarray
		@param other sortedarray to swap
	**/
	void swap(sortedarray &other) {
		std::swap(other._size, this->_size);
		std::swap(other._filled, this->_filled);
        std::swap(other._unsortedarray, this->_unsortedarray);
        std::swap(other._sortedarray, this->_sortedarray);
	}

    /**
        @brief Size of the sortedarray
        @return size of the sortedarray
    **/
    size_type size() const {
        return _size;
    }

    /**
        @brief Filled portion of the sortedarray
        @return filled size of the sortedarray
    **/
    size_type filled() const {
        return _filled;
    }

    
    /**
       @brief Insert a an element in the sortedarray
       @param value to insert
       @throw exception
       @return boolean, true if the insertion succeded or false if it didn't
    **/
    bool insert(const T &value) {
        if((_size == 0) | (_size == _filled))
            return false;

        try{
            _unsortedarray[_filled] = value;
            _sortedarray[_filled] = &_unsortedarray[_filled];
            ++_filled;

            #ifndef NDEBUG
                std::cout << " _u: " << _unsortedarray[_filled - 1] 
                << " | addr: "<< static_cast<const void*>(&_unsortedarray[_filled - 1]) << std::endl;
                std::cout << " _s: " << static_cast<const void*>(_sortedarray[_filled - 1]) 
                << " | addr: "<< &_sortedarray[_filled - 1] << std::endl;
            #endif

            insertion_sort();
        }catch(...){
            throw;
        }
        
        #ifndef NDEBUG
        std::cout << "sortedarray::insert()" << std::endl;
		#endif

        return true;
    }

    void insertion_sort() {
        for (size_type i = 1; i < _filled; ++i) {
            for (size_type j = i; 
                 j > 0 && _funct(*_sortedarray[j - 1], *_sortedarray[j]); --j) {
                T *tmp = _sortedarray[j];
                _sortedarray[j] = _sortedarray[j - 1];
                _sortedarray[j - 1] = tmp;
            }
        }
    }

}; // sortedarray

/**
	@brief Stream operator

	Sends on an output stream the contents of the sortedarray

	@param os Output stream
	@param sa sortedarray to use
	@return Output stream reference
**/
template <typename T, typename F>
std::ostream &operator<<(std::ostream &os, 
                        const sortedarray<T, F> &sa) {

    typename sortedarray<T, F>::unsorted_const_iterator i, ie;

    os << "[*** Unsorted array:]" << std::endl;
    for(i = sa.ubegin(), ie = sa.uend(); i!=ie; ++i) {
        #ifndef NDEBUG
		os << "Address: " << static_cast<const void*>(&(*i)) << std::endl;
		#endif
        
		os << *i << std::endl;
    }

    typename sortedarray<T, F>::const_iterator j, je;

    os << "[*** Sorted array:]" << std::endl;
    for(j = sa.begin(), je = sa.end(); j!=je; ++j) {
		#ifndef NDEBUG
		os << "Address: " << static_cast<const void*>(&(*j)) << std::endl;
		#endif

        if(&(*j) == nullptr)
            os << "*nullptr" << std::endl;
        else
		    os << *j << std::endl;
    }
    
	return os;
}


/**
	@brief find_count function

    Sends on an output stream the count of elements of a sortedarray sa
    of type T that given a target value T satisfy P(sa[i], target)
 
	@param sa Sortedarray to use for the count
	@param target T value used to compare each element of sa with
    @param funct P functor
**/
template <typename T, typename F, typename P>
void find_count(const sortedarray<T, F> &sa, const T &target, const P &funct) {
	int count = 0;
    typename sortedarray<T, F>::unsorted_const_iterator i, ie;

    for(i = sa.ubegin(), ie = sa.uend(); i!=ie; ++i) {
        try{
            if(funct(*i, target)==1) ++count;
        }catch(...){
            throw;
        }
    }
    std::cout << "[*] Elements in sa satisfying the functor against [" << target << "]: " << count << std::endl;
}

#endif
