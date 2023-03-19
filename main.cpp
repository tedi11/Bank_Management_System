#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include <cstring>
#include <ctime>
using namespace std;

int contorDeposit = 0;
int contorCredit = 0;
int contorClient = 0;
int contorBank = 0;
time_t now = time(0);
tm *ltm = localtime(&now);
int to_year = 1900 + ltm->tm_year;
int to_mon = 1 + ltm->tm_mon;

///TO DO:
///ADUNARI CLASE

class BankFunds;
class Deposit;

int pass_verification()
{
    cout<<"Enter admin password: ";
    string pass;
    string try1 = "Y";
    cin>>pass;
    while(pass != "0000")
    {
        cout<<"Wrong password!"<<endl;
        cout<<"Try again?"<<endl;
        cout<<"(y/n): ";
        cin>>try1;
        if(try1 != "y" & try1 != "Y")
            return 0;
        system("CLS");
        cout<<"Enter admin password: ";
        cin>>pass;
    }
    return 1;
}

class Client
{
private:
    static int idCounter;
    const int clientId;
    long clientSsn;
    char *name;
    string firstName;
    char sex;
public:
    ///constructor
    Client();
    Client(const long clientSsn,char *name, string firstName,char sex);
    Client(const Client& Obj);
    Client& operator=(const Client & Obj);

    ///operator
    bool operator==(const Client & Obj);///same client different id
    operator string();///explicit firstName
    Client operator +(char *a);///add a new name
    friend Client operator+(char *a, Client);
    bool operator<(const Client & Obj);///compare ids
    bool operator>(const Client & Obj);

    ///friend functions
    friend ostream& operator <<(ostream& out, const Client& c1);
    friend istream& operator >>(istream& out, Client& c1);

    ///setters
    void setIdCounter(int idCounter)
    {
        this->idCounter = idCounter;
    }
    void setFirstName(string firstName)
    {
        this->firstName = firstName;
    }
    void setClientSsn(long clientSsn)
    {
        this->clientSsn = clientSsn;
    }
    void setSex(char sex)
    {
        this->sex = sex;
    }
    void setName(char* name)
    {
        if(this->name!=NULL)
        {
            delete[] this->name;
            this->name=NULL;
        }
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
    }
    ///getters
    int static getIdCounter();
    const int getClientId()
    {
        return this->clientId;
    }
    long getClientSsn()
    {
        return this->clientSsn;
    }
    char getSex()
    {
        return this->sex;
    }
    char* getName()
    {
        return this->name;
    }
    string getFirstName()
    {
        return this->firstName;
    }

    ///destructor
    ~Client()
    {
        if(this->name!=NULL)
        {
            delete[] this->name;
            this->name=NULL;///de ce se face asta?
        }
    }
};

Client Client::operator +(char *a)
{
    Client aux(*this) ;
    int l = strlen(aux.name);
    char aux2[l+1];
    for (int i = 0; i < l; i++)
        aux2[i] = aux.name[i];
    aux2[l] = ' ';
    if(aux.name != NULL)
        delete[] aux.name;
    aux.name = new char [strlen(a) + 1 + l];
    for (int i = 0; i <=l; i++)
        aux.name[i] = aux2[i];
    for (int i = l+1; i <strlen(a) + l + 1; i++)
        aux.name[i] = a[i-l-1];
    return aux;
}

Client operator+(char *a, Client obj)
{
    Client aux(obj) ;
    int l = strlen(obj.name);
    char aux2[l+1];
    for (int i = 0; i < l; i++)
        aux2[i] = obj.name[i];
    aux2[l] = ' ';
    if(aux.name != NULL)
        delete[] aux.name;
    aux.name = new char [strlen(a) + 1 + l];
    for (int i = 0; i <=l; i++)
        aux.name[i] = aux2[i];
    for (int i = l+1; i <strlen(a) + l + 1; i++)
        aux.name[i] = a[i-l-1];
    return aux;
}


Client& Client::operator=(const Client& Obj)
{
    if(this!=&Obj)
    {
        if(this->name!=NULL)
        {
            delete[] this->name;
            this->name=NULL;
        }
        this->clientSsn=Obj.clientSsn;
        this->name=new char[strlen(Obj.name)+1];
        strcpy(this->name, Obj.name);
        this->firstName=Obj.firstName;
        this->sex=Obj.sex;
    }
    return *this;
}
Client::operator string()
{
    return this->firstName;
}
bool Client::operator==(const Client& Obj)
{
    if(this->clientSsn != Obj.clientSsn)
        return false;
    if(this->firstName != Obj.firstName)
        return false;
    if(this->sex != Obj.sex)
        return false;
    if(strlen(this->name)!=strlen(Obj.name))
        return false;
    for(int i = 0; i<strlen(name); i++)
        if(this->name[i] != Obj.name[i])
            return false;
    if(this->clientId == Obj.clientId)
        return false;
    return true;
}

ostream& operator <<(ostream& out, const Client& c1)
{
    out << "Client id: " << c1.clientId << endl;
    out << "Client ssn: " << c1.clientSsn << endl;
    out << "Client name: " << c1.name << endl;
    out << "Client first name: " << c1.firstName << endl;
    out << "Client sex: " << c1.sex << endl;
}

