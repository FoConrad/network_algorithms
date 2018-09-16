#pragma once

namespace nets {
    
template <class T>
class ResizeArray {
    private:
        T* _items;
        unsigned int _size;
        unsigned int _capacity;

        void increase_size();
        void decrease_size();
    public:
        ResizeArray();
        ResizeArray(int start_size);
        ~ResizeArray();

        // Time O(1)
        unsigned int size();

        // Amortized time O(1)
        void append(T);
        T pop();

        // Time O(1)
        T& operator[](unsigned int index);
};
}

#include "resize_array.tpp"
