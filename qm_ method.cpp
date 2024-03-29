/* 
	Ariyan Molazem
	This program uses Quine-McCluskey method to simplify boolean equations (up to 10 variables).
*/
#include <iostream>
#include <conio.h>
#include <cmath>
#include <sstream>
#include <cstring>
using namespace std;
/////////////////////////////////////////////////////////////////////     
void line();                                     // Appearance
/////////////////////////////////////////////////////////////////////
int num_v;                                       // Main Variables
int minterms[1024];
int count_m;

int dontcares[1024];
int count_d;

int all_m[1024];
int count_a;

string binary_form[1024];

string groups_1[11][252];
string groups_2[10][252];
string groups_3[9][252];
int index_g1[11], index_g2[10], index_g3[9];
bool flag_list2, flag_list3; 

int primary_m[1023];
int count_p;
int ess_m[1023];
int count_e;

string essential[1023];
int index_e;
/////////////////////////////////////////////////////////////////////
void get_inputs();                               // Main Functions
void show_func();                                // Print info of inputs.

string convert_to_binary(int number);
string convert_to_decimal(string number);
void make_binary_form();                         // Make binary form of minterms.

void make_groups_1();                            // 1st list
void make_groups_2();                            // 2nd list
void make_groups_3();                            // 3rd list
void check_groups_3();						     // Remove the repeated elements.

void find_primary1();                            // if 1 list is needed.
void find_primary2();                            // if 2 lists are needed.
void find_primary3();				             // if 3 lists are needed.

void find_essential1();                          // if 1 list is needed.
void find_essential2();                          // if 2 lists are needed.
void find_essential3();				             // if 3 lists are needed.
void check_essential();                          // Remove the repeated elements.

