#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;

int rec_flag=0,no_book=0,no_student=0;
char rec_ind[5];

struct record2
{ char usn[6],ind[5],name[20],stbno[5],token[2];
}student[20];

struct record1
{ char bno[5],ind[5],bname[20],aname[20];
}book[20];

class bok
{

struct index
{ char bno[5],ind[5];
}in_book[20],temp;

public:
void file_no_book()
{
	ifstream file("book.txt");
	string line;
	int count=0;
	while(getline(file,line))
    {
    	count +=1;
    	
    }
    no_book = count;
    file.close();
}

void load_book()
{   file_no_book();
	char bno[5],bname[20],aname[20],ind[5];
	fstream file3,file4;
	  file3.open("book.txt",ios::in);
      file4.open("index1.txt",ios::in);
       
       for(int i=0;i<no_book;i++)
       {
		file3.getline(ind,5,'|');
		file3.getline(bno,5,'|');
		file3.getline(bname,20,'|');
		file3.getline(aname,20,'\n');
		strcpy(book[i].ind,ind);
		strcpy(book[i].bno,bno);
		strcpy(book[i].bname,bname);
		strcpy(book[i].aname,aname);
       }

      for(int i=0;i<no_book;i++)
       {
		file4.getline(bno,5,'|');
		file4.getline(ind,5,'\n');
		strcpy(in_book[i].bno,bno);
		strcpy(in_book[i].ind,ind);
       }

   file3.close();
   file4.close();

		
}




void sort_index()
{ int i,j;
  for(i=0;i<no_book-1;i++)
  for(j=0;j<no_book-i-1;j++)
  if(strcmp(in_book[j].bno,in_book[j+1].bno)>0)
  {
    temp=in_book[j];
    in_book[j]=in_book[j+1];
    in_book[j+1]=temp;
  }
}

void retrieve_record(char *ind)
{ for(int i=0;i<no_book;i++) 
  {  if(strcmp(book[i].ind,ind)==0)
     {
      strcpy(rec_ind,ind);
      rec_flag=1;
      cout<<"\n record found\n";

      cout<<book[i].bno<<"\t"<<book[i].bname<<"\t"<<book[i].aname<<"\n";
      return;
     }
  }
}

int search_index(char *bno)
{ int flag=0;
  for(int i=0;i<no_book;i++) 
  { if(strcmp(in_book[i].bno,bno)==0) 
    { retrieve_record(in_book[i].ind);
      flag=1;
    }
  }
  if(flag)
    return 1;
  else 
    return -1;
}

int search_bno(char *bno,int j)
{ int flag=0;
  for(int i=0;i<j;i++)
  {
   if(strcmp(book[i].bno,bno)==0)
   {  flag=1; 
      break;
   }
  }
  if(flag)
    return 1;
  else
    return -1;
}

void delet(char *bno)
{ rec_flag=0;
  int fr=0,i;
  search_index(bno);
  if(!rec_flag)
  { cout<<"\ndeletion failed record not found";
    return;
  }
  for(int i=0;i<no_book;i++)
  { if(strcmp(book[i].ind,rec_ind)==0)
    {
      fr=i;
      break;
    }
  }
  for(int i=fr;i<no_book-1;i++)
  {
    book[i]=book[i+1];
    char str[3];
    sprintf(str,"%d",i);
    strcpy(book[i].ind,str);
  }

  no_book--;
  fstream f1,f2;
  f1.open("book.txt",ios::out);
  f2.open("index1.txt",ios::out);
  for(int i=0;i<no_book;i++)
  {
    strcpy(in_book[i].bno,book[i].bno);
    strcpy(in_book[i].ind,book[i].ind);
  }

  sort_index();
  for(i=0;i<no_book;i++)
  {
    f1<<book[i].ind<<"|"<<book[i].bno<<"|"<<book[i].bname<<"|"<<book[i].aname<<"\n";
    f2<<in_book[i].bno<<"|"<<in_book[i].ind<<"\n";
  }
  f1.close();
  f2.close();
  cout<<"\n deletion successful";
}


void add_book()
{      fstream file1;
	   char bno[5],bname[20],aname[20],ind[5];
       file1.open("book.txt",ios::app|ios::out);
       if(!file1)
       {
        cout<<"file creation error \n";
        exit(0);
       }
        int n;
        cout<<"enter the no of book\n";
        cin>>n;
        cout<<"enter the details";
        for(int i=no_book;i<no_book+n;i++)
		{
		 label:  cout<<"\n Book No. :\n";
				 cin>>book[i].bno;
				 cout<<"\n Book Name:\n";
				 cin>>book[i].bname;
				 cout<<"\n Author Name:\n";
				 cin>>book[i].aname;
         int q=search_bno(book[i].bno,i);
		 if(q==1)
		 {
	 	  cout<<"\n duplicate value\n";
		  cout<<"\n enter again";
	 	  goto label;
		 }
         file1<<i<<"|"<<book[i].bno<<"|"<<book[i].bname<<"|"<<book[i].aname<<"\n";
        } 
       file1.close();
       no_book=no_book+n;
       fstream file2;
       file1.open("book.txt",ios::in);
       file2.open("index1.txt",ios::out);
       
       for(int i=0;i<no_book;i++)
       {
		file1.getline(ind,5,'|');
		file1.getline(bno,5,'|');
		file1.getline(bname,20,'|');
		file1.getline(aname,20,'\n');
		//strcpy(book[i].ind,ind);
		strcpy(in_book[i].bno,bno);
		strcpy(in_book[i].ind,ind);
       }
       sort_index();
       cout<<"\n after sorting index file contents are \n";
       for(int i=0;i<no_book;i++)
       cout<<in_book[i].bno<<"\t"<<in_book[i].ind<<endl;
       for(int i=0;i<no_book;i++)
       {
        file2<<in_book[i].bno<<"|"<<in_book[i].ind<<"\n";
       }
       file1.close();
       file2.close();
 
 }