istream& operator >>(istream& in, Client& c1)
{
    cout<<"Create your client acount."<<endl<<endl;
    cout<<"Your ssn: ";
    in >> c1.clientSsn;
    cout<<"Your name:";
    char aux[50];
    in>>aux;
    if (c1.name != NULL)
        delete[] c1.name;
    c1.name = new char[strlen(aux)+1];
    strcpy(c1.name, aux);
    cout<<"Your first name: ";
    in >> c1.firstName;
    cout<<"Your sex (M/F): ";
    string aux2;
    in >> aux2;
    while(aux2 != "M" & aux2 !="F")
    {
        cout<<"Invalid input. Try again."<<endl;
        cout<<"Your sex (M/F): ";
        in >> aux2;
    }
    c1.sex = aux2[0];

    return in;
}

int Client::idCounter=1000;
int Client::getIdCounter()
{
    return Client::idCounter;
}

Client::Client():clientId(idCounter++)
{
    clientSsn = 1000000000;
    name = new char[strlen("ANONIM")+1];
    strcpy(name, "ANONIM");// doar aloc spatiu
    firstName = "ANONIM";
    sex = 'x';
}

Client::Client(const long clientSsn,char *name, string firstName,char sex):clientId(idCounter++)
{
    this->clientSsn=clientSsn;
    this->name=new char[strlen(name)+1];
    strcpy(this->name, name);
    this->firstName = firstName;
    this->sex=sex;
}

Client::Client(const Client& Obj):clientId(idCounter++)
{
    this->clientSsn=Obj.clientSsn;
    this->name=new char[strlen(Obj.name)+1];
    strcpy(this->name, Obj.name);
    this->firstName=Obj.firstName;
    this->sex=Obj.sex;
}

bool Client::operator<(const Client &C)
{
    if(this->clientId < C.clientId)
        return true;
    return false;
}

bool Client::operator>(const Client &C)
{
    if(this->clientId > C.clientId)
        return true;
    return false;
}

class Deposit
{
private:
    //static int depositIdCounter;
    long clientSsn;
    double interestRate;
    long amount;
    int year;
    int month;
public:
    ///constructor
    Deposit();
    Deposit(long clientSsn, long amount, int year, int month);
    Deposit(Deposit& Obj);
    Deposit& operator=(const Deposit & Obj);

    ///operator
    Deposit& operator--()
    {
        this->year -=1;
        return *this;
    }
    Deposit operator--(int)
    {
        Deposit aux = *this;
        operator--();
        return aux;
    }
    Deposit& operator++()
    {
        this->year +=1;
        return *this;
    }
    Deposit operator++(int)
    {
        Deposit aux = *this;
        operator++();
        return aux;
    }
    Deposit operator +(long a); ///add to amount
    friend Deposit operator+(long a, Deposit);
    friend BankFunds operator+(Deposit, BankFunds);
    Deposit operator -(long a);
    friend Deposit operator-(long a, Deposit);
    operator int();///year*12+month
    bool operator==(const Deposit & D);///same ssn, year, month
    bool operator>(const Deposit & D);///compare the amount
    bool operator<(const Deposit & D);

    ///friend functions
    friend ostream& operator <<(ostream& out, const Deposit& d1);
    friend istream& operator >>(istream& out, Deposit& d1);

    ///setters
    void setClientSsn(long clientSsn)
    {
        this->clientSsn = clientSsn;
    }
    void setInterestRate(double interestRate)
    {
        this->interestRate = interestRate;
    }
    void setAmount(long amount)
    {
        this->amount = amount;
    }
    void setMonth(int month)
    {
        this->month = month;
    }
    void setYear(int year)
    {
        this->year = year;
    }

    ///getters
    int getClientSsn()
    {
        return this->clientSsn;
    }
    double getInterestRate()
    {
        return this->interestRate;
    }
    long getAmount()
    {
        return this->amount;
    }
    int getYear()
    {
        return this->year;
    }
    int getMonth()
    {
        return this->month;
    }
};

bool Deposit::operator>(const Deposit & D)
{
    if(this->amount <= D.amount)
        return false;
    return true;
}

bool Deposit::operator<(const Deposit & D)
{
    if(this->amount >= D.amount)
        return false;
    return true;
}


bool Deposit::operator==(const Deposit & D)
{
    if(this->clientSsn != D.clientSsn)
        return false;
    if(this->month != D.month)
        return false;
    if(this->year != D.year)
        return false;
    return true;
}

Deposit Deposit::operator +(long a)
{
    Deposit aux(*this) ;
    //aux = *this;
    aux.amount+=a;
    return aux;
}

Deposit operator+(long a, Deposit obj)
{
    Deposit aux(obj);
    aux.amount +=obj.amount;
    return aux;
}

Deposit Deposit::operator -(long a)
{
    Deposit aux(*this) ;
    //aux = *this;
    aux.amount-=a;
    return aux;
}

Deposit operator-(long a, Deposit obj)
{
    Deposit aux(obj);
    aux.amount -=obj.amount;
    return aux;
}

Deposit::operator int()
{
    return this->year*12+this->month;
}

Deposit& Deposit::operator=(const Deposit& Obj)
{
    if(this!=&Obj)
    {
        this-> clientSsn = Obj.clientSsn;
        this-> interestRate = Obj.interestRate;
        this->amount=Obj.amount;
        this->year=Obj.year;
        this->month=Obj.month;
    }
    return *this;
}

Deposit::Deposit(Deposit& Obj)
{
    this->clientSsn = Obj.clientSsn;
    this->interestRate = Obj.interestRate;
    this->amount=Obj.amount;
    this->year=Obj.year;
    this->month=Obj.month;
}

