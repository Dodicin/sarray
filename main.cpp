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

void test_initialization1() {
    std::cout << "\n\n***TEST COSTRUTTORE DI DEFAULT SU TIPO PRIMITIVO INT***" << std::endl;
    sarray<int, a_less_b<int>> s_int;
    assert(s_int.size() == 0 && "Problema con size, costruttore di default su tipo primitivo");
    assert(s_int.filled() == 0 && "Problema con occupied, costruttore di default su tipo primitivo");
    assert(s_int.insert(2) == false && "Problema con insert costruttore di default su tipo primitivo");
    assert(s_int.filled() == 0 && "Problema con occupied, costruttore di default su tipo primitivo");
    std::cout << "Ordinati" << std::endl;
    for(int i=0; i<s_int.size(); ++i){
        std::cout << &s_int[i] << std::endl;
        std::cout << s_int[i] << std::endl;
    }
     std::cout << "Non ordinati" << std::endl;
    for(int i=0; i<s_int.size(); ++i){
        std::cout << &s_int(i) << std::endl;
        std::cout << s_int(i) << std::endl;
    }
    assert(s_int.size() == 0 && "Problema con size, costruttore di default su tipo primitivo, dopo insert e remove_head");
    assert(s_int.filled() == 0 && "Problema con occupied, costruttore di default su tipo primitivo, dopo insert e remove_head");
    std::cout << "!!!TEST COSTRUTTORE DI DEFAULT SU TIPO PRIMITIVO INT PASSATO!!!" <<std::endl;
}

void test_initialization() {
    std::cout << "Inizio" << std::endl;
    sarray<int, a_less_b<int>> s_int(5);
    s_int.insert(1);
    s_int.insert(2);
    std::cout << s_int << std::endl;
}

int main() {
    // test del costruttore di default su tipo primitivo
    test_initialization();

    /*// test del costruttore da un iteratore
    test_costruttore_iteratori();
    
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
