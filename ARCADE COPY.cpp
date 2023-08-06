//  ****************************
//  * COMPUTER SCIENCE PROJECT *
//  *      ON HANDLING FILE    *
//  *   OF  THE GAME PLAYERS   *					        
//  ****************************

//  *******************************
//  * GAME PARLOUR : PLAY ZONE 47 *
//  *******************************

//  ******************************
//	*     HEADER FILES USED      *
//  ******************************

#include<fstream>        //For reading and writing files
#include<conio.h>        //For clrscr()
#include<stdio.h>        //For gets and puts function
#include<string.h>       //For string values
#include<process.h>      //For exit function
#include<iostream>       //For console input/output operations
#include<map>

using namespace std;
// using std::cout;
// using std::cin;

//  ******************************************
//  *   CLASS FOR PLAYER REQUIRED DEATAILS   *
//  ******************************************

// CLASS STRUCTURE OF  PLAYER 

class player
{ 
  int player_code;
  int player_credit_card_number;
  int player_credit_card_amount;
  char date_of_renewal[10];
  char date_of_expiry[10];
  char player_name[30];

  public:
  
  player()
  { 
            player_code=0;  
            player_credit_card_number=0; 
            player_credit_card_amount=0; 
            strcpy(player_name,"NULL");
            strcpy(date_of_expiry,"NULL");
            strcpy(date_of_renewal,"NULL");

  }

  // ~player(){ std::cout << "\n\nEnd of player variable's scope\n"<<std::endl; }

  void entry_player();
  void update_credit();
  void view_player();
  void view_all();
  void delete_player();
  void tofile(player p);
  void display();
  void trash_read();
} p;

//  ******************************************
//  *         FUNCTION PROTOTYPES            *
//  ******************************************

void recent_display();
void delete_database();
void restore_from_trash();
void clear_trash();


// LIST OF FUNCTIONS / OPERATIONS ON THE DATABASE OPERATIONS
/*

  0.  MAIN DRIVER FUNCTION WITH MENU
  1.  FUNCTION TO ENTER DATA FOR PLAYER
  2.  FUNCTION TO WRITE DATA TO FILE
  3.  FUNCTION TO DISPLAY CONTENTS OF OBJECT
  4.  FUNCTION TO VIEW ALL PLAYERS IN FILE
  5.  FUNCTION TO DISPLAY THE RECENTLY ACCESSED RECORDS
  6.  FUNCTION TO VIEW A SINGLE PLAYER 
  7.  FUNCTION TO UPDATE THE CREDIT AMOUNT OF PLAYER
  8.  FUNCTION TO DELETE THE RECORD OF SINGLE PLAYER
  9.  FUNCTION TO DELETE THE COMPLETE DATDBASE
  10. FUNCTION TO READ TRASH
  11. FUNCTION TO RESTORE DELETED RECORDS FROM THE TRASH 
  12. FUNCTION TO CLEAR THE TRASH
  13. EXIT THE DATABASE

*/


//  MAP TO STORE ALL RECENTLY ACCESSED DATA

std::map<int,player> recent;


// 0. MAIN DRIVER FUNCTION WITH MENU

int main()  
{ 
  system("CLS");
  bool status=true;

  while(status) 
  {
   system("CLS"); 
   
   std::cout << "****************************************************************" << std::endl;
   std::cout << "*                 ARCADE FILE SYSTEM MANAGMENT                 *" << std::endl;
   std::cout << "****************************************************************" << std::endl;

   std::cout << "1.  ENTER NEW PLAYER DATA "       << std::endl; 
   std::cout << "2.  SEARCH A PLAYER DATA "        << std::endl; 
   std::cout << "3.  DISPLAY ALL PLAYERS DATA "    << std::endl; 
   std::cout << "4.  RECENT ACCESSES "             << std::endl; 
   std::cout << "5.  UPDATE CREDIT CARD AMOUNT "   << std::endl; 
   std::cout << "6.  DELETE A PLAYER DATA "        << std::endl; 
   std::cout << "7.  DELETE ALL PLAYER DATA "      << std::endl; 
   std::cout << "8.  DISPLAY CONTENETS OF TRASH "  << std::endl; 
   std::cout << "9.  RESTORE ALL DELETED DATA "    << std::endl; 
   std::cout << "10. CLEAR TRASH FILE "            << std::endl; 
   std::cout << "11. EXIT THE DATABASE "           << std::endl; 

   int n;
   std::cout << "\nENTER A CHOICE : " ;  std::cin>> n; 
   switch(n)
   {
      case 1:  {  p.entry_player();      } break;
      case 2:  {  p.view_player();       } break;
      case 3:  {  p.view_all();          } break;
      case 4:  {  recent_display();      } break;
      case 5:  {  p.update_credit();     } break;
      case 6:  {  p.delete_player();     } break;
      case 7:  {  delete_database();     } break;
      case 8:  {  p.trash_read();        } break;
      case 9:  {  restore_from_trash();  } break;
      case 10: {  clear_trash();         } break;
      case 11: {  status=false;          } break;
      default: {  std::cout<<"\nINVALID INPUT\nENTER VALUES BETWEEN 1 TO 11\n\n";  } break;
   }   
  }
  
   
  std::cout << "\nHIT ENTER TO EXIT !!!  "; 
  getch ();
  system("CLS");
  return 0;
  
}


