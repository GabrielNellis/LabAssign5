#include <iostream>
#include <vector>
template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T(*) (int);

template <class T>
using pred_t = bool (*) (T);

template <class T>
using map_t = T(*) (T, T);

template <class T>
void printElem(ELEM<T>& v) { //prints an element of that type
    if (v.size > 1) std::cout << "(";
    for (auto e : v) {
        std::cout << v[e] << " ";
    }
    if (v.size > 1) std::cout << ")";
}
void initVec(VEC<int>& v, ELEM<int>&& cons) {
    for (auto e : v) {
        v.push_back(cons[e]);
    }
}
/*
template <class T>
void initVec(VEC<T>& v, ELEM<T>&& cons) { //initializes the vector with the given elements
    for (auto e : v) {
        v.push_back(cons[e]);
    }
}
*/
template <class T>
void printVec(VEC<T>& v) { //prints a vector, calls printElem
    for (auto e : v) {
        printElem(v[e]);
    }
}

template <class T>
VEC<T> generate(int N, action_t<T> f) { //takes an int and a function, runs a loop to run that function (using the number in the loop) n times. produces a vector of type T
    VEC<T> tmp;
    for (int i = 0; i < N; i++) {
        tmp.push_back(f(i));
    }
    return tmp;
}

template<class T>
VEC<T> zip(VEC<T>& v, VEC<T>& w) { //takes 2 vectors, zips the elements together into one vector ((1),(2),(3)) ((4),(5),(6)) -> ((1,4),(2,5),(3,6))

}

template<class T>
VEC<T> filter(VEC<T>& v, pred_t<T> f) { //extracts the elements of a vector that meets the condition, tosses out those that don't
    VEC<T> tmp;
    for (int i = 0; i < v.size; i++) {
        if (f(i)) tmp.push_back(i);
    }
    return tmp;
}

template<class T>
VEC<T> map(VEC<T>& v, action_t<T> f) { //
    VEC<int> tmp;
    for (auto e : v) {
        tmp.push_back(f(e));
    }
    return tmp;
}

template<class T>
ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident) { //reduces a vector to a scalar (f(f(ident,v1),v2)) where ident shouldn't change v1 (like multiplying by 1)
    ELEM<T> sum = ident;
    for (auto e : v) {
        sum = f(sum, e);
    }
    return sum;
}

template<class T>
T f(T a) {
    return a * a;
}

template<class T>
bool g(T a) {
    return (a > 0);
}

template<class T>
int h(T a) {
    if (a > 1) return 1;
    else return 0;
}

template<class T>
T k(T a, T b) {
    return a + b;
}

int main()
{
    VEC<int> v;
    initVec(v, ELEM<int>{1, 2, 3, 4});
    VEC<int> w;
    initVec(w, ELEM<int>{-1, 3, -3, 4});
    printVec(v);
    /*
    std::cout << std::string(10, '*') << std::endl;
    printVec(w);
    std::cout << std::string(10, '*') << std::endl;
    VEC<int> z = zip(v, w);
    printVec(z);
    std::cout << std::string(10, '*') << std::endl;
    VEC<int> x = zip(z, z);
    printVec(x);
    std::cout << std::string(10, '*') << std::endl;
    VEC<int> a = generate(10, f); //f is a function that squares
    printVec(a);
    VEC<int> y = filter(w, g); //g is a bool that returns true if arg > 0
    printVec(y);
    VEC<int> u = map(w, h); //h is like g but returns 1 or 0
    printVec(u);
    ELEM<int> e = reduce(u, k, ELEM<int>{0});
    printElem(e);

    std::cout << std::string(10, '$') << std::endl;
    VEC<std::string> ws;
    initVec(ws, ELEM<std::string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);
    ELEM<std::string> es = reduce(ws, k, ELEM<std::string>{""});
    printElem(es);

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printVec(wc);
    ELEM<char> ec = reduce(wc, k, ELEM<char>{' '});
    std::cout << std::endl << std::string(10, '$') << std::endl;
    printElem(ec);

    return 0;
    */
}