#include "Tree.h"
#include "Node.h"
#include <stack>

void CTree::cDelete(CTree* c_tree)
{
	if (c_tree->c_root != NULL) cHelpDelete(c_tree->c_root);
	c_tree->c_root = NULL;
}

void CTree::cHelpDelete(CNode* c_current)
{
	if (c_current->cGetParent() != NULL) delete c_current->cGetParent();
	if(c_current->cGetChildren().empty()) delete c_current;
	else
	{
		for (int i = 0; i < c_current->cGetChildren().size(); i++)
		{
			cHelpDelete(c_current->cGetChildren()[i]);
			
		}
	}
}

CTree::CTree()
{
}

CTree::CTree(CNode * c_r)
{
	c_root = c_r;
}

CTree::CTree(CNode * c_r, int i_lastIn)
{
	c_root = c_r;
	i_lastIndex = i_lastIn;
}

CTree::CTree(int i_e)
{
	c_root = nullptr;
	i_error = i_e;
}


CTree::~CTree()
{
	cDelete(this);
}

CNode * CTree::cGetRoot()
{
	return c_root;
}

int CTree::cGetError()
{
	return i_error;
}


int CTree::cGetLastIndex()
{
	return i_lastIndex;
}

void CTree::cSetRoot(CNode * c_newRoot)
{
	c_root = c_newRoot;
}

void CTree::cSetError(int i_newError)
{
	i_error = i_newError;
}

void CTree::cSetLastIndex(int i_newIndex)
{
	i_lastIndex = i_newIndex;
}

map<string, int> CTree::cCount()
{
	map<string, int> m_products;
	return cHelpCount(c_root, m_products, 1);
}

map<string, int> CTree::cHelpCount(CNode* c_current, map<string, int> &m_products, int i_mult)
{
	map<string, int>::iterator it = m_products.find(c_current->cGetName());
	if (it != m_products.end())
	{
		it->second = it->second + c_current->cGetQuant()*i_mult;
	}
	else m_products.insert(pair<string, int>(c_current->cGetName(), c_current->cGetQuant()*i_mult));

	for (int i = 0; i < c_current->cGetChildren().size(); i++)
	{
		cHelpCount(c_current->cGetChildren()[i], m_products, i_mult*c_current->cGetQuant());
	}

	return m_products;
}

void CTree::cEditTree(CNode* c_new, int i_index)
{
	CNode* c_parent = cFind(c_root, i_index);
	c_parent->cGetChildren().push_back(c_new);
	c_new->cSetParent(c_parent);
	i_lastIndex++;
}

CNode* CTree::cFind(CNode* c_current, int i_index)
{
	if (c_current->cGetIndex() == i_index)
	{
		return c_current;

	}
	else
	{
		for (int i = 0; i < c_current->cGetChildren().size(); i++)
		{
			if (cFind(c_current->cGetChildren()[i], i_index) != NULL) return cFind(c_current->cGetChildren()[i], i_index);
			cFind(c_current->cGetChildren()[i], i_index);
		}
	}
}


string CTree::cFixString(string s_input)
{
	bool c_opened = false;
	string s_fixed;
	for (int i = 0; i < s_input.length(); i++)
	{
		if (s_input[i] == '"')
		{
			if (c_opened) c_opened = false;
			else c_opened = true;
		}

		if (!(!c_opened && isspace(s_input[i])))
		{
			s_fixed += s_input[i];
		}
	} //for (int i = 0; i < s_input.length; i++)
	return s_fixed;
}

CTree* CTree::cLoad(string s_input)
{
	s_input = cFixString(s_input);
	int i_index = 0;
	int i = 0;
	int i_lvl = 0;
	int i_currLvl = 0;
	int i_state = 1;
	bool b_error = false;
	string s_name;
	int i_quantity;
	stack<CNode*> p_stack;
	CNode* c_root = NULL;
	CNode* c_parent = NULL;
	CTree* c_t;
	while (i < s_input.length() && !b_error)
	{
		string s_name1;
		char c_sign = s_input[i];
		int i_num = 0;
		i++;
		switch (i_state)
		{
		case 1:
			if (c_sign == '[') i_state = 2;
			else b_error = true;
			break;
		case 2:
			if (c_sign == '"') i_state = 3;
			else b_error = true;
			break;
		case 3:
			while (s_input[i - 1] != '"' && i < s_input.length() && !b_error)
			{
				if (isalpha(s_input[i - 1]) || isspace(s_input[i - 1]))
				{
					s_name1 += s_input[i - 1];
					i++;
				} //if (isalpha(s_input[i]))
				else b_error = true;
			} //while (s_input[i] != '"' || i < s_input.length || !b_error)
			if (s_input[i - 1] != '"') b_error = true;
			//i++;
			if (!b_error)
			{
				i_state = 4;
				s_name = s_name1;
			}
			break;
		case 4:
			if (c_sign == ',') i_state = 5;
			else b_error = true;
			break;
		case 5:
			while (s_input[i - 1] != ',' && i < s_input.length() && !b_error)
			{
				if (isdigit(s_input[i - 1]))
				{
					i_num = i_num * 10 + s_input[i - 1] - '0';
					i++;
				}
				else b_error = true;
			} //while (s_input[i] != '"' || i < s_input.length || !b_error)
			if (s_input[i - 1] != ',') b_error = true;
			//i++;
			if (!b_error)
			{
				i_state = 6;
				i_quantity = i_num;
				c_parent = new CNode(s_name, i_quantity, i_index);
				i_index++;
				if (c_root == NULL) c_root = c_parent;
				if (!p_stack.empty()) 
				{
					p_stack.top()->cGetChildren().push_back(c_parent);
					c_parent->cSetParent(p_stack.top());
				}
			}
			break;
		case 6:
			if (c_sign == '(')
			{
				i_state = 7;
				i_lvl++;
			}
			else b_error = true;
			break;
		case 7:
			if (c_sign == ')')
			{
				i_lvl--;
				i_state = 8;
			}
			else if (c_sign == '[')
			{
				p_stack.push(c_parent);
				i_state = 2;
				i_currLvl = i_lvl - 1;
			}
			else b_error = true;
			break;
		case 8:
			if (c_sign = ']')
			{
				if (i_lvl != 0) i_state = 9;
				if (i_currLvl == i_lvl)
				{
					if (!p_stack.empty()) p_stack.pop();
				}
			}
			else b_error = true;
			break;
		case 9:
			if (c_sign == ',') i_state = 1;
			else if (c_sign == ')')
			{
				i_lvl--;
				i_state = 8;
			}
			else b_error = true;
			break;
		} //switch (i_state)
	}//while (i < s_input.length && b_error = false)
	if (b_error) return c_t = new CTree(i - 1);
	else return c_t = new CTree(c_root, i_index - 1);
}