void print_final_answer();	                     // Print the final answer with chars.
/////////////////////////////////////////////////////////////////////
int main()
{ 
	int num_menu;
	bool flag;
	while(true)     
    {
		system("cls");
		get_inputs();
		system("cls");
		
		show_func();
		make_binary_form();
		make_groups_1();
		
		make_groups_2();
		if(!flag_list2)
		{
			find_primary1();
			find_essential1();
		}
		else
		{
			make_groups_3();
			if(!flag_list3)
			{
				find_primary2();
				find_essential2();
			}
			else
			{
				check_groups_3();
				find_primary3();
				find_essential3();
			} 
		}
		print_final_answer();
		
		line();
		cout << " Again(1)  Exit(0) \n";
		flag = true;
		while(flag)
		{
			flag = false;
			
			while(true)
			{
				cout << "\n Num: "; cin >> num_menu;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "  [Enter a number] \n";
				}
				else
					break;
			}
			
			line();
			switch(num_menu)
			{
				case 1: break;
				case 0: exit(1);
				default:
					flag = true;
					cout << "\n  [Enter the menu number]";
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////
void get_inputs()
{
	
	while(true)
	{
		while(true)                              // Getting number of variables.
		{
			cout << "\n Enter number of variables (1 to 10): ";    
			cin >> num_v;
			if(cin.fail())                       // Checking the validity of input.
			{
				cin.clear();
				cin.ignore();                        
				cout << " [Enter a number] \n";
			} else
				break;
		}
		
		if(num_v < 1 || num_v > 10)              // Check the range.
		{
			cout << " [Number should be in the range] \n";
			continue;
		}
		break;	
	}
	
	count_m = 0;
	count_a = 0;
	count_d = 0;
	int input;
	bool flag; 
	
	line();
	cout << "\n Enter Minterms [negative num to stop] \n\n";
	while(true)                                  // Getting minterms.
	{
		flag = false;
		while(true)                          
		{
			cout << " minterm: ";    
			cin >> input;
			if(cin.fail())                       // Checking the validity of input.
			{
				cin.clear();
				cin.ignore();
				cout << " [Enter a number] \n";
			} else
				break;
		}
		
		if(input < 0)                            // Stop point
		{
			if(count_m == 0)
			{
				cout << " [Enter at least 1 minterm] \n";
				continue;
			}
			break;
		}
		
		for(int i = 0; i < count_a; i++)         // Check if it's repeated
		{
			if(input == all_m[i])
			{
				cout << " [Minterm is already added] \n";
				flag = true;
			}
		}
		if(input >= pow(2, num_v))               // Check the range.
		{
			cout << " [Minterm should be less than " << pow(2, num_v) << "] \n";
			flag = true;
		}
		
		if(flag)
			continue;
		
		all_m[count_a] = input;
 	 	minterms[count_m] = input;
		count_m++;
		count_a++;
	}
	
	line();
	cout << "\n Enter Don't cares [negative num to stop] \n\n";
	while(true)	                                 // Get don't cares.
	{
		flag = false;
		while(true)                          
		{
			cout << " don't care: ";    
			cin >> input;
			if(cin.fail())                       // Checking the validity of input.
			{
				cin.clear();
				cin.ignore();
				cout << " [Enter a number] \n";
			} else
				break;
		}
		
		if(input < 0)                            // Stop point
			break;
		
		for(int i = 0; i < count_a; i++)         // Check if it's repeated.
		{
			if(input == all_m[i])
			{
				cout << " [This is already added] \n";
				flag = true;
			}
		}
		if(input >= pow(2, num_v))               // Check the range.
		{
			cout << " [Don't care should be less than " << pow(2, num_v) << "] \n";
			flag = true;
		}
		
		if(flag)
			continue;
		
		all_m[count_a] = input;
		dontcares[count_d] = input;
		count_d++;
		count_a++;
	}
}
/////////////////////////////////////////////////////////////////////
void show_func()
{
	cout << "\n Number of variables: " << num_v;
	
	cout << "\n\n Minterms: ";
	for(int i = 0; i < count_m; i++)
		cout << minterms[i] << " ";
	
	cout << "\n\n Don't cares: ";
	for(int i = 0; i < count_d; i++)
		cout << dontcares[i] << " ";
}
/////////////////////////////////////////////////////////////////////
string convert_to_binary(int number)
{	
	long long sum = 0;
	int index = 0;
	int rem;
	
	while(number != 0)                           
	{
		rem = number % 2;
		number = number / 2;
		sum += rem * pow(10, index);
		index++;
	}
	
	stringstream a;                              
	a << sum;
	string num;
	a >> num;
	return num;
}
/////////////////////////////////////////////////////////////////////
string convert_to_decimal(string number)
{
	int num;
	stringstream a;
	a << number;
	a >> num;
	int index, sum, rem;
	index = sum = 0;
	while(num > 0)
	{
		rem = num % 10;
		num /= 10;
		sum += rem * pow(2, index);
		index++;
	}
	stringstream b;
	b << sum;
	string s;
	b >> s;
	return s;
}
/////////////////////////////////////////////////////////////////////
void make_binary_form()
{
	string temp;
	for(int i = 0; i < count_a; i++)
	{
		binary_form[i] = "";
		temp = convert_to_binary(all_m[i]);
		for(int j = 0; j < num_v - temp.length(); j++)
			binary_form[i] += '0';	
		binary_form[i] += temp;
	}
}
/////////////////////////////////////////////////////////////////////
void make_groups_1()
{
	for(int i = 0; i <= num_v; i++)
		index_g1[i] = -1;
	
	int count;
	for(int i = 0; i < count_a; i++)
	{
		count = 0;
		for(int j = 0; j < num_v; j++)
		{
			if(binary_form[i][j] == '1')
				count++;
		}
		index_g1[count]++;
		groups_1[count][index_g1[count]] = binary_form[i];
	}
	
	cout << "\n\n\t     List 1";
	line();
	for(int i = 0; i <= num_v; i++)
	{
		if(index_g1[i] == -1)
			continue;
		cout << "\n Group " << i << "\n ";
		for(int j = 0; j <= index_g1[i]; j++)
			cout << groups_1[i][j] << "\n ";
	}	
}
/////////////////////////////////////////////////////////////////////
void make_groups_2()
{
	flag_list2 = false;
	for(int i = 0; i <= num_v - 1; i++)
		index_g2[i] = -1;
	int flag;
	int index;
	for(int i = 0; i <= num_v - 1; i++)
	{
		for(int j = 0; j <= index_g1[i]; j++)
		{
			for(int k = 0; k <= index_g1[i + 1]; k++)
			{
				flag = 0;
				index = -1;
				for(int l = 0; l < num_v; l++)
				{
					if(groups_1[i][j][l] != groups_1[i + 1][k][l])
					{
						flag++;
						index = l;
					}
				}
				
				if(flag == 1)
				{
					string a, b;
					a = convert_to_decimal(groups_1[i][j]);
					b = convert_to_decimal(groups_1[i + 1][k]);
					
					string temp = groups_1[i][j];
					temp[index] = '_';
					
					flag_list2 = true;
					index_g2[i]++;
					groups_2[i][index_g2[i]] = "";
					groups_2[i][index_g2[i]] += a;
					groups_2[i][index_g2[i]] += " ";
					groups_2[i][index_g2[i]] += b;
					groups_2[i][index_g2[i]] += " ";
					groups_2[i][index_g2[i]] += temp;
				}
			}
		}
	}
	
	cout << "\n\n\t     List 2";
	line();
	for(int i = 0; i <= num_v - 1; i++)
	{
		if(index_g2[i] == -1)
			continue;
		cout << "\n Group " << i << "\n ";
		for(int j = 0; j <= index_g2[i]; j++)
			cout << groups_2[i][j] << "\n ";
	}
}
/////////////////////////////////////////////////////////////////////
void make_groups_3()
{
	flag_list3 = false;
	for(int i = 0; i <= num_v - 2; i++)
		index_g3[i] = -1;
	int flag;
	int index;
	for(int i = 0; i <= num_v - 2; i++)
	{
		for(int j = 0; j <= index_g2[i]; j++)
		{
			for(int k = 0; k <= index_g2[i + 1]; k++)
			{
				flag = 0;
				index = -1;
				int sp1 = groups_2[i][j].length() - num_v;
				int sp2 = groups_2[i + 1][k].length() - num_v;
				
				for(sp1; sp1 < groups_2[i][j].length(); sp1++)
				{
					if(groups_2[i][j][sp1] != groups_2[i + 1][k][sp2])
					{
						flag++;
						index = sp1;
					}
					sp2++;
				}
				
				if(flag == 1)
				{
					string a, b;
					a = b = "";
					int up1 = 0;
					int up2 = 0;
					int low1 = 0;
					int low2 = 0;
					for(int l = 0; l < groups_2[i][j].length(); l++)
					{
						up1++;
						up2++;
						if(groups_2[i][j][l] == ' ')
						{
							a += groups_2[i][j].substr(low1, up1 - 1);
							a += " ";
							low1 = l + 1;
							up1 = 0;
						}
						if(groups_2[i + 1][k][l] == ' ')
						{
							b += groups_2[i + 1][k].substr(low2, up2 - 1);
							b += " ";
							low2 = l + 1;
							up2 = 0;
						}
					}
					string temp = groups_2[i][j];
					temp[index] = '_';
					
					flag_list3 = true;
					index_g3[i]++;
					groups_3[i][index_g3[i]] = "";
					groups_3[i][index_g3[i]] += a;
					groups_3[i][index_g3[i]] += b;					
					groups_3[i][index_g3[i]] += temp.substr(low1);	
				}
			}
		}
	}
	
	cout << "\n\n\t     List 3";
	line();
	for(int i = 0; i <= num_v - 2; i++)
	{
		if(index_g3[i] == -1)
			continue;
		cout << "\n Group " << i << "\n ";
		for(int j = 0; j <= index_g3[i]; j++)
			cout << groups_3[i][j] << "\n ";
	}
}
/////////////////////////////////////////////////////////////////////
void check_groups_3()
{
	for(int i = 0; i <= num_v - 2; i++)
	{
		if(index_g3[i] <= 0)
			continue;
		for(int j = 0; j <= index_g3[i]; j++)
		{
			int sp1, sp2;
			sp1 = groups_3[i][j].length() - num_v;
			for(int k = j + 1; k <= index_g3[i]; k++)
			{
				sp2 = groups_3[i][k].length() - num_v;
				if(groups_3[i][j].substr(sp1) == groups_3[i][k].substr(sp2))
				{
					for(int n = j; n < index_g3[i]; n++)
						groups_3[i][n] = groups_3[i][n + 1];
					index_g3[i]--;
				}
			}
		}
	}	
}
/////////////////////////////////////////////////////////////////////
void find_primary1()
{
	count_p = 0;
	for(int i = 0; i <= num_v; i++)
	{
		if(index_g1[i] == -1)
			continue;
		for(int j = 0; j <= index_g1[i]; j++)
		{
			stringstream a;
			a << convert_to_decimal(groups_1[i][j]);
			a >> primary_m[count_p];
			count_p++;
		}
	}
	
	line();
	cout << "\n Primary Minterms: ";
	for(int i = 0; i < count_p; i++)
		cout << primary_m[i] << " ";
}
/////////////////////////////////////////////////////////////////////
void find_primary2()
{
	count_p = 0;
	for(int i = 0; i <= num_v - 1; i++)
	{
		if(index_g2[i] == -1)
			continue;
		for(int j = 0; j <= index_g2[i]; j++)
		{
			string num;
			int up = 0;
			int low = 0;
			for(int l = 0; l < groups_2[i][j].length(); l++)
			{
				up++;
				if(groups_2[i][j][l] == ' ')
				{
							
					num = groups_2[i][j].substr(low, up - 1);
					stringstream a;
					a << num;
					a >> primary_m[count_p];
					count_p++;
					low = l + 1;
					up = 0;
				}
			}
		}
	}
	
	line();
	cout << "\n Primary Minterms: ";
	for(int i = 0; i < count_p; i++)
		cout << primary_m[i] << " ";
}
/////////////////////////////////////////////////////////////////////
void find_primary3()
{
	count_p = 0;
	for(int i = 0; i <= num_v - 2; i++)
	{
		if(index_g3[i] == -1)
			continue;
		for(int j = 0; j <= index_g3[i]; j++)
		{
			string num;
			int up = 0;
			int low = 0;
			for(int l = 0; l < groups_3[i][j].length(); l++)
			{
				up++;
				if(groups_3[i][j][l] == ' ')
				{
							
					num = groups_3[i][j].substr(low, up - 1);
					stringstream a;
					a << num;
					a >> primary_m[count_p];
					count_p++;
					low = l + 1;
					up = 0;
				}
			}
		}
	}
	
	line();
	cout << "\n Primary Minterms: ";
	for(int i = 0; i < count_p; i++)
		cout << primary_m[i] << " ";
}
/////////////////////////////////////////////////////////////////////
void find_essential1()
{
	int count;
	int count_e = 0;
	for(int i = 0; i < count_m; i++)
	{
		count = 0;
		for(int j = 0; j < count_p; j++)
		{
			if(minterms[i] == primary_m[j])
				count++;
		}
		if(count == 1)
		{
			ess_m[count_e] = minterms[i];
			count_e++;
		}
	}
	if(count_e == 0)
	{
		for(int i = 0; i < count_m; i++)
		{
			ess_m[count_e] = minterms[i];
			count_e++;
		}
	}
	
	cout << "\n\n Essential Minterms: ";
	for(int i = 0; i < count_e; i++)
		cout << ess_m[i] << " ";
	
	index_e = -1;
	for(int i = 0; i <= num_v; i++)
	{
		if(index_g1[i] == -1)
			continue;
		for(int j = 0; j <= index_g1[i]; j++)
		{
			int number;
			stringstream a;
			a << convert_to_decimal(groups_1[i][j]);
			a >> number;
			
			for(int n = 0; n < count_e; n++)
			{
				if(ess_m[n] == number)
				{
					index_e++;
					essential[index_e] = groups_1[i][j];
				}
			}
		}
	}
	
	check_essential();
	cout << "\n\n Essentials: \n ";
	for(int i = 0; i <= index_e; i++)
		cout << essential[i] << "\n ";
}
/////////////////////////////////////////////////////////////////////
void find_essential2()
{
	int count;
	int count_e = 0;
	for(int i = 0; i < count_m; i++)
	{
		count = 0;
		for(int j = 0; j < count_p; j++)
		{
			if(minterms[i] == primary_m[j])
				count++;
		}
		if(count == 1)
		{
			ess_m[count_e] = minterms[i];
			count_e++;
		}
	}
	if(count_e == 0)
	{
		for(int i = 0; i < count_m; i++)
		{
			ess_m[count_e] = minterms[i];
			count_e++;
		}
	}
	
	cout << "\n\n Essential Minterms: ";
	for(int i = 0; i < count_e; i++)
		cout << ess_m[i] << " ";
	
	index_e = -1;
	for(int i = 0; i <= num_v - 1; i++)
	{
		if(index_g2[i] == -1)
			continue;
		for(int j = 0; j <= index_g2[i]; j++)
		{
			string num;
			int up = 0;
			int low = 0;
			for(int l = 0; l < groups_2[i][j].length(); l++)
			{
				up++;
				if(groups_2[i][j][l] == ' ')
				{
							
					num = groups_2[i][j].substr(low, up - 1);
					stringstream a;
					int number;
					a << num;
					a >> number;
					for(int n = 0; n < count_e; n++)
					{
						if(ess_m[n] == number)
						{
							int sp = groups_2[i][j].length() - num_v;
							index_e++;
							essential[index_e] = groups_2[i][j].substr(sp);
						}
					}
					low = l + 1;
					up = 0;
				}
			}
		}
	}
	
	check_essential();
	cout << "\n\n Essentials: \n ";
	for(int i = 0; i <= index_e; i++)
		cout << essential[i] << "\n ";
}
/////////////////////////////////////////////////////////////////////
void find_essential3()
{
	int count;
	int count_e = 0;
	for(int i = 0; i < count_m; i++)
	{
		count = 0;
		for(int j = 0; j < count_p; j++)
		{
			if(minterms[i] == primary_m[j])
				count++;
		}
		if(count == 1)
		{
			ess_m[count_e] = minterms[i];
			count_e++;
		}
	}
	if(count_e == 0)
	{
		for(int i = 0; i < count_m; i++)
		{
			ess_m[count_e] = minterms[i];
			count_e++;
		}
	}
	
	cout << "\n\n Essential Minterms: ";
	for(int i = 0; i < count_e; i++)
		cout << ess_m[i] << " ";
	
	index_e = -1;
	for(int i = 0; i <= num_v - 2; i++)
	{
		if(index_g3[i] == -1)
			continue;
		for(int j = 0; j <= index_g3[i]; j++)
		{
			string num;
			int up = 0;
			int low = 0;
			for(int l = 0; l < groups_3[i][j].length(); l++)
			{
				up++;
				if(groups_3[i][j][l] == ' ')
				{
							
					num = groups_3[i][j].substr(low, up - 1);
					stringstream a;
					int number;
					a << num;
					a >> number;
					for(int n = 0; n < count_e; n++)
					{
						if(ess_m[n] == number)
						{
							int sp = groups_3[i][j].length() - num_v;
							index_e++;
							essential[index_e] = groups_3[i][j].substr(sp);
						}
					}
					low = l + 1;
					up = 0;
				}
			}
		}
	}
		
	check_essential();
	cout << "\n\n Essentials: \n ";
	for(int i = 0; i <= index_e; i++)
		cout << essential[i] << "\n ";
}
/////////////////////////////////////////////////////////////////////
void check_essential()
{
	int i = 0;
	while(i < index_e)
	{
		for(int j = i + 1; j <= index_e;)
		{
			if(essential[i] == essential[j])
			{
				for(int k = i; k < index_e; k++)
					essential[k] = essential[k + 1];
				index_e--;
				continue;
			} 
			else 
			{
				i++;
				j++;
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////
void print_final_answer()
{
	char chars[10];
	int char_num = 65;
	for(int i = 0; i < num_v; i++)
	{
		chars[i] = char_num;
		char_num++;
	}

	string answer = "";
	for(int i = 0; i <= index_e; i++)
	{
		for(int j = 0; j < num_v; j++)
		{
			if(essential[i][j] == '_')
				continue;
			answer += chars[j];
			if(essential[i][j] == '0')
				answer += "'";
		}
		
		if(i != index_e)
			answer += " + ";
	}
	
	line();
	cout << "\n Answer: \n\n " << answer << endl;
}
/////////////////////////////////////////////////////////////////////
void line() 
{
	cout << "\n --------------------------------\n";
}
   
