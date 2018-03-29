#include "sortedarray.h"
#include <string>
#include <cassert>
#include <vector>

void def_init_test() {
    std::cout << std::endl << "***Initialization test (default)***" << std::endl << std::endl;
    typedef sortedarray<int, a_less_b<int>> sarray;

    sarray a;

    assert(a.size() == 0 && "[-] Issue with _size, default ctor on primitive type");
    assert(a.filled() == 0 && "[-] Issue with _filled, default ctor on primitive type");
    assert(a.insert(2) == false && "[*] Issue with insert(), default ctor on primitive type");
    assert(a.filled() == 0 && "[-] Issue with _filled, default ctor on primitive type");

    std::cout << "[*] Contents of a: " << std::endl;
    std::cout << a << std::endl;

    std::cout << "***Initialization test (default) successful***" << std::endl;
}

void init_test() {
    std::cout << std::endl << "***Initialization test***" << std::endl << std::endl;

    typedef sortedarray<int, a_less_b<int>> sarray;

    sarray a(2);

    assert(a.size() == 2 && "[-] Issue with _size, default ctor on primitive type");
    assert(a.filled() == 0 && "[-] Issue with _filled, default ctor on primitive type");
    assert(a.insert(1) == true && "[-] Issue with _filled, default ctor on primitive type");
    a.insert(1);
    assert(a.insert(2) == false && "[-] Issue with _filled, default ctor on primitive type");
    a.insert(2);
    assert(a.filled() == 2 && "[-] Issue with _filled, default ctor on primitive type");

    a.clean();
    assert(a.size() == 2 && "[-] Issue with _size, default ctor on primitive type");
    assert(a.filled() == 0 && "[-] Issue with _filled, default ctor on primitive type");
    a.insert(2);
    a.insert(3);

    std::cout << "[*] Contents of a: " << std::endl;
    std::cout << a << std::endl;
   
    sarray b(10, 42);
    assert(b.size() == 10 && "[-] Issue with _size, default ctor on primitive type");
    assert(b.filled() == 10 && "[-] Issue with _filled, default ctor on primitive type");

    std::cout << "[*] Contents of b: " << std::endl;
    std::cout << b << std::endl;

    a.clean();
    assert(a.filled() == 0 && "[-] Issue with _filled, default ctor on primitive type");

    a.insert(1);
    a.insert(2);
    a.insert(10000);
    a.insert(-8);
    a.insert(92);
    a.insert(112);

    std::cout << "[*] Contents of a: " << std::endl;
    std::cout << std::endl << a << std::endl;

    a.clean();
    std::cout << "[*] Contents of a: " << std::endl;
    std::cout << std::endl << a << std::endl;

    std::cout << "***Initialization test successful***" << std::endl;

}

void iterators_test() {
    std::cout << std::endl << "***Iterators test on primitive type***" << std::endl << std::endl;
    typedef sortedarray<char, a_less_b<char>> sarray;

    sarray a(6, 'w');

    std::cout << "[*] Contents of a: " << std::endl;
    std::cout << a << std::endl;

    a.clean();
    assert(a.size() == 6 && "[-] Issue with _size, default ctor on primitive type");
    assert(a.filled() == 0 && "[-] Issue with _filled, default ctor on primitive type");

    a.insert('r');
    a.insert('a');
    a.insert('k');
    a.insert('u');
    a.insert('g');
    a.insert('o');
    assert(a.filled() == 6 && "[-] Issue with _filled, default ctor on primitive type");

    sarray::unsorted_const_iterator i, ie;
    sarray::const_iterator j, je;

    std::cout << "[*] Contents of a using iterators: " << std::endl;
    std::cout << "[*** Sorted array:]" << std::endl;
    for(j = a.begin(), je = a.end(); j != je; ++j) 
		std::cout << *j << std::endl;

    std::cout << "[*** Unsorted array:]" << std::endl;
    for(i = a.ubegin(), ie = a.uend(); i != ie; ++i) 
		std::cout << *i << std::endl;

    std::cout << "***Iterators test on primitive successful***" << std::endl;
}

