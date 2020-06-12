/*
# 参考&感谢
    1.  Linux kernel
        +   linux\tools\lib\rbtree.c

    2.  SL_World
        +   https://blog.csdn.net/SL_World/article/details/84584503?utm_medium=distribute.pc_relevant.none-task-blog-baidujs-2

    3.  那谁的技术博客
        +   http://www.cppblog.com/converse/archive/2008/11/10/66530.html (主要是抄袭)

####### @xMushroom
*/

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

namespace xRBTree
{
    typedef enum _NodeColor
    {
        NC_None = 0xFF,
        NC_Black = 0x00,
        NC_Red = 0x01
    }NodeColor;

    template<typename KType, typename VType>
    class Tree;

    template<typename KType, typename VType>
	class Node
	{
        friend Tree<KType, VType>;
    private:
        NodeColor color_;
    private:
        class Node* parent_;
        class Node* left_;
        class Node* right_;
    private:
        KType key_;
        VType value_;
    public:
        Node()
        {
            color_ = NC_None;
            parent_ = nullptr;
            left_ = nullptr;
            right_ = nullptr;
        }
        Node(KType _key, VType _value, NodeColor _type = NC_Red)
        {
            color_ = _type;
            key_ = _key;
            value_ = _value;
            parent_ = nullptr;
            left_ = nullptr;
            right_ = nullptr;
        }
        ~Node()
        {

        }
    public:
        Node* Parent()
        {
            return parent_;
        }
        Node* Left()
        {
            return left_;
        }
        Node* Right()
        {
            return right_;
        }

        bool TryParent(Node*& _p)
        {
            _p = parent_;
            if (_p == nullptr)
                return false;
            return true;
        }

        Node* Grandparent()
        {
            if (parent_ == nullptr)
                return parent_;
            return parent_->parent_;
        }
        bool TryGrandparent(Node*& _p)
        {
            _p = Grandparent();
            if (_p == nullptr)
                return false;
            return true;
        }

        NodeColor LeftColor()
        {
            if (left_ == nullptr)
                return NodeColor::NC_Black;
            return left_->color_;
        }
        NodeColor RightColor()
        {
            if (right_ == nullptr)
                return NodeColor::NC_Black;
            return right_->color_;
        }

        bool IsLeaf()
        {
            return left_ == nullptr && right_ == nullptr;
        }
	};

    template<typename KType, typename VType>
    class Tree
    {
        using NodeType = Node<KType, VType>;
        using PNodeType = NodeType*;
    private:
        PNodeType tree_;
    private:
        /*
        左旋:
        |rt  |旋转点
        |l   |r左子节点
        |r   |r右子节点
        |rl  |c左子结点
        |rr  |c右子节点

            rt                               r
          /    \                           /   \
         l      r            ===>        rt     rr
               / \                      /  \
             rl   rr                   l    rl
        */
        void left_rotate(PNodeType _rt)
        {
            PNodeType r = _rt->right_;
            _rt->right_ = r->left_;
            if (r->left_ != nullptr)
                r->left_->parent_ = _rt;
            r->left_ = _rt;

            r->parent_ = _rt->parent_;

            if (_rt->parent_ == nullptr)
            {
                tree_ = r;
            }
            else
            {
                if (_rt == _rt->parent_->left_)
                    _rt->parent_->left_ = r;
                else
                    _rt->parent_->right_ = r;
            }
            _rt->parent_ = r;
        }


        /*
        右旋:
        |rt  |旋转点
        |l   |r左子节点     
        |r   |r右子节点
        |ll  |l左子结点
        |lr  |l右子节点

               rt                               l
             /    \                           /   \
            l      r            ===>        ll     rt
           / \                                    /  \
         ll   lr                                 lr   l
        */
        void right_rotate(PNodeType _rt)
        {
            PNodeType l = _rt->left_;
            _rt->left_ = l->right_;
            if (l->right_ != nullptr)
                l->right_->parent_ = _rt;
            l->right_ = _rt;

            l->parent_ = _rt->parent_;

            if (_rt->parent_ == nullptr)
            {
                tree_ = l;
            }
            else
            {
                if (_rt == _rt->parent_->left_)
                    _rt->parent_->left_ = l;
                else
                    _rt->parent_->right_ = l;
            }
            _rt->parent_ = l;
        }
    private:
        PNodeType find_node(int _key)
        {
            PNodeType node = tree_;

            while (node != NULL)
            {
                if (_key < node->key_)
                {
                    node = node->left_;
                }
                else if (_key > node->key_)
                {
                    node = node->right_;
                }
                else
                {
                    return node;
                }
            }

            return nullptr;
        }
        NodeColor get_color(PNodeType _node)
        {
            if (_node == nullptr)
                return NodeColor::NC_Black;
            return _node->color_;
        }

