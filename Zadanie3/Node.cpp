#include "Node.h"
#include <string>;
#include <map>;


CNode::CNode()
{
}


CNode::~CNode()
{
}

CNode::CNode(std::string s_n, int i_qua, int i_in)
{
	s_name = s_n;
	i_quantity = i_qua;
	i_index = i_in;
}

std::string CNode::cGetName()
{
	return s_name;
}

int CNode::cGetQuant()
{
	return i_quantity;
}

vector<CNode*>& CNode::cGetChildren()
{
	return p_children;
}

int CNode::cGetIndex()
{
	return i_index;
}

CNode * CNode::cGetParent()
{
	return p_parent;
}

void CNode::cSetParent(CNode* p_newParent)
{
	p_parent = p_newParent;
}

void CNode::cSetName(std::string s_newName)
{
	s_name = s_newName;
}

void CNode::cSetQuant(int i_newQuan)
{
	i_quantity = i_newQuan;
}

void CNode::cSetChildren(vector<CNode*> p_newChildren)
{
	if (!p_children.empty()) 
	{
		for (int i = 0; i < p_children.size(); i++)
		{
			delete p_children[i];
		}
	}
	p_children = p_newChildren;
}

void CNode::cSetIndex(int i_newIndex)
{
	i_index = i_newIndex;
}
