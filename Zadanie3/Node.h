#pragma once
using namespace std;
#include <string>
#include <map>
#include <vector>

class CTree;

class CNode
{
	//friend CTree;
public:
	CNode();
	~CNode();
	CNode(string s_n, int i_qua, int i_in);

	std::string cGetName();
	int cGetQuant();
	vector<CNode*>& cGetChildren();
	int cGetIndex();
	CNode* cGetParent();

	void cSetParent(CNode* p_newParent);
	void cSetName(std::string s_newName);
	void cSetQuant(int i_newQuan);
	void cSetChildren(vector <CNode*> p_newChildren);
	void cSetIndex(int i_newIndex);
	




private:
	std::string s_name;
	int i_quantity;
	vector <CNode*> p_children;
	int i_index;
	CNode* p_parent;

};

