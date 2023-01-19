#include<iostream>
#include<string>
#include <fstream>

using namespace std;

string cmd="./cmd_line ";

void fetch_files(string file)
{
	ifstream in;
	string data;

	in.open(file);
	while(getline(in,data))
	{
		if(data=="device1_files.txt" || data=="device2_files.txt")
		{
			continue;
		}
		cmd = cmd+data+" "; 	
	}
	in.close();	
}
void device1()
{
	fstream out;
	
	out.open("selected_device.txt");
	out<<"device1";
	out.close();

	system("cd device1; ls >device1_files.txt;mv device1_files.txt /home/kalyani/sp2");
	
	fetch_files("device1_files.txt");
	
	const char *command = cmd.c_str();
	system(command);
	
	cmd="./cmd_line ";	
}
void device2()
{
	fstream out;
	
	out.open("selected_device.txt");
	out<<"device2";
	out.close();

	system("cd device2;ls >device2_files.txt;mv device2_files.txt /home/kalyani/sp2");
	fetch_files("device2_files.txt");
	
	const char *command = cmd.c_str();
	system(command);
	
	cmd="./cmd_line ";	
}


int main()
{ 

	int ch;
	cout<<":::::::::::::::: WELCOME TO AUTOMATIC IMAGE UPGRADE APPLICATION SOFTWARE :::::::::::::::: \n";
	cout<<"\n********************************** Menu **********************************\n";
	cout<<"\n 1. Device 1 \n 2. Device 2 \n 3. Exit "; //Add comments in config file \n 4.
	cout<<"\n Enter your choice : ";
	cin>>ch;
	
		switch(ch)
		{
			case 1 :
				device1();
				break;
			case 2 :
				device2();
				break;
			case 3 :
				cout<<"\n Exiting from application ..... \n";
				exit(0);
				break;
			default :
			cout<<"\n Invalid choice,Try again! \n";
		}

	
	
	return 0;
}