// 1. FUNCTION TO ENTER DATA FOR PLAYER

void player::entry_player()
{ 
   
   std::cout<<"Enter Player's CODE :";
   std::cin>>p.player_code;
   std::cin.ignore();
   
   std::cout<<"Enter Player's NAME :";
   gets_s(p.player_name);
   
   std::cout<<"Enter Player's 10-digit CREDIT CARD NUMBER :";
   char s[10];     std::cin>>s;    
   int n=atoi(s);
   p.player_credit_card_number=n;
   std::cin.ignore();

   std::cout<<"Enter CREDIT AMOUNT: (0-9999)";
   char q[4];     std::cin>>q;    
   int m=atoi(q);
   p.player_credit_card_amount=m;
   std::cin.ignore();

   std::cout<<"Enter Player's Credit Card's DATE OF RENEWAL:";
   gets_s(p.date_of_renewal);
   
   std::cout<<"Enter Player's Credit Card's DATE OF EXPIRY :";
   std::cin.ignore();
   gets_s(p.date_of_expiry);
   
   tofile( p);
   
   recent[p.player_code]=p;
   
   std::cout<<"Player data loaded successfully to file" << std::endl;
   
   std::cout<<"\n\n( Hit enter to continue to menu )"<<std::endl;
   
   getch();
  
}


// 2. FUNCTION TO WRITE DATA TO FILE

void player::tofile(player p)
{ 
  ofstream ofile;
  
  ofile.open("ply",ios::app);
  ofile.write((char*)&p,sizeof(p));
  ofile.close();
}


// 3. FUNCTION TO DISPLAY CONTENTS OF OBJECT

void player::display()
{
  
  std::cout<<"\nPlayer's CODE :" << player_code;
  std::cout<<"\nPlayer's NAME :" << this->player_name;
  std::cout<<"\nPlayer's CREDIT CARD NUMBER :"<<this->player_credit_card_number;
  std::cout<<"\nEnter Player's Credit Card's DATE OF RENEWAL:"<<this->date_of_renewal;
  std::cout<<"\nEnter Player's Credit Card's DATE OF EXPIRY :"<<this->date_of_expiry;
  
}


// 4.  FUNCTION TO VIEW ALL PLAYERS IN FILE

void player::view_all()
{  
  system("CLS");

   std::cout << "****************************************************************" << std::endl;
   std::cout << "*                   ZONE 47 PLAYER DATABASE                    *" << std::endl;
   std::cout << "****************************************************************" << std::endl;
  
  ifstream fin;
  
  fin.open("ply");
  fin.seekg(0,ios::beg);
  fin.read((char*)&p,sizeof(p));
  int n=0;
  while(fin)
  { 
       
       std::cout<<std::endl;
       p.display();
       std::cout<<std::endl;
       fin.read((char*)&p,sizeof(p));
       n++;
  }
  if(n==0) std::cout<<"\nRECORDS ARE EMPTY"<<std::endl;
  fin.close();
  std::cout<<"\n\n( Hit enter to continue to menu )"<<std::endl;
  getch();
}


// 5. FUNCTION TO DISPLAY THE RECENTLY ACCESSED RECORDS 

void recent_display()
{
  std::map<int,player>::iterator it=recent.begin();
  if(it==recent.end()) { std::cout<<"NO RECENT ACCESSED RECORDS \n\n"; }
  for ( it=recent.begin(); it!=recent.end(); ++it)
  {

    std::cout << it->first << std::endl;
    it->second.display() ;
  }

  std::cout<<"\n\n( Hit enter to continue to menu )"<<std::endl;
  getch();

}


// 6. FUNCTION TO VIEW A SINGLE PLAYER

