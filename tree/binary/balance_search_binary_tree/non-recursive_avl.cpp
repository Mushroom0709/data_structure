#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

namespace xAVL
{
    template<typename KType, typename VType>
    class Tree;

    template<typename KType, typename VType>
    class Node
    {
        friend Tree<KType, VType>;
    private:
        KType key_;
        VType value_;

        int height_;
        Node<KType, VType>* left_;
        Node<KType, VType>* right_;
    private:
        Node()
        {
            key_ = 0;
            height_ = 1;
            left_ = nullptr;
            right_ = nullptr;
        }
        Node(KType _key,VType _value)
        {
            key_ = _key;
            value_ = _value;
            height_ = 1;
            left_ = nullptr;
            right_ = nullptr;
        }
        ~Node()
        {
            //
        }
    };

    template<typename KType, typename VType>
    class Tree
    {
        using PNode = Node<KType, VType>*;
    private:
        PNode root_;
    private:
        int get_height(PNode _root)
        {
            if (_root == nullptr)
                return 0;
            return _root->height_;
        }
        int get_max_height(PNode _a, PNode _b)
        {
            return std::max(get_height(_a), get_height(_b));
        }
        int get_balance(PNode _root)
        {
            if (_root == NULL)
                return 0;
            return get_height(_root->left_) - get_height(_root->right_);
        }

        PNode ll_rotate(PNode _root)
        {
            PNode povit = _root->left_;
            _root->left_ = povit->right_;
            povit->right_ = _root;

            _root->height_ = get_max_height(_root->left_, _root->right_) + 1;
            povit->height_ = get_max_height(povit->left_, povit->right_) + 1;

            return povit;
        }
        PNode rr_rotate(PNode _root)
        {
            PNode povit = _root->right_;
            _root->right_ = povit->left_;
            povit->left_ = _root;

            _root->height_ = get_max_height(_root->left_, _root->right_) + 1;
            povit->height_ = get_max_height(povit->left_, povit->right_) + 1;

            return povit;
        }
        PNode lr_rotate(PNode _root)
        {
            _root->left_ = rr_rotate(_root->left_);
            return ll_rotate(_root);
        }
        PNode rl_rotate(PNode _root)
        {
            _root->right_ = ll_rotate(_root->right_);
            return rr_rotate(_root);
        }

