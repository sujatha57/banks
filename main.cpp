/*Created on 11 Oct 2021
Copy rigths By K.sujatha*/

//The preprocessor segment including the required files during the compilatuion
#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>

//additional namespaces requiured
using namespace std;

//declaration of local funtions
void aboutBank();
void mainMenu();

//Declaring  Parent class
class Banking
{
  public:
      ///Declaring Variables
      int ac_no=100;//initializing Account no. to 100
      char cust_nm[50], ac_type[7];
      float bal;  

  public:
      //Declaring Member funtions
      void createAccount(){}     
      void deposit(float){}
	    void withdraw(float){}

      void display()
      { 
        cout<<"\n\n Accout No. : "<<ac_no;
        cout<<"\n Name : "<<cust_nm;        
        cout<<"\n Account Type : "<<ac_type;
        cout<<"\n Balance : "<<bal;
        cout<<"\n";  
      }
      

};

//Declaring child class
class Operations : public Banking
{
  protected:
    int bal1;
    int wit_dr;

  public:
      
      //This function used to Create an account for a customer
      void createAccount()
      {
        char inp1_acc[8]="Savings",inp2_acc[8]="Current";

        cout<<"\nPlease enter your Details\n--------------------------------\n";
        ac_no++;//Automatically increments account no. each time the f. is called
        cout<<"\nAccout Number : "<<ac_no<<endl;
        cout<<"Name : ";
        cin.ignore();
        cin.getline(cust_nm,50);
        

        //Checking the account type
        while(1)
        {
          cout<<"Account Type : ";
          cin>>ac_type;
          if(strcmp(inp1_acc,ac_type)==0 || strcmp(inp2_acc,ac_type)==0 )
          {
            break;
          }
          else
          {
            cout<<"\nPlease enter the correct account type\n";
          }
        } 
        
        //Balance Entry
        while(1)
        {
          cout<<"Balance : ";
          cin>>bal;
          if(bal>0)
          {
            break;
          }
          else
          {
            cout<<"Balance cannot be in negative. Type correct balance\n";       
          }
        }       

        cout<<"\nCongratulations your account has been successfully created";
      }      

      //Deposite fn. performs deposite operation
      void deposit(float x)
      {
        bal1=x;
        bal = bal+bal1;
      }

      //Withdraw fn. performs withdraw operation
      void withdraw(float x)
      {		
        wit_dr=x;
        if(wit_dr>bal)
          cout<<"\nCannot Withdraw Amount, Amout is greater than balance";
        bal = bal-wit_dr;		
      }

      //Returns the account no.
      int retacno() const
      {
        return ac_no;
      }

};


//declaration of local funtions
void deposit_fn(int , Operations);
void withdraw_fn(int , Operations);
void display_fn(int , Operations);
void allCust(Operations);
void closeAcc_fn(int ac,Operations o);


int main()
{
  int w_ch;
  cout<<"\n\nHi, Welcome to HARMAN Bank";
  cout<<"\n1.Main Menu";
  cout<<"\n2.About Us\n";
  cin>>w_ch;
  if(w_ch==2)
  {
    aboutBank();
  }
  else if(w_ch==1)
  {
    mainMenu();
  }
}

void aboutBank()
{
  cout<<"\nHARMAN Bank is a leading private sector bank in India. The Bank’s consolidated total assets stood at Rs. 14.76 trillion at September 30, 2020.  HARMAN Bank currently has a network of 5,288 branches and 15,158 ATMs across India.";
  cout<<"\nHARMAN Bank was originally promoted in 1994 by HARMAN Limited, an Indian financial institution, and was its wholly-owned subsidiary.";
  cout<<"\nHARMAN Bank offers a wide range of banking products and financial services to corporate and retail customers through a variety of delivery channels and through its group companies.";
  cout<<"\nHARMAN Bank's Board members include eminent individuals with a wealth of experience in international business, management consulting, banking and financial services.";
  cout<<"\nAll the latest, in-depth information about HARMAN Bank's financial performance and business initiatives.";
  cout<<"\nExplore diverse openings with HARMAN Bank.";
  cout<<"\nTime and again our innovative banking services has been recognized and rewarded world over.";
  cout<<"\nCatch up with HARMAN Bank's latest business and social initiatives, as well as innovative product launches.";
  cout<<"\nHARMAN Bank is deeply engaged in human and economic development at the national level. The Bank works closely with HARMAN Foundation across diverse sectors and programs.";
  cout<<"\nCatch up with HARMAN Bank's latest communication related to Acknowledgements, information on regulatory notices, banking ombudsman schemes and others.";
}

