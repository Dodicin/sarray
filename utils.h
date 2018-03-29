#ifndef UTILS_H
#define UTILS_H

/**
	@brief Functor to check equality between data
	@param a T element
	@param b T element
	@return boolean True if a is not equal to b
**/
template <typename T>
struct a_nequal_b {
	bool operator()(const T &a, const T &b) const {
		return a!=b;
	}
};

/**
	@brief Functor to check if a type T is less than another
	@param a T element
	@param b T element
	@return boolean True if the a is less than b
**/
template <typename T>
struct a_less_b {
	bool operator()(const T &a, const T &b) const {
		return a<b;
	}
};

template <typename T>
struct point {
	T _x;
  	T _y;
	point() {}
  	point(T x, T y) : _x(x), _y(y) {}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const point<T> &p) {
	os << "(" << p._x << ", " << p._y << ")";
  	return os;
}

/**
	@brief Functor to check if two points are in the same quadrant of a Cartesian coordinate graph
	@param a Point A
	@param b Point B
	@return boolean True if the two points are in the same quadrant
**/
template <typename T>
struct same_quadrant {
	bool operator()(const point<T> &a, const point<T> &b) const {
		return (((a._x * b._x) >= 0) && ((a._y * b._y) >= 0));
	}
};

#endif