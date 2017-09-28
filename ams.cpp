#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<stdlib.h>

using namespace std;

class admin
{
 int attempt;
 char username[20];
 char password1[20];
 public:
	void login();
	void mainmenu();
	admin()
	{
	 attempt=1;
	 strcpy(username,"savneet");
	 strcpy(password1,"nikita");
	}
};
class stud
{  public:
	int id;
	char fname[10];
	char lname[10];
	char mname[10];
	public:
		void addrec();
		virtual void display()
		{

		}
};
class percent:public stud
{
    int maths,eng,science,social;
    int rl;
    char namm[10];
	public:
	    float fpercent;
		void calper();
		void display();
		void search(int);
        void search(char *);
        friend void update(percent,int);
        percent(){
        }
        percent(int);
        void namz();
        int operator ==(char *);
};
void flwrite();
void fldisplay();
void flsearch();
void flcount();
void flupdate();
void flgenerate();

int percent::operator ==(char namz[])
{
  if(strcmp(percent::fname,namz)==0)
  {
    return 1;
  }
   else
   return 0;
}
void admin::login()
{
 char userid[20],password[20];
 int i=0;
 char ch;
 if(attempt<=3)
 {
  cout<<"\n\n\t=====================ADMISSION MANAGEMENT SYSTEM==========================\t\n";
  cout<<" \n\t Enter Username : ";
  cin>>userid;
  cout<<"\n\t Enter Password : ";
  ch=getch();
  while(ch!=13)
  {
   password[i]=ch;
   i++;
   putch('*');
   ch=getch();
   }
 password[i]='\0';
 if(strcmp(userid,username)==0)
 {
     if(strcmp(password,password1)==0)
    {
        cout<<"\n\n";
        cout<<"\n\t\tLOGIN SUCCESSFUL\n\n";
        cout<<"\tPress any key to continue.....\n\n\n";
        getch();
        mainmenu();
    }
    else{
        cout<<"\n Incorrect username or password, you have only "<<3-attempt<<" chances left\n";
        attempt++;
       getch();
        login();
    }
 }

 else
 {
 cout<<"\n Incorrect username or password, you have only "<<3-attempt<<" chances left\n";
 attempt++;
 getch();
 login();
 }
}
else
{
 cout<<"\n\n You cannot login. Try again later ";

}
}

void admin::mainmenu()
{
	int ch,i3d;
	char c;
    system("cls");
	do{
	cout<<"\n************************************************************\n";
	cout<<"\nWelcome to Admission Mangagement System\n";
	cout<<"\n************************************************************\n";
	cout<<"\n1. Add record\n2. Delete Record\n3. Modify details\n4. Search Detail\n5. Display records\n6. Count \n7. Generate receipt \n \nEnter Your Choice\t";
	cin>>ch;
	try
	{
	    if(ch>7||ch<=0)
        {
           throw(ch);
        }
		else
        {
            switch(ch)
            {
                case 1:
                    flwrite();
                    break;
                case 2:
                    {
                        system("CLS");
                    cout<<"\nEnter id to delete";
                    cin>>i3d;
                    percent(i3d);
                    }
                    break;
                case 3:
                    flupdate();
                    break;
                case 4:
                    flsearch();
                    break;
                case 5:
                    fldisplay();
                    break;
                case 6:
                    flcount();
                    break;
                case 7:
                    flgenerate();
                    break;
            }
        }
	}
	catch(int log)
	{
	    cout<<"\n\tException caught,the choice entered incorrect";
	}
	cout<<"\n\tDo u want to other operations. Press y for yes.....";
	cin>>c;
}while(c=='y'|| c=='Y');
system("CLS");
}
percent::percent(int i3d)
{
    ifstream ifp;
	int found=0;
	percent p;
	ofstream ofp;
	ifp.open("stud", ios::binary);
	ofp.open("stud1", ios::binary);
	while(ifp.read((char*)&p,sizeof(p)))
	{
		if(p.id != i3d)
		{
			ofp.write((char*)&p,sizeof(p));
		}
		else
		{
			found=1;
		}
	}
	ofp.close();
	ifp.close();
	if(found==0)
	cout<<"\nCannot be deleted; Id not found.";
	else
	cout<<"\nRecord deleted Successfully";
	remove("stud");
	rename("stud1","stud");
	remove("stud1");
}
void percent::search(int id1)
{
	ifstream ifp;
	percent md;
	int found=0;
	ifp.open("stud",ios::binary);
	while(ifp.read((char*)&md,sizeof(md))!=NULL)
	{
		if(md.id==id1)
		{
			found=1;
			break;
		}
	}
	if(found==1)
	{
		cout<<"\n Student found";
		cout<<"\nName:\t"<<md.fname;
	}
	else
	{
		cout<<"\nRecord not found";
	}
}
void percent::search(char name[])
{
	ifstream ifp;
	percent md;
	int found=0;
	ifp.open("stud",ios::binary);
		while(ifp.read((char*)&md,sizeof(md))!=NULL)
	{
		if(strcmp(md.fname,name)==0)
		{
			found=1;
			break;
		}
	}
	if(found==1)
	{
		cout<<"\n Student found";
		cout<<"\nID: "<<md.id;
	}
	else
	{
		cout<<"\nRecord not found";
	}
}

