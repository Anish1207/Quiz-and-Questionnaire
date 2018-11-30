				// LETS QUIZ //

/*  The following program has been aimed at providing a platform for teachers
    to manage a question bank (a file storing questions) and students to take
    up quizzes with some options to choose from.

    An attempt has been made to incorporate most of the elements object
    oriented C++ taught in CBSE XII Computer Science course.
    The following concepts have been used here,
      1.Classes
      2.Data file handling
      3.Arrays (1-D and 2-D)
      4.Constructors
*/

#include <iostream.h>             //                 .
#include <conio.h>                //                 .
#include <iomanip.h>              //setw(),endl      .
#include <dos.h>                  //delay()          .
#include <process.h>              //exit()           .
#include <fstream.h>              //                 .
#include <stdio.h>                //gets(),puts()    .
#include <string.h>               //strcmp(),strcpy().
#include <stdlib.h>               //random()         .

////////////////////////////////////////////////////////////////////////////
//                        USER DEFINED FUNCTIONS
////////////////////////////////////////////////////////////////////////////

void inline title(char id[]="\0");
void mainmenu();
void sign_in(char);
void sign_up();
void que_menu();
void add_que();
void del_que();
void mod_que();
void display_contrb();
void stu_rank();
void stu_menu();
void quiz();
void quiz_menu();
void perf_rep();
void random_quiz(long r=0,int t=0);
void score_updt(int,int);

////////////////////////////////////////////////////////////////////////////
//		      GLOBAL VARIABLE FOR SIGNED IN
char cur_acc[15]="\0";
////////////////////////////////////////////////////////////////////////////
//                       CLASS TO MANAGE QUESTIONS
////////////////////////////////////////////////////////////////////////////

class question
{  int q_no;
   char que[250];
   char op[4][25];
   char contrb[15];
   int topic;
   int ans;

  public:
   void add_qno()
   { cout<<"\n Enter question number: ";
     cin>>q_no;
   }

   void add_q();
   void display_q();
   void modify_q();
   void display_qno()
   {cout<<" Q"<<q_no<<" : ";}

   int get_ans()
    { return ans;}
   int get_q_no()
    { return q_no;}
   char* get_contrb()
    { return contrb;}
   int get_topic()
    { return topic;}

}que;

void question::add_q()
{ cout<<"\n Enter the question:\n  ";
     gets(que);
     strcat(que,"?");
     cout<<"\n Enter the topic number(1.GK, 2.Science, 3.Math) : ";
     cin>>topic;
     for(int i=0;i<4;i++)
     { cout<<"\n Enter option: "<<i+1<<". ";
       gets(op[i]);
     }
     cout<<"\n Enter the correct answer :";
     cin>>ans;
     strcpy(contrb,cur_acc);
     cout<<"\nAdding question...." ;
     delay(1000);

}

void question::display_q()
{
     puts(que);
     cout<<endl<<"\t";
     for(int i=0;i<4;i++)
     { cout<<i+1<<". ";
       puts(op[i]);
       cout<<"\t";
     }
}

void question::modify_q()
{ cout<<"\n The question you want to modify is:\n";
     cout<<"Q"<<q_no<<" : ";
     puts(que);
     cout<<"\n\t";
     int i,a;
     for(i=0;i<4;i++)
     { cout<<i+1<<". ";
       puts(op[i]);
       cout<<"\t";
     }
     cout<<"\n Topic(1.GK,2.Science,3.Math):"<<topic;
     cout<<"\n Answer : "<<ans;

     char q[250],opt[4][25];
     cout<<"\nNew question (Enter '.' to retain old one):\n";
     gets(q);
     cout<<"\n";
     if(strcmp(q,".")!=0)
	strcpy(que,q);
     for(i=0;i<4;i++ )
     { cout<<"New option (Enter '.' to retain old one)"<<i+1<<" : ";
       gets(opt[i]);
       if(strcmp(opt[i],".")!=0)
	 strcpy(op[i],opt[i]);
     }
     cout<<"\nNew answer (Enter 5 to retain old one): ";
     cin>>a;
     if(a==1||a==2||a==3||a==4)
       ans=a;

     cout<<"\nEnter topic (Enter 5 to retain old one): ";
     cin>>a;
     if(a==1||a==2||a==3)
       ans=a;
}


////////////////////////////////////////////////////////////////////////////
//                 	 CLASS TO MANAGE ACCOUNTS
////////////////////////////////////////////////////////////////////////////