        void insert_fix(PNodeType _node)
        {
            PNodeType uncle = nullptr;
            PNodeType parent = nullptr;
            PNodeType gparent = nullptr;

            while (_node->TryParent(parent) == true && parent->color_ == NC_Red)
            {
                _node->TryGrandparent(gparent);

                if (parent == gparent->left_) // 当前节点的父节点是祖父节点的左孩子
                {
                    uncle = gparent->right_; // 当前节点的叔叔点是祖父节点的右孩子
                    if (uncle != nullptr && uncle->color_ == NC_Red)
                    {
                        /*
                        # 插入可能 1.1
                        
                        ## 情景
                            当前节点(n)的父节点(p)为红色、叔叔节点(u)为红色
                        
                        ## 处理
                            则将父节点和叔叔节点染黑，祖父节点染红，并在下一次过程跳跃2级以祖父节点为起点
                        -----------------------------
                              G            g
                             / \          / \
                            p   u  -->   P   U
                           /            /
                          n            n
                        -----------------------------
                        */

                        uncle->color_ = NC_Black;
                        parent->color_ = NC_Black;
                        gparent->color_ = NC_Red;
                        _node = gparent;
                    }
                    else
                    {
                        if (parent->right_ == _node)
                        {
                            /*
                            # 插入可能 1.2

                            ## 情景
                                1.  当前节点(n)是父节点(p)的右孩子
                                2.  当前节点(n)是红色，父节点(p)为红色、叔叔节点(u)为黑色(叔、父节点为红色，祖父节点必然为黑色)

                            ## 处理
                                通过左旋转节点p使情况变成 1.3
                            -----------------------------
                                  G             G
                                 / \           / \
                                p   U  -->    n   U
                                 \           /
                                  n         p
                            -----------------------------
                            */


                            left_rotate(parent);
                            std::swap(parent, _node);
                        }

                        /*
                        # 插入可能 1.3

                        ## 情景
                            1.  当前节点(n)是父节点(p)的左孩子
                            2.  当前节点(n)是红色，父节点(p)为红色、叔叔节点(u)为黑色(父节点为红色，祖父节点必然为黑色)

                        ## 处理
                            将父节点染黑祖父节点染红，随后右旋祖父节点，这样在以旋转后P->n、P->g 路径上的黑色节点数量并未发生改变
                        -----------------------------
                                 G           P
                                / \         / \
                               p   U  -->  n   g
                              /                 \
                             n                   U
                        -----------------------------
                        */

                        parent->color_ = NC_Black;
                        gparent->color_ = NC_Red;
                        right_rotate(gparent);
                    }
                }
                else//if (parent == gparent->right_) 当前节点的父节点是祖父节点的右孩子
                {
                    // 镜像 当前节点的父节点是祖父节点的左孩子 的操作
                    uncle = gparent->left_;
                    if (get_color(uncle) == NC_Red)
                    {
                        uncle->color_ = NC_Black;
                        parent->color_ = NC_Black;
                        gparent->color_ = NC_Red;
                        _node = gparent;
                    }
                    else
                    {
                        if (parent->left_ == _node)
                        {
                            right_rotate(parent);
                            std::swap(parent, _node);
                        }
                        
                        parent->color_ = NC_Black;
                        gparent->color_ = NC_Red;
                        left_rotate(gparent);
                    }
                }
            }

            tree_->color_ = NC_Black;
        }
        bool insert_node(PNodeType _node)
        {
            if (tree_ == NULL)
            {
                _node->color_ = NodeColor::NC_Black;
                tree_ = _node;
                return true;
            }

            PNodeType root = tree_;

            while (true)
            {
                if (_node->key_ > root->key_)
                {
                    if (root->right_ != NULL)
                    {
                        root = root->right_;
                    }
                    else if (root->right_ == NULL)
                    {
                        _node->parent_ = root;
                        root->right_ = _node;
                        break;
                    }
                }
                else if (_node->key_ < root->key_)
                {
                    if (root->left_ != NULL)
                    {
                        root = root->left_;
                    }
                    else if (root->left_ == NULL)
                    {
                        _node->parent_ = root;
                        root->left_ = _node;
                        break;
                    }
                }
                else
                {
                    return false;
                }
            }

            insert_fix(_node);
            return true;
        }

