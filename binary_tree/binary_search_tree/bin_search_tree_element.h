#ifndef _BIN_SEARCH_TREE_ELEMENT_H_
#define _BIN_SEARCH_TREE_ELEMENT_H_

#include <stack>

#include "bin_search_tree_node.h"

template<class KeyType, class ValueType>
class xBinSearchTree;

template<class KeyType, class ValueType>
class xSearchElement
{
public:
	friend xBinSearchTree<KeyType, ValueType>;
private:
	xBinSearchTreeNode<KeyType, ValueType> data_;
	xSearchElement<KeyType, ValueType>* left_;
	xSearchElement<KeyType, ValueType>* right_;
private:
	xSearchElement()
	{
		left_ = nullptr;
		right_ = nullptr;
	}
	xSearchElement(KeyType _key, ValueType _value) :
		data_(_key, _value)
	{
		left_ = nullptr;
		right_ = nullptr;
	}
	xSearchElement(const xBinSearchTreeNode<KeyType, ValueType>& _data) :
		data_(_data)
	{
		left_ = nullptr;
		right_ = nullptr;
	}
	~xSearchElement()
	{

	}
private:
	void copy(const xSearchElement<KeyType, ValueType>* _tree)
	{
		xSearchElement<KeyType, ValueType>* dst_element = nullptr;
		xSearchElement<KeyType, ValueType>* src_element = nullptr;

		std::stack<xSearchElement<KeyType, ValueType>*> src_cache;
		std::stack<xSearchElement<KeyType, ValueType>*> dst_cache;

		src_cache.push((xSearchElement<KeyType, ValueType>*)_tree);
		dst_cache.push(this);

		while (src_cache.empty() == false)
		{
			src_element = src_cache.top();
			src_cache.pop();

			dst_element = dst_cache.top();
			dst_cache.pop();

			dst_element->data_ = src_element->data_;

			if (src_element->right_ != NULL)
			{
				dst_element->right_ = new xSearchElement<KeyType, ValueType>(src_element->right_->data_);

				src_cache.push(src_element->right_);
				dst_cache.push(dst_element->right_);
			}

			if (src_element->left_ != NULL)
			{
				dst_element->left_ = new xSearchElement<KeyType, ValueType>(src_element->left_->data_);

				src_cache.push(src_element->left_);
				dst_cache.push(dst_element->left_);
			}
		}
	}
	void destroy()
	{
		xSearchElement<KeyType, ValueType>* now_element = this;

		std::stack<xSearchElement<KeyType, ValueType>*> element_cache;
		element_cache.push(this);

		while (element_cache.empty() == false)
		{
			now_element = element_cache.top();
			element_cache.pop();

			if (now_element->right_ != NULL)
				element_cache.push(now_element->right_);

			if (now_element->left_ != NULL)
				element_cache.push(now_element->left_);

			delete now_element;
		}
	}
};

#endif //_BIN_SEARCH_TREE_ELEMENT_H_
