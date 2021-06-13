#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector> 
#include <sstream>

using namespace std;

class Plotter
{	

public:
	void plotBar(vector<int> barValue, int n,string name, string sid)
	{
		cout<<"Name: "<<name<<"\tSID: "<<sid<<"\n\n";
		int maxi = barValue.at(0);	
		
		for (int i = 1; i < n; ++i)
	        if (barValue.at(i) > maxi)
	            maxi = barValue.at(i);
	            
		for (int j = 0; j < n; ++j)  
		{
	        for ( int i = maxi+1; i >= 1; --i)
			{
	            if (barValue.at(j) >= i) 
	                cout << "|" << "  ";
	            else
	                cout << "   ";
	        }
	        cout << "\n";
	    }
	    for (int j = 0; j < n; ++j)
	        cout << "__ ";
	    cout << endl;
	    for (int j = 0; j < n; ++j)
	        cout <<barValue.at(j) <<"  ";
	    cout<<"\n";
	}
	
	void plotBarWithSand(vector<int> sandValue, vector<int> barValue, int n,string name, string sid)
	{
		cout<<"Name: "<<name<<"\tSID: "<<sid<<"\n\n";
		vector<int>total;
		for(int i=0;i<n;i++)
		{
			total.push_back( barValue.at(i)+ sandValue.at(i));
		}
			
	    int maxi = barValue.at(0);
	    for (int i = 1; i < n; ++i)
	        if (barValue.at(i) > maxi)
	            maxi = barValue.at(i);
	            
	    for (int i = maxi+1; i >= 1; --i)
		{
	        for (int j = 0; j < n; ++j) 
			{
	            if (barValue.at(j) >= i) 
	                cout << "|" << "  ";
	                
	            else if(total.at(j)==i-1)
	            {
	            	if(total.at(j)-barValue.at(j) != 0)
	            		cout<<total.at(j)-barValue.at(j)<<"  ";
	            	else
	            	cout<<"   ";
	            }
	            	
	            else if(total.at(j)==i)
	            {
	            	cout<<"-"<<"  "; 
	            }
	            else if(total.at(j)>i)
	            	cout<<"."<<"  ";
	            else
	                cout << "   ";
	        }
	        
	    	cout << "\n";
	    }
	    for (int j = 0; j < n; ++j)
	        cout << "__ ";
	    cout << endl;
	    for (int j = 0; j < n; ++j)
	        cout << barValue.at(j) <<"  ";
	    int sum=0;
	    for(int i=0;i<n;i++)
	    	sum+=sandValue.at(i);
	    cout<<"\n>> Total "<<sum<<" units of sand\n";
	}
};


class Exporter
{
public:
	
	void export_as_txt(vector<int> sandValue, vector<int> barValue, int n, string filename,string name, string sid)
	{
		
		fstream newfile;
	   	newfile.open(filename,ios::out);  
	  	if(newfile.is_open())
	   	{
	   		newfile<<"Name: "<<name<<"\tSID: "<<sid<<"\n\n";
	      	vector<int>total;
			for(int i=0;i<n;i++)
			{
				total.push_back( barValue.at(i)+ sandValue.at(i));
			}
				
		    int maxi = barValue.at(0);
		    for (int i = 1; i < n; ++i)
		        if (barValue.at(i) > maxi)
		            maxi = barValue.at(i);
		            
		    for (int i = maxi+1; i >= 1; --i)
			{
		        for (int j = 0; j < n; ++j) 
				{
		            if (barValue.at(j) >= i) 
		                newfile << "|" << "  ";
		                
		            else if(total.at(j)==i-1)
		            {
		            	if(total.at(j)-barValue.at(j) != 0)
		            		newfile<<total.at(j)-barValue.at(j)<<"  ";
		            	else
		            	newfile<<"   ";
		            }
		            	
		            else if(total.at(j)==i)
		            {
		            	newfile<<"-"<<"  "; 
		            }
		            else if(total.at(j)>i)
		            	newfile<<"."<<"  ";
		            else
		                newfile << "   ";
		        }
		        
		    	newfile << "\n";
		    }
		    for (int j = 0; j < n; ++j)
		        newfile << "__ ";
		    newfile << endl;
		    for (int j = 0; j < n; ++j)
		        newfile << barValue.at(j) <<"  ";
		    int sum=0;
		    for(int i=0;i<n;i++)
		    	sum+=sandValue.at(i);
		    newfile<<"\n>> Total "<<sum<<" units of sand\n";
	      	newfile.close(); 
	   	}
	}
	
};


class SandCalculator
{
private:
	vector<int> barValue;
	vector<int> sandValue;
	Plotter plot;
	string name,sid;
	int n;
public:
	SandCalculator(string n, string s)
	{
		name = n;
		sid=s;
	}
	int readInput(int ch)
	{
		int flag=0;
		switch(ch)
		{
			case 1://read console
				{
					std::string input;
					getline(cin, input);
					getline(cin, input);
					std::istringstream iss(input);
					int temp;
					while(iss >> temp)
					{
					   barValue.push_back(temp);
					}
					flag=1;
					break;
				}
			case 2://read file
				{
					fstream newfile;
					string tp;
					string filename;
					cout<<"\n>> Enter the file name: ";
					cin>>filename;
					newfile.open(filename,ios::in);
					if(!newfile)
					{
						cout<<"\n>>No file found!! \n>>Note:Don't forget extension.\n";
						break ;
					}
					if (newfile.is_open())
					{
						string data = "";
						while(getline(newfile, data,','))
						{
						  tp=tp+data+' ';
						}
						newfile.close();
					}
					
					int n = tp.length();
					char str[n + 1];
					strcpy(str, tp.c_str());
					storeReadValue(str);
					flag=1;
					break;
				}
			case 3:// generate random
				{
					srand(time(NULL));
					int n = 3+(rand()%20);
					for(int i=0;i<n;i++)
					{
						int temp = 1+(rand()%9);
						barValue.push_back(temp);
					}
					flag=1;
					break;
				}
		}
		
		n=barValue.size();
		return flag;
	}
	

