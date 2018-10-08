#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<iomanip.h>
#include<process.h>
#include<dos.h>

int temp;
char file[15];

void list();
void title();
void cursour();

class show
{
	private:
		int scr_no;
		char mov_nam [30];
		char t1[10],t2[10],t3[10];
	public: void entermovie();
		void showmovie();
		void updatemovie();
		char *retmovie()
		{
			return mov_nam;
		}
		int retscr_no()
		{
			return scr_no;
		}
}movdat[3],mov;

void show :: entermovie()
{
	cout<<"Enter the screen no.  : ";
	cin>>scr_no;
	cout<<"Enter the movie name. : ";
	gets(mov_nam);
	cout<<"Enter the 1st show.   : ";
	gets(t1);
	cout<<"Enter the 2nd show.   : ";
	gets(t2);
	cout<<"Enter the 3rd show.   : ";
	gets(t3);
	cout<<endl;
}
void show :: showmovie()
{
	fstream f;
	f.open("C:\\TURBOC3\\Projects\\moviedata.txt",ios::in);
	while(!f.eof())
	{
		f.read((char*)&mov,sizeof(show));
		if(f.eof())
			break;
		cout<<"\n\nScreen no. : "<<scr_no;
		cout<<"\nMovie name.  : "<<mov_nam;
		cout<<"\n1st show.    : "<<t1;
		cout<<"\n2nd show.    : "<<t2;
		cout<<"\n3rd show.    : "<<t3<<endl;
	}
	f.close();
	struct dosdate_t d;
	_dos_getdate(&d);
	struct dostime_t t;
	_dos_gettime(&t);

	int x=d.day;
	int y=d.month;
	int z=d.year;

	cout<<endl;
	int a=t.hour;
	int b=t.minute;
	int c=t.second;
	cout<<"\nBOOKING VALID FROM DATE :"<<x<<"/"<<y<<"/"<<z<<" AND TIME :"<<a<<":"<<b<<":"<<c;
}

void show :: updatemovie()
{
	int sn;
	int i=0;
	ifstream fin("C:\\TURBOC3\\Projects\\moviedata.txt");
	if(fin.fail())
	{
		fstream f1;
		f1.open("C:\\TURBOC3\\Projects\\moviedata.txt",ios::binary | ios::out);
		for(int j=0; j<3; j++)
		{
			mov.entermovie();
			f1.write((char*)&mov,sizeof(show));
		}
		f1.close();
	}
	else
	{
		fstream f;
		mov.showmovie();
		cout<<"\nEnter the screen to update : ";
		cin>>sn;
		f.open("C:\\TURBOC3\\Projects\\moviedata.txt",ios::binary | ios::in | ios::out);
		f.seekg(0);
		while(!f.eof())
		{
			f.read((char*)&mov,sizeof(show));
			if(f.eof())
				break;
			i++;
			if(mov.retscr_no()==sn)
			{
				break;
			}
		}
		f.seekp((i-1)*sizeof(show),ios::beg);
		mov.entermovie();
		f.write((char*)&mov,sizeof(show));
		f.close();
	}
}


class bookticket
{
	private:
		  int ticket_no;
		  int screen_no;
		  char movie_name[30];
		  char date[9];
		  char time[6];
		  float fare;
		  int seat;
public:
		bookticket()
		{
			fare=100;
		}
		void setticno(int n)
		{
			ticket_no=n;
		}
		int retticno()
		{
return ticket_no;
		}
		int retseat()
		{
			return seat;
		}
		void firsttimetic();
		int readtic(char []);
		void settemp(char []);
		int retscreen_no()
		{
			return screen_no;
		}
		void show_create();
		void displayshow_det();
		void delticket();
}btic;

void bookticket :: firsttimetic()
{
	btic.setticno(temp);
}
int bookticket :: readtic(char tn[])
{
	fstream f;
	int x;
	f.open(tn,ios::binary | ios::in);
	while(!f.eof())
	{
		f.read((char*)&btic,sizeof(btic));
		if(f.eof())
			break;
	}

		f.close();
		x=btic.retticno();
  return x;
}
void bookticket :: settemp(char tn[])
{
	fstream f;
	int t;
	f.open(tn, ios::binary | ios::in);
	while(!f.eof())
	{
		f.read((char*)&btic,sizeof(bookticket));
		if(f.eof())
			break;
	}
	t=btic.retticno();
temp=++t;
}

