#pragma once
#include <map>
#include <string>
using namespace std;

class CNode;

class CTree
{
	//friend CNode;
public:
	CTree();
	CTree(CNode* c_r);
	CTree(CNode* c_r, int i_lastIn);
	CTree(int i_e);
	~CTree();

	map<string, int> cCount();
	void cDelete(CTree* c_tree);
	static CTree* cLoad(string s_input);
	void cEditTree(CNode* c_new, int i_index);
	static CNode* cFind(CNode* c_current, int i_index);


	CNode* cGetRoot();
	int cGetError();
	int cGetLastIndex();

	void cSetRoot(CNode* c_newRoot);
	void cSetError(int i_newError);
	void cSetLastIndex(int i_newIndex);

		


private:
	CNode* c_root = NULL;
	int i_error = 0;
	int i_lastIndex;

	void cHelpDelete(CNode* c_current);
	map<string, int> cHelpCount(CNode* c_current, map<string, int> &m_products, int i_mult);
	static string cFixString(string s_input);

};