Deposit::Deposit():clientSsn(1000000000)
{
    interestRate = 0.0;
    amount = 0;
    year = 1970;
    month = 1;
}

Deposit::Deposit(long clientSsn, long amount, int year, int month)
{
    this->clientSsn = clientSsn;
    this->amount = amount;
    if(amount > 2000 & amount < 5000)
        this->interestRate = 0.05;
    if(amount > 0 & amount < 2001)
        this->interestRate = 0.03;
    if(amount > 4999)
        this->interestRate = 0.07;
    if(amount < 1)
        this->interestRate = 0.0;
    this->year = year;
    this->month = month;
}

istream& operator >>(istream& in, Deposit& d1)
{
    cout<<"Make a new deposit."<<endl<<endl;
    cout<<"What is your ssn? ";
    in >> d1.clientSsn;
    cout<<"What is the amount you want to deposit? ";
    in>> d1.amount;
    cout<<"Year: ";
    in >> d1.year;
    cout<<"Month: ";
    in >> d1.month;

    return in; ///de ce se da return la in si la out nu????????????????????????
}

ostream& operator <<(ostream& out, const Deposit& d1)
{
    out << "Your interest rate is: " << d1.interestRate << endl;
    out << "The amount is: " << d1.amount << endl;
    out << "Month and year of this deposit: " << d1.month << " "<< d1.year<< endl;
}

class Credits
{
private:
    string name;
    float percent;
    bool available;
    long maxAmount;
public:
    ///constructor
    Credits();
    Credits(string name, float percent, bool available, long maxAmount);
    Credits(const Credits& Obj);
    Credits& operator=(const Credits & Obj);

    ///operator
    Credits& operator--()
    {
        this->percent -=0.1;
        return *this;
    }
    Credits operator--(int)
    {
        Credits aux = *this;
        operator--();
        return aux;
    }
    Credits& operator++()
    {
        this->percent +=0.1;
        return *this;
    }
    Credits operator++(int)
    {
        Credits aux = *this;
        operator++();
        return aux;
    }

    Credits operator +(long a);///add to maxAmount
    friend Credits operator+(long a, Credits);
    Credits operator -(long a);
    friend Credits operator-(long a, Credits);
    operator string()///name
    {
        return this->name;
    }
    bool operator==(const Credits & Obj);///same credit, different name
    bool operator>(const Credits & Obj);///for maxAmount
    bool operator<(const Credits & Obj);
    //operator+=(int a){setMaxAmount(getMaxAmount()+a);}
    //friend Credits operator+(Credits l, const Credits& r){l =l + r; return l;}


    friend ostream& operator <<(ostream& out, const Credits& c1);
    friend istream& operator >>(istream& out, Credits& c1);
    ///set
    void setName(string name)
    {
        this->name = name;
    }
    void setPercent(float percent)
    {
        this->percent = percent;
    }
    void setAvailable(bool available)
    {
        this->available = available;
    }
    void setMaxAmount(long maxAmount)
    {
        this->maxAmount = maxAmount;
    }
    ///get
    string getName()
    {
        return this->name;
    }
    float getPercent()
    {
        return this->percent;
    }
    bool getAvailable()
    {
        return this->available;
    }
    long getMaxAmount()
    {
        return this->maxAmount;
    }
};

Credits::Credits()
{
    name = "NO NAME";
    percent = 0.0;
    available = false;
    maxAmount = 0;
}

Credits::Credits(string name, float percent, bool available, long maxAmount)
{
    this->name = name;
    this->percent = percent;
    this->available = available;
    this->maxAmount = maxAmount;
}

Credits& Credits::operator=(const Credits& Obj)
{
    if(this!=&Obj)
    {
        this->name=Obj.name;
        this->percent=Obj.percent;
        this->available=Obj.available;
        this->maxAmount=Obj.maxAmount;
    }
    return *this;
}

Credits::Credits(const Credits& Obj)
{
    this->name=Obj.name;
    this->percent=Obj.percent;
    this->available=Obj.available;
    this->maxAmount=Obj.maxAmount;
}

istream& operator >>(istream& in, Credits& c1)
{
    cout<<"Create a new credit type."<<endl<<endl;
    cout<<"The name of the credit: ";
    in >> c1.name;
    cout<<"The percent: ";
    in>> c1.percent;
    cout<<"Is it available? ";
    in >> c1.available;
    cout<<"What is the max amount? ";
    in >> c1.maxAmount;

    return in; ///de ce se da return la in si la out nu????????????????????????
}

ostream& operator <<(ostream& out, const Credits& c1)
{
    out << "The name of the credit: " << c1.name << endl;
    out << "The percent: " << c1.percent << "%" << endl;
    if(c1.available == 1)
        out << "Available"<< endl;
    else
        out<< "Not available" <<endl;
    out << "The max amount for this credit is: " << c1.maxAmount << endl;
}
Credits Credits::operator +(long a)
{
    Credits aux(*this) ;
    //aux = *this;
    aux.maxAmount += a;
    return aux;
}

bool Credits::operator==(const Credits & C)
{
    if(this->percent != C.percent)
        return false;
    if(this->available != C.available)
        return false;
    if(this->maxAmount != C.maxAmount)
        return false;
    return true;
}

Credits operator+(long a, Credits obj)
{
    Credits aux(obj);
    aux.maxAmount +=a;
    return aux;
}

