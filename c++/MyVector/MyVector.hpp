
namespace MyVector 
{

    template<class T>
    class vector
    {
        template<class type> 
        friend std::ostream& operator<<(std::ostream& out, vector<type>);

        public:
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

        protected:
        size_t capacity_;
        size_t size_;
        T* data;
    };

}