class accounts
{  char user_id[15];
   char password[15];
   char name[25];
   long id;


  public:
   char desc;
   void ent_det()
    { cout<<"\t Enter Details:"
	  <<"\n\n\t Name :";
      gets(name);

    }

   void ent_idno()
    { cout<<"\t ID/Registration number:";
      cin>>id;
    }

   void ent_id()
    { cout<<"\n\tEnter Credentials (within 15 characters): "
	  <<"\n\n\t Username :";
      gets(user_id);
    }
   void ent_pwd();

   char* ret_id()
   {return user_id;}

   char* ret_pwd()
   {return password;}

   char* ret_name()
   {return name;}

   long int get_idno()
   {return id;}

}acc;

void accounts::ent_pwd()
{  cout<<"\n\t Password :";
      for(int i=0;i<=15;i++)
       { password[i]=getch();
	 if(password[i]==13)
	    break;
	 cout<<"*";
       }

}

////////////////////////////////////////////////////////////////////////////
//			CLASS TO MANAGE STUDENT REPORT
////////////////////////////////////////////////////////////////////////////

class s_report
{  long s_id;
   int n_test;
   float average;

  public:

   s_report()
   { s_id=0;
     n_test=0;
     average=0.0;
   }

   void ent_id(long id)
   {s_id=id;}

   void updt_avg(float);
   float getavg()
   { return average;}

   void updt_n();
   int getn()
   { return n_test;}

   long int ret_s_id()
   { return s_id;}

}rep;

void s_report::updt_avg(float n)
{ average=(average+n)/2.0;
}

void s_report::updt_n()
{ n_test++;
}


////////////////////////////////////////////////////////////////////////////
//                              MAIN FUNCTION
////////////////////////////////////////////////////////////////////////////


void main()
{  mainmenu();
}

////////////////////////////////////////////////////////////////////////////
//                         FUNCTION DEFINITIONS
////////////////////////////////////////////////////////////////////////////

void inline title(char id[20])
{ clrscr();
  cout<<"\t\t       ----- LETS  QUIZ !!!! -----    \n";
  if(strcmp(id,"\0")!=0)
    cout<<"\t\t\t\t\t\t   -> Signed in as "<<id<<"\n\n\n";
  else
    cout<<"\n\n\n";
}

void mainmenu()
{ while(1)
 {
  clrscr();
  int num;
  title();
  cout<<"Welcome to LETS QUIZ .inc  .\n\n\n"
      <<"Choose your corresponding identity:"
      <<"\n\n 1.Teacher \t\t 2. Student \t\t 3.Exit \n\n :-> ";
  cin>>num;

  switch(num)
  { case 1  : title();
	      menu2:
	      cout<<"\t 1. SIGN IN \t 2. SIGN UP\n\n  :-> ";
	      cin>>num;
	      if(num==1)
	       { sign_in('t');}
	      else if(num==2)
	       { acc.desc='t';
		 sign_up();}
	      else
	       {  cout<<"Wrong choice !";
		  delay(3000);
		  goto menu2;}
	      break;

    case 2  : title();
	      menu3:
	      cout<<"\t 1. SIGN IN \t 2. SIGN UP\n\n  :-> ";
	      cin>>num;
	      if(num==1)
	       { sign_in('s'); }
	      else if (num==2)
	       { acc.desc='s';
		 sign_up();}
	      else
	       {  cout<<"Wrong choice !";
		  delay(3000);
		  goto menu3;}
	      break;
    case 3  : exit(0);
    default : cout<<"Wrong choice ! Try Again."; delay(2000);

   }
 }
}

void sign_up()
{ title();
  char found;
  acc.ent_det();
  cout<<"\n\n";
  while(1)
  { found='f';
    acc.ent_idno();
    acc.ent_id();
    accounts a;
    ifstream f_acc("accounts.dat",ios::in|ios::binary);
    while(f_acc.read((char*)&a,sizeof(a)))
    { if((strcmp(acc.ret_id(),a.ret_id())==0)||(a.get_idno()==acc.get_idno()))
	{ cout<<"\nThis username/ID/R.no. already exists. Try a different one.\n\n";
	  delay(2000);
	  found='t';break;
	}
    }
    f_acc.close();
    if(found=='f')
	break;

  }

  acc.ent_pwd();
  ofstream f_acc("accounts.dat",ios::app|ios::binary);
  f_acc.write((char*)&acc,sizeof(acc));
  f_acc.close();
  if(acc.desc=='s')
  {  ofstream f_rep("report.dat",ios::app|ios::binary);
     s_report r;
     long rno=acc.get_idno();
     r.ent_id(rno);
     f_rep.write((char*)&r,sizeof(r));
     f_rep.close();
  }
  cout<<"\n\nThankyou for joining us. ";
  delay(3000);

}