	void storeReadValue(char * str)
	{
		char * pch = strtok (str," ");
		while (pch != NULL)              
		{
			barValue.push_back(atoi(pch)); 
      		pch = strtok (NULL, " ");
  		}
	}

	void writeConsole(vector<int> V)
	{
		for(int i=0; i < V.size(); i++)
	  		cout << V.at(i) << ' ';
	  	cout<<"\n";
	}

	void plotBar()
	{
		plot.plotBar(barValue, n,name,sid);
	}

	void calculateSand()
	{
		int maxR[n],maxL[n],k=1;
	    maxR[0] = barValue.at(0);
	    maxL[0] = barValue.at(n-1);
	    
	    for(int i=1; i<n; i++)
	    	maxR[i] = max(maxR[i-1], barValue.at(i) );
	    
	    for(int i=n-2;i>=0;i--)
	    	maxL[k++] = max(maxL[n-i-2], barValue.at(i));
	    	
	    int start=0,end=n-1;
		while (start < end)
	    {
	        int temp = maxL[start]; 
	        maxL[start] = maxL[end];
	        maxL[end] = temp;
	        start++;
	        end--;
	    }
	    for(int i=0; i<n; i++)
	    	sandValue.push_back( min(maxR[i],maxL[i]) - barValue.at(i));
	    
	}

	void getSandValues()
	{
		writeConsole(sandValue);
	}
	
	void getBarValues()
	{
		writeConsole(barValue);
	}
	
	void plotComplete()
	{
		plot.plotBarWithSand(sandValue,barValue, n,name,sid);
	}

	void saveGraph(string filename)
	{
		Exporter ex;
		ex.export_as_txt(sandValue,barValue, n, filename,name,sid);
	}

	void reset()
	{
		barValue.clear();
		sandValue.clear();
	}
};

int main()
{
	
	string name="dummy", sid="idxxxx";
	SandCalculator obj(name,sid);
	int home = 1;
	while(home == 1)
	{
		cout<<"_-_-_-_-_- Sand Trap _-_-_-_-_-\n";
		cout<<"Name: "<<name<<"\tSID: "<<sid<<"\n\n";
		
		int t=1,ch,flag=0;
		while (t==1)
		{
			cout<<"1.Enter data\n";
			cout<<"2.Show data\n";
			cout<<"3.Show Bar Chart of only data\n";
			cout<<"4.Show Bar Chart with sand\n";
			cout<<"5.Exit\n";
			cout<<"\n\n>>";
			
			cin>>ch;
			switch(ch)
			{
				case 1:
					{
						
						cout<<"1.Enter space separated values\n2.Read From Text File\n3.Generate random Bar graph\n\n>> ";
						cin>>ch;
						int ind = obj.readInput(ch);
						if (ind==0)
						{
							cout<<">>Bar Graph not generated...\n\n";
							break;
						}
						flag=1;
						cout<<"\n>>Bar Graph Generated....\n\n";
						break;
					}
				case 2:
					{
						if(flag==0)
						{
							cout<<"\n>>Enter data first....\n";
							break;
						}
						obj.getBarValues();
						cout<<"\n\n";
						break;
					}
				case 3:
					{
						if(flag==0)
						{
							cout<<"\n>>Enter data first....\n";
							break;
						}
						obj.plotBar();
						cout<<"\n\n";
						break;
					}
				case 4:
					{
						if(flag==0)
						{
							cout<<"\n>>Enter data first....\n";
							break;
						}
						obj.calculateSand();
						obj.plotComplete();
						cout<<"\n\n";
						break;
					}
				case 5:
					{
						t=0;
						
						if(flag==0)
							break;
						int k=0;
						while(k==0)
						{
							char temp;
							cout<<"\n>>Do you want to save the graph?(y/n)\n>>";
							char c;
							cin>>c;
							if(c=='y')
							{
								string filename;
								cout<<"\n>> Enter the file name: ";
								cin>>filename;
								obj.saveGraph(filename);
								cout<<"\nGraph saved in file "<<filename<<"....\n";
								k=1;
							}
							else if(c=='n')
							{
								cout<<"\n>>Exiting........\n";
								k=1;
							}
							else
							cin>>temp;
						}
						break;
					}
				default:
					{
					cout<<"Wrong choice try again.......\n";
					break;
				}
			}	
		}
		
		cout<<">>Rerun?(y/n)";
		char f;
		cin>>f;
		if(f=='n')
		{
			home=0;
		}
		else if(f=='y')
		{
			obj.reset();
		}
	}
	
	
	
	
}
