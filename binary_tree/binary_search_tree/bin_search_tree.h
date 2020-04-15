#ifndef _BIN_SEARCH_TREE_H_
#define _BIN_SEARCH_TREE_H_


//1.基于C++模板实现了简单的二叉查找树,想起来捎带复习下模板的简单使用
//2.在泛型上，诸如比较，拷贝，没有做过多处理，仅仅示意二叉查找原理
//3.未实现删除节点，因为要写很多T_T，我懒。(原理上，删除的核心部分是:不能直接删除的，需要将同方向的叶子节点与被删除的节点进行替换，然后删掉该叶子节点)


#include <stack>

#include "bin_search_tree_element.h"

template<class KeyType, class ValueType>
class xBinSearchTree
{
private:
	xSearchElement<KeyType, ValueType>* element_;
public:
	xSearchElement<KeyType, ValueType>& Root()
	{
		return element_;
	}
public:
	xBinSearchTree()
	{
		element_ = nullptr;
	}
	xBinSearchTree(const xBinSearchTree<KeyType, ValueType>& _tree)
	{
		element_ = new xSearchElement<KeyType, ValueType>();

		element_->copy(_tree.element_);
	}
	~xBinSearchTree()
	{
		Destroy();
	}
public:
	bool Add(KeyType _key, ValueType _value)
	{
		if (element_ == nullptr)
		{
			element_ = new xSearchElement<KeyType, ValueType>(_key, _value);
			return true;
		}
		else
		{
			xSearchElement<KeyType, ValueType>* now_node = element_;
			while (true)
			{
				BSTNODE_COMPARE_RES cmp_res = now_node->data_.Compare(_key);
				if (cmp_res == BSTNODE_GREATER)
				{
					if (now_node->left_ != nullptr)
						now_node = now_node->left_;
					else
					{
						now_node->left_ = new xSearchElement<KeyType, ValueType>(_key, _value);
						return true;
					}
				}
				else if(cmp_res == BSTNODE_LESS)
				{
					if (now_node->right_ != nullptr)
						now_node = now_node->right_;
					else
					{
						now_node->right_ = new xSearchElement<KeyType, ValueType>(_key, _value);
						return true;
					}
				}
				else
				{
					return false;
				}
			}
		}
	}
	bool Find(KeyType _key, ValueType& _value)
	{
		xSearchElement<KeyType, ValueType>* now_node = element_;

		while (now_node != nullptr)
		{
			BSTNODE_COMPARE_RES cmp_res = now_node->data_.Compare(_key);
			if (cmp_res == BSTNODE_GREATER)
			{
				now_node = now_node->left_;
			}
			else if (cmp_res == BSTNODE_LESS)
			{
				now_node = now_node->right_;
			}
			else
			{
				_value = now_node->data_.Value();
				return true;
			}
		}

		return false;
	}
	bool Change(KeyType _key, ValueType& _value)
	{
		xSearchElement<KeyType, ValueType>* now_node = element_;

		while (now_node != nullptr)
		{
			BSTNODE_COMPARE_RES cmp_res = now_node->data_.Compare(_key);
			if (cmp_res == BSTNODE_GREATER)
			{
				now_node = now_node->left_;
			}
			else if (cmp_res == BSTNODE_LESS)
			{
				now_node = now_node->right_;
			}
			else
			{
				now_node->data_.Value() = _value;
				return true;
			}
		}

		return false;
	}
	void Destroy()
	{
		if (element_ != nullptr)
		{
			element_->destroy();
			element_ = nullptr;
		}
	}
};

#endif //_BIN_SEARCH_TREE_H_