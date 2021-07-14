/*Implementation of a basic Banking System using C++ functions, classes and basic STL */

#include <bits/stdc++.h>
using namespace std;

#define MIN_BALANCE 500

class Account
{
private:
    long accountNumber;
    string firstName;
    string lastName;
    float balance;
    static long NextAccountNumber;
public:
    Account(){}
    Account(string fname,string lname,float balance);           //To create a account for the person
    long getAccNo(){return accountNumber;}                      //To get account number
    string getFirstName(){return firstName;}                    //To get first name of account holder
    string getLastName(){return lastName;}                      //To get last name of account holder
    float getBalance(){return balance;}                         //To get account balance
  
    void Deposit(float amount);                                 //To deposit money into account
    void Withdraw(float amount);                                //To withdraw money from account
    static void setLastAccountNumber(long accountNumber);       //To set Last Account Number
    static long getLastAccountNumber();                         //To get last used Account Number
    friend ofstream & operator<<(ofstream &ofs,Account &acc);   //To store data in a text file
    friend ifstream & operator>>(ifstream &ifs,Account &acc);   //To load data from text file
    friend ostream & operator<<(ostream &os,Account &acc);      //To display account details
};
long Account::NextAccountNumber=0;

Account::Account(string fname,string lname,float balance)
{
    NextAccountNumber++;
    accountNumber=NextAccountNumber;
    firstName=fname;
    lastName=lname;
    this->balance=balance;
}

void Account::Deposit(float amount)
{
    balance+=amount;
}

void Account::Withdraw(float amount)
{
    if(balance-amount<MIN_BALANCE)   //Will not allow amount to fall below Minbalance after any withdrawal
    {
        cout<<"Transaction failed ...."<<endl;   
        return;
    } 
    else  
    {    
        balance-=amount;
        cout<<endl<<"Amount Withdrawn"<<endl;
    }

}

void Account::setLastAccountNumber(long accountNumber)
{
    NextAccountNumber=accountNumber;
}

long Account::getLastAccountNumber()
{
    return NextAccountNumber;
}

ofstream & operator<<(ofstream &ofs,Account &acc)
{
    ofs<<acc.accountNumber<<endl;
    ofs<<acc.firstName<<endl;
    ofs<<acc.lastName<<endl;
    ofs<<acc.balance<<endl;
    return ofs;
}

ifstream & operator>>(ifstream &ifs,Account &acc)
{
    ifs>>acc.accountNumber;
    ifs>>acc.firstName;
    ifs>>acc.lastName;
    ifs>>acc.balance;
    return ifs;
}

ostream & operator<<(ostream &os,Account &acc)
{
    os<<"First Name:"<<acc.getFirstName()<<endl;
    os<<"Last Name:"<<acc.getLastName()<<endl;
    os<<"Account Number:"<<acc.getAccNo()<<endl;
    os<<"Balance:"<<acc.getBalance()<<endl;
    return os;
}


class Bank
{
private:
    map<long,Account> accounts;
public:
    Bank();                                                        //Will load existing aacount details from text file bankdata.txt
    Account OpenAccount(string fname,string lname,float balance);  //To open account in bank and update the text file 
    Account BalanceEnquiry(long accountNumber);                    //To return balance for the given acount Number
    Account Deposit(long accountNumber,float amount);              //To deposit given amount in account with given account Number.
    Account Withdraw(long accountNumber,float amount);             //To withdraw given amount from account with given account Number.
    void CloseAccount(long accountNumber);                         //To close a account
    void ShowAllAccounts();                                        //To show all account details
    ~Bank();                                                       //Updates the text file bankdata.txt and closes the bank
}; 

Bank::Bank()
{
 
    Account account;
    ifstream infile; infile.open("Bankdata.txt");        
    if(!infile)
    {
        //cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    while(!infile.eof())
    {
        infile>>account;
        accounts.insert(pair<long,Account>(account.getAccNo(),account));
    }
    Account::setLastAccountNumber(account.getAccNo());
 
    infile.close();
}

Account Bank::OpenAccount(string fname,string lname,float balance)
{
    ofstream outfile;
    Account account(fname,lname,balance);
    accounts.insert(pair<long,Account>(account.getAccNo(),account));
    
    outfile.open("Bankdata.txt", ios::trunc);
    
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
        outfile<<itr->second;
    }
    outfile.close();
    return account;
}

Account Bank::BalanceEnquiry(long accountNumber)
{
    map<long,Account>::iterator itr=accounts.find(accountNumber);
    return itr->second;
}

Account Bank::Deposit(long accountNumber,float amount)
{
    map<long,Account>::iterator itr=accounts.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}

Account Bank::Withdraw(long accountNumber,float amount)
{
    map<long,Account>::iterator itr=accounts.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}

void Bank::CloseAccount(long accountNumber)
{
    map<long,Account>::iterator itr=accounts.find(accountNumber);
    cout<<"Account Deleted"<<endl<<itr->second;
    accounts.erase(itr);
}

void Bank::ShowAllAccounts()
{
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
        cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
    }
}

Bank::~Bank()
{ 
    ofstream outfile;
    outfile.open("Bankdata.txt", ios::trunc);
    
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
    outfile<<itr->second;
    }
    outfile.close();
}

int main()
{
    Bank SBI;
    Account accnt;
    
    int choice;
    string fname,lname;
    long accountNumber;
    float balance;
    float amount;
    cout<<"***Banking System***"<<endl;
    cout<<"Welcome to SBI Bank!"<<endl;
    cout<<endl;
    do
    {
        cout<<"\tSelect one option below "<<endl;
        cout<<"\t1 Open an Account"<<endl;
        cout<<"\t2 Balance Enquiry"<<endl;
        cout<<"\t3 Deposit"<<endl;
        cout<<"\t4 Withdrawal"<<endl;
        cout<<"\t5 Close an Account"<<endl;
        cout<<"\t6 Show All Accounts"<<endl;
        cout<<"\t7 Quit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
    switch(choice)
    {
    case 1:
        cout<<"Enter First Name: ";
        cin>>fname;
        cout<<"Enter Last Name: ";
        cin>>lname;
        cout<<"Enter initil Balance: ";
        cin>>balance;
        accnt=SBI.OpenAccount(fname,lname,balance);
        cout<<endl<<"Congradulations, Your Account is Created"<<endl;
        cout<<accnt<<endl;
        break;
    case 2:
        cout<<"Enter Account Number:";
        cin>>accountNumber;
        accnt=SBI.BalanceEnquiry(accountNumber);
        cout<<endl<<"Your Account Details"<<endl;
        cout<<accnt<<endl;
        break;
    case 3:
        cout<<"Enter Account Number:";
        cin>>accountNumber;
        cout<<"Enter Balance:";
        cin>>amount;
        accnt=SBI.Deposit(accountNumber, amount);
        cout<<endl<<"Amount is Deposited"<<endl;
        cout<<accnt<<endl;
        break;
    case 4:
        cout<<"Enter Account Number:";
        cin>>accountNumber;
        cout<<"Enter Balance:";
        cin>>amount;
        accnt=SBI.Withdraw(accountNumber, amount);
        cout<<accnt;
        break;
    case 5:
        cout<<"Enter Account Number:";
        cin>>accountNumber;
        SBI.CloseAccount(accountNumber);
        cout<<endl<<"Account is Closed"<<endl;
        break;
    case 6:
        SBI.ShowAllAccounts();
        break;
    case 7: 
        break;
    default: 
        cout<<"Enter valid choice"<<endl;
        exit(0);
    }
    }while(choice!=7);
    
    return 0;
}