        void swap_node(PNode _a, PNode _b)
        {
            std::swap(_a->key_, _b->key_);
        }
    private:
        bool insert_node(PNode _node)
        {
            if (root_ == NULL)
            {
                root_ = _node;
                return true;
            }

            int balance_1 = 0;
            int balance_2 = 0;
            PNode now_addr = root_;
            PNode old_addr = nullptr;
            PNode new_addr = nullptr;
            std::stack<PNode> cache;

            while (true)
            {
                cache.push(now_addr);
                if (_node->key_ < now_addr->key_)
                {
                    if (now_addr->left_ == NULL)
                    {
                        now_addr->left_ = _node;
                        break;
                    }
                    else
                    {
                        now_addr = now_addr->left_;
                    }
                }
                else if (_node->key_ > now_addr->key_)
                {
                    if (now_addr->right_ == NULL)
                    {
                        now_addr->right_ = _node;
                        break;
                    }
                    else
                    {
                        now_addr = now_addr->right_;
                    }
                }
                else
                {
                    return false;
                }
            }

            while (cache.empty() == false)
            {
                now_addr = cache.top();
                if (now_addr == nullptr)
                    return false;
                cache.pop();

                if (now_addr->left_ == old_addr && new_addr != nullptr)
                    now_addr->left_ = new_addr;
                else if (now_addr->right_ == old_addr && new_addr != nullptr)
                    now_addr->right_ = new_addr;

                old_addr = now_addr;
                new_addr = NULL;

                now_addr->height_ = get_max_height(now_addr->left_, now_addr->right_) + 1;
                balance_1 = get_balance(now_addr);

                if (balance_1 > 1)
                {
                    balance_2 = get_balance(now_addr->left_);
                    if (balance_2 > 0)
                        new_addr = ll_rotate(now_addr);
                    else if (balance_2 < 0)
                        new_addr = lr_rotate(now_addr);
                }
                else if (balance_1 < -1)
                {
                    balance_2 = get_balance(now_addr->right_);
                    if (balance_2 < 0)
                        new_addr = rr_rotate(now_addr);
                    else if (balance_2 > 0)
                        new_addr = rl_rotate(now_addr);
                }
            }

            if (root_ == old_addr && new_addr != nullptr)
                root_ = new_addr;

            return true;
        }
        bool erase_node(KType _key)
        {
            std::stack<PNode> cache;
            PNode now_addr = root_;

            while (now_addr)
            {
                while (now_addr)
                {
                    if (_key < now_addr->key_)
                    {
                        if (now_addr->left_ != nullptr)
                        {
                            cache.push(now_addr);
                            now_addr = now_addr->left_;
                        }
                        else
                            return false;
                    }
                    else if (_key > now_addr->key_)
                    {
                        if (now_addr->right_ != nullptr)
                        {
                            cache.push(now_addr);
                            now_addr = now_addr->right_;
                        }
                        else
                            return false;
                    }
                    else
                        break;
                }

                if (now_addr == nullptr)
                    return false;

                if (now_addr->left_ != nullptr && now_addr->right_ != nullptr)
                {
                    PNode temp = now_addr->right_;
                    while (temp->left_ != nullptr)
                        temp = temp->left_;

                    swap_node(now_addr, temp);
                    cache.push(now_addr);
                    now_addr = now_addr->right_;
                }
                else
                {
                    PNode last = cache.top();
                    if (now_addr->right_ != nullptr && now_addr == last->left_)
                    {
                        last->left_ = now_addr->right_;
                    }

                    delete now_addr;
                    now_addr = nullptr;
                }
            }


            int balance_1 = 0;
            int balance_2 = 0;
            PNode old_addr = nullptr;
            PNode new_addr = nullptr;

            while (cache.empty() == false)
            {
                now_addr = cache.top();
                if (now_addr == nullptr)
                    return false;
                cache.pop();

                if (now_addr->left_ == old_addr && new_addr != nullptr)
                    now_addr->left_ = new_addr;
                else if (now_addr->right_ == old_addr && new_addr != nullptr)
                    now_addr->right_ = new_addr;

                old_addr = now_addr;
                new_addr = NULL;

                now_addr->height_ = get_max_height(now_addr->left_, now_addr->right_) + 1;
                balance_1 = get_balance(now_addr);

                if (balance_1 > 1)
                {
                    balance_2 = get_balance(now_addr->left_);
                    if (balance_2 >= 0)
                        new_addr = ll_rotate(now_addr);
                    else if (balance_2 < 0)
                        new_addr = lr_rotate(now_addr);
                }
                else if (balance_1 < -1)
                {
                    balance_2 = get_balance(now_addr->right_);
                    if (balance_2 <= 0)
                        new_addr = rr_rotate(now_addr);
                    else if (balance_2 > 0)
                        new_addr = rl_rotate(now_addr);
                }
            }

            return true;
        }
        bool find_node(const KType& _key, VType*& _value)
        {
            if (root_ == NULL)
            {
                return false;
            }

            PNode now_addr = root_;

            while (true)
            {
                if (_key < now_addr->key_)
                {
                    if (now_addr->left_ == NULL)
                        return false;
                    else
                        now_addr = now_addr->left_;
                }
                else if (_key > now_addr->key_)
                {
                    if (now_addr->right_ == NULL)
                        return false;
                    else
                        now_addr = now_addr->right_;
                }
                else
                {
                    _value = &(now_addr->value_);
                    return true;
                }
            }

            return false;
        }
        void destroy_tree()
        {
            PNode now_node = nullptr;
            std::queue<PNode> cache;

            while (cache.empty() == false)
            {
                now_node = cache.front();
                cache.pop();

                if (now_node->left_ != nullptr)
                    cache.push(now_node->left_);
                if (now_node->right_ != nullptr)
                    cache.push(now_node->right_);

                delete now_node;
            }

            root_ = nullptr;
        }
    public:
        Tree()
        {
            root_ = nullptr;
        }
        ~Tree()
        {
            destroy_tree();
        }
    public:
        bool Insert(KType _key, VType _value)
        {
            return insert_node(new Node<KType, VType>(_key, _value));
        }
        bool Erase(KType _key)
        {
            return erase_node(_key);
        }
        bool TryFind(const KType& _key, VType& _value)
        {
            VType* value = nullptr;
            if (false == find_node(_key, value))
            {
                return false;
            }
            _value = *value;
            return true;
        }
        void Clear()
        {
            destroy_tree();
        }
    public:
        VType& operator[](const KType& _key)
        {
            VType* value = nullptr;
            if (false == find_node(_key, value))
            {
                throw "The key was not found";
            }
            return *value;
        }
    };
}

#include <string>

int main(int _argc, char* argv[])
{
    xAVL::Tree<int,std::string> tree;

    for (int i = 31; i >= 0; i--)
    {
        tree.Insert(i,std::to_string(i));
    }

    tree.Erase(27);

    std::string value = tree[10];

    return 0;
}