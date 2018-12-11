#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <map>
using namespace std;
map<unsigned short, char> Base64Table {
	{0,'A'},
	{1,'B'},
	{2,'C'},
	{3,'D'},
	{4,'E'},
	{5,'F'},
	{6,'G'},
	{7,'H'},
	{8,'I'},
	{9,'J'},
	{10,'K'},
	{11,'L'},
	{12,'M'},
	{13,'N'},
	{14,'O'},
	{15,'P'},
	{16,'Q'},
	{17,'R'},
	{18,'S'},
	{19,'T'},
	{20,'U'},
	{21,'V'},
	{22,'W'},
	{23,'X'},
	{24,'Y'},
	{25,'Z'},
	{26,'a'},
	{27,'b'},
	{28,'c'},
	{29,'d'},
	{30,'e'},
	{31,'f'},
	{32,'g'},
	{33,'h'},
	{34,'i'},
	{35,'j'},
	{36,'k'},
	{37,'l'},
	{38,'m'},
	{39,'n'},
	{40,'o'},
	{41,'p'},
	{42,'q'},
	{43,'r'},
	{44,'s'},
	{45,'t'},
	{46,'u'},
	{47,'v'},
	{48,'w'},
	{49,'x'},
	{50,'y'},
	{51,'z'},
	{52,'0'},
	{53,'1'},
	{54,'2'},
	{55,'3'},
	{56,'4'},
	{57,'5'},
	{58,'6'},
	{59,'7'},
	{60,'8'},
	{61,'9'},
	{62,'+'},
	{63,'/'},
	
};

map<char, unsigned short> RevTb {
	{'A',0},
	{'B',1},
	{'C',2},
	{'D',3},
	{'E',4},
	{'F',5},
	{'G',6},
	{'H',7},
	{'I',8},
	{'J',9},
	{'K',10},
	{'L',11},
	{'M',12},
	{'N',13},
	{'O',14},
	{'P',15},
	{'Q',16},
	{'R',17},
	{'S',18},
	{'T',19},
	{'U',20},
	{'V',21},
	{'W',22},
	{'X',23},
	{'Y',24},
	{'Z',25},
	{'a',26},
	{'b',27},
	{'c',28},
	{'d',29},
	{'e',30},
	{'f',31},
	{'g',32},
	{'h',33},
	{'i',34},
	{'j',35},
	{'k',36},
	{'l',37},
	{'m',38},
	{'n',39},
	{'o',40},
	{'p',41},
	{'q',42},
	{'r',43},
	{'s',44},
	{'t',45},
	{'u',46},
	{'v',47},
	{'w',48},
	{'x',49},
	{'y',50},
	{'z',51},
	{'0',52},
	{'1',53},
	{'2',54},
	{'3',55},
	{'4',56},
	{'5',57},
	{'6',58},
	{'7',59},
	{'8',60},
	{'9',61},
	{'+',62},
	{'/',63},
	
};



class Base64
{
	public:
		vector<char> vch;
		Base64()
		{}
		Base64(const vector<char> & vc)
		{
			vch = vc;
		}
		Base64(const string& str)
		{		
			assert(!str.empty());
			for(unsigned int i = 0; i < str.size(); i++)
			{
				vch.push_back(str.at(i));
			}
		}
		string encode()
		{
			unsigned int q,r,nsize;
			string strret = "";
			nsize = vch.size();
			q = nsize / 3;
			r = nsize % 3;
			unsigned short tmp;			
			for(unsigned int i = 0; i < q; i++)//3*i,3*i+1,3*i+2
			{	
				auto it = vch.begin() + 3*i;			
				tmp = ((*(it)) >> 2) & 0x3f;
				strret.push_back(Base64Table[tmp]);
				tmp = ((*(it) & 0x03) << 4) | ((*(it + 1) >> 4) & 0x0f);
				strret.push_back(Base64Table[tmp]);
				tmp = ((*(it + 1) & 0x0f) << 2) | ((*(it + 2) >> 6) & 0x03);
				strret.push_back(Base64Table[tmp]);
				tmp = ((*(it + 2))) & 0x3f;
				strret.push_back(Base64Table[tmp]);
			}
			auto it = vch.begin() + 3*q;
			if(r == 1)
			{
				tmp = (*(it) >> 2) & 0x3f;
				strret.push_back(Base64Table[tmp]);
				tmp = (*(it) & 0x03) << 4;
				strret.push_back(Base64Table[tmp]);
				strret.push_back('=');
				strret.push_back('=');
			}
			if(r == 2)
			{
				tmp = ((*(it)) >> 2) & 0x3f;
				strret.push_back(Base64Table[tmp]);
				tmp = ((*(it) & 0x03) << 4) | ((*(it + 1) >> 4) & 0x0f);
				strret.push_back(Base64Table[tmp]);
				tmp = (*(it + 1) & 0x0f) << 2;
				strret.push_back(Base64Table[tmp]);
				strret.push_back('=');
			}
			return strret;
		}

		string decode()
		{
			unsigned int q,nsize;
			string strret = "";
			nsize = vch.size();
			q = nsize / 4;
			//r = nsize % 3;
			unsigned short tmp;			
			for(unsigned int i = 0; i < q; i++)//4*i,4*i+1,4*i+2,4*i+3
			{	
				auto it = vch.begin() + 4*i;
				if(*(it + 2) != '=' && *(it + 3) != '=')
				{					
					tmp = ((RevTb[*(it)] & 0x3f) << 2) | ((RevTb[*(it + 1)]>>4) & 0x03);
					strret.push_back((char)tmp);
					tmp = ((RevTb[*(it + 1)] & 0x0f) << 4) | ((RevTb[*(it + 2)] >> 2) & 0x0f);
					strret.push_back((char)tmp);
					tmp = ((RevTb[*(it + 2)] & 0x03) << 6) | (RevTb[*(it + 3)] & 0x03f);
					strret.push_back((char)tmp);
				}
				else if(*(it + 2) != '=')
				{
					tmp = ((RevTb[*(it)] & 0x3f) << 2) | ((RevTb[*(it + 1)]>>4) & 0x03);
					strret.push_back((char)tmp);
					tmp = ((RevTb[*(it + 1)] & 0x0f) << 4) | ((RevTb[*(it + 2)] >> 2) & 0x0f);
					strret.push_back((char)tmp);
				}
				else
				{
					tmp = ((RevTb[*(it)] & 0x3f) << 2) | ((RevTb[*(it + 1)] >> 4) & 0x03);
					strret.push_back((char)tmp);
				}
				//tmp = (*(it + 2)) & 0x3f;
				//strret.push_back(Base64Table[tmp]);
			}
			return strret;
		}
};

int main()
{
	//Base64 basetest("SLFw");
	Base64 basetest("U0xGdw==");
	//cout<<basetest.encode();
	cout<<basetest.decode();
	return 0;
}