Credits Credits::operator -(long a)
{
    Credits aux(*this) ;
    //aux = *this;
    aux.maxAmount -= a;
    return aux;
}

Credits operator-(long a, Credits obj)
{
    Credits aux(obj);
    aux.maxAmount -=a;
    return aux;
}

bool Credits::operator<(const Credits & C)
{
    if(this->maxAmount >= C.maxAmount)
        return false;
    return true;
}

bool Credits::operator>(const Credits & C)
{
    if(this->maxAmount <= C.maxAmount)
        return false;
    return true;
}

class BankFunds
{
private:
    string currency;
    long availableAmount;
    long transactions;
    long* transactionHistory;
    bool profit;

public:
    ///constructor
    BankFunds();
    BankFunds(string currency, long availableAmount, long transactions, long* transactionHistory);
    BankFunds(const BankFunds& Obj);
    BankFunds& operator=(const BankFunds & Obj);

    ///operator
    BankFunds operator +(long a);
    friend BankFunds operator+(long a, BankFunds);///a transaction with +
    BankFunds operator+(Deposit);
    BankFunds operator -(long a);
    friend BankFunds operator-(long a, BankFunds);///a transaction with -
    bool operator==(const BankFunds & B);///same currency
    bool operator<(const BankFunds & B);///availableAmount
    bool operator>(const BankFunds & B);
    long  operator[](long a);///index of transaction
    operator string();///explicit
    operator long() const;///implicit

    ///friend functions
    friend ostream& operator <<(ostream& out, const BankFunds& b1);
    friend istream& operator >>(istream& out, BankFunds& b1);

    ///setter
    void setCurrency(string currency)
    {
        this->currency = currency;
    }
    void setAvailableAmount(long availableAmount)
    {
        this->availableAmount = availableAmount;
    }
    void setTransactions(long transactions)
    {
        this->transactions = transactions;
    }
    void setProfit(bool profit)
    {
        this->profit = profit;
    }
    void setTransactionHistory(long* transactionHistory, long transactions)
    {
        if(this->transactionHistory!=NULL)
        {
            delete[] this->transactionHistory;
            this->transactionHistory=NULL;
        }
        this->transactionHistory=new long[transactions];
        for(long i = 0; i < transactions; i++)
            this->transactionHistory[i] = transactionHistory[i];
    }

    ///getter
    string getCurrency()
    {
        return this->currency;
    }
    long getAvailableAmount()
    {
        return this->availableAmount;
    }
    long getTransactions()
    {
        return this->transactions;
    }
    bool getProfit()
    {
        return this->profit;
    }
    const long* getTransactionHistory()
    {
        return this->transactionHistory;
    }

    ///destructor
    ~BankFunds()
    {
        if(this->transactionHistory!=NULL)
        {
            delete[] this->transactionHistory;
            this->transactionHistory=NULL;
        }
    }
};

BankFunds::BankFunds()
{
    currency = "NONE";
    availableAmount = 0;
    transactions = 0;
    transactionHistory = 0;
    profit = false;
}

BankFunds::BankFunds(const BankFunds& Obj)
{
    this->currency=Obj.currency;
    this->availableAmount=Obj.availableAmount;
    this->transactions=Obj.transactions;
    this->profit=Obj.profit;
    this->transactionHistory = new long [Obj.transactions];
    for(int i =0; i<Obj.transactions; i++)
        this->transactionHistory[i] = transactionHistory[i];
}

BankFunds::BankFunds(string currency, long availableAmount,long transactions, long* transactionHistory)
{
    this->currency = currency;
    this->availableAmount = availableAmount;
    this->transactions = transactions;
    this->transactionHistory = new long[transactions];
    for(long i = 0; i < transactions; i++)
        this->transactionHistory[i] = transactionHistory[i];
    if(availableAmount > 0)
        this->profit = true;

}

BankFunds& BankFunds::operator=(const BankFunds& Obj)
{
    if(this!=&Obj)
    {
        if(this->transactionHistory!=NULL)
        {
            delete[] this->transactionHistory;
            this->transactionHistory = NULL;
        }
        this->currency = Obj.currency;
        this->availableAmount = Obj.availableAmount;
        this->transactions = Obj.transactions;
        this->transactionHistory = new long[Obj.transactions];
        for(long i = 0; i <= Obj.transactions; i++)
            this->transactionHistory[i] = Obj.transactionHistory[i];
        this->profit = Obj.profit;
    }

}

istream& operator >>(istream& in, BankFunds& b1)
{
    cout<<"Create a bank account."<<endl<<endl;
    cout<<"The currency: ";
    in >> b1.currency;
    cout<<"The available amount: ";
    in>> b1.availableAmount;
    cout<<"If there is a transaction history, please specify how many transactions have been made: ";
    in >> b1.transactions;
    if (b1.transactionHistory != NULL)
        delete[] b1.transactionHistory;
    b1.transactionHistory = new long[b1.transactions];
    if (b1.transactions > 0)
    {
        cout<<"For every transaction specify the amount: "<<endl;
        for(int i = 0; i<b1.transactions; i++)
        {
            cout<<"Transaction "<<i+1<<" out of "<<b1.transactions<<":";
            in >> b1.transactionHistory[i];
        }
    }

    return in;
}