 void display_sb()
 {  load_book();
 	char sbno[5];
 	cout<<"\n enter bno of book whose rec is to be displayed \n";
	cin>>sbno;
	int q=search_index(sbno);
	if(q==1)
	  cout<<"\n search successful\n";
	else
	  cout<<"\n search not successful\n";
  }

 void delete_book()
 {  load_book();
 	char sbno[5];
 	cout<<"enter bno of book whose rec is to be del \n";
	cin>>sbno;
	delet(sbno);
 }

 void display_book()
 {  load_book();
 	char ind[5];
 	for(int i=0;i<no_book;i++)
 	{ 
       cout<<book[i].bno<<"\t"<<book[i].bname<<"\t"<<book[i].aname<<"\n";
 	}
 }
};
//############################################################################################
//############################################################################################
class stu
{


struct index
{ char usn[6],ind[5];
}in_student[20],temp;

public:
void file_no_student()
 {
 	ifstream file("student.txt");
 	string line;
 	int count=0;
 	while(getline(file,line))
     {
     	count +=1;
     }
     no_student = count;
     file.close();
 }

 void load_student()
{   file_no_student();
	char usn[5],name[20],stbno[5],ind[5],token[2];
	fstream file3,file4;
	  file3.open("student.txt",ios::in);
      file4.open("index2.txt",ios::in);
       
       for(int i=0;i<no_student;i++)
       {
		file3.getline(ind,5,'|');
		file3.getline(usn,6,'|');
		file3.getline(name,20,'|');
		file3.getline(stbno,5,'|');
		file3.getline(token,2,'\n');
		strcpy(student[i].ind,ind);
		strcpy(student[i].usn,usn);
		strcpy(student[i].name,name);
		strcpy(student[i].stbno,stbno);
		strcpy(student[i].token,token);
       }

      for(int i=0;i<no_student;i++)
       {
		file4.getline(usn,6,'|');
		file4.getline(ind,5,'\n');
		strcpy(in_student[i].usn,usn);
		strcpy(in_student[i].ind,ind);
       }

   file3.close();
   file4.close();

}

void sort_index()
{ int i,j;
  for(i=0;i<no_student-1;i++)
  for(j=0;j<no_student-i-1;j++)
  if(strcmp(in_student[j].usn,in_student[j+1].usn)>0)
  {
    temp=in_student[j];
    in_student[j]=in_student[j+1];
    in_student[j+1]=temp;
  }
}

void retrieve_record(char *ind)
{ for(int i=0;i<no_student;i++) 
  {  if(strcmp(student[i].ind,ind)==0)
     {
      strcpy(rec_ind,ind);
      rec_flag=1;
      cout<<"\n record found\n";

      cout<<student[i].usn<<"\t"<<student[i].name<<"\t"<<student[i].stbno<<"\t"<<student[i].token<<"\n";
      return;
     }
  }
}

int search_index(char *usn)
{ int flag=0;
  for(int i=0;i<no_student;i++) 
  { if(strcmp(in_student[i].usn,usn)==0) 
    { retrieve_record(in_student[i].ind);
      flag=1;
    }
  }
  if(flag)
    return 1;
  else 
    return -1;
}

int search_usn(char *usn,int j)
{ int flag=0;
  for(int i=0;i<j;i++)
  {
   if(strcmp(student[i].usn,usn)==0)
   {  flag=1; 
      break;
   }
  }
  if(flag)
    return 1;
  else
    return -1;
}



void delet(char *usn)
{ rec_flag=0;
  int fr=0,i;
  search_index(usn);
  if(!rec_flag)
  { cout<<"\ndeletion failed record not found";
    return;
  }
  for(int i=0;i<no_student;i++)
  { if(strcmp(student[i].ind,rec_ind)==0)
    {
      fr=i;
      break;
    }
  }
  for(int i=fr;i<no_student-1;i++)
  {
    student[i]=student[i+1];
    char str[3];
    sprintf(str,"%d",i);
    strcpy(student[i].ind,str);
  }

  no_student--;
  fstream f1,f2;
  f1.open("student.txt",ios::out);
  f2.open("index2.txt",ios::out);
  for(int i=0;i<no_student;i++)
  {
    strcpy(in_student[i].usn,student[i].usn);
    strcpy(in_student[i].ind,student[i].ind);
  }

  sort_index();
  for(i=0;i<no_student;i++)
  {
    f1<<student[i].ind<<"|"<<student[i].usn<<"|"<<student[i].name<<"|"<<student[i].stbno<<"|"<<student[i].token<<"\n";
    f2<<in_student[i].usn<<"|"<<in_student[i].ind<<"\n";
  }
  f1.close();
  f2.close();
  cout<<"\n deletion successful";
}

void add_student()
{      fstream file1;
	   char usn[6],name[20],stbno[5],ind[5],token[2];
       file1.open("student.txt",ios::app|ios::out);
       if(!file1)
       {
        cout<<"file creation error \n";
        exit(0);
       }
        int n;
        cout<<"enter the no of student\n";
        cin>>n;
        cout<<"enter the details";
        for(int i=no_student;i<no_student+n;i++)
		{
		 label:  cout<<"\n student usn. :\n";
				 cin>>student[i].usn;
				 cout<<"\n student Name:\n";
				 cin>>student[i].name;
				 strcpy(student[i].token,"0");
				 strcpy(student[i].stbno,"0");

         int q=search_usn(student[i].usn,i);
		 if(q==1)
		 {
	 	  cout<<"\n duplicate value\n";
		  cout<<"\n enter again";
	 	  goto label;
		 }
         file1<<i<<"|"<<student[i].usn<<"|"<<student[i].name<<"|"<<student[i].stbno<<"|"<<student
         [i].token<<"\n";
        } 
       file1.close();
       no_student=no_student+n;
       fstream file2;
       file1.open("student.txt",ios::in);
       file2.open("index2.txt",ios::out);
       
       for(int i=0;i<no_student;i++)
       {
		file1.getline(ind,5,'|');
		file1.getline(usn,6,'|');
		file1.getline(name,20,'|');
		file1.getline(stbno,5,'|');
		file1.getline(token,2,'\n');
		//strcpy(book[i].ind,ind);
		strcpy(in_student[i].usn,usn);
		strcpy(in_student[i].ind,ind);
       }
       sort_index();
       cout<<"\n after sorting index file contents are \n";
       for(int i=0;i<no_student;i++)
       cout<<in_student[i].usn<<"\t"<<in_student[i].ind<<endl;
       for(int i=0;i<no_student;i++)
       {
        file2<<in_student[i].usn<<"|"<<in_student[i].ind<<"\n";
       }
       file1.close();
       file2.close();
 
 }

void display_ss()
 {  load_student();
 	char susn[6];
 	cout<<"\n enter usn of student whose rec is to be displayed \n";
	cin>>susn;
	int q=search_index(susn);
	if(q==1)
	  cout<<"\n search successful\n";
	else
	  cout<<"\n search not successful\n";
  }

