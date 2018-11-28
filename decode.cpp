#include <math.h>
#include <iostream>
#include <string>
#include<fstream>
using namespace std;
string invert_seq(string a)
{
  string opstr="";
	for (int i = str.length()-1; i >= 0; i--)
	{
		opstr += str[i];
	}
  return opstr;
}
int bin_to_dec(string str,int len)
{
	int output=0;
	for (int i = 0; i < len; i++)
	{
		if (str[i]=='1')
		output +=  pow(2, i);
	}
	return output;
}
void decode_mem_access(string a)
{
	string rn = a.substr(16, 4);
	string rd = a.substr(12, 4);
	string addr = a.substr(0, 12);
	int rnintex = bin_to_dec(rn, 4);
	int rdintex = bin_to_dec(rd, 4);
	int addrintex = bin_to_dec(addr, 12);
	if (a[20] == '1')
	{
		cout << "LDR  ";
	}
	else
	{
		cout << "STR  ";
	}
	cout << "R" << rdintex << ",[";
	cout << "R" << rnintex ;
	if (a[24] == '0'){
		cout << "]";
	}

	if (a[25] == '0')
	{
		cout << ",";
		if (a[23] == '0')
			cout << "-";
		cout << "#" << addrintex;
	}
	else if (addrintex!=0)
	{
		cout << ",R" << addrintex;
	}
	if (a[24] == '1')
		cout << "]";

}
void decode_operate(string a)
{
	string opcode = a.substr(21,4);
	string rn = a.substr(16,4);
	string rd = a.substr(12, 4);
	string op2 = a.substr(0,12);
	int rnintex = bin_to_dec(rn, 4);
	int rdintex = bin_to_dec(rd, 4);
	bool intexn = true;
	bool intexd = true;
	if (opcode == "0000")
		cout << "AND  ";
	if (opcode == "0010")
		cout << "ADD  ";
	if (opcode == "0101")
	{
		cout << "CMP  ";
		intexd = false;
	}
	if (opcode == "1011")
	{
		cout << "MOV  ";
		intexn = false;
	}
	if (opcode == "0011")
		cout << "ORR  ";
	if (intexd)
	cout << "R" << rdintex << ",";
	if (intexn)
	cout<<"R"<< rnintex << ",";
	if (a[25] == '1')
	{
		cout << "#" << bin_to_dec(op2, 12);
	}
	else
	{
		cout << "R" << bin_to_dec(op2, 12);
	}
	
}
void decode_mul(string a)
{
	cout << "MUL  ";
	string rd = a.substr(16, 4);
	string rm = a.substr(0, 4);
	string rs = a.substr(8, 4);
	int rmintex = bin_to_dec(rm, 4);
	int rdintex = bin_to_dec(rd, 4);
	int rsintex = bin_to_dec(rs, 4);
	cout << "R" << rdintex << ",";
	cout << "R" << rmintex << ",";
	cout << "R" << rsintex ;
}
void decode_mrs(string a){}
void decode_swi(string a){}
void decode_branche(string a){}
void classification(string line)
{
	string a= invert_seq(line);
	if (line.substr(4, 5) == "00010" && line.substr(10,6) == "001111" && line.substr(20,12) == "000000000000") {
		decode_mrs(a);
	}
	else if(line.substr(4,4) == "1111"){
		decode_swi(a);
	}
	else if (line.substr(4, 3) == "101") {
		decode_branch(a);
	}
	else if (line.substr(4, 7) == "0000000" && line.substr(24, 4) == "1001") {
		decode_mul(a);
	}
	else if (line.substr(4, 2) == "00") {
		decode_operate(a);
	}
	else if (line.substr(4, 2) == "01") {
		decode_mem_access(a);
	}
	else {
		cout << "Fails!" << endl;
	}
}
void openfiles()
{
  ifstream in("arm.txt");
	string str;
	while (!in.eof())
	{
		getline(in, str);
		classification(str);
		cout << endl;
	}
	in.close();
}
int main()
{
  openfiles();
  return 0;
}