void flwrite()
{
    system("cls");
	ofstream fp;
	fp.open("stud",ios::binary | ios::app);
	percent s;
	s.addrec();
	s.calper();
	fp.write((char *)&s,sizeof(s));
	fp.close();
}
void fldisplay()
{
    stud *f;
	percent p ;
	f = &p;
	f->display();
}
void flsearch()
{
	system("cls");
	 ofstream fp;
    fp.open("stud",ios::binary | ios::app);
	int choice;
	percent p;
	cout<<"1.enter search by id.\n2.enter search by name\nENTER CHOICE:\t\n";
	cin>>choice;
	if(choice==1)
	{
		int id1;
		cout<<"enter id to search:\t";
		cin>>id1;
		p.search(id1);
	}
	else
	{
		char name1[20];
		cout<<"\nenter name to search:\t";
		cin>>name1;
		p.search(name1);
	}
}
void flupdate()
{
    int iid;
    percent per;
    system("cls");
    cout<<"\nEnter id to update";
    cin>>iid;
    update(per,iid);
}
void flcount()
{
	ifstream ifp;
	int count=0;
	percent b;
	float perc;
	system("cls");
	cout<<"\n\nEnter percentage to count:\t";
	cin>>perc;
	cout<<"\n\n Students with "<<perc<<"% or greater are \t\n ";
	ifp.open("stud",ios::binary);
	while(ifp.read((char*)&b,sizeof(b))!=NULL)
	{
		if(b.fpercent>=perc)
		{
			count++;
			cout<<"\n Student's Name:\t"<<b.fname<<" "<<b.lname;
            cout<<"\n---------------------------------------------------";
		}
	}
	ifp.close();
	cout<<"\n Total Students:\t"<<count;
}

void stud::addrec()
{
    system("cls");
	cout<<"\n\t\tEnter Student Id:\t";
	cin>>id;
	cout<<"\n\t\tEnter student's First Name:\t";
	cin>>fname;
	cout<<"\n\t\tEnter Last name:\t";
	cin>>lname;
	cout<<"\n\t\tEnter Mother's name:\t";
	cin>>mname;
}
void percent::calper()
{

    cout<<"\n\n\n";
	cout<<"\n\t\tEnter marks of math,english,science and social science:\t";
	cin>>maths>>eng>>science>>social;
	fpercent= ((maths+eng+science+social)/4);
}
void percent::display()
{
    ifstream fip;
    fip.open("stud",ios::binary);
    percent obj;
    while(fip.read((char*)&obj, sizeof(obj))!=NULL)
    {
        cout<<"\n Student Id:\t"<<obj.id;
        cout<<"\n Student's First Name:\t"<<obj.fname;
        cout<<"\n Last name:\t"<<obj.lname;
        cout<<"\n Mother's name:\t"<<obj.mname;
        cout<<"\n Percentage:\t"<<obj.fpercent<<"\n--------------------------------------------------------------------------------";
    }
    fip.close();

}
template<class percent>
void generate(percent obj)
{
	cout<<"*************** GHRCE ******************";
	cout<<" \n************\t\t\t\t ####\t\t\t Receipt \t\t\t\t #####\t\t\t ************** \n";
	cout<<"\n Student Id:\t"<<obj.id;
        cout<<"\n Student's First Name:\t"<<obj.fname;
        cout<<"\n Last name:\t"<<obj.lname;
        cout<<"\n Mother's name:\t"<<obj.mname;
        cout<<"\n Percentage:\t"<<obj.fpercent;
	cout<<"\n\n\n************\t\t\t\t\t 	HAPPY TO SERVE YOU \t\t\t\t\t**********\n";
	cout<<"*******\t\t\t\t\t  THANK YOU , VISIT AGAIN  \t\t\t\t**********\n";
}
void flgenerate()
{
	ifstream ifp;
	int id,found=0;percent obj;
	cout<<"enter id :";
	cin>>id;
	ifp.open("stud",ios::binary);
	while(ifp.read((char*)&obj,sizeof(obj))!=NULL)
	{
		if (obj.id==id)
		{
			found =1;
			break;
		}
	}
	ifp.close();
	if(found==0)
	{
	 cout<<"no record found";
	}
	else
	{

		generate(obj);
    }
}

void update(percent per,int iid)
{
    int found=0;
    fstream fp;
    system("cls");
    fp.open("stud",ios::binary|ios::in|ios::out);
    while(fp.read((char*)&per,sizeof(per))!=NULL)
    {
        if(per.id==iid)
        {
            int loc=(-1*sizeof(per));
            fp.seekp(loc,ios::cur);
            per.addrec();
            per.calper();
            fp.write((char*)&per,sizeof(per));
            found=1;
            break;
        }
    }

    if(found==0)
    {
        cout<<"\nRecord not found";
    }
    else{

        cout<<"\nRecord Updated";
    }
    fp.close();
}


int main()
{
	system("CLS");
	admin a;
	a.login();
	getch();
	return 0;
}