void sign_in(char ch)
{ title();
  accounts a;
  char found='f';
  int i=0;
  ifstream f_acc("accounts.dat",ios::in|ios::binary);
  a.ent_id();

  while(f_acc.read((char*)&acc,sizeof(acc)))
  { if((strcmp(a.ret_id(),acc.ret_id())==0)&&(ch==acc.desc))
    {  pwd:
       cout<<"\n\tAccount holder - "<<acc.ret_id()<<" - Enter your, \n";
       a.ent_pwd();
       if(strcmp(a.ret_pwd(),acc.ret_pwd())==0)
	{  cout<<"\n\n\t SUCCESSFUL LOGIN";
	   found='t';
	   strcpy(cur_acc,acc.ret_id());
	   delay(2000);
	   if(acc.desc=='t')
	     que_menu();
	   else if(acc.desc=='s')
	     stu_menu();
	   exit(0);
	}
	else
	{  cout<<"\n\nIncorrect password!\n";delay(1000);
	   i++;
	   if(i<3)
	     goto pwd;
	   else
	     exit(0);
	}
    }

  }
  if(found=='f')
    { cout<<"\n\nAccount NOT found!  Try again.";delay(1000);}

  f_acc.close();

}

////                      TEACHER RELATED FUNCTIONS

void que_menu()
{ title();
  int choice;
  while(1)
  { title(cur_acc);
    char ch='y';
    cout<<"\n\nWhat would you like to do?";
    cout<<"\nMENU :\n\t 1.Add a question to question reservoir."
	<<	  "\n\t 2.Delete a question."
	<<        "\n\t 3.Modify a question."
	<<        "\n\t 4.View your previous contributions."
	<<        "\n\t 5.View ranking of registered students."
	<<        "\n\t 6.Sign out and exit to main menu.\n\n\t:";
    cin>>choice;
    switch(choice)
    { case 1: while(ch=='y')
	      { title(cur_acc);
		add_que();
		cout<<"\nWant to continue?(y/n) :";
		cin>>ch;
	      }
	      break;
      case 2: while(ch=='y')
	      { title(cur_acc);
		del_que();
		cout<<"\nWant to continue?(y/n) :";
		cin>>ch;
	      }
	      break;
      case 3: while(ch=='y')
	      { title(cur_acc);
		mod_que();
		cout<<"\nWant to continue?(y/n) :";
		cin>>ch;
	      }
	      break;
      case 4: title(cur_acc);
	      display_contrb();
	      cout<<"\n Press Enter to continue.";
	      getch();
	      break;
      case 5: stu_rank();
	      break;
      case 6: mainmenu();
	      break;
     default: cout<<"Wrong choice!Try again;";
	      delay(2000);
  }
 }



}

void add_que()
{ question q;
  char found;
  while(1)
  { q.add_qno();
    ifstream fin("question.dat",ios::in|ios::binary);
    found='f';
    while(fin.read((char*)&que,sizeof(que)))
    { if(q.get_q_no()==que.get_q_no())
      { cout<<"\n\nThis que no. already exists.Enter different one.\n";
	delay(3000);
	found='t';
	break;
      }
    }
    if(found=='f')
      break;

    fin.close();
  }
  q.add_q();

  ofstream f_que("question.dat",ios::app|ios::binary);
  f_que.write((char*)&q,sizeof(q));
  cout<<"\nThankyou for adding a question!";
  f_que.close();
}

void del_que()
{ ifstream f_que("question.dat",ios::in|ios::binary);
  ofstream temp("temp.dat",ios::out|ios::binary);
  int qno;
  question q;
  char found='f',confirm='n';
  cout<<"Enter the Q.no. of question to be deleted : ";
  cin>>qno;
  while(f_que.read((char*)&q,sizeof(q)))
  { if(q.get_q_no()==qno)
    { q.display_qno();
      q.display_q();
      cout<<"Answer is :"<<q.get_ans();
      cout<<"Topic(1.GK, 2.Science, 3.Math)"<<q.get_topic();
      found='t';
      cout<<"\nAre you sure you want to delete this question?(y/n)";
      cin>>confirm;
      if(confirm=='n')
	temp.write((char*)&q,sizeof(q));
    }
    else
    { temp.write((char*)&q,sizeof(q));
    }

  }
  if(found=='f')
     cout<<"Record not found!";
  f_que.close();
  temp.close();
  remove("question.dat");
  rename("temp.dat","question.dat");
}