void bookticket :: show_create()
{
	int scrno;
	B:
	cout<<"\nEnter the screen of the movie : ";
	cin>>scrno;
	if(scrno==1 || scrno==2 || scrno==3)
	{
	fstream s;
	s.open("C:\\TURBOC3\\Projects\\moviedata.txt",ios::in);
	while(!s.eof())
	{
		s.read((char*)&mov,sizeof(show));
		if(s.eof())
			break;
		int x=mov.retscr_no();
		if(scrno==x)
		{
			switch(scrno)
			{
				case 1:strcpy(movie_name,mov.retmovie());
					break;
				case 2:strcpy(movie_name,mov.retmovie());
					break;
				case 3:strcpy(movie_name,mov.retmovie());
					break;
				default :cout<<"Enter the correct screen no. : ";
					  break;
			}
		}
	}
	s.close();

	screen_no=scrno;
	cout<<"\tdate (ddmmyyyy):";
	gets(date);
	cout<<"\tshow time :";
	gets(time);

	strcat(file,"C:\\TURBOC3\\Projects\\");
	strcat(file,date);
	strcat(file,time);
	strcat(file,".txt");

	ifstream f1(file);
	if(f1.fail())
	{
		temp=1;
		btic.firsttimetic();
		ticket_no=btic.retticno();
		cout<<"Enter the seat no. : ";
		cin>>seat;
		fstream f;
		f.open(file,ios::binary | ios::out | ios::app);
		f.write((char*)&btic,sizeof(bookticket));
		f.close();
		cout<<"\nTICKET BOOKED\n";
	}
	else
	{
		int st,flag=0;
		A:
		cout<<"Enter the seat no. : ";
		cin>>st;
		fstream s1;
		s1.open(file,ios::binary|ios::in);
		while(!s1.eof())
		{
			s1.read((char*)&btic,sizeof(bookticket));
			if(s1.eof())
				break;
			int x=btic.retseat();
			if(x==st)
			{
				cout<<"\nALREADY BOOKED!\n";
				flag=1;
				break;
			}
			else
			{
				flag=0;
			}
		}
		s1.close();
		if(flag==1)
		{
			goto A;
		}

		btic.settemp(file);
		btic.firsttimetic();
		ticket_no=btic.retticno();
		if(flag==0)
		{
			seat=st;
		}
		cout<<"Your ticket is : \n";
		cout<<"\nTicket no.   : "<<ticket_no;
		cout<<"\nScreen no.   : "<<screen_no;
		cout<<"\nMovie name   : "<<movie_name;
		cout<<"\nDate         : "<<date;
		cout<<"\nTime         : "<<time;
		cout<<"\nSeat no      : "<<seat;
		cout<<"\nFare         : "<<fare;
		cout<<endl<<endl;
		fstream f;
		f.open(file,ios::binary | ios::out | ios::app);
		f.write((char*)&btic,sizeof(bookticket));
		f.close();
		cout<<"\nTICKET BOOKED\n";
	}
	}
	else
	{
	cout<<"\nEnter valid screen no.!";
	goto B;
	}
}

void bookticket :: delticket()
{
	int x;
	fstream f,f1;
	cout<<"\nEnter the date and time of the show to delete.\n";
	cout<<"\ndate (ddmmyyyy):";
	gets(date);
	cout<<"\nshow time :";
	gets(time);

	strcat(file,"C:\\TURBOC3\\Projects\\");
	strcat(file,date);
	strcat(file,time);
	strcat(file,".txt");

	cout<<"\nEnter the ticket no. : ";
	cin>>x;

	f.open(file,ios::in);
	f1.open("C:\\TURBOC3\\Projects\\temp.txt",ios::binary|ios::out);
	while(!f.eof())
	{
		f.read((char*)&btic,sizeof(bookticket));
		if(f.eof())
			break;
		int y=btic.retticno();
		if(y!=x)
		{
			f1.write((char*)&btic,sizeof(bookticket));
		}
	}
 
f.close();
f1.close();
remove(file);
rename("C:\\TURBOC3\\Projects\\temp.txt",file);
cout<<"\nRECORD DELETED!\n";
}

