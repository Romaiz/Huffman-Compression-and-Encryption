#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <iterator>
#include <assert.h>

using namespace std;

struct node
{
	char ch;
	int frequency;
	node* left;
	node* right;

	node(int f = 0, char d = ' ', node* l = nullptr, node* r = nullptr) :frequency{ f }, ch{ d }, left{ l }, right{ r }
	{

	}

	
};


template<typename t>
struct sortHtree
{
	bool operator()(node* const& a, node* const& b)
	{
		return a->frequency > b->frequency;
	}
};

class huffman
{
	priority_queue<node*,vector<node*>, sortHtree<node*>> htree;
	node* root;
	string txt;
	string etxt;
	string dtxt;
	string buffer;
	string huffcode;
	map<char, string> obj;
public:
	huffman(node* r = nullptr) :root{ r }
	{

	}

	bool isEmpty()
	{
		return htree.empty();
	}

	node* getRoot()
	{
		return root;
	}

	void deleteTree(node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}

	//void bitcode(string k)
	//{
	//	string ret = txtfile(k);

	//	/*for (size_t i = 0; i < ret.size(); i++)
	//	{
	//		cout << ret[i];
	//	}*/

	//	cout << endl;
	//	cout << "File size: " << ret.size() << " bytes" << endl;
	//	/*cout << "Bitstream before compression: ";

	//	for (size_t i = 0; i < ret.size(); i++) 
	//	{
	//		cout << bitset<8>(ret[i]);
	//	}*/

	//	cout << endl << endl;
	//}

	void addbits()
	{
		int add = 8 - (buffer.size() % 8);
		for (int i = 0; i < add; i++)
		{
			buffer.append("0");
		}
		string addedbits = convertInttoByte(add);
		buffer.append(addedbits);
	}

	void removebits()
	{
		huffcode.erase(huffcode.size() - 8, 8);
		string temp = "";
		for (int i = 0; i < 8; i++)
		{
			temp = huffcode[huffcode.size() - 1] + temp;
			huffcode.pop_back();
		}
		int excess = stoi(temp, nullptr, 2);
		for (int i = 0; i < excess; i++)
		{
			huffcode.pop_back();
		}
	}

	long convert(int num)
	{
		long bin = 0;
		int rem, i = 1;

		while (num != 0)
		{
			rem = num % 2;
			num /= 2;
			bin += rem * i;
			i *= 10;
		}
		if (bin < 0)
		{
			return -bin;
		}
		return bin;
	}

	string convertInttoByte(int a)
	{
		int temp;
		(a < 0) ? temp = -(a - 127) : temp = a;
		string bits;
		while (temp > 0)
		{
			bits.append(to_string(temp % 2));
			temp /= 2;
		}
		for (int i = bits.length(); i < 8; i++)
		{
			bits.append(std::to_string(0));
		}
		temp = bits.length() - 1;
		for (int i = 0; i < bits.length() / 2; i++)
		{
			char temp2 = bits[i];
			bits[i] = bits[temp - i];
			bits[temp - i] = temp2;
		}
		return bits;
	}

	int convertBytetoInt(string bits)
	{
		int m = 1;
		int res = 0;
		for (int i = bits.length() - 1; i >= 0; i--)
		{
			res += (bits[i] - '0') * m;
			m *= 2;
		}
		if (bits[0] == '1')
		{
			res = -(res - 127);
		}
		return res;
	}

	void encryptedTxtFile(string k)
	{
		fstream encrypted_txtfile;
		encrypted_txtfile.open("blegh.txt", ios::out);
		
			if (!encrypted_txtfile)
			{
				cout << "File creation failed" << endl;
			}
			else
			{
				cout << "Compressed File created" << endl;
				encrypted_txtfile << k << endl;
				encrypted_txtfile << "blegh-meh" << endl;
				map<char, string> ::iterator it;
				for (it = obj.begin(); it != obj.end(); ++it)
				{
					encrypted_txtfile << it->first << it->second << endl;
				}
				encrypted_txtfile.close();
			}
		
		//bitcode("blegh.txt");
	}


	string txtfile(string k)
	{
		string name = k;
		fstream testFile;
		string temp;
		testFile.open(name, ios::in);
		if (!testFile.is_open())
		{
			cout << "Please make sure that file " << name << " exists" << endl;
			exit(0);
		}

		if (testFile.is_open())
		{
			while (!testFile.eof())
			{
				getline(testFile, temp);
				txt = txt + temp + "\n";
			}

			testFile.close();
		}
		cout << txt << endl;
		cout << "Size in bytes: " << txt.size() << " bytes" << endl;
		return txt;
	}

