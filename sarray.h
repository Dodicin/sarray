#ifndef SARRAY_H
#define SARRAY_H

#include <ostream> // std::ostream
#include <iostream>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iterator> // std::iterator_category
#include <cstddef>  // std::ptrdiff_t

/**
@file sarray.h 
@brief sarray class declaration
**/

/**
@brief Templated sorted array

This class implements a templated sorted array.
The sorting is done by a generic comparation functor F.

**/

template <
    typename T,
    typename F>
class sarray {
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
            return &(*ptr);
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
        friend class sarray;
        const_iterator(const T * const *p) : ptr(p) {}
    }; //const_iterator class

    const_iterator begin() const{
        #ifndef NDEBUG
		    std::cout << "const_iterator::begin() - addr: " << _sortedarray << std::endl;
		#endif
        return const_iterator(_sortedarray);
    }

    const_iterator end() const{
       #ifndef NDEBUG
		    std::cout << "const_iterator::end() - addr: " << _sortedarray+_filled << std::endl;
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
        friend class sarray;
        unsorted_const_iterator(const T *p) : ptr(p) {}
    }; //unsorted_const_iterator class

    unsorted_const_iterator ubegin() const{
        #ifndef NDEBUG
		    std::cout << "unsorted_const_iterator::ubegin() - addr: " << _unsortedarray << std::endl;
		#endif
        return unsorted_const_iterator(_unsortedarray);
    }

    unsorted_const_iterator uend() const{
        #ifndef NDEBUG
		    std::cout << "unsorted_const_iterator::uend() - addr: " << _unsortedarray+_filled << std::endl;
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

		Instantiates an empty sarray
	**/
	sarray(): _size(0), _filled(0), _unsortedarray(0), _sortedarray(0) { 
		#ifndef NDEBUG
		std::cout << "sarray::sarray()" << std::endl;
		#endif
	}

    /**
		@brief Secondary constructor

		Instantiates an sarray with a given size
        @param size Dimension of sarray to instantiate
	**/
	explicit sarray(size_type size): _size(0), _filled(0), _unsortedarray(0), _sortedarray(0) {
        _unsortedarray = new T[size];
        _sortedarray = new T*[size];
        _size = size;
        
		#ifndef NDEBUG
		std::cout << "sarray::sarray(size_type)" << std::endl;
		#endif
	}

    /**
		@brief Secondary constructor

        Instantiates an sarray with a given size, allowing to initialize the cells
        of the sarray with a given value.
		@param size Dimension of the sarray to instantiate
		@param value Value for the initialization of the cells
	**/
	sarray(size_type size, const T &value) : _size(0), _filled(0), _unsortedarray(0), _sortedarray(0) {
		_unsortedarray = new T[size];
        _sortedarray = new T*[size];
        _size = size;
        
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
		std::cout << "sarray::sarray(size_type, T)" << std::endl;
		#endif
	}

    /**
		@brief Copy constructor 

        Copy constructor. Instantiates a sarray with the values taken from another sarray
		@param other sarray to use to create the current one
	**/
	sarray(const sarray &other) : _size(0), _filled(0), _sortedarray(0), _unsortedarray(0) {
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
		std::cout << "sarray::sarray(const sarray&)" << std::endl;
		#endif
	}

    /**
    @brief Method to clear the sarray
    Clears the sarray to leave the mmeory in a consistent state
    **/

    void clear() { 
        delete[] _unsortedarray;
        delete[] _sortedarray;
        _filled = 0;
        _unsortedarray = 0;
        _sortedarray = 0;

        #ifndef NDEBUG
		std::cout << "sarray::clear" << std::endl;
		#endif
    }

    /**
    @brief Method to clean the sarray
    Empties the sarray by swapping it with a new one (the old one gets automatically deleted)
    **/

    void clean() {
        _filled = 0;

        #ifndef NDEBUG
		std::cout << "sarray::clean" << std::endl;
		#endif
    }

    /**
		@brief Assignment operator

		Assignement operator, permits the copy between sarray
		@param other Source sarray
		@return Reference to this
	**/
	sarray &operator=(const sarray &other) {

		if (this != &other) {
			sarray tmp(other);
			this->swap(tmp);
		}

		#ifndef NDEBUG
		std::cout << "sarray::operator=(const sarray&)" << std::endl;
		#endif

		return *this;
	}

    /**
		@brief Distructor

		Distructor, removes the allocated memory
	    **/
	~sarray() {
		clear();
        _size = 0;

		#ifndef NDEBUG
		std::cout << "sarray::~sarray()" << std::endl;
		#endif
	}

    /**
		@brief Data access for the sorted array (read only)

		@pre index < size
		@param index Index of the cell to read
	**/
	const T &operator[](size_type index) const {
		assert(index < _size); 
		return *_sortedarray[index];
	}

    /**
		@brief Data access for the unsorted array (read only)

		@pre index < size
		@param index Index of the cell to read
	**/
	const T &operator()(size_type index) const {
		assert(index < _size); 
		return _unsortedarray[index];
	}

	/**
		@brief Swaps the content of two sarray
		@param other sarray to swap
	**/
	void swap(sarray &other) {
		std::swap(other._size, this->_size);
		std::swap(other._filled, this->_filled);
        std::swap(other._unsortedarray, this->_unsortedarray);
        std::swap(other._sortedarray, this->_sortedarray);
	}

    /**
        @brief Size of the sarray
        @return size of the sarray
    **/
    size_type size() const {
        return _size;
    }

    /**
        @brief Filled portion of the sarray
        @return filled size of the sarray
    **/
    size_type filled() const {
        return _filled;
    }

    
    /**
       @brief Insert a an element in the sarray
       @param value to insert
       @throw exception
       @return boolean, true if the insertion succeded or false if it didn't
    **/
    bool insert(const T &value) {
        if(_size == 0 | _size == _filled)
            return false;
        try{
            _unsortedarray[_filled] = value;
            _sortedarray[_filled] = &_unsortedarray[_filled];
            ++_filled;

            #ifndef NDEBUG
                std::cout << " _u: " << _unsortedarray[_filled - 1] << " | addr: "<< &_unsortedarray[_filled - 1] << std::endl;
                std::cout << " _s: " << _sortedarray[_filled - 1] << " | addr: "<< &_sortedarray[_filled - 1] << std::endl;
            #endif

            insertion_sort();
        }catch(...){
            throw;
        }
        
        #ifndef NDEBUG
        std::cout << "sarray::insert()" << std::endl;
		#endif
    }

    void insertion_sort() {
        for (int i = 1; i < _filled; ++i) {
            for (int j = i; j > 0 && 
                _funct(*_sortedarray[j - 1], *_sortedarray[j]); --j) {
                T *tmp = _sortedarray[j];
                _sortedarray[j] = _sortedarray[j - 1];
                _sortedarray[j - 1] = tmp;
            }
        }
    }

}; // sarray

/**
	@brief Stream operator

	Sends on an output stream the contents of the sarray

	@param os Output stream
	@param sa Sarray to use
	@return Output stream reference
**/
template <typename T, typename F>
std::ostream &operator<<(std::ostream &os, 
                        const sarray<T, F> &sa) {

    typename sarray<T, F>::unsorted_const_iterator i, ie;

    os << "[*** Unsorted array:]" << std::endl;
    for(i = sa.ubegin(), ie = sa.uend(); i!=ie; ++i) {
        #ifndef NDEBUG
		os << "Address: " << &(*i) << std::endl;
		#endif
        
		os << *i << std::endl;
    }

    typename sarray<T, F>::const_iterator j, je;

    os << "[*** Sorted array:]" << std::endl;
    for(j = sa.begin(), je = sa.end(); j!=je; ++j) {
		#ifndef NDEBUG
		os << "Address: " << &(*j) << std::endl;
		#endif

        if(&(*j) == nullptr)
            os << "*nullptr" << std::endl;
        else
		    os << *j << std::endl;
    }
    
	return os;
}

#endif