#include<iostream>
#include<string>
#include "imgUpgrade.cpp"
using namespace std;

class Image 
{

public:

Upgrade up;

void pass_file(string file)
{
	up.upgrade_image(file);
}
void check_arg(int narg)
{
	if(narg<3)
	{
		cout<<"\n Device should contain 2 or more files...."<<endl;
		up.log_obj.add_log(up.get_curr_dtime()," Device should contain 2 or more files....");
		exit(0);
	}
}
};
int main(int argc, char** argv)
{ 
	string arguments;
	Image img;

	img.check_arg(argc);

	 for (int i = 1; i < argc; i++)
	  {
    		arguments = argv[i];
		img.pass_file(arguments);
  	 }

	return 0;
}
