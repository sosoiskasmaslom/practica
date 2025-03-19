
#pragma once

namespace own 
{

    template<class T>
    class vector
    {
        template<class> 
        friend std::ostream& operator<<(std::ostream& out, vector<T>);
        
        public:
        class iterator
        {
            public:
            iterator(vector<T>*, size_t);
            iterator(const iterator&);

            iterator& operator=(vector<T>*);
            iterator& operator=(iterator);
            T& operator*();

            iterator& operator+=(int);
            iterator& operator-=(int);
            iterator operator+(int);
            iterator operator-(int);
            size_t operator-(iterator);

            iterator& operator++();
            iterator& operator--();

            iterator operator++(int);
            iterator operator--(int);

            bool operator==(iterator);
            bool operator!=(iterator);
            bool operator>(iterator);
            bool operator>=(iterator);
            bool operator<(iterator);
            bool operator<=(iterator);

            protected:
            vector<T>* ptr;
            size_t position;
        };

        vector();
        template<size_t N> vector(T(&array)[N]);
        vector(int, int);
        vector(const vector&);
        ~vector();
        
        vector& operator=(vector);
        T& operator[](int);
        T operator[](int) const;

        vector& operator+=(const vector&);
        vector operator+(const vector&);

        vector& resize(size_t);
        vector& reserve(size_t);
        vector& shrink_to_fit();
        T& front();
        T& back();
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        vector& push_back(T);
        vector& insert(T, int);
        vector& erase(int, int);
        vector& erase(int);

        iterator cbegin();
        iterator cend();

        protected:
        size_t capacity_;
        size_t size_;
        T* data;
    };

    template<>
    class vector<bool>
    {
        using byte = unsigned char;

        public:
        vector();
        template<size_t N> vector(bool(&array)[N]);
        vector(bool, int);
        vector(const vector&);
        ~vector();

        vector& operator=(vector);
        bool& operator[](int);
        bool operator[](int) const;

        vector& operator+=(const vector&);
        vector operator+(const vector&);

        vector& resize(size_t);
        vector& reserve(size_t);
        vector& shrink_to_fit();
        bool& front();
        bool& back();
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        vector& push_back(bool);
        vector& insert(bool, int);
        vector& erase(int, int);
        vector& erase(int);

        // iterator cbegin();
        // iterator cend();

        protected:
        size_t capacity_;
        size_t size_;
        byte* data;
    };

    class IndexOutError;

}