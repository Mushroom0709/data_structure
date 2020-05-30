#ifndef _BIN_SEARCH_TREE_NODE_H_
#define _BIN_SEARCH_TREE_NODE_H_

#define BSTNODE_LESS	-1	//小于
#define BSTNODE_GREATER	1	//等于
#define BSTNODE_EQUAL	0	//大于

typedef int BSTNODE_COMPARE_RES; //返回比较结果

template<class KeyType,class ValueType>
class xBinSearchTreeNode
{
private:
	KeyType key_;
	ValueType value_;
public:
	KeyType& Key()
	{
		return key_;
	}

	ValueType& Value()
	{
		return value_;
	}

public:
	xBinSearchTreeNode()
	{
		//
	}
	xBinSearchTreeNode(KeyType _key, ValueType _value)
	{
		key_ = _key;
		value_ = _value;
	}
	xBinSearchTreeNode(const xBinSearchTreeNode<KeyType, ValueType>& _value)
	{
		key_ = _value.key_;
		value_ = _value.value_;
	}
	~xBinSearchTreeNode()
	{
		//
	}
public:
	BSTNODE_COMPARE_RES Compare(const KeyType _key)
	{
		if (this->key_ < _key)
			return BSTNODE_LESS;
		else if (this->key_ == _key)
			return BSTNODE_EQUAL;
		else
			return BSTNODE_GREATER;
	}
};

#endif //_BIN_SEARCH_TREE_NODE_H_