#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include "log.cpp"
using namespace std;



class Upgrade 
{
	public :
	
	Log log_obj;

	ifstream filein;
	ofstream fileout;
	
	string get_specific_value(string field,string file_name)
	{			
		ifstream filein;
		int flag=0;
		string strTemp;

		filein.open(file_name);
	
		while (filein >> strTemp)
		{
    			if(flag==1)
			{
				flag=0;
				return strTemp;
				break;
			}
        			if(strTemp == field)
      			 {
	    			flag=1;
        			}	
    		}
  		 filein.close();
	}
	
	void update_file(string file,string tmpfile,string vfield_name,string vdata,string fnfield_name,string fndata)
	{
		int vflag=0,flag=0,counter=0;
		string strTemp;
		
		filein.open(file);

		if(filein)
		{

		fileout.open(tmpfile);

		while (filein >> strTemp)
		{
    		 	if(vflag==1)
			{
				strTemp=vdata;
				fileout<<strTemp;
				vflag=0;
				strTemp=" ";
			}
			if(flag==1)
			{
				strTemp=fndata;
				fileout<<strTemp;
				flag=0;
				strTemp=" ";
			}
        			if(strTemp == vfield_name)
      			{
	    			vflag=1;
        			}
			if(strTemp == fnfield_name)
      			{
	    			flag=1;
        			}
			
			if(counter==2)
			{
				fileout<<endl;
				counter=0;
			}
			
        			fileout <<strTemp<<" ";

			if(strTemp=="Header:"||strTemp=="BaseAddress:")
			{
				fileout<<endl;
			}
			else
			{
		if(strTemp=="BOOTIMAGE:"||strTemp=="start_addr="||strTemp=="size="||strTemp=="ver="||strTemp==",")
				{
					counter=0;
				}
				else
				{
			 		counter++;	
				}
    			}
			}
  			 filein.close();
   			 fileout.close();
		}
		else
		{
			cout<<" \n File not exit ";
			exit(0);
		} 
	}
	char* get_curr_dtime()
	{
		time_t now = time(0);
 		char* date_time = ctime(&now);
		return date_time;
	}
	string get_time()
	{
		int hr,min,sec;
	
		time_t now = time(0);	
		tm* ltm = localtime(&now);  

		hr =  5 +ltm->tm_hour;
		min =  30+ltm->tm_min;
		sec =  ltm->tm_sec ;
	
		return to_string(hr)+":"+to_string(min)+":"+to_string(sec)+"_";
	
	}
	void upgrade_image(string file)
	{
		string tmp_file,cpfile,change_name,cmd,ver,device_n,path="/home/kalyani/sp2/";
		int tmp_ver;

		ifstream in;
		in.open("selected_device.txt");

		getline(in,device_n);
		path +=device_n;

		in.close();

		filesystem::current_path(path);

		tmp_file = get_time()+file; // creating file name 

		ver = get_specific_value("ver=",file);	
		
		tmp_ver = stoi(ver);
		tmp_ver += 1;
		ver = to_string(tmp_ver);

 		update_file(file,tmp_file,"ver=",ver,"file=",tmp_file);  // updating  file 
		
		if(get_specific_value("Checksum:",file)==get_specific_value("Checksum:",tmp_file))
		{
			cout<<"\n "<<file<<" upgraded successfully .... "<<endl;	

			log_obj.add_log(get_curr_dtime(),file+" upgraded successfully ....");
		}
		else
		{
			cout<<"\n integrity issue occured .... "<<endl;	

			log_obj.add_log(get_curr_dtime(),file+" integrity issue occured ....");
		}
	}	

};

