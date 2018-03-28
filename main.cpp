#include "sarray.h"
#include <string>
#include <cassert>
#include <vector>

template <typename T>
struct a_less_b {
	bool operator()(const T &a, const T &b) const {
		return a<b;
	}
};


void def_init_test() {
    std::cout << std::endl << "***Initialization test (default)***" << std::endl << std::endl;

    sarray<int, a_less_b<int>> a;

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

    sarray<int, a_less_b<int>> a(1);

    assert(a.size() == 2 && "[-] Issue with _size, default ctor on primitive type");
    assert(a.filled() == 0 && "[-] Issue with _filled, default ctor on primitive type");
    assert(a.insert(1) == true && "[-] Issue with _filled, default ctor on primitive type");
    a.insert(1);
    assert(a.insert(2) == false && "[-] Issue with _filled, default ctor on primitive type");
    a.insert(2);
    assert(a.filled() == 1 && "[-] Issue with _filled, default ctor on primitive type");

    a.clean();
    assert(a.size() == 2 && "[-] Issue with _size, default ctor on primitive type");
    assert(a.filled() == 0 && "[-] Issue with _filled, default ctor on primitive type");
    a.insert(2);
    a.insert(3);

    std::cout << "[*] Contents of a: " << std::endl;
    std::cout << a << std::endl;
   
    sarray<int, a_less_b<int>> b(10, 42);
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

    sarray<char, a_less_b<char>> a(6, 'w');

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

    sarray<char, a_less_b<char>>::unsorted_const_iterator i, ie;
    sarray<char, a_less_b<char>>::const_iterator j, je;

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

    sarray<std::string, a_less_b<std::string>> a(10);

    a.insert("marmelade");
    a.insert("to");
    a.insert("sugar song");
    a.insert("peanuts");
    a.insert("and");
    a.insert("bitter step");

    assert(a.filled() == 6 && "[-] Issue with _filled, default ctor on primitive type");

    sarray<std::string, a_less_b<std::string>>::unsorted_const_iterator i, ie;
    sarray<std::string, a_less_b<std::string>>::const_iterator j, je;

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

    sarray<std::string, a_less_b<std::string>> a(10);

    a.insert("marmelade");
    a.insert("to");
    a.insert("sugar song");
    a.insert("peanuts");
    a.insert("and");
    a.insert("bitter step");

    assert(a.filled() == 6 && "Issue with _filled, default ctor on primitive type");

    sarray<std::string, a_less_b<std::string>>::unsorted_const_iterator i, ie;
    sarray<std::string, a_less_b<std::string>>::const_iterator j, je;

    std::cout << "Contents of a using iterators: " << std::endl;

    std::cout << std::endl << "Unsorted array: " << std::endl;
    for(i = a.ubegin(), ie = a.uend(); i != ie; ++i) {
		if(&(*i) == nullptr)
            std::cout << "*nullptr" << std::endl;
        else
		    std::cout << *i << std::endl;
    }

    std::cout << "Sorted array: " << std::endl;

    for(j = a.begin(), je = a.end(); j != je; ++j) {
		if(&(*j) == nullptr)
            std::cout << "*nullptr" << std::endl;
        else
		    std::cout << *j << std::endl;
    }

    std::cout << "Contents of a: " << std::endl;
    std::cout << a << std::endl;

    std::cout << "***Iterators test on non-primitive type successful***" << std::endl;
}

int main() {
    // Initialization test with the default constructor
    //def_init_test();

    // Initialization test with secondary constructor, copy constructor, assignment operator
    //init_test();

    // Iterators test on primitive type
    //iterators_test();

    // Iterators test on non-primitive type
    //iterators_test2();

    /*
    // test del costruttore secondario, data la size, su tipo complesso
    test_non_molto_buono();

    // test costruttore copia su tipi semplici e complessi
    test_costruttore_copia();

    // test che crea un cbuffer di cbuffer di voci e ci lavora su
    test_cbuffer_di_cbuffer_di_voci();

    // test che prova evaluate_if su varie struct
    test_evaluate_if();

    // test che prova a fondo operator[]
    test_operator_quadre();
    
    // test che chiama la clear su un cbuffer e poi lo riempie di nuovo
    test_clear_poi_riempi();*/

    return 0;
}
