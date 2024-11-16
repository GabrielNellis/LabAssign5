#include <iostream>
#include <vector>
template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>; //VEC = std::vector<vector<T>>

template <class T>
using action_t = T(*) (int); //function that takes an int and returns a variable of type T

template <class T>
using pred_t = bool (*) (T); //function that takes a variable of type T and returns a bool

template <class T>
using map_t = T(*) (T, T); //function that takes 2 variables of type T (same type) and returns a variable of type T (same type as the variables)

template <class T>
void initVec(VEC<T>& v, ELEM<T>&& cons) { //initializes the vector with the given elements
    for (auto e : cons) {
        ELEM<T> tmp;
        tmp.push_back(e);
        v.push_back(tmp);
    }
}

template <class T>
void printElem(ELEM<T>& v) { //prints an element of that type
    if (v.size() > 1) std::cout << "(";
    for (int i = 0; i < v.size(); i++) {
        if ((i < v.size()-1)) std::cout << v[i] << " , ";
        else std::cout << v[i] << " "; //using the if else statement in order to prevent extra commas from printing
    }
    if (v.size() > 1) std::cout << ")";
}

template <class T>
void printVec(VEC<T>& v) { //prints a vector, calls printElem
    std::cout << "[ ";
    for (int i = 0; i < v.size(); i++) {
        if (i < v.size() - 1) {
            printElem(v[i]);
            std::cout << ", "; //using the if else statement to prevent extra commas from printing, either way it'll call printElem
        }
        else printElem(v[i]);
    }
    std::cout << "] \n";
}

template <class T>
VEC<T> generate(int N, action_t<T> f) { //takes an int and a function, runs a loop to run that function (using the number in the loop) n times. produces a vector of type T
    VEC<T> tmp;
    for (int i = 0; i < N; i++) {
        tmp.push_back(ELEM<T>({f(i)})); //making f(i) an ELEM<T> to push onto tmp
    }
    return tmp;
}

template<class T>
VEC<T> zip(VEC<T>& v, VEC<T>& w) { //takes 2 vectors, zips the elements together into one vector ((1),(2),(3)) ((4),(5),(6)) -> ((1,4),(2,5),(3,6))
    VEC<T> tmp;
    for (auto e : v) { //loads tmp with the first elements (gives it a size
        tmp.push_back(e);
    }
    for (int i = 0; i < tmp.size(); i++) { //since tmp is now loaded with values and therefore has a size to work with
        for (int j = 0; j < w[i].size(); j++) { //to get the element(s) of w at the loaction which I want to push onto tmp
            tmp[i].push_back(w[i][j]); 
        }
    }
    return tmp;
}

template<class T>
VEC<T> filter(VEC<T>& v, pred_t<T> f) { //extracts the elements of a vector that meets the condition, tosses out those that don't
    VEC<T> tmp;
    for (ELEM<T> e : v) { //goes through the elements of v (using ELEM<T> e to use e.size() for the next loop)
        for (int i = 0; i < e.size(); i++) { //goes through the elements of e (since e is a vector of type T)
            if (f(e[i])) { //e[i] since this'll go through all elements of e
                tmp.push_back(e); //push_back(e) since e is a vector that can be pushed back onto tmp
            }
        }
    }
    return tmp;
}

template<class T>
VEC<T> map(VEC<T>& v, action_t<T> f) { //
    VEC<int> tmp;
    for (ELEM<T> e : v) { //goes through the elements of v (using ELEM<T> e to use e.size() for the next loop)
        for (int i = 0; i < e.size(); i++) { //goes through the elements of e (since e is a vector of type T)
            tmp.push_back(ELEM<T>{f(e[i])}); //pushing back the result of the function as an ELEM<T>
        }
    }
    return tmp;
}

template<class T>
ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident) { //reduces a vector to a scalar (f(f(ident,v1),v2)) where ident shouldn't change v1 (like multiplying by 1)
    ELEM<T> sum = ident;
    for (ELEM<T> e : v) { //making e of type ELEM<T> to use e.size() since it'll be a vector
        for (int i = 0; i < e.size(); i++) { //goes through the elements of e (needed to make e of tpye ELEM<T> to do this)
            sum[i] = f(sum[i], e[i]); 
        }
    }
    return sum;
}

int f(int a) {
    return a * a;
}

template<class T>
bool g(T a) {
    return (a > 0);
}

template<class T>
int h(T a) {
    return (a > 1 ? 1 : 0); //returns 1 if a>1, otherwise returns 0
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
    std::cout << std::string(10, '*') << std::endl;
    printVec(w);
    std::cout << std::string(10, '*') << std::endl;
    VEC<int> z = zip(v, w);
    printVec(z);
    std::cout << std::string(10, '*') << std::endl;
    VEC<int> x = zip(z, z);
    printVec(x);
    std::cout << std::string(10, '*') << std::endl;
    VEC<int> a = generate(10, f); //f is a function that squares   f is an unknown type?
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
}