void mainMenu()
{
  Operations o;//child class object creation  
  int op,ac;
  ofstream fileWrite;
  while(1)
  {
    cout<<"\nMAIN MENU\n------------\n";
    cout<<"\n1.New Account";
    cout<<"\n2.Deposit Amount";
    cout<<"\n3.Withdraw Amount";
    cout<<"\n4.Customer Details";
    cout<<"\n5.Show all Bank Customers";
    cout<<"\n6.Close Account";   
    cout<<"\n7.Exit";
    cout<<"\n\nSelect Your Option: ";
    cin>>op;    

    switch(op)
    {
    case 1:
      fileWrite.open("Details.dat",ios::binary|ios::app);
      o.createAccount();
      fileWrite.write((char *) (&o), sizeof(Operations));
      fileWrite.close();
      break;
    case 2:
      cout<<"\n\nPlease enter your account No. : "; 
      cin>>ac;
      deposit_fn(ac,o);        
      break;
    case 3:
      cout<<"\n\nPlease enter your account No. : "; 
      cin>>ac;
      withdraw_fn(ac,o);
      break;      
    case 4:      
      cout<<"\n\nPlease enter your account No. : "; 
      cin>>ac;
      display_fn(ac,o);
      break;      
    case 5:
      allCust(o);
      break;      
    case 6:      
      cout<<"\n\nPlease enter your account No. : ";
      cin>>ac;
      closeAcc_fn(ac,o);
      break;          
    case 7:     
      cout<<"\n\nThank You for using our Bank";
      exit(0);
      break;
    default :cout<<"\nInvalid option";
    }      
  }
}

//Used to extract data from file and perform deposite operations
void deposit_fn(int ac, Operations o)
{
  ofstream fileWrite;
  fileWrite.open("Details.dat",ios::binary|ios::in|ios::out);
  float dp;
  bool flag=false;
  while(!fileWrite.eof() && flag==false)
	{
    if(o.retacno()==ac)
		{
      
    cout<<"\n\nHello "<<o.cust_nm;
    cout<<"\n\nEnter The amount to be deposited: ";
    cin>>dp;
    o.deposit(dp);
    int pos=(-1)*static_cast<int>(sizeof(o));
    fileWrite.seekp(pos,ios::cur);
    fileWrite.write((char *) (&o), sizeof(Operations));
    cout<<"\n\nRecord Updated";
    flag=true;
    }
    else
    {
      cout<<"Invalid Acc no.";
      break;
    }
  }
}


//Used to extract data from file and perform withdraw operations
void withdraw_fn(int ac, Operations o)
{
  ofstream fileWrite;
  fileWrite.open("Details.dat",ios::binary|ios::in|ios::out);
  float wd;
  bool flag=false;
  while(!fileWrite.eof() && flag==false)
	{
    if(o.retacno()==ac)
		{
      
    cout<<"\n\nHello "<<o.cust_nm;
    cout<<"\n\nEnter The amount to be deposited: ";
    cin>>wd;
    o.withdraw(wd);
    int pos=(-1)*static_cast<int>(sizeof(o));
    fileWrite.seekp(pos,ios::cur);
    fileWrite.write((char *) (&o), sizeof(Operations));
    cout<<"\n\nRecord Updated";
    flag=true;
    }
    else
    {
      cout<<"Invalid Acc no.";
      break;
    }
  }
}


//Displays the customer details stored in the file
void display_fn(int ac, Operations o)
{
	bool flag=false;
	ifstream fileRead;
	fileRead.open("Details.dat",ios::binary);
	if(!fileRead)
	{
		cout<<"File not found !!";
		return;
	}
	cout<<"\nCustomer Details\n";
  while(fileRead.read((char *) (&o), sizeof(Operations)))
	{
		if(o.retacno()==ac)
		{
			o.display();
			flag=true;
		}
	}
    fileRead.close();
	  if(flag==false)
		  cout<<"\n\nAccount number does not exist";
}


//Displays all the customer details stored in the file
void allCust(Operations o)
{
  ifstream fileRead;
	fileRead.open("Details.dat",ios::binary);
	if(!fileRead)
	{
		cout<<"File not found !!";
		return;
	}
	cout<<"\n\n\t\tDetails of all the Customers\n\n";
	cout<<"A/c no.     Customer Name          Balance\n";
	cout<<"--------------------------------------------------\n";
 while(fileRead.read((char *) (&o), sizeof(Operations)))
	{
    cout<<o.ac_no<<"         "<<o.cust_nm<<setw(20)<<o.bal<<endl;
	}
 fileRead.close();

}

//Used to delete any account from the file
void closeAcc_fn(int ac,Operations o)
{
	
	ifstream fileRead;
	ofstream fileWrite;
	fileRead.open("Details.dat",ios::binary);
	if(!fileRead)
	{
		cout<<"File not found !!";
		return;
	}
	fileWrite.open("Temp.dat",ios::binary);
	fileRead.seekg(0,ios::beg);
	while(fileRead.read((char *) (&o), sizeof(Operations)))
	{
		if(o.retacno()!=ac)
		{
			fileWrite.write((char *) (&o), sizeof(Operations));
		}
	}
    fileRead.close();
	fileWrite.close();
	remove("Details.dat");
	rename("Remove.dat","Details.dat");
	cout<<"\n\nRecord Deleted ..";
}
