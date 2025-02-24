
#include <iostream>

using namespace std;

class List
{

    public:

    int value;

    int count;
    List* next;
    List* prev;

    List(int value = 0): 
        value(value), count(0), next(this), prev(this) {};
    List(List& minilist);
    ~List();

    int& operator[] (int c);
    bool operator== (List& other);

    void pushback(int val); // пережиток прошлого
    void insert(int val, int c);
    void delete_first();
    void delete_last(); // пережиток прошлого
    void erase(int c);
    bool erase(bool(*cond)(int));

    int len();
    void dubl(bool(*cond)(int));
    void sort(bool(*cond)(int, int));

};

List::List(List& minilist): value(minilist.value), count(0), next(this), prev(this)
{

    List* other = minilist.next;
    while(other->count != 0) 
    {
        this->insert(other->value, -1);
        other = other->next;
    } 

}

List::~List()
{

    value = 0;
    count = 0;
    next = nullptr;
    prev = nullptr;

}

int& List::operator[] (int c)
{

    List* link = this;
    while(link->count != c) {link = link->next;}
    
    return link->value;

}

bool List::operator== (List& minilist)
{

    List* link = this;
    List* other = &minilist;
    int len;

    if (this->prev->count != other->prev->count) return 0;
    else len = this->prev->count;

    do
    {

        if (link->value != other->value) return 0;

        link = link->next;
        other = other->next;

    } while (link->next->count != 0);

    return 1;

}

void List::insert(int val, int c = -1)
{

    List* elem = new List(val);
    List* link = this;

    if (c<0) {c = this->prev->count + c + 1;}
    while(link->count != c) {link = link->next;}

    elem->next = link->next;
    elem->prev = link;
    elem->count = link->count + 1;

    link->next->prev = elem;
    link->next = elem;
    
    link = link->next;

    while(link->next->count != 0) 
    {
        link = link->next;
        link->count++;
    }

}

void List::delete_first()
{

    this->value = this->next->value;
    this->erase(1);

}

void List::erase(int c = -1)
{

    List* link = this;

    if (c == 0) 
    {
        this->delete_first();
        return;
    }

    if (c<0) {c = this->prev->count + c + 1;}
    while(link->count != c) {link = link->next;}
    
    link->prev->next = link->next;
    link->next->prev = link->prev;
    List* copy = link;

    while(link->next->count != 0) 
    {
        link = link->next;
        link->count--;
    }

    delete copy;

}

bool List::erase(bool(*cond)(int))
{

    List* link = this;

    while(!cond(link->value)) 
    {
        if (link->next->count == 0) return 0;
        link = link->next;
    }
    
    if (link->count == 0) 
    {
        this->delete_first();
        return 1;
    }

    link->prev->next = link->next;
    link->next->prev = link->prev;
    List* copy = link;

    while(link->next->count != 0) 
    {
        link = link->next;
        link->count--;
    }

    delete copy;

    return 1;

}

int List::len() {return this->prev->count;}

void swap(List* one, List* two)
{
    int copy = one->value;
    one->value = two->value;
    two->value = copy;
}

void List::sort(bool(*cond)(int, int) = [](int a, int b) {return a<b;})
{

    for (int c = 0; c < this->prev->count; c++)
    {
        for (List* link = this; link->next->count != 0; link = link->next)
        {
            if (cond(link->value, link->next->value)) swap(link, link->next);
        }
    }

}

List& sorted(List copy, bool(*cond)(int, int) = [](int a, int b) {return a<b;})
{

    List* that = &copy;
    for (int c = 0; c < that->prev->count; c++)
    {
        for (List* link = that; link->next->count != 0; link = link->next)
        {
            if (cond(link->next->value, link->value)) swap(link->next, link);
        }
    }

    return *(that);

}

void List::dubl(bool(*cond)(int))
{

    List* link = this;

    do 
    {
        if (cond(link->value)) 
        {
            this->insert(link->value, link->count);
            link = link->next;
        }
        link = link->next;
    } while (link->count != 0);

}

template<class Type>
void print(Type value)
{
    cout << value << endl;
}

template<>
void print<List*>(List* link)
{

    do 
    {
        cout << link->count << ' ' << link->value << endl;
        link = link->next;
    } while (link->count != 0);

} 

bool unsort(int a, int b) {return a>b;}
bool erase_list(int a) {return !(a%15);}

bool easy(int a)
{
    for(int i = 2; i<a; i++)
    {
        if (!(a%i)) return 0;
    }
    return 1;
}

bool first_num(int a, int b)
{

    while (!(0 < a && a < 10)) {a /= 10;}
    while (!(0 < b && b < 10)) {b /= 10;}

    return a>b;

}
