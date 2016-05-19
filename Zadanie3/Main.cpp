#include <string>
#include <map>
#include <iostream>
#include "Node.h"
#include "Tree.h"
#include <stack>
#include <queue>
using namespace std;

class Node;
class Tree;




vector<CNode*> CMod(CNode* c_curr)
{
	vector<CNode*> p_stack;
	vector<CNode*> p_help;
	bool b_children = true;
	for (int i = 0; i < c_curr->cGetChildren().size(); i++)
	{
		if (c_curr->cGetChildren()[i]->cGetChildren().empty()) b_children = false;
	}
	if (b_children) p_stack.push_back(c_curr);
	for (int i = 0; i < c_curr->cGetChildren().size(); i++)
	{
		if (!(c_curr->cGetChildren()[i]->cGetChildren().empty()))
		{
			 p_help = CMod(c_curr->cGetChildren()[i]);
			 for (int i = 0; i < p_help.size(); i++)
			 {
				 p_stack.push_back(p_help[i]);
			 }

		}
		else
		{
			p_stack.push_back(c_curr->cGetChildren()[i]);
		}
	}
	return p_stack;
}

void cPrintMod(CTree* c_tree)
{
	vector<CNode*> p_stack;
	if (!c_tree->cGetRoot()->cGetChildren().empty())
	{
		p_stack = CMod(c_tree->cGetRoot());
	}

	for (int i = 0; i < p_stack.size(); i++)
	{
		stack<CNode*> p_help;
		bool noParents = false;
		CNode* c_curr = p_stack[i];
		if (c_curr->cGetParent() == NULL) p_help.push(c_curr);
		while (!noParents)
		{
			if (c_curr->cGetParent() != NULL)
			{
				p_help.push(c_curr->cGetParent());
				c_curr = c_curr->cGetParent();
			}
			else
			{
				noParents = true;
			}
		}
		while (!p_help.empty())
		{
			cout << p_help.top()->cGetName() << "->";
			p_help.pop();
		}
		cout << "\n";
	}

}






void cPrint(map<string, int> m_products)
{
	cout << "\n Lista zsumowanych produktow: \n";
	for (map<string, int>::iterator it = m_products.begin(); it != m_products.end(); ++it)
	{
		cout << it->first << " " << it->second << '\n';
	}
}

void cPrintHelp(CNode* c_current)
{
	cout << c_current->cGetIndex() << ". " << c_current->cGetName() << "\n";
	{
		for (int i = 0; i < c_current->cGetChildren().size(); i++)
		{
			cPrintHelp(c_current->cGetChildren()[i]);
		}
	}
}

void cPrintTree(CTree* c_tree)
{
	if (c_tree != NULL && c_tree->cGetRoot() != NULL)
	{
		cout << "\n Lista wezlow: \n";
		cPrintHelp(c_tree->cGetRoot());
	}
	else cout << "\n Drzewo puste \n";
}



int cStringToInt(string s_string)
{
	int i_num = 0;
	for (int i = 0; i < s_string.length(); i++)
	{
		if(s_string[i] >= '0' && s_string[i] <= '9') i_num = i_num * 10 + (s_string[i] - '0');
		else return -1;
	}
	return i_num;
}


static void cInterface()
{
	bool b_end = false;
	bool b_isValid = false;
	bool b_newTree = false;
	int i_in;
	CTree* c_tree = NULL;
	CNode* c_new = NULL;
	string s_name;
	string s_num;
	int i_num = -1;
	while (!b_end)
	{
		while (!b_isValid && !b_end)
		{
			i_num = -1;
			string s_action;
			b_isValid = true;
			string s_tree;
			cout << "\n Co chcesz zrobic? \n 1. Podac cale drzewo \n 2. Dodac pojedynczy wezel \n 3. Zakonczyc \n";
			cin >> s_action;
			int i_act = cStringToInt(s_action);
			switch (i_act)
			{
			case 1:
				cout << "\n Podaj cale drzewo: ";
				cin >> s_tree;
				c_tree = CTree::cLoad(s_tree);
				if (c_tree->cGetRoot() == NULL)
				{
					cout << "\n Blad w znaku " << c_tree->cGetError() << "\n";
					delete c_tree;
					c_tree = NULL;
					b_isValid = false;
				}
				b_newTree = false;
				break;
			case 2:
				cout << "\n Podaj nazwe produktu: ";
				cin >> s_name;
				while (i_num == -1) {
					cout << "\n Podaj liczbe produktow tego rodzaju: ";
					cin >> s_num;
					i_num = cStringToInt(s_num);
					if (i_num == -1) cout << "\n To nie jest wlasciwa liczba \n";
				}
				c_new = new CNode(s_name, i_num, 0);
				c_tree = new CTree(c_new, 0);
				b_newTree = false;
				break;
			case 3:
				b_end = true;
				break;
			default:
				cout << "\n Bledne polecenie \n";
				b_isValid = false;
				break;
			}
		}

		b_isValid = false;

		while (!b_isValid && !b_end && !b_newTree)
		{
			i_num = -1;
			i_in = 0;
			string s_action;
			b_isValid = true;
			string s_in;
			cout << "\n Co chcesz zrobic? \n 1. Wydrukowac liste produktow \n 2. Dodac wezel do istniejacego drzewa \n 3. Usunac drzewo \n 4. Zakonczyc \n 5. Wypisac sciezki \n";
			cin >> s_action;
			int i_act = cStringToInt(s_action);
			switch (i_act)
			{
			case 1:
				cPrint(c_tree->cCount());
				break;
			case 2:
				cPrintTree(c_tree);
				i_in = c_tree->cGetLastIndex()+1;
				while (i_in > c_tree->cGetLastIndex())
				{
					cout << "\n Podaj numer wezla, do ktorego chcesz dopiac nowy wezel: ";
					cin >> s_in;
					i_in = cStringToInt(s_in);
					if (i_in == -1)
					{
						cout << "\n To nie jest wlasciwa liczba \n";
						i_in = c_tree->cGetLastIndex() + 1;
					}
					else if (i_in > c_tree->cGetLastIndex()) cout << "\n Nie ma wezla o podanym indeksie \n";
				}
				cout << "\n Podaj nazwe produktu: ";
				cin >> s_name;
				while (i_num == -1) {
					cout << "\n Podaj liczbe produktow tego rodzaju: ";
					cin >> s_num;
					i_num = cStringToInt(s_num);
					if (i_num == -1) cout << "\n To nie jest wlasciwa liczba \n";
				}
				c_new = new CNode(s_name, i_num, c_tree->cGetLastIndex()+1);
				c_tree->cEditTree(c_new, i_in);
				break;
			case 3:
				delete c_tree;
				c_tree = NULL;
				b_newTree = true;
				break;
			case 4:
				b_end = true;
				break;
			case 5:
				cPrintMod(c_tree);
				break;
			default:
				cout << "\n Bledne polecenie \n";
				b_isValid = false;
				break;
			}
		}
	}
	if (c_tree != NULL && c_tree->cGetRoot() != NULL)
	{
		delete c_tree;
	}
	
}



void main()
{	
	cInterface();

}