void mod_que()
{ fstream f_que("question.dat",ios::in|ios::out|ios::binary);
  int qno;
  question q;
  long pos;
  char found='f';
  cout<<"Enter the Q.no. of question to be modified. :";
  cin>>qno;
  while(!f_que.eof())
  { pos=f_que.tellg();
    f_que.read((char*)&q,sizeof(q));
    if(q.get_q_no()==qno)
    { q.modify_q();
      found='t';
      f_que.seekg(pos);
      f_que.write((char*)&q,sizeof(q));
      break;

    }

  }
  if(found=='f')
     cout<<"Record not found!";
  f_que.close();

}

void display_contrb()
{ ifstream f_que("question.dat",ios::in|ios::binary);
  int i=0;
  while(f_que.read((char*)&que,sizeof(que)))
  { if(strcmp(cur_acc,que.get_contrb())==0)
     { if(i==2)
	{ cout<<"\n\n Press Enter to move to next page.";
	  getch();
	  title(cur_acc);
	  i=0;
	}
       cout<<"\n";
       que.display_qno();
       que.display_q();
       cout<<"Answer is : "<<que.get_ans();
       cout<<"\nTopic(1.GK, 2.Science, 3.Math) : "<<que.get_topic()<<"\n";
       i++;
     }
  }
  f_que.close();
}

void stu_rank()
{ title(cur_acc);

  cout<<"\n\n"<<"The Registered students and thier average scores are as follows:";
  cout<<"\n\n\t NAME \t   AVERAGE SCORE";
  ifstream f_acc("accounts.dat",ios::in|ios::binary);
  while(f_acc.read((char*)&acc,sizeof(acc)))
  { if(acc.desc=='s')
    { ifstream f_rep("report.dat",ios::in|ios::binary);
      while(f_rep.read((char*)&rep,sizeof(rep)))
      { if(acc.get_idno()==rep.ret_s_id())
	  { cout<<"\n"<<setw(15)<<acc.ret_name();
	    cout<<"\t\t"<<rep.getavg();
	  }
      }
    }
  }

  cout<<"\n\nPress Enter to continue.";
  getch();

}

////                 	  STUDENT REALTED FUNCTIONS


void stu_menu()
{ title();
  int choice;
  while(1)
  { title(cur_acc);
    char ch='y';
    cout<<"\n\nWhat would you like to do?";
    cout<<"\nMENU :\n\t 1.Take up a quiz."
	<<	  "\n\t 2.View performance report."
	<<        "\n\t 3.Sign out and exit to main menu.\n\n\t:";
    cin>>choice;
    switch(choice)
    { case 1: while(ch=='y')
	      { title(cur_acc);
		quiz_menu();
		cout<<"\nWant to test yourself again?(y/n) :";
		cin>>ch;
	      }
	      break;
      case 2: title(cur_acc);
	      perf_rep();
	      cout<<"\nPress enter to continue.";
	      getch();

	      break;
      case 3: mainmenu();
	      break;
     default: cout<<"Wrong choice!Try again;";
	      delay(2000);
  }
 }
}


void quiz_menu()
{ title(cur_acc);
  int num,n;
  cout<<"\tChoose your type of quiz...\n"
      <<"\n\n\t 1.Generate a random questionnaire."
      <<  "\n\t 2.Questions by reknowned teachers."
      <<  "\n\t 3.Topic based questionnaire."
      <<  "\n\t 4.Return to previous menu.\n\n\t:";
  cin>>num;

  switch(num)
  { case 1:
      random_quiz();
      break;

    case 2:
      title(cur_acc);
      long int t_id;
      cout<<"\t Choose one of the following teachers and enter their ID:\n";

      ifstream f_acc("accounts.dat",ios::in|ios::binary);
      while(f_acc)
      { f_acc.read((char*)&acc,sizeof(acc));
	if(acc.desc=='t')
	{ cout<<"\n"<<setw(20)<<acc.ret_name();
	  cout<<"\t"<<acc.get_idno();
	}
      }

      f_acc.close();
      cout<<"\n\n \t ID: ";
      cin>>t_id;
      random_quiz(t_id);
      break;

    case 3:
      title(cur_acc);
      int t;
      cout<<"\n\n Enter one of the following topic numbers."
	  <<"\n\n\t 1. GK (A mix of general knowledge question)"
	  <<  "\n\t 2. Science (Questions from varied scientific fields)"
	  <<  "\n\t 3. Math (Intriguing math questions)\n :";
      cin>>t;
      random_quiz(0,t);
      break;

    case 4:
      stu_menu();
      break;
    default:
      cout<<"Wrong choice !!!";
      delay(2000);
      exit(0);


  }
}