 void delete_student()
 {  load_student();
 	char susn[6];
 	cout<<"enter usn of student whose rec is to be del \n";
	cin>>susn;
	delet(susn);
 }

 void display_student()
 {  load_student();
 	char ind[5];
 	for(int i=0;i<no_student;i++)
 	{ 
       cout<<student[i].usn<<"\t"<<student[i].name<<"\t"<<student[i].stbno<<"\t"<<student[i].token<<"\n";
 	}
 }
};


bok bk;
stu st;

//***************************************************************
//    	function to issue book
//****************************************************************

void book_issue()
{
	char sn[6],bn[5];
	int found=0,flag=0,flag2=0;
	fstream fp;
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter The student's usn";
	cin>>sn;
	fp.open("student.txt",ios::in|ios::out);
    for(int i = 0;i<no_student;i++)
    {
    	
		if(strcmp(student[i].usn,sn)==0)
		{
			found=1;
			if(strcmp(student[i].token,"0")==0)
			{   flag = 1;
				cout<<"\n\n\tEnter The book no.";
				cin>>bn;
				for(int j= 0;j<no_book;j++)
				{
					if(strcmp(book[j].bno,bn)==0)
					{   flag2 =1;
						strcpy(student[i].token,"1");
		                strcpy(student[i].stbno,bn);
                        cout<<"Book issue successful\n";
                        break;
					}
				}
				if(flag2==0)
    	           cout<<"book doesnt exist\n";
				

			}

			 if(flag==0)
    	            cout<<"The old book is not returned yet\n";
		}
		fp<<i<<"|"<<student[i].usn<<"|"<<student[i].name<<"|"<<student[i].stbno<<"|"<<student
         [i].token<<"\n";
    }	

    if(found==0)
      cout<<"Student record not exist...\n";
	
  	fp.close();
}