void iterators_test2() {
    std::cout << std::endl << "***Iterator test on non-primitive type***" << std::endl << std::endl;

    typedef sortedarray<std::string, a_less_b<std::string>> sarray;

    sarray a(10);

    a.insert("marmelade");
    a.insert("to");
    a.insert("sugar song");
    a.insert("peanuts");
    a.insert("and");
    a.insert("bitter step");

    assert(a.filled() == 6 && "[-] Issue with _filled, default ctor on non-primitive type");

    sarray::unsorted_const_iterator i, ie;
    sarray::const_iterator j, je;

    std::cout << "[*] Contents of a using iterators: " << std::endl;

    std::cout << std::endl << "[*** Unsorted array:]" << std::endl;
    for(i = a.ubegin(), ie = a.uend(); i != ie; ++i) {
		if(&(*i) == nullptr)
            std::cout << "*nullptr" << std::endl;
        else
		    std::cout << *i << std::endl;
    }

    std::cout << "[*** Sorted array:]" << std::endl;

    for(j = a.begin(), je = a.end(); j != je; ++j) {
		if(&(*j) == nullptr)
            std::cout << "*nullptr" << std::endl;
        else
		    std::cout << *j << std::endl;
    }

    std::cout << "[*] Contents of a: " << std::endl;
    std::cout << a << std::endl;

    a.clean();
    a.insert("cha");
    a.insert("la");
    a.insert("head");
    a.insert("cha");
    a.insert("la");

    std::cout << "[*] Contents of a: " << std::endl;
    std::cout << a << std::endl;

    std::cout << "***Iterators test on non-primitive type successful***" << std::endl;
}

void operators_test() {

    std::cout << std::endl << "***Operators test***" << std::endl << std::endl;

    typedef sortedarray<std::string, a_less_b<std::string>> sarray;

    sarray a(4);
    a.insert("bright");
    a.insert("burning");
    a.insert("shout");
    assert(a.filled() == 3 && "Issue with _filled");

    std::cout <<"[*] Contents of a using operators:" << std::endl;
    std::cout <<"[*** Sorted array:] " << std::endl;
    for(unsigned int i=0; i<a.filled(); ++i)
        std::cout << a[i] << std::endl;
    std::cout <<"[*** Unsorted array:] " << std::endl;
    for(unsigned int i=0; i<a.filled(); ++i)
        std::cout << a(i) << std::endl;

    sarray b(3, "bright");
    assert(a(0) == b(0) && "Issue with copy constructor");
    assert(a(1) != b(1) && "Issue with copy constructor");

    a = b;
    std::cout <<"[*] Contents of a:" << std::endl;
    std::cout << a << std::endl;

    std::cout << "***Operators test successful***" << std::endl;
}

void find_count_test() {
    std::cout << std::endl << "***find_count test***" << std::endl << std::endl;

    typedef sortedarray<int> sarray_int;

    sarray_int a(4);
    a.insert(3);
    a.insert(2);
    a.insert(1);
    a.insert(3);

    a_nequal_b<int> funct;
    find_count(a, 3, funct);

    typedef sortedarray<point<double>, same_quadrant<double>> sarray_point;
    typedef point<double> point;

    sarray_point line(6);
    for(unsigned int i=0; i<line.size(); ++i)
        line.insert(point(i-3, -i-3));
    std::cout << line << std::endl;

    same_quadrant<double> funct2;
    find_count(line, point(1, 1), funct2);

    line.clean();
    for(unsigned int i=0; i<line.size(); ++i)
        line.insert(point(i-3.5, i-3.5));
    std::cout << line << std::endl;

    find_count(line, point(1, 1), funct2);

    std::cout << "***find_count test successful***" << std::endl;
}

int main() {
    
    // Initialization test with the default constructor
    def_init_test();

    // Initialization test with secondary constructor, copy constructor, assignment operator
    init_test();

    // Iterators test on primitive type
    iterators_test();

    // Iterators test on non-primitive type
    iterators_test2();

    // Operators test
    operators_test();

    // find_count test
    find_count_test();

    std::cout << std::endl << "*** All test completed successfully ***" << std::endl;

    return 0;
}