void random_quiz(long r, int t)
{ int arr[50],a[50],cnt=0,k,j,num,flag,ans[50],score=0,n;
  // arr[] holds all question numbers, a[] will hold the questions already shown.
  ifstream f_que("question.dat",ios::in|ios::binary);
  char t_uid[15];

  for(int i=0;i<50;i++)
     a[i]=-1;


  if(r!=0)
  { ifstream f_acc("accounts.dat",ios::in|ios::binary);
    while(f_acc.read((char*)&acc,sizeof(acc)))
    { if(r==acc.get_idno())
	{ strcpy(t_uid,acc.ret_id());
	  break;
	}
    }
    f_acc.close();
  }

  while(f_que.read((char*)&que,sizeof(que)))
  { if((r!=0)&&(strcmp(t_uid,que.get_contrb())==0))
    { arr[cnt]=que.get_q_no();
      cnt++;

    }
    else if(que.get_topic()==t)
    { arr[cnt]=que.get_q_no();
      cnt++;
    }
    else if(r==0&&t==0)
    { arr[cnt]=que.get_q_no();
      cnt++;
    }
  }

  f_que.close();

  cout<<"\nWe have "<<cnt<<" questions of your chosen type available.\n";
  cout<<"Enter no. of questions : ";
  cin>>n;

  if(cnt<n)
  { cout<<"Sorry, We have only "<<cnt<<" questions available.";
    delay(2000);
    quiz_menu();
  }
  randomize();

  title(cur_acc);

  for(k=0;k<n;)
  { num=arr[random(cnt)];
    flag=0;

    for(j=0;j<=k;j++)
      if(a[j]==num)
	flag=1 ;

    if(flag==1)
      continue;

    else
    { a[k]=num;
      title(cur_acc);
      cout<<"\n  Q."<<k+1<<"  ";
      ifstream f_que("question.dat",ios::in|ios::binary);
      while(f_que.read((char*)&que,sizeof(que)))
      { if(que.get_q_no()==a[k])
	{ que.display_q();
	  cout<<"\n\n  Enter answer : ";
	  cin>>ans[k];

	  if(ans[k]==que.get_ans())
	    score++;
	}
      }
      f_que.close();
      k++;
    }
  }

  score_updt(score,n);
  cout<<"\n\t Your score was "<<score<<" out of "<<n;
  cout<<"\n\t Your average for the test was "<<((float)score/n)*100<<"%\n";

}


void score_updt(int sc,int no)
{ title(cur_acc);
  float s=sc,avg;
  avg= (s/no)*100;
  long rno=0,pos;

  ifstream f_acc("accounts.dat",ios::in|ios::binary);
  while(f_acc.read((char*)&acc,sizeof(acc)))
  { if(strcmp(acc.ret_id(),cur_acc)==0)
      rno=acc.get_idno();
  }
  f_acc.close();

  fstream f_rep("report.dat",ios::in|ios::out|ios::binary);
  f_rep.seekg(0);
  while(!f_rep.eof())
  { pos=f_rep.tellg();
    f_rep.read((char*)&rep,sizeof(rep));
    if(rno==rep.ret_s_id())
    { rep.updt_avg(avg);
      rep.updt_n();
      f_rep.seekg(pos);
      f_rep.write((char*)&rep,sizeof(rep));
      break;
    }
  }
  f_rep.close();
}


void perf_rep()
{ ifstream f_rep("report.dat",ios::in|ios::binary);
  long rno;

  ifstream f_acc("accounts.dat",ios::in|ios::binary);
  while(f_acc.read((char*)&acc,sizeof(acc)))
  { if(strcmp(acc.ret_id(),cur_acc)==0)
      rno=acc.get_idno();
  }
  f_acc.close();

  while(f_rep.read((char*)&rep,sizeof(rep)))
  { if(rno==rep.ret_s_id())
    {  cout<<"\n\n Your quizzing history is as follows:" ;
       cout<<"\n\n\t Number of tests taken: "<<rep.getn()
	   <<  "\n\t Average score : "<<rep.getavg()<<"%";
       break;
    }
  }
  f_rep.close();

}