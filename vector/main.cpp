//# xVector
//
//### 简介
//  基于SGI STL提供的 allocate & type_traits 实现的简略版本的vector容器。
//
//### 参考&感谢
//  1. 《STL 源码剖析》侯捷 著 [主要是抄写]
//  2.  现行SGI STL源码。
//
//###### @xMushroom

#include <iostream>
#include <string>
#include <memory>
#include <type_traits>


template<class _Ty, class _Alloc = std::allocator<_Ty>>
class xVector
{
public:
    // const using_name variable; const会失效
    // const 和 volatile 也会发生折叠
    using value_type = _Ty;
    using pointer = value_type *;
    using reference = value_type &;
    using iterator = value_type *; //迭代器 因为指针符合 random access iterator 类型迭代器
    using size_type = size_t;
    using difference = ptrdiff_t;
protected:
    _Alloc allocer;     //使用std的分配器
    iterator start;             //目前使用空间的头
    iterator finish;            //目前使用空间的尾 (可用空间的头)
    iterator end_of_storage;    //目前可用空间的尾
protected:
    void insert_aux(iterator position, const _Ty &x)
    {
        if (finish != end_of_storage) //如果当前空间没有使用完毕
        {
            std::_Construct(finish, *(finish - 1)); //为新添加的元素添加一个位置
            ++finish;
            value_type x_copy = x;
            std::copy_backward(position, finish - 2, finish - 1); //将position位置到finish-1的元素都向后移动一位(值拷贝)
            *position = x_copy;
        }
        else //当前无可用空间
        {
            const size_type old_size = size(); //记录当前数据大小
            const size_type len = old_size != 0 ? 2 * old_size : 1; //计算新内存大小
            iterator new_start = allocer.allocate(len); //配置新内存
            iterator new_finish = new_start; //记录新内存可用起始位置
            __try
            {
                new_finish = std::uninitialized_copy(start, position, new_finish); //将原有内存的前半部分，拷贝构造到新内存上的对应位置
                std::_Construct(new_finish, x); //拷贝构造新添加的值
                ++new_finish; //迭代可用空间起始位置
                new_finish = std::uninitialized_copy(position, finish, new_finish); //将原有内存的后半部分，拷贝构造到新内存上的对应位置
            }
            __catch (...)
            {
                std::_Destroy(new_start, new_finish);
                allocer.deallocate(new_start, len);
                throw;
            }

            //释放并析构原有内存
            std::_Destroy(begin(), end());
            deallocate();


            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }
    }

    //配置并填充
    void fill_initialize(size_type n, const _Ty &value)
    {
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }

    //配置相应大小内存并填充(构造成默认值x)
    iterator allocate_and_fill(size_type n, const _Ty &x)
    {
        iterator result = allocer.allocate(n);
        std::uninitialized_fill_n(result, n, x);
        return result;
    }

    //释放已申请的内存
    void deallocate()
    {
        if (start != nullptr)
            allocer.deallocate(start, end_of_storage - start);
    }

public:
    iterator begin()
    {
        return start;
    }

    iterator end()
    {
        return finish;
    }

    size_type size() const
    {
        return static_cast<size_type>(finish - start);
    }

    //容量
    size_type capacity() const
    {
        return static_cast<size_type>(end_of_storage - start);
    }

    bool empty() const
    {
        return begin() == end();
    }

    reference operator[](size_type n)
    {
        return *(begin() + n);
    }

    void clear()
    {
        erase(begin(), end());
    }

public:
    reference front()
    {
        return *begin();
    }

    reference back()
    {
        return *end();
    }

    void insert(iterator position, size_type n, const _Ty &x)
    {
        if (n != 0)
        {
            if (size_type(end_of_storage - finish) >= n) //如果备用空间足够
            {
                value_type x_copy = x;
                const size_type elems_after = finish - position; //插入点后方已使用长度
                iterator old_finish = finish;
                if (elems_after > n) // 如果插入点后侧已使用长度 大于 插入数据长度
                {
                    finish = std::uninitialized_copy(finish - n, finish, finish); //拷贝后侧数据到原始已使用结尾处
                    std::copy_backward(position, old_finish - n, old_finish); //将插入点之后
                    std::fill(position, position + n, x_copy); //构造并赋值插入部分
                }
                else //如果插入点后侧已使用长度 小于 插入数据长度
                {
                    std::uninitialized_fill_n(finish, n - elems_after, x_copy); //补充 插入数据还差的部分
                    finish += n - elems_after;//移动已使用空间尾部，剩下的就是原始数据了
                    std::uninitialized_copy(position, old_finish, finish);//拷贝后侧数据到原始已使用结尾处
                    finish += elems_after;//移动尾部
                    std::fill(position, old_finish, x_copy);//把原来的插入点后半已使用部分的元素填充成插入值
                }
            }
            else //剩余空间不足够
            {
                const size_type old_size = size();
                const size_type len = old_size + std::max(old_size, n); //至少新空间是老空间×2
                iterator new_start = allocer.allocate(len); //配置新空间
                iterator new_finish = new_start;

                __try
                {
                    new_finish = std::uninitialized_copy(start, position, new_start);//拷贝构造插入点的前半截
                    new_finish = std::uninitialized_fill_n(new_finish, n, x); //构造填充插入的数据
                    new_finish = std::uninitialized_copy(position, finish, new_finish); //拷贝构造插入点的后半截
                }
                __catch(...)
                {
                    std::_Destroy(new_start, new_finish);
                    allocer.deallocate(new_start, len);
                    throw;
                }

                std::_Destroy(start, finish); //析构老空间
                allocer.deallocate(start, end_of_storage - start); //释放老空间

                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + len;
            }
        }
    }