        void erase_fix(PNodeType _node, PNodeType _parent)
        {
            PNodeType bother = nullptr;

            while (_node != tree_ && get_color(_node) == NC_Black)
            {
                if (_parent->left_ == _node) // 当前节点是父节点的左孩子
                {
                    bother = _parent->right_;

                    if (get_color(bother) == NC_Red)
                    {
                        /*
                        # 删除可能 1.1

                        ## 情景
                            当前节点(n)为黑色，兄弟节点(s)为红色(兄弟节点为红色则父节点一定是黑色，冲突)

                        ## 处理
                            1.  将兄弟节点染黑，父节点染红，然后左旋父节点，此时新父节点S的左右孩子均为红色。
                            2.  因为旋转后，原兄弟节点的左孩子成(Sl)为旋转后父节点(p)的右孩子，此刻二者都为红色，所以
                                继续处理处理Sl，即情况1.2
                        -----------------------------
                             P               S
                            / \             / \
                           N   s    -->    p   SR   
                              / \         / \
                             SL  SR      N   SL
                        -----------------------------
                        */

                        bother->color_ = NC_Black;
                        _parent->color_ = NC_Red;
                        left_rotate(_parent);
                        bother = _parent->right_;
                    }

                    if (get_color(bother->left_) == NC_Black &&
                        get_color(bother->right_) == NC_Black)
                    {
                        /*
                        # 删除可能 1.2.1

                        ## 情景
                            1.  当前节点(N)的父节点颜色不确定，如果是从情况1.1而来，则为红色
                            2.  当前节点(N)的兄弟节点(S)的孩子节点(SL,SR)均为黑色

                        ## 处理
                            1.  将兄弟节点(S)染为红色
                        -----------------------------
                            (p)           (p)
                            / \           / \
                           N   S    -->  N   s
                              / \           / \
                             SL  SR        SL  SR
                        -----------------------------
                        */

                        bother->color_ = NC_Red;
                        _node = _parent;
                        _parent = _node->parent_;
                    }
                    else
                    {
                        if (get_color(bother->right_) == NC_Black) 
                        {
                            /*
                            # 删除可能 1.2.2.1

                            ## 情景
                                1.  当前节点(N)的父节点颜色不确定，如果是从情况1.1而来，则为红色
                                2.  当前节点(N)的兄弟节点(s)的左孩子(Sl)推断为红色，SR为黑色

                            ## 处理
                                1.  将S1染成红色
                            -----------------------------
                                (p)           (p)
                                / \           / \
                               N   S    -->  N   S
                                  / \           / \
                                 Sl SR         SL  SR
                            -----------------------------
                            */

                            bother->left_->color_ = NC_Black;

                            /*
                            # 删除可能 1.2.2.2

                            ## 情景
                                1.  当前节点(N)的父节点颜色不确定，如果是从情况1.1而来，则为红色
                                2.  当前节点(N)的兄弟节点(s)的孩子(SL、SR)颜色为黑色

                            ## 处理
                                1.  将S染成红色，并右旋兄弟节点(S)
                                2.  将旋转后SL作为新的兄弟节点
                            -----------------------------
                                (p)           (p)
                                / \           / \
                               N   S    -->  N   SL
                                  / \             \
                                 SL SR             s
                                                    \
                                                     SR
                            -----------------------------
                            */

                            bother->color_ = NC_Red;
                            right_rotate(bother);
                            bother = _parent->right_;
                        }

                        /*
                        # 删除可能 1.3

                        ## 情景
                            继承 1.2.2.2

                        ## 处理
                            1.  将sL设置为父节点颜色
                            2.  将父节点染黑，
                            3.  左旋sL节点
                            4.  如果sR节点存在则一定是红色，染成黑色
                        -----------------------------
                           (p)            (sL)
                           / \            /  \
                          N   sL   -->   P    s
                               \        /      \
                                s      N       (sR)
                                 \
                                 (sr)
                        -----------------------------
                        */

                        bother->color_ = _parent->color_;
                        _parent->color_ = NC_Black;
                        if (bother->right_ != nullptr)
                            bother->right_->color_ = NC_Black;

                        left_rotate(_parent);

                        _node = tree_; //此刻平衡
                        //break;
                    }
                }
                else // 当前节点是父节点的右孩子
                {
                    //镜像 当前节点是父节点的左孩子 的操作

                    bother = _parent->left_;

                    if (get_color(bother) == NC_Red)
                    {
                        bother->color_ = NC_Black;
                        _parent->color_ = NC_Red;
                        right_rotate(_parent);
                        bother = _parent->left_;
                    }

                    if (get_color(bother->left_) == NC_Black &&
                        get_color(bother->right_) == NC_Black)
                    {
                        bother->color_ = NC_Red;
                        _node = _parent;
                        _parent = _node->parent_;
                    }
                    else
                    {
                        if (get_color(bother->left_) == NC_Black)
                        {
                            bother->right_->color_ = NC_Black;

                            bother->color_ = NC_Red;
                            left_rotate(bother);
                            bother = _parent->left_;
                        }

                        bother->color_ = _parent->color_;
                        _parent->color_ = NC_Black;
                        if (bother->left_ != nullptr)
                            bother->left_->color_ = NC_Black;

                        right_rotate(_parent);

                        _node = tree_;
                        //break;
                    }
                }
            }

            if (_node != nullptr)
                _node->color_ = NC_Black;
        }
        void erase_node(PNodeType _node)
        {
            PNodeType child = nullptr;
            PNodeType parent = nullptr;
            PNodeType left = nullptr;
            PNodeType old = nullptr;
            NodeColor color = NC_None;

            old = _node;

            if (_node->left_ != nullptr && _node->right_ != nullptr) //当前节点左右孩子都不为空
            {
                //则寻找可以替换的大于当前节点的最小节点进行替换
                _node = _node->right_;
                while (_node->left_ != nullptr)
                    _node = _node->left_;

                child = _node->right_; //替换节点的左孩子一定为null
                parent = _node->parent_;
                color = _node->color_;

                //将替换节点的孩子的父节点设置为替换节点的父节点，切断替换节点的父子关系
                if (child != nullptr)
                    child->parent_ = parent;

                if (parent != nullptr)
                {
                    if (parent->left_ == _node)
                        parent->left_ = child;
                    else
                        parent->right_ = child;
                }
                else
                    tree_ = child; //如果删除节点的父节点为null，则表明删除节点是根节点

                if (_node->parent_ == old) // 如果替换节点的父节点是删除节点 
                    parent = _node; // 则缓存父节点为删除节点(执行完交换之后，交换节点就是删除节点的父节点)

                //交换节点
                _node->parent_ = old->parent_;
                _node->color_ = old->color_;
                _node->right_ = old->right_;
                _node->left_ = old->left_;

                //
                if (old->parent_ != nullptr)
                {
                    if (old->parent_->left_ == old)
                        old->parent_->left_ = _node;
                    else
                        old->parent_->right_ = _node;
                }
                else
                    tree_ = _node;

                old->left_->parent_ = _node;
                if(old->right_ != nullptr)
                    old->right_->parent_ = _node;
            }
            else //如果左右孩子有其一为空，则直接删除该节点，不需要替换
            {
                if (_node->left_ != nullptr)
                    child = _node->left_;
                else if(_node->right_ != nullptr)
                    child = _node->right_;

                parent = _node->parent_;
                color = _node->color_;

                if (child != nullptr)
                    child->parent_ = parent;

                if (parent != nullptr)
                {
                    if (parent->left_ == _node)
                        parent->left_ = child;
                    else
                        parent->right_ = child;
                }
                else
                    tree_ = child;
            }

            delete old;

            if (color == NC_Black) //如果替换节点的颜色是黑色，则在删除后因为该节点上的历史
                                   //路径的黑色节点发生数量变化，则从该节点的子节点，或该节点
                                   //是叶子节点，则从父节点开始进行平衡修正
            {
                erase_fix(child, parent);
            }
        }
    private:
        void destroy()
        {
            PNodeType now_node = nullptr;
            std::queue<PNodeType> cache;
            cache.push(tree_);
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

            tree_ = nullptr;
        }
    public:
        bool insert(int _key, int _value)
        {
            return insert_node(new NodeType(_key, _value));
        }
        bool erase(int _key)
        {
            PNodeType node = find_node(_key);
            if (node == nullptr)
                return false;
            erase_node(node);
            return true;
        }
        void Print()
        {
            if (tree_ == NULL)
                return;

            PNodeType n = NULL;
            std::stack<PNodeType> cache;

            n = tree_;

            while (cache.empty() == false || n != NULL)
            {
                if (n != NULL)
                {
                    cache.push(n);
                    n = n->left_;
                }
                else
                {
                    n = cache.top();
                    cache.pop();
                    printf("[%d,%d][%s]\n", n->key_, n->value_, n->color_ == NC_Red ? "红" : "黑");
                    n = n->right_;
                }
            }
            printf("\n");
        }
    public:
        Tree()
        {
            tree_ = NULL;
        }
        ~Tree()
        {
            destroy();
        }
    };
}

int main()
{
    xRBTree::Tree<int,int> tree;

    for (int i = 0; i < 32; i++)
    {
        tree.insert(i, i * 10);
    }

    tree.Print();

    tree.erase(8);

    tree.Print();

    return 0;
}