ostream& operator <<(ostream& out, const BankFunds& b1)
{
    out << "The currency: " << b1.currency << endl;
    out << "Current available amount: " << b1.availableAmount << endl;
    out << "How many transactions have been made: " << b1.transactions << endl;
    if (b1.transactions > 0)
    {
        out << "Transation history: "<<endl<<endl;
        for(int i = 0; i < b1.transactions; i++)
            cout<<"Tr. #"<<i+1<<": "<<b1.transactionHistory[i]<<endl;
    }
    if(b1.profit == true)
        out << "There is profit.";
    else
        out << "There is no profit.";
}

BankFunds BankFunds::operator -(long a)
{
    BankFunds aux(*this) ;
    //aux = *this;
    if(aux.transactionHistory != NULL)
        delete[] aux.transactionHistory;
    aux.transactionHistory = new long [aux.transactions + 1];
    for (long i = 0; i <this->transactions; i++)
        aux.transactionHistory[i] = this->transactionHistory[i];
    aux.transactionHistory[this->transactions] = -a;
    aux.transactions++;
    aux.availableAmount-=aux.transactionHistory[transactions];
    if(aux.availableAmount > 0)
        aux.profit = true;
    else
        aux.profit = false;
    return aux;
}

BankFunds operator-(long a, BankFunds obj)
{
    BankFunds aux(obj);
    if(aux.transactionHistory != NULL)
        delete[] aux.transactionHistory;
    aux.transactionHistory = new long [aux.transactions + 1];
    for (long i = 0; i < obj.transactions; i++)
        aux.transactionHistory[i] = obj.transactionHistory[i];
    aux.transactionHistory[obj.transactions] = -a;
    aux.transactions++;
    aux.availableAmount-=aux.transactionHistory[aux.transactions];
    if(aux.availableAmount > 0)
        aux.profit = true;
    else
        aux.profit = false;
    return aux;
}

BankFunds BankFunds::operator +(long a)
{
    BankFunds aux(*this) ;
    //aux = *this;
    if(aux.transactionHistory != NULL)
        delete[] aux.transactionHistory;
    aux.transactionHistory = new long [aux.transactions + 1];
    for (long i = 0; i <this->transactions; i++)
        aux.transactionHistory[i] = this->transactionHistory[i];
    aux.transactionHistory[this->transactions] = a;
    aux.transactions++;
    aux.availableAmount+=aux.transactionHistory[transactions];
    if(aux.availableAmount > 0)
        aux.profit = true;
    else
        aux.profit = false;
    return aux;
}

BankFunds operator+(long a, BankFunds obj)
{
    BankFunds aux(obj);
    if(aux.transactionHistory != NULL)
        delete[] aux.transactionHistory;
    aux.transactionHistory = new long [aux.transactions + 1];
    for (long i = 0; i < obj.transactions; i++)
        aux.transactionHistory[i] = obj.transactionHistory[i];
    aux.transactionHistory[obj.transactions] = a;
    aux.transactions++;
    aux.availableAmount+=aux.transactionHistory[aux.transactions];
    if(aux.availableAmount > 0)
        aux.profit = true;
    else
        aux.profit = false;
    return aux;
}

bool BankFunds::operator==(const BankFunds &B)
{
    if(this->currency == B.currency)
        return true;
    return false;
}

bool BankFunds::operator<(const BankFunds &B)
{
    if(this->availableAmount < B.availableAmount)
        return true;
    return false;
}

bool BankFunds::operator>(const BankFunds &B)
{
    if(this->availableAmount > B.availableAmount)
        return true;
    return false;
}

long BankFunds::operator[](long a)
{
    if((a<0 || a>this->transactions-1) && this->transactions !=NULL)
        throw runtime_error("index invalid");
    else
        return this->transactionHistory[a];
}

BankFunds::operator string()
{
    return this->currency;
}

BankFunds::operator long()const
{
    return this->availableAmount;
}


Client ClientList[100];
BankFunds BankList[100];
Credits CreditList[100];
Deposit DepositList[100];

int account_search(int n)
{
    int nr = 0;
    for(int i = 0; i<=contorClient; i++)
        if(ClientList[n] == ClientList[i])
            nr++;
    return nr;
}

int calculate_bal(Deposit D)
{
    long mon = to_year *12 + to_mon;
    long mon2 = D.getYear()*12 + D.getMonth();
    long months = mon - mon2;
    long amount = D.getAmount()*D.getInterestRate()*months;
    return amount+D.getAmount();
}

void calculate_monthly_rate(Credits C, long yearF, long monthF, long amount)
{
    if(C.getAvailable() == 0 || amount > C.getMaxAmount())
    {
        cout<<"Credit not available!";
        return;
    }

    long mon = to_year *12 + to_mon;
    long mon2 = yearF*12 + monthF;
    long months = mon2 - mon;
    if (months == 0)
    {
        cout<<"Credit not available for this date.";
        return;
    }
    long sum = C.getMaxAmount() * C.getPercent() + C.getMaxAmount();
    cout<<"The monthly rate for the max amount and the date you provided is: "<< sum/months;
    cout<<endl<<endl;
    cout<<"The monthly rate for the amount specified and the date you provided is: "<<amount/months;
}

long profit_for_transactions(BankFunds& B, int first_transaction, int last_transaction)
{
    long suma = 0;
    for(int i = first_transaction; i<=last_transaction; i++)
    {
        suma+=B[i];
    }
    return suma;
}

BankFunds BankFunds::operator+( Deposit D)
{
    BankFunds aux(*this) ;
    if(aux.transactionHistory != NULL)
        delete[] aux.transactionHistory;
    aux.transactionHistory = new long [aux.transactions + 1];
    for (long i = 0; i <this->transactions; i++)
        aux.transactionHistory[i] = this->transactionHistory[i];
    aux.transactionHistory[this->transactions] = D.getAmount();
    aux.transactions++;
    aux.availableAmount+=aux.transactionHistory[transactions];
    if(aux.availableAmount > 0)
        aux.profit = true;
    else
        aux.profit = false;
    return aux;
}
/*
BankFunds operator+(Deposit D, BankFunds B)
{
    BankFunds aux(B);
    if(aux.transactionHistory != NULL)
        delete[] aux.transactionHistory;
    aux.transactionHistory = new long [aux.transactions + 1];
    for (long i = 0; i <this->transactions; i++)
        aux.transactionHistory[i] = this->transactionHistory[i];
    aux.transactionHistory[this->transactions] = D.getAmount();
    aux.transactions++;
    aux.availableAmount+=aux.transactionHistory[transactions];
    if(aux.availableAmount > 0)
        aux.profit = true;
    else
        aux.profit = false;
    return aux;
}*/

int main()
{
    /*Client B;
    Client A(B);
    cout<<B.getClientId()<<endl;
    cout<<A.getFirstName()<<endl;
    cout<<A.getClientId()<<endl;
    cout<<A.getClientSsn()<<endl;
    cout<<A.getIdCounter()<<endl;
    cout<<A.getName()<<endl;
    cout<<A.getSex()<<endl;
    cout<<A.getAmount()<<endl;
    cout<<A.getClientSsn()<<endl;
    cout<<A.getInterestRate()<<endl;
    cout<<A.getMonth()<<endl;
    cout<<A.getYear()<<endl;*/
    char n[] = {"Dumitru"};
    long o[] = {2, 3, 4, 6, 7};
    long o2[] = {-1000, 100};
    //Client B(1234567890, n, "Alex", 'M');
    //Deposit A(B.getClientSsn(), 2000, 2003, 11); ///Se poate folosi doar B?
    /*Deposit C; C=A*/ ///C=A nu merge ca folosesc cnp ca const, e problema?
    /*Credits A("Credit Prima Casa", 15.7, 1, 1000000);
    Credits A(B);
    Credits B;
    A = B;
    cout<<A.getAvailable()<<endl;
    cout<<A.getMaxAmount()<<endl;
    cout<<A.getName()<<endl;
    cout<<A.getPercent()<<endl;*/
    //long tr[] = {-10, 100, -200, 110, 100000};
    //BankFunds S;
    //BankFunds B("RON", 100000, 5, tr, 1);
    //cout<<B.getCurrency();
    //Client C(B);
    //A.setIdCounter(3000);
    //cout<<C.getClientId();
    //BankFunds Q;
    //cin>>Q;
    //cout<<Q;

    int k = 1;
    //    Credits C;
    //    Credits A;
    //    A.setMaxAmount(100);
    //    cout<<C;
    //    cout<<C+A;
    //    cout<<C;
    //    cout<<A;
    //    cout<<C;
    //BankFunds B("ron", -100, 2, o);
    //BankFunds C("ron", -110, 2, o2);
    //    cout<<(B==C);
    //    cout<<B[2];
    //    cout<<B+100;
    //    B=B+200;
    //    cout<<(B>C);
    //    cout<<B[0];
//    Credits C("Casa", 0.29, 1, 2000);
//    Credits D("Casa2", 0.39, 0, 5000);
//    Credits E("Casa3", 0.39, 0, 3000);
//    Credits F("Casa4", 0.39, 0, 1000);
//    cout<<C;
//    C=C+D+E+F;
//    cout<<C;
//Client A;
//cout<<A;
//A=A+"alex";
//cout<<A;
//Deposit D;
//cout<<D;
//cout<<D++;
//cout<<D;
//cout<<++D;
//cout<<D+1;
//D=D+1;
//cout<<D++;
//Deposit D;
//Client C;
//cout<<C;

//cout<<int(D);
//BankFunds B("ron", -900, 2, o2 );
//  Deposit D(1234, 1000, 2020, 3);
//  cout<<B+D+D+D;
//  return 0;
//    cout<<D;
//    cout<<calculate_bal(D);
//    cout<<endl;
//    Credits C("Casa", 0.09, 1, 10000);
//    cout<<C;
//    cout<<endl;
//    calculate_monthly_rate(C, 2023, 3);
//    BankFunds B("ron", 100, 3, o2);
//    cout<<profit_for_transactions(B, 1, 2);

//    return 0;
    while(k==1)
    {
        system("CLS");
        cout<<"Welcome to our bank system."<<endl;
        int comanda;
        cout<<"\n1-Make a client account";
        cout<<"\n2-Credits";
        cout<<"\n3-Make a deposit";
        cout<<"\n4-My deposits";
        cout<<"\n5-Calculate monthly rate for a credit";
        cout<<"\n6-Calculate deposit money";
        cout<<"\n7-Add deposit money into the bank account - admin required";
        cout<<"\n8-Client accounts - admin required";
        cout<<"\n9-Delete duplicated accounts - admin required";
        cout<<"\n10-Create a new credit - admin required";
        cout<<"\n11-New bank currency - admin required";
        cout<<"\n12-View bank accounts - admin required";
        cout<<"\n13-View bank profit for some transactions - admin required";
        cout<<"\n14-Verify duplicated accounts - admin required";
        cout<<"\n15-Quit";
        cout<<endl;
        cout<<endl;
        cout<<"Enter your option: ";
        cin>>comanda;
        switch (comanda)
        {

        case 1:
        {
            system("CLS");
            Client c;
            cin>>c;
            ClientList[contorClient]=c;
            contorClient++;
            system("CLS");
            break;
        }
        case 2:
        {
            system("CLS");
            for(int i=0; i<contorCredit; i++)
            {
                system("CLS");
                cout<<"This is credit #"<<i+1<<" out of "<<contorCredit<<endl;
                cout<<CreditList[i]<<endl;
                cout<<"Type 'Next'"<<endl;
                string aux;
                cin>>aux;
            }
            system("CLS");
            if(contorCredit == 0)
                cout<<"There are no credits listed yet."<<endl;
            cout<<"Type 'Back' to go to the main menu."<<endl;
            string aux;
            cin>>aux;

            break;
        }
        case 3:
        {
            system("CLS");
            Deposit d;
            cin>>d;
            if(d.getAmount() > 2000 & d.getAmount() < 5000)
                d.setInterestRate(0.05);
            if(d.getAmount() > 0 & d.getAmount() < 2001)
                d.setInterestRate(0.03);
            if(d.getAmount() > 4999)
                d.setInterestRate(0.07);
            if(d.getAmount() < 1)
                d.setInterestRate(0.0);
            DepositList[contorDeposit]=d;
            contorDeposit++;
            system("CLS");
            break;
        }
        case 4:
        {

            system("CLS");
            long auxssn;
            int okk = 0;
            cout<<"What is your ssn? ";
            cin>>auxssn;
            for(int i=0; i<contorDeposit; i++)
                if(DepositList[i].getClientSsn() == auxssn)
                {
                    system("CLS");
                    cout<<DepositList[i]<<endl;
                    ///cout<<"The amount you can withdraw: "<<calculate_bal(DepositList[i])<<endl;
                    cout<<"Type 'Next'"<<endl;
                    string aux;
                    cin>>aux;
                    okk = 1;
                }
            system("CLS");
            if(contorDeposit == 0 || okk == 0)
                cout<<"You have no deposits yet. "<<endl;
            cout<<"Type 'Back' to go to the main menu."<<endl;
            string aux;
            cin>>aux;

            break;
        }
        case 5:
        {

            system("CLS");

            cout<<"What is the name of the credit you are interested in? "<<endl;
            string name;
            cin>>name;
            int crno=-1;
            for(int i = 0; i<= contorCredit; i++)
                if(CreditList[i].getName()==name)
                {
                    crno = i;
                    break;
                }
            if(crno == -1)
            {
                system("CLS");
                cout<<"There is no credit with this name"<<endl;
                string aux4;
                cout<<"Type 'Back' to go to the main menu."<<endl;
                cin>>aux4;
                break;
            }
            cout<<"What is the amount you want to get the credit for?"<<endl;
            int amo;
            cin>>amo;
            if(amo > CreditList[crno].getMaxAmount() || amo < 1)
            {
                system("CLS");
                cout<<"The credit is not available for this amount"<<endl;
                string aux4;
                cout<<"Type 'Back' to go to the main menu."<<endl;
                cin>>aux4;
                break;
            }
            cout<<"What is the year you want to end the credit? "<<endl;
            int yy;
            cin>>yy;
            cout<<"What is the month you want to end the credit"<<endl;
            int mon;
            cin>>mon;
            calculate_monthly_rate(CreditList[crno], yy, mon, amo);
            cout<<endl;
            string aux3;
            cout<<"Type 'Back' to go to the main menu."<<endl;
            cin>>aux3;

            break;
        }
        case 6:
        {
            system("CLS");

            cout<<"What is your ssn? "<<endl;
            long ssn;
            cin>>ssn;

            system("CLS");
            int nr = 0;
            for(int i=0; i<contorDeposit; i++)
                if((DepositList[i].getClientSsn()) == ssn)
                {
                    nr++;
                    cout<<"Your deposits: #"<<nr<<endl<<endl;
                    cout<<DepositList[i];
                    cout<<endl;
                    cout<<"The amount you can withdraw is: "<<calculate_bal(DepositList[i])<<endl<<endl;
                    cout<<"Type 'Next'"<<endl;
                    string aux;
                    cin>>aux;
                    system("CLS");
                }
            if(nr == 0)
                cout<<"You don't have any deposits yet."<<endl<<endl;;

            cout<<"Type 'Back' to go to the main menu."<<endl;
            string aux;
            cin>>aux;

            break;
        }
        case 7:
        {

            system("CLS");

            if (pass_verification() == 0)
                break;
            system("CLS");
            cout<<"What is the deposit number you want to select? "<<endl;
            int nrd;
            cin>>nrd;
            if(nrd >= contorDeposit)
            {
                cout<<"Id invalid."<<endl<<endl;
                cout<<"Type 'Back' to go to the main menu."<<endl;
                string aux;
                cin>>aux;
                break;
            }
            cout<<endl;
            cout<<"What is the bank account you want to move the money into? "<< endl;
            int nrb;
            cin>>nrb;
            if(nrb >= contorBank)
            {
                cout<<"Id invalid."<<endl<<endl;
                cout<<"Type 'Back' to go to the main menu."<<endl;
                string aux;
                cin>>aux;
                break;
            }
            BankList[nrb] = BankList[nrb] + DepositList[nrd];

            system("CLS");
            cout<<"Process complete! "<<endl<<endl;

            cout<<"Type 'Back' to go to the main menu."<<endl;
            string aux;
            cin>>aux;

            break;
        }
        case 8:
        {

            system("CLS");

            if (pass_verification() == 0)
                break;

            for(int i=0; i<contorClient; i++)
            {
                system("CLS");
                cout<<"This is client #"<<i+1<<" out of "<<contorClient<<endl;
                cout<<ClientList[i]<<endl;
                cout<<"Type 'Next'"<<endl;
                string aux;
                cin>>aux;
            }
            system("CLS");
            if(contorClient == 0)
                cout<<"There are no clients registered yet."<<endl;
            cout<<"Type 'Back' to go to the main menu."<<endl;
            string aux;
            cin>>aux;

            break;
        }
        case 9:
        {
            int no;
            system("CLS");
            if (pass_verification() == 0)
                break;

            system("CLS");
            cout<<"What is the number of the account? "<<endl;
            cin>>no;
            int nnr = account_search(no);
            if(nnr == 0)
            {
                cout<<"There are no duplicates for this!";
                cout<<"Type 'Back' to go to the main menu."<<endl;
                string aux;
                cin>>aux;
                break;
            }
            Client aux(ClientList[no]);
            int nr = 0;
            for(int i = 0; i<contorClient-1; i++)
                if(aux == ClientList[i])
                {
                    if(nr == nnr)
                        break;
                    nr++;
                    for(int j = i; j< contorClient-1; j++)
                        ClientList[j] = ClientList[j+1];
                }
            contorClient-=nnr;
            cout<<nnr<<" duplicates deleted! "<<endl<<endl;
            cout<<"Type 'Back' to go to the main menu."<<endl;
            string aux2;
            cin>>aux2;
            break;
        }
        case 10:
        {
            system("CLS");
            if (pass_verification() == 0)
                break;

            system("CLS");
            Credits c;
            cin>>c;
            CreditList[contorCredit]=c;
            contorCredit++;
            system("CLS");
            break;
        }
        case 11:
        {
            system("CLS");

            if (pass_verification() == 0)
                break;

            system("CLS");

            BankFunds b;
            cin>>b;
            if(b.getAvailableAmount() > 0)
                b.setProfit(1);
            BankList[contorBank]=b;
            contorBank++;
            system("CLS");
            break;
        }
        case 12:
        {

            system("CLS");

            if (pass_verification() == 0)
                break;

            system("CLS");

            for(int i=0; i<contorBank; i++)
            {
                system("CLS");
                cout<<"This is bank account #"<<i+1<<" out of "<<contorBank<<endl;
                cout<<BankList[i]<<endl;
                cout<<endl;
                cout<<"Type 'Next'"<<endl;
                string aux;
                cin>>aux;
            }
            system("CLS");
            if(contorBank == 0)
                cout<<"There are no bank accounts opened yet."<<endl;
            cout<<"Type 'Back' to go to the main menu."<<endl;
            string aux;
            cin>>aux;

            break;
        }

        case 13:
        {
            system("CLS");

            if (pass_verification() == 0)
                break;

            system("CLS");

            int a, l, f;
            cout<<"What is the id of the bank account? "<<endl;
            cin>>a;
            cout<<endl;
            if(a<0 || a>=contorBank)
            {
                cout<<"Id invalid!"<<endl<<endl;
                cout<<"Type 'Back' to go to the main menu."<<endl;
                string aux;
                cin>>aux;
                break;
            }
            cout<<"What is the first transaction? "<<endl;
            cin>>f;
            if(f<0)

            {
                cout<<"Id invalid!"<<endl<<endl;
                cout<<"Type 'Back' to go to the main menu."<<endl;
                string aux;
                cin>>aux;
                break;
            }

            cout<<"What is the last transaction? "<<endl;
            cin>>l;
            long nr = profit_for_transactions(BankList[a], f, l);
            system("CLS");
            cout<<"The profit of this interval of transactions is: "<<nr<<endl;
            cout<<"Type 'Back' to go to the main menu."<<endl;
            string aux;
            cin>>aux;
            break;
        }
        case 14:
        {
            system("CLS");

            if (pass_verification() == 0)
                break;

            system("CLS");

            int a;
            cout<<"What is the id of the account you want to search?"<<endl;
            cin>>a;
            cout<<endl;
            if(a-1000 < 0 || a-1000>=contorClient)
            {
                cout<<"Id invalid!"<<endl<<endl;
                cout<<"Type 'Back' to go to the main menu."<<endl;
                string aux;
                cin>>aux;
                break;
            }
            int nr = account_search(a-1000);

            if(nr!=0)
                cout<<"The account has been duplicated for "<<nr<<" times."<<endl<<endl;
            else
                cout<<"There is no copy of this account"<<endl<<endl;
            cout<<"Type 'Back' to go to the main menu."<<endl;
            string aux;
            cin>>aux;
            break;
        }
        case 15:
        {
            k=0;
            break;
        }
        default:
        {
            cout<<"\n\tComanda Necunoscuta";
        }
        }

    }


    return 0;
}


/*
class withdrawal{
private:
    float* withdrawals;
    double totalWithdrawal;
    int withdrawalCounter;
};
class bank{
private:
    static int accountId;
    const string bankName;
    int clientCounter;
    int* accountIds;

};
class account{
private:
    static int accountId;
    const int clientId;
    float balance;
    bool verified;
};*/