void player::view_player()
{  
   int pcd;
   std::cout <<"\nEnter player code to search for:";
   std::cin>>pcd;
   
  ifstream fin;
  fin.open("ply");
   fin.seekg(0,ios::beg);
   fin.read((char*)&p,sizeof(p));
   int n=0;
   while(fin)
   { 
      if(pcd==p.player_code)    
      {
        std::cout<<"\nPLAYER FOUND"<<std::endl;
        p.display();
        break;
        n++;
      }
      else fin.read((char*)&p,sizeof(p));
  }
  if(n==0) std::cout<<"\nPLAYER NOT FOUND"<<std::endl;

  std::cout<<"\n\n( Hit enter to continue to menu )"<<std::endl;
  getch();

   fin.close();
}


// 7. FUNCTION TO UPDATE THE CREDIT AMOUNT OF PLAYER

void player::update_credit()
{
  
   int n=0;
  std::cout<<"\nEnter Player's code to update credit card number: "; std::cin>>n;
   
  fstream fin;
  fin.open("ply",ios::in|ios::out);
   fin.seekg(0,ios::beg);
   fin.read((char*)&p,sizeof(p));
   while(fin)
   { 
      if(n==p.player_code)    
      {
        std::cout<<"\nPLAYER FOUND"<<std::endl;
        int a=fin.tellg();
        p.display();
        std::cout<<"Enter CREDIT AMOUNT: (0-9999)";
        char q[4];     std::cin>>q;    
        int m=atoi(q);
        std::cin.ignore();
        p.player_credit_card_amount+=m;
        fin.seekg(a*(sizeof(p)),ios::beg);
        fin.write((char *)&p,sizeof(p));
        break;
        n++;
      }
      else fin.read((char*)&p,sizeof(p));
  }
  if(n==0) std::cout<<"\nPLAYER NOT FOUND"<<std::endl;

  std::cout<<"\n\n( Hit enter to continue to menu )"<<std::endl;
  getch();

   fin.close();
}


// 8. FUNCTION TO DELETE THE RECORD OF SINGLE PLAYER

void player::delete_player()
{
  ifstream fin;
  ofstream fout;
  fin.open("ply");
  fout.open("trash",ios::app);
  int pcd;
  std::cout<<"\nEnter Player's code to update credit card number: "; std::cin>>pcd;
   fin.seekg(0,ios::beg);
  fin.read((char*)&p,sizeof(p));
   int n=0;
   while(fin)
   { 
      if(pcd== player_code)    
      {
        std::cout<<"\nPLAYER FOUND"<<std::endl;
        display();
        break;
        n++;
      }
      else fin.read((char*)&p,sizeof(p));
  }
  if(n==0) std::cout<<"\nPLAYER NOT FOUND"<<std::endl;

  std::cout<<"\n\n( Hit enter to continue to menu )"<<std::endl;
  getch();

   fin.close();

}


// 9. FUNCTION TO DELETE THE COMPLETE DATDBASE

void delete_database()
{
  ifstream fin;
  ofstream fout;
  fin.open("ply");
  fout.open("trash",ios::app);
  fin.seekg(0,ios::beg);
  fin.read((char*)&p,sizeof(p));
  int n=0;
  while(fin)
  { 
       fout.write((char*)&p,sizeof(p));
       n++;
  }
  fin.close();
  fout.close();
  if(n==0) 
  {
    std::cout<<"\nRECORDS ARE EMPTY"<<std::endl;
    std::cout<<"NO RECORDS MOVED TO TRASH !!!"<<std::endl;
    std::cout<<"\n\n( Hit enter to continue to menu )"<<std::endl;
    return;
    getch();
  }
  remove("ply");

  std::cout<<"ALL RECORDS MOVED TO TRASH !!!"<<std::endl;

  std::cout<<"\n\n( Hit enter to continue to menu )"<<std::endl;
  getch();
}


// 10. FUNCTION TO READ TRASH

void player::trash_read()
{
  ifstream fin;
  
  fin.open("trash");
  fin.seekg(0,ios::beg);
  fin.read((char*)&p,sizeof(p));
  int n=0;
  while(fin)
  { 
       
       std::cout<<std::endl;
       p.display();
       std::cout<<std::endl;
       fin.read((char*)&p,sizeof(p));
       n++;
  }
  if(n==0) std::cout<<"\nTRASH IS EMPTY"<<std::endl;
  fin.close();
  std::cout<<"\n\n( Hit enter to continue to menu )"<<std::endl;
  getch();
}


// 11. FUNCTION TO RESTORE DELETED RECORDS FROM THE TRASH 

void restore_from_trash()
{

}


// 12. FUNCTION TO CLEAR THE TRASH

void clear_trash()
{

}