	void PQI(string data)
	{
		map<char, int> PM;
		for (int i = 0; i < data.length(); i++)
		{
			PM[data[i]]++;
		}

		map<char, int>::iterator it;
		for (it = PM.begin(); it != PM.end(); ++it)
		{
			node* temp = new node(it->second, it->first);
			htree.push(temp);
		}
	}

	
	void compress(string data)
	{
		PQI(data);
		while (htree.size() > 1)
		{
			node* temp = htree.top(); 
			htree.pop();
			node* temp2 = htree.top();
			htree.pop();
			root = new node(temp->frequency + temp2->frequency);
			root->left = temp;
			root->right = temp2;
			htree.push(root);
		}
		root = htree.top();
		/*cout << "Root frequency: " << root->frequency << endl;
		cout << "Root char: " << root->ch << endl;
		cout << "It works" << endl;*/

		node* temp = getRoot();
		string r = "";
		huffmantreebitcode(temp, r, obj);

		//cout << "Huffman Code: ";
		huffcode = "";
		buffer = "";

		for (char c : data)
		{
			//cout << it->first << " : " << it->second << endl;
		    //cout<< it->second;
			buffer += obj[c];

		}
		cout << buffer << endl;
		//huffcode = buffer;
		addbits();
		encrypted_file(buffer);
	}

	void huffmantreebitcode(node* root, string k, map<char , string> &obj)
	{
		if (root == nullptr)
		{
			return;
		}

		if (root->left == nullptr && root->right == nullptr)
		{
			obj[root->ch] = (!k.empty()) ? k : "1";
		}
		huffmantreebitcode(root->left, k + '0', obj);
		huffmantreebitcode(root->right, k + '1', obj);

	}

	void encrypted_file(string k)
	{
		string temp = "";
		for (int i = 0; i < k.length(); i+=8)
		{
			int r = convertBytetoInt(k.substr(i,8));
			char blegh = r;
			temp.push_back(blegh);
		}
		encryptedTxtFile(temp);
	}


	void encryption(string k)
	{
		string data = txtfile(k);
		//bitcode(k);
		compress(data);
		//cout << buffer << endl;
		txt = "";
		buffer = "";
		huffcode = "";
		deleteTree(root);
	}

	void retrieveHuffcode(string x)
	{
		huffcode = huffcode + x;
	}

	void regeneration(node* root, string huff, char c)
	{
		node* temp = root;
		for (int i = 0; i < huff.size(); i++)
		{
			if (huff[i] == '1')
			{
				if (temp->right == nullptr)
				{
					temp->right = new node;
				}
				temp = temp->right;
			}
			if (huff[i] == '0')
			{
				if (temp->left == nullptr)
				{
					temp->left = new node;
				}
				temp = temp->left;
			}
		}
		temp->ch = c;
	}

	void startDecompression(string k)
	{
		string name = k;
		fstream testFile;
		string temp;
		testFile.open(name, ios::in | ios::binary);
		if (!testFile.is_open())
		{
			cout << "Please make sure that file " << name << " exists" << endl;
			exit(0);
		}

		if (testFile.is_open())
		{
			root = new node;
			getline(testFile, temp);
			temp.pop_back();
			while (temp != "blegh-meh")
			{
				txt = txt + temp + "\n";
				getline(testFile, temp);
				temp.erase(temp.size() - 1);
			}
			cout << txt << endl;
			//cout << "Compressed file size in bytes: " << txt.size() << " bytes" << endl;
			while (!testFile.eof())
			{
				char c;
				string huff;
				getline(testFile, temp);
				if (temp.size() == 0)
				{
					break;
				}
				temp.erase(temp.size() - 1);
				if (temp.size()==0)
				{
					c = '\n';
					getline(testFile, temp);
					temp.erase(temp.size() - 1);
					huff = temp;
					if (huff.size() == 0)
					{
						break;
					}
				}
				else
				{
					c = temp[0];
					huff = temp.substr(1, temp.size() - 1);
				}
				regeneration(root, huff, c);
			}

			testFile.close();
		}
		
		decrypt();
	}

	string chartoBinary(char c)
	{
		int temp = c;
		if (temp < 0)
		{
			temp += 128;
		}
		string temp2;
		while (temp / 2 > 0)
		{
			temp2 = to_string(temp % 2) + temp2;
			temp /= 2;
		}
		temp2 = to_string(temp % 2) + temp2;
		for (int i = temp2.size(); i < 8; i++)
		{
			temp2 = "0" + temp2;
		}
		return temp2;
	}

	void decrypt()
	{
		for (int i = 0; i < txt.length(); i++)
		{
			//string hci = chartoBinary(txt[i]);
			string hci = convertInttoByte(txt[i]);
			retrieveHuffcode(hci);
		}
		removebits();
		cout << huffcode << endl;
	}

	void decompression(string k)
	{
		startDecompression(k);
		node* temp = root;
		for (int i = 0; i < huffcode.size(); i++)
		{
			if (temp == nullptr)
			{
				break;
			}
			if (temp->left == nullptr && temp->right == nullptr)
			{
				dtxt += temp->ch;
				temp = root;
			}
			if (huffcode[i] == '1')
			{
				temp = temp->right;
			}
			if (huffcode[i] == '0')
			{
				temp = temp->left;
			}
		}

		cout << "Decompressed text:" << endl;
		cout << dtxt << endl;
	}
};


int main()
{
	huffman obj;
	obj.encryption("Testing2.txt");
	cout << endl;
	obj.decompression("blegh.txt");
	//obj.encryption("Testing3.txt");

}