//基于 memory 实现的 list(双向链表)
//xMushroom

#include <memory>

template<class _Ty>
struct __xlist_node
{
    typedef void *void_pointer;
    void_pointer prev;
    void_pointer next;
    _Ty data;
};

template<class _Ty, class _Tr, class _Tp>
struct __xlist_iterator
{
    using iterator = __xlist_iterator<_Ty, _Ty &, _Ty *>;
    using self = __xlist_iterator<_Ty, _Tr, _Tp>;

    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = _Ty;
    using pointer = _Tp;
    using reference = _Tr;
    using link_type = __xlist_node<_Ty> *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    link_type node;

    __xlist_iterator(link_type x) : node(x)
    {

    }

    __xlist_iterator()
    {}

    __xlist_iterator(const iterator &x) : node(x.node)
    {

    }

    bool operator==(const self &x) const
    {
        return node == x.node;
    }

    bool operator!=(const self &x) const
    {
        return node != x.node;
    }

    reference operator*() const
    {
        return (*node).data;
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    self &operator++()
    {
        node = (link_type) ((*node).next);
        return *this;
    }

    self operator++(int)
    {
        self tmp = *this;
        node = (link_type) ((*node).next);
        return tmp;
    }

    self &operator--()
    {
        node = (link_type) ((*node).prev);
        return *this;
    }

    self operator--(int)
    {
        self tmp = *this;
        node = (link_type) ((*node).prev);
        return tmp;
    }
};

template<class _Ty, class _Alloc = std::allocator<__xlist_node<_Ty>>>
class xlist
{
public:
    using value_type = _Ty;
    using reference = _Ty &;
    using pointer = _Ty *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    using list_node = __xlist_node<_Ty>;
    using link_type = list_node *;
    using iterator = __xlist_iterator<_Ty, _Ty &, _Ty *>;
protected:
    _Alloc alloc;
    link_type node;
protected:
    link_type alloc_node()
    {
        return alloc.allocate(1);
    }

    void dealloc_node(link_type p)
    {
        alloc.deallocate(p, 1);
    }

    link_type create_node(const _Ty &x)
    {
        link_type p = alloc_node();
        std::_Construct(&p->data, x);
        return p;
    }

    link_type create_node()
    {
        link_type p = alloc_node();
        std::_Construct_novalue(p);
        return p;
    }

    void destroy_node(link_type p)
    {
        std::_Destroy(&p->data);
        dealloc_node(p);
    }

    void empty_initialize()
    {
        node = alloc_node();
        node->next = node;
        node->prev = node;
    }

public:
    xlist()
    {
        empty_initialize();
    }
    ~xlist()
    {
        clear();
    }
public:
    iterator begin()
    {
        return (link_type) ((*node).next);
    }

    iterator end()
    {
        return node;
    }

    bool empty() const
    {
        return node->next == node;
    }

    size_type size() const
    {
        return (size_type) std::distance(begin(), end());
    }

    reference front()
    {
        return *begin();
    }

    reference back()
    {
        return *(--end());
    }

    void swap(xlist<_Ty,_Alloc>& x)
    {
        std::swap(this->node,x.node);
    }

public:
    iterator insert(iterator position, const _Ty &x)
    {

        /*  n   : the insertion position
         *  np  : the forward node of the insertion position
         *  nn  : the behind node of the insertion position
         *  tmp : the new node be insertion
         *
         *  np      np
         *  ↓       ↓
         *  n   ->  tmp
         *  ↓       ↓
         *  nn      n
         *          ↓
         *          np
         * */
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        (link_type(position.node->prev))->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }

    void push_back(const _Ty &x)
    {
        insert(end(), x);
    }

    void push_front(const _Ty &x)
    {
        insert(begin(), x);
    }

    iterator erase(iterator position)
    {
        /*  n   : the need erase position
         *  np  : the forward node of the insertion position
         *  nn  : the behind node of the insertion position
         *
         *  np      np
         *  ↓       ↓
         *  n   ->  np
         *  ↓
         *  nn
         * */

        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }

    void pop_fornt()
    {
        erase(begin());
    }

    void pop_back()
    {
        erase(end());
    }

public:
    void clear()
    {
        link_type current = link_type(node->next);
        link_type tmp = nullptr;
        while (current != node)
        {
            tmp = current;
            current = link_type(current->next);
            destroy_node(tmp);
        }

        node->next = node;
        node->prev = node;
    }

    void remove(const _Ty &value)
    {
        iterator first = begin();
        iterator last = end();
        iterator next;
        while (first != last)
        {
            if (*first == value)
                first = erase(first);
            else
                first++;
        }
    }

private:
    void transfer(iterator position, iterator first, iterator last)
    {
        if (position != last)
        {
            link_type(last.node->prev)->next = position.node;
            link_type(first.node->prev)->next = last.node;
            link_type(position.node->prev)->next = first.node;

            link_type tmp = link_type((*position.node).prev);

            position.node->prev = first.node->prev;
            last.node->prev = first.node->prev;
            first.node->prev = tmp;
        }
    }

public:
    void splice(iterator position, xlist<_Ty,_Alloc>& x)
    {
        if(!x.empty())
        {
            transfer(position,x.begin(),x.end());
        }
    }

    void splice(iterator position,xlist<_Ty,_Alloc>& x,iterator i)
    {
        iterator j = i;
        ++j;
        if(position == i || position == j)
            return;
        transfer(position,i,j);
    }

    void splice(iterator position,xlist<_Ty,_Alloc>& x,iterator first,iterator last)
    {
        if(first != last)
        {
            transfer(position,first,last);
        }
    }

public:
    void merge(xlist<_Ty,_Alloc>& x)
    {
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = x.begin();
        iterator last2 = x.end();

        while(first1 != last1 && first2 != last2)
        {
            if(*first2 < *first1)
            {
                iterator  next = first2;
                transfer(first1,first2,++next);
                first2 = next;
            }
            else
            {
                ++first2;
            }

            if(first2 != last2)
                transfer(last1,first2,last2);
        }
    }

    void reverse()
    {
        if(node->next == node || link_type(node->next)->next == node)
            return;

        iterator first = begin();
        ++first;
        while (first != end())
        {
            iterator  old = first;
            ++first;
            transfer(begin(),old,first);
        }
    }
};

int main()
{
    xlist<int> list;
    for (int i = 10; i >0; --i)
    {
        list.push_back(i*10);
    }

    list.reverse();

    for (xlist<int>::iterator ite = list.begin();ite != list.end();ite++)
    {
        printf("%d\n",*ite);
    }

    return 0;
}