void book_deposit()
{   char sn[6];
	int found=0,flag=0,day,fine;
	fstream fp;
	cout<<"\n\nBOOK DEPOSIT...";
	cout<<"\n\n\tEnter The student's usn";
	cin>>sn;
	fp.open("student.txt",ios::in|ios::out);
    for(int i = 0;i<no_student;i++)
    {
    	
		if(strcmp(student[i].usn,sn)==0)
		{
			found=1;
			if(strcmp(student[i].token,"1")==0)
			{   flag = 1;
                strcpy(student[i].token,"0");
		        strcpy(student[i].stbno,"0");
				cout<<"\n\nBook deposited in no. of days\n";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\nFine has to deposited Rs. "<<fine<<"\n";
				   break;
				}

			}

			    if(flag==0)
			    {
			    	cout<<"No book is Issued\n";
			    }
		}
		fp<<i<<"|"<<student[i].usn<<"|"<<student[i].name<<"|"<<student[i].stbno<<"|"<<student
         [i].token<<"\n";
    }	
   


    if(found==0)
    cout<<"Student record not exist...\n";
	
  	fp.close();
}



void admin_menu()
{
	
	int ch2;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\n\n\t4.DELETE STUDENT RECORD";
	cout<<"\n\n\t5.CREATE BOOK ";
	cout<<"\n\n\t6.DISPLAY ALL BOOKS ";
	cout<<"\n\n\t7.DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t8.DELETE BOOK ";
	cout<<"\n\n\t9.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-9) ";
	cin>>ch2;
	switch(ch2)
	{
    		case 1: st.add_student();break;
    		case 2: st.display_student();break;
    		case 3: st.display_ss();break;
      		case 4: st.delete_student();break;
		    case 5: bk.add_book();break;
		    case 6: bk.display_book();break;
		    case 7: bk.display_sb();break;
      		case 8: bk.delete_book();break;
     		case 9: return;
      		default:cout<<"\a";
   	}
   	admin_menu();
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	char ch;
	st.load_student();
    bk.load_book();

	do
	{
		
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
	  	cout<<"\n\n\t03. ADMINISTRATOR MENU";
	  	cout<<"\n\n\t04. EXIT";
	  	cout<<"\n\n\tPlease Select Your Option (1-4) ";
	  	cin>>ch;
	  	switch(ch)
	  	{
			case '1':
				 book_issue();
			   	 break;
		  	case '2':book_deposit();
			    	 break;
		  	case '3':admin_menu();
				 break;
		  	case '4':return 0;
		  	default :cout<<"\a";
		}
    	}while(ch!='4');
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************

