#include <stdio.h>
#include <assert.h>
#include <malloc.h>


#define XBOOL int
#define XTRUE 1
#define XFALSE 0


typedef struct _AVL_NODE
{
    int key;
    int value; //懒得用void* 实现类似模板了，一堆回调要传 T_T.用int示例一下就行了
    int height;
    struct _AVL_NODE* left;
    struct _AVL_NODE* right;
}AVL_NODE, * PAVL_NODE;

int x_max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}

int x_min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}

PAVL_NODE avl_make_node(int _key,int _value)
{
    PAVL_NODE node = (PAVL_NODE)calloc(1, sizeof(AVL_NODE));
    if (node != NULL)
    {
        node->key = _key;
        node->value = _value;
        node->height = 1;
    }

    return node;
}

int avl_get_height(PAVL_NODE _root)
{
    if (_root == NULL)
        return 0;
    return _root->height;
}
int avl_get_balance(PAVL_NODE _root)
{
    if (_root == NULL)
        return 0;
    return avl_get_height(_root->left) - avl_get_height(_root->right);
}

PAVL_NODE avl_ll_rotate(PAVL_NODE _root)
{
    PAVL_NODE pivot = _root->left;
    _root->left = pivot->right;
    pivot->right = _root;

    _root->height = x_max(avl_get_height(_root->left), avl_get_height(_root->right)) + 1;
    pivot->height = x_max(avl_get_height(pivot->left), avl_get_height(pivot->right)) + 1;

    return pivot;
}

PAVL_NODE avl_rr_rotate(PAVL_NODE _root)
{
    PAVL_NODE pivot = _root->right;
    _root->right = pivot->left;
    pivot->left = _root;

    _root->height = x_max(avl_get_height(_root->left), avl_get_height(_root->right)) + 1;
    pivot->height = x_max(avl_get_height(pivot->left), avl_get_height(pivot->right)) + 1;

    return pivot;
}

PAVL_NODE avl_lr_rotate(PAVL_NODE _root)
{
    _root->left = avl_rr_rotate(_root->left);
    return avl_ll_rotate(_root);
}

PAVL_NODE avl_rl_rotate(PAVL_NODE _root)
{
    _root->right = avl_ll_rotate(_root->right);
    return avl_rr_rotate(_root);
}

PAVL_NODE avl_insert_node(PAVL_NODE _root, PAVL_NODE _nood)
{
    if (_nood == NULL)
        return _root;

    if (_root == NULL)
        return _nood;

    assert(_nood->key != _root->key);

    if (_nood->key < _root->key)
        _root->left = avl_insert_node(_root->left, _nood);
    else if (_nood->key > _root->key)
        _root->right = avl_insert_node(_root->right, _nood);
    //else
    //    return _root;

    _root->height = x_max(avl_get_height(_root->left), avl_get_height(_root->right)) + 1;
    int root_balance = avl_get_balance(_root);

    if (root_balance > 1)
    {
        int left_balance = avl_get_balance(_root->left);
        if (left_balance > 0)
            return avl_ll_rotate(_root);
        else if (left_balance < 0)
            return avl_lr_rotate(_root);
    }
    else if (root_balance < -1)
    {
        int right_balance = avl_get_balance(_root->right);
        if (right_balance > 0)
            return avl_rl_rotate(_root);
        else if (right_balance < 0)
            return avl_rr_rotate(_root);
    }

    return _root;
}

PAVL_NODE avl_insert(PAVL_NODE _root, int _key,int _value)
{
    return avl_insert_node(_root, avl_make_node(_key,_value));
}

PAVL_NODE avl_erase_node(PAVL_NODE _root, int _key)
{
    if (_root == NULL)
        return _root;

    if (_key < _root->key)
        _root->left = avl_erase_node(_root->left, _key);
    else if (_key > _root->key)
        _root->right = avl_erase_node(_root->right, _key);
    else
    {
        if (_root->left != NULL && _root->right != NULL)
        {
            PAVL_NODE node = _root->right;

            while (node->left != NULL)
                node = node->left;

            //swap

            _root->key = node->key;

            _root->right = avl_erase_node(_root->right, node->key);
        }
        else
        {
            PAVL_NODE node = _root;
            _root = _root->left != NULL ? _root->left : _root->right;
            free(node);

            if (_root == NULL)
                return NULL;
        }
    }


    _root->height = x_max(avl_get_height(_root->left), avl_get_height(_root->right)) + 1;
    int root_balance = avl_get_balance(_root);

    if (root_balance > 1)
    {
        int left_balance = avl_get_balance(_root->left);
        if (left_balance >= 0)
            return avl_ll_rotate(_root);
        else if (left_balance < 0)
            return avl_lr_rotate(_root);
    }
    else if (root_balance < -1)
    {
        int right_balance = avl_get_balance(_root->right);
        if (right_balance > 0)
            return avl_rl_rotate(_root);
        else if (right_balance <= 0)
            return avl_rr_rotate(_root);
    }

    return _root;
}

PAVL_NODE avl_erase(PAVL_NODE _root, int _key)
{
    return avl_erase_node(_root, _key);
}

XBOOL avl_find(PAVL_NODE _root, int _key, int* _value)
{
    if (_root == NULL)
        return XFALSE;

    if (_key < _root->key)
        return avl_find(_root->left, _key, _value);
    else if(_key > _root->key)
        return avl_find(_root->right, _key, _value);
    else
    {
        *_value = _root->value;
        return XTRUE;
    }

    return XFALSE;
}

void avl_destroy(PAVL_NODE _root)
{
    if (_root == NULL)
        return;

    avl_destroy(_root->left);
    avl_destroy(_root->right);

    free(_root);
}

int main(int _argc, char* argv[])
{
    PAVL_NODE root = NULL;

    for (int i = 0; i < 32; i++)
    {
        root = avl_insert(root, i, i * 10);
    }

    root = avl_erase(root, 27);

    int find_res = -1;

    avl_find(root, 12, &find_res);

    avl_destroy(root);

    root = NULL;
    return 0;
}