void bookticket :: displayshow_det()
{
	int x,flag=0;
	fstream f;
	cout<<"\nEnter the data(ddmmyyyy) of the show. : ";
	gets(date);
	cout<<"\nEnter the show time. :";
	gets(time);

	strcat(file,"C:\\TURBOC3\\Projects\\");
	strcat(file,date);
	strcat(file,time);
	strcat(file,".txt");

	cout<<"\nEnter the ticket no. : ";
	cin>>x;

	f.open(file, ios::binary | ios::in);
	while(!f.eof())
	{
		f.read((char*)&btic,sizeof(bookticket));
		if(f.eof())
			break;
		if(btic.retticno()==x)
		{
			flag=1;
			break;
		}
		else
		{
			flag=0;
		}
}
	f.close();
		if(flag==1)
		{
			cout<<"\nTicket no.   : "<<ticket_no;
			cout<<"\nScreen no.   : "<<screen_no;
			cout<<"\nMovie name   : "<<movie_name;
			cout<<"\nDate         : "<<date;
			cout<<"\nTime         : "<<time;
			cout<<"\nSeat no      : "<<seat;
			cout<<"\nFare         : "<<fare<<endl<<endl;
 
}
		else
		{
			cout<<"\nTICKET NOT BOOKED\n";
		}
}


 void main()
{
clrscr();
int gdriver = DETECT, gmode, errorcode;
initgraph(&gdriver, &gmode, "C:\\TurboC3\\BGI");

title();
getch();
cursour();

}

void title()
{
 int poly[10];
 poly[0]=150;
 poly[1]=100;

 poly[2]=150;
 poly[3]=300;

 poly[4]=500;
 poly[5]=300;

 poly[6]=500;
 poly[7]=100;

 poly[8]=150;
 poly[9]=100;

 drawpoly(5,poly);
 setfillstyle(1,BLUE);
 fillpoly(5,poly);
 setcolor(YELLOW);
 settextstyle(0,0,12);
 outtextxy(190,160,"P");
 settextstyle(0,0,12);
 outtextxy(284,160,"V");
 settextstyle(0,0,12);
 outtextxy(378,160,"R");
}
 void list()
  {
   cleardevice();
   setcolor(WHITE);
   settextstyle(0,0,2);
   outtextxy(200,180,"BOOK A TICKET");
   settextstyle(0,0,2);
   outtextxy(200,210,"CANCEL A TICKET");
   settextstyle(0,0,2);
   outtextxy(200,240,"DISPLAY TICKET");
   settextstyle(0,0,2);
   outtextxy(200,270,"ADMINISTRATOR");
   settextstyle(0,0,2);
   outtextxy(200,300,"EXIT");
   settextstyle(0,0,0);
   outtextxy(200,340,"PRESS 'w' TO SCROLL DOWN.");
   outtextxy(200,360,"PRESS 's' TO SCROLL DOWN.");
   int poly[10];
	poly[0]=160;
	poly[1]=155;

	poly[2]=160;
	poly[3]=330;

	poly[4]=450;
	poly[5]=330;

	poly[6]=450;
	poly[7]=155;

	poly[8]=160;
	poly[9]=155;

	drawpoly(5,poly);
  }

void cursour()
  {
   int x=180,y=185;
   char ch='w';
   while(ch=='w' || ch=='s' || ch==13)
	{
	 A:
	 list();
	 settextstyle(0,0,1);
	 setcolor(GREEN);
	 outtextxy(x,y,"¯");
	 ch=getch();

	 if(ch=='w')
	   {
	    cleardevice();
	    if(y==185)
	      {
	       y=335;
	      }
	    y=y-30;
	    goto A;
	   }

	 else if(ch=='s')
	   {
	    cleardevice();
	    if(y==305)
	      {
	       y=155;
	      }
	    y=y+30;
	    goto A;
	   }
	 else if(ch==13)
	 {
		if(y==185)
		{
			cleardevice();
			mov.showmovie();
			btic.show_create();
			getch();
		}
		else if(y==215)
		{
			cleardevice();
			mov.showmovie();
			btic.delticket();
			getch();
		}
		else if(y==245)
		{
			cleardevice();
			mov.showmovie();
			btic.displayshow_det();
			getch();
		}
		else if(y==275)
		{
			ifstream fin("C:\\TURBOC3\\Projects\\moviedata.txt");
			if(fin.fail())
			{
				cleardevice();
				fstream f;
				f.open("C:\\TURBOC3\\Projects\\moviedata.txt",ios::binary| ios::out);
				for(int i=0; i<3; i++)
				{
				       mov.entermovie();
				       f.write((char*)&mov,sizeof(show));
				}
				f.close();
			}
			else
			{
				cleardevice();
				mov.updatemovie();
			}
			mov.showmovie();

			getch();
		}
		else if(y==305)
		{
			break;
		}
	 }
	}
  }
