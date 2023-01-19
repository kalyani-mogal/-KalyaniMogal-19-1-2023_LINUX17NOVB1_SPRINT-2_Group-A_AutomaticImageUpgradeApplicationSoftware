#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
class Log
{
	public : 
	void add_log(char* time,string info)
	{
		ofstream out;
		filesystem::current_path("/home/kalyani/sp2");

		out.open("log_file.txt",ios::app);
		out<<time<<" "<<info;

		out<<"\n--------------------------------------------------------------"<<endl;
		out.close();
	}

};