    void copy_to(iterator position, iterator _Frist, iterator _Last)
    {
        size_type n = _Last - _Frist;
        if (n != 0)
        {
            if (size_type(end_of_storage - finish) >= n) //如果备用空间足够
            {
                const size_type elems_after = finish - position; //插入点后方已使用长度
                iterator old_finish = finish;
                if (elems_after > n) // 如果插入点后侧已使用长度 大于 插入数据长度
                {
                    finish = std::uninitialized_copy(finish - n, finish, finish); //拷贝后侧数据到原始已使用结尾处
                    std::copy_backward(position, old_finish - n, old_finish); //将插入点之后
                    std::uninitialized_copy(_Frist, _Last, position);//构造并赋值插入部分
                }
                else //如果插入点后侧已使用长度 小于 插入数据长度
                {
                    std::uninitialized_copy(_Last - n - elems_after, _Last, finish);
                    finish += n - elems_after;//移动已使用空间尾部，剩下的就是原始数据了
                    std::uninitialized_copy(position, old_finish, finish);//拷贝后侧数据到原始已使用结尾处
                    finish += elems_after;//移动尾部
                    std::uninitialized_copy(_Frist, _Last, position);//构造并赋值插入部分
                }
            }
            else //剩余空间不足够
            {
                const size_type old_size = size();
                const size_type len = old_size + std::max(old_size, n); //至少新空间是老空间×2
                iterator new_start = allocer.allocate(len); //配置新空间
                iterator new_finish = new_start;

                __try
                {
                    new_finish = std::uninitialized_copy(start, position, new_start);//拷贝构造插入点的前半截
                    new_finish = std::uninitialized_copy(_Frist, _Last, new_finish);//构造并赋值插入部分
                    new_finish = std::uninitialized_copy(position, finish, new_finish); //拷贝构造插入点的后半截
                }
                __catch(...)
                {
                    std::_Destroy(new_start, new_finish);
                    allocer.deallocate(new_start, len);
                    throw;
                }

                std::_Destroy(start, finish); //析构老空间
                allocer.deallocate(start, end_of_storage - start); //释放老空间

                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + len;
            }
        }
    }

    //在末尾添加一个元素
    void push_back(const _Ty &x)
    {
        if (finish != end_of_storage) //如果当前还有剩余内存
        {
            std::_Construct(finish, x); //配置并赋值第一个未使用内存
            ++finish; //迭代未使用内存开头位置
        }
        else
        {
            insert_aux(end(), x);
        }
    }

    //丢弃最后一个元素
    void pop_back(const _Ty &x)
    {
        if (size() > 0)
        {
            --finish; // 可用起始位置迭代
            std::_Destroy(finish); // 析构可用起始位置的元素
        }
    }

    iterator erase(iterator position)
    {
        if (position + 1 != end()) //如果不是最后元素
        {
            std::copy(position + 1, finish, position); // 被删除元素的后边元素都向前移动一位
        }
        --finish; // 已用向前移动一位
        std::_Destroy(finish); //析构最后一位
        return position;
    }

    void resize(size_type new_size, const _Ty &x)
    {
        if (new_size < size())
        {
            erase(begin() + new_size, end()); //析构已使用所有元素
        }
        else
        {
            insert(end(), new_size - size(), x); //借用添加配置所有元素
        }
    }

    void resize(size_type new_size)
    {
        resize(new_size, value_type());
    }

public:
    explicit xVector() :
            start(nullptr), finish(nullptr), end_of_storage(nullptr)
    {
        //
    }

    xVector(size_type n, const _Ty &value)
    {
        fill_initialize(n, value);
    }

    xVector(int n, const _Ty &value)
    {
        fill_initialize(n, value);
    }

    xVector(long n, const _Ty &value)
    {
        fill_initialize(n, value);
    }

    xVector(xVector<_Ty, _Alloc> &_value) :
            start(nullptr), finish(nullptr), end_of_storage(nullptr)
    {
        copy_to(begin(), _value.begin(), _value.end());
    }

    xVector(const xVector<_Ty, _Alloc> &&_value)
    {
        this->start = _value.start;
        this->finish = _value.finish;
        this->end_of_storage = _value.end_of_storage;

        _value.start = nullptr;
        _value.finish = nullptr;
        _value.end_of_storage = nullptr;
    }

    explicit xVector(size_type n)
    {
        fill_initialize(n, value_type());
    }

    ~xVector()
    {

        std::_Destroy(start, finish); //析构已使用内存(并不释放内存)
        deallocate();
    }
};

int main()
{
    int sum = 20;
    xVector<std::string> test;

    for (int i = 0; i < sum; ++i)
    {
        test.insert(test.begin(), 1, std::to_string(i));
    }

    for (xVector<std::string>::iterator ite = test.begin(); ite != test.end(); ite++)
    {
        printf("%p:\t%s\n", ite, ite->c_str());
    }

    printf("\n**********************************\n");

    xVector<std::string> test2(test);
    test2.copy_to(test2.end(), test.begin(), test.end());

    for (int i = 0; i < test2.size(); ++i)
    {
        printf("%d:\t%s\n", i, test2[i].c_str());
    }
    return 0;
}