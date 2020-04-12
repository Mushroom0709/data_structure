#include <stdio.h>
#include <malloc.h>
#include <conio.h>

#include <stack>

//                          建立的二叉树模型
//
//                                 1
//                    /                       \
//                   /                         \
//                  /                           \
//                 /                             \
//                2                               3
//           /         \                     /         \
//          /           \                   /           \
//         /             \                 /             \
//        4               5               6               7
//      /   \           /    \          /    \          /    \
//     /     \         /      \        /      \        /      \
//    8       9       10      11      12      13      14      15
//   /  \    /  \    /  \    /  \    /  \    /  \    /  \    /  \
//  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31

typedef struct _BIN_TREE_NODE
{
    int value;
    struct _BIN_TREE_NODE* left;
    struct _BIN_TREE_NODE* right;
}BIN_TREE_NODE, BIN_TREE_ROOT,*PBIN_TREE_NODE,*PBIN_TREE_ROOT;

// 创建节点
PBIN_TREE_NODE alloc_bin_tree_node(int _value, PBIN_TREE_NODE _left = NULL, PBIN_TREE_NODE _right = NULL)
{
    PBIN_TREE_NODE node = (PBIN_TREE_NODE)calloc(1, sizeof(BIN_TREE_NODE));
    if (NULL == node)
        return NULL;

    node->value = _value;
    node->left = _left;
    node->right = _right;

    return node;
}

// 释放节点
void free_bin_tree_node(PBIN_TREE_NODE* _node)
{
    free(*_node);
    *_node = NULL;
}

// 建立完全二叉树
PBIN_TREE_ROOT build_complete_bin_tree(int _start,int _num)
{
    PBIN_TREE_ROOT root = NULL;
    PBIN_TREE_NODE* nodes = (PBIN_TREE_ROOT*)calloc(_num, sizeof(PBIN_TREE_NODE));
    if (NULL == nodes)
        return NULL;

    for (size_t i = 0; i < _num; i++)
    {
        nodes[i] = alloc_bin_tree_node(_start + i);
    }

    for (size_t i = 0; i < _num; i++)
    {
        int left_index = (i + 1) * 2 - 1;
        int right_index = (i + 1) * 2 + 1 -1;

        if (left_index < _num)
        {
            nodes[i]->left = nodes[left_index];
        }

        if (right_index < _num)
        {
            nodes[i]->right = nodes[right_index];
        }
    }

    root = nodes[0];
    free(nodes);

    return root;
}

// 释放二叉树(基于非递归的先序遍历实现)
void destroy_bin_tree(PBIN_TREE_ROOT* _root)
{
    PBIN_TREE_NODE now_node = NULL;
    PBIN_TREE_NODE last_node = NULL;
    std::stack<PBIN_TREE_NODE> node_cache;

    node_cache.push(*_root);

    while (node_cache.empty() == false)
    {
        now_node = node_cache.top();
        node_cache.pop();

        if (now_node->right != NULL)
        {
            node_cache.push(now_node->right);
        }

        if (now_node->left != NULL)
        {
            node_cache.push(now_node->left);
        }

        free_bin_tree_node(&now_node);
    }

    *_root = NULL;
}


// 递归实现 先序遍历
void recursive_preorder_traversal_bin_tree(PBIN_TREE_NODE _node)
{
    if (_node != NULL)
    {
        printf("%d ", _node->value);

        recursive_preorder_traversal_bin_tree(_node->left);
        recursive_preorder_traversal_bin_tree(_node->right);
    }
}

// 递归实现 中序遍历
void recursive_inorder_traversal_bin_tree(PBIN_TREE_NODE _node)
{
    if (_node != NULL)
    {
        recursive_inorder_traversal_bin_tree(_node->left);

        printf("%d ", _node->value);

        recursive_inorder_traversal_bin_tree(_node->right);
    }
}

// 递归实现 后序遍历
void recursive_postorder_traversal_bin_tree(PBIN_TREE_NODE _node)
{
    if (_node != NULL)
    {
        recursive_postorder_traversal_bin_tree(_node->left);
        recursive_postorder_traversal_bin_tree(_node->right);

        printf("%d ", _node->value);
    }
}


void print_traversal_bin_tree(void (*_fun)(PBIN_TREE_NODE), PBIN_TREE_ROOT _root, const char* _title)
{
    printf("%s:", _title);
    _fun(_root);
    printf("\n");
}

int main(int argc, char* argv[])
{
    PBIN_TREE_ROOT root = build_complete_bin_tree(1, 31);

    print_traversal_bin_tree(recursive_preorder_traversal_bin_tree, root, "递归-前序遍历");
    print_traversal_bin_tree(recursive_inorder_traversal_bin_tree, root, "递归-中序遍历");
    print_traversal_bin_tree(recursive_postorder_traversal_bin_tree, root, "递归-后序遍历");

    destroy_bin_tree(&root);

    return 0;
}
