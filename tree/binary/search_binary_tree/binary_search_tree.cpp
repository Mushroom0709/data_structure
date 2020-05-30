#include <string>

#include "bin_search_tree.h"


//       建立的二叉查找树模型
//
//                1
//           /         \
//          /           \
//         /             \
//        /               \
//       -3                2
//      /                   \
//     /                     \
//    /                       \
//  -52                        10
//     \                     /    \
//      \                   /      \
//      -34                5       128
//         \                       /   
//         -4                     36   


int main()
{
    xBinSearchTree<int, std::string> bst_tree;

    bst_tree.Add(1, "1");
    bst_tree.Add(2, "2");
    bst_tree.Add(10, "10");
    bst_tree.Add(5, "5");
    bst_tree.Add(128, "128");
    bst_tree.Add(36, "36");
    bst_tree.Add(-3, "-3");
    bst_tree.Add(-52, "-52");
    bst_tree.Add(-34, "-34");
    bst_tree.Add(-4, "-4");

    xBinSearchTree<int, std::string> test_tree(bst_tree);

    std::string value = "";
    test_tree.Find(-34, value);

    return 0;
}
