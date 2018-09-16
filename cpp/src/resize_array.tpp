#include "resize_array.h"

using namespace nets;
    
template <class T>
void ResizeArray<T>::increase_size() {};

template <class T>
void ResizeArray<T>::decrease_size() {};

template <class T>
ResizeArray<T>::ResizeArray() {};

template <class T>
ResizeArray<T>::ResizeArray(int start_size) {};

template <class T>
ResizeArray<T>::~ResizeArray() {};

template <class T>
unsigned int ResizeArray<T>::size() {return 0;};

template <class T>
void ResizeArray<T>::append(T) {};

template <class T>
T ResizeArray<T>::pop() {return _items[_size-- - 1];};

// Time O(1)
template <class T>
T& ResizeArray<T>::operator[](unsigned int index) {return _items[index];};
