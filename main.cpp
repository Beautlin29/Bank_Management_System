#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>

using namespace std;

class Bank_Account{
    int acc_no;
    char name[50];
    char acc_type;
    int deposit_money;

    public:
        int ret_acc_num() const{
            return acc_no;
        }
        void create_account();
        void display_account();
        void report() const;

};

void Bank_Account :: report() const{
    cout << acc_no << setw(10) << " " << name << setw(10) << acc_type << setw(6) << deposit_money << endl;
}

void Bank_Account :: create_account(){
    system("cls");
    cout << "\t Enter the account number: ";
    cin >> acc_no;
    cout << "\t Enter the account holder name: ";
    cin.ignore();
    cin.getline(name, 50); 
    cout << "\t Enter the type of the account (C/S): ";
    cin >> acc_type;
    acc_type = toupper(acc_type);
    cout << "\t Enter the initial amount: ";
    cin >> deposit_money;
    cout << endl;
    cout << "\t Account Created... :)" << endl;
}

void Bank_Account :: display_account(){
    cout << "\t Bank Account Number: " << acc_no << endl;
    cout << "\t Account Holder Name: " << name << endl;
    cout << "\t Account Type: ";
    if(acc_type == 'C') cout << "Current" << endl; 
    else cout << "Savings" << endl;
    cout << "\t Balance Amount: " << deposit_money << endl;
}

void new_account(){
    Bank_Account AC;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    AC.create_account();
    outFile.write(reinterpret_cast<char *> (&AC), sizeof(Bank_Account));
    outFile.close();
}

void delete_account(int acc_no){
    Bank_Account AC;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile){
        cout << "File could not be opened!! Press any key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);

    while(inFile.read(reinterpret_cast<char *> (&AC), sizeof(Bank_Account))){
        if(AC.ret_acc_num() != acc_no){
            outFile.write(reinterpret_cast<char *> (&AC), sizeof(Bank_Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("Bank_Account.dat");
    rename("Temp.dat", "Bank_Account.dat");
    cout << "\t Record Deleted..." << endl;
}

void balance_enquiry(int acc_no){
    Bank_Account AC;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile){
        cout << "File could not be opened!! Press any key...";
        return;
    }
    cout << "\t Bank Account Details" << endl;
    while(inFile.read(reinterpret_cast<char *> (&AC), sizeof(Bank_Account))){
        if(AC.ret_acc_num() == acc_no){
            AC.display_account();
            flag = true;
        }
    }
    inFile.close();
    if(flag == false){
        cout << "\t Account number does not exist" << endl;
    }
}

void display_all_details(){
    system("cls");
    Bank_Account AC;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile){
        cout << "File could not be opened!! Press any key...";
        return;
    }
    cout << "\t Bank Account Holder List" << endl;
    cout << "=============================================" << endl;
    cout << "A/c no.       NAME        TYPE        BALANCE" << endl;
    cout << "=============================================" << endl;
    while(inFile.read(reinterpret_cast<char *> (&AC), sizeof(Bank_Account))){
        AC.report();
    }
}

int main()
{
    
    int ch, acc_no;
    do{
    system("cls");
    cout << "\t\t\t--------------------------------------------" << endl;
    cout << "\t\t\t| Welcome to the Banking Management System |" << endl;
    cout << "\t\t\t--------------------------------------------" << endl;

    cout << endl;
    cout << "\t\t\t\t--- Main Menu ---" << endl;
    cout << endl;
    cout << "\t 1. Create an Account" << endl;
    cout << "\t 2. Deposit Money" << endl;
    cout << "\t 3. Withdraw Money" << endl;
    cout << "\t 4. Balance Enquiry" << endl;
    cout << "\t 5. All Account Holder List" << endl;
    cout << "\t 6. Modify an Account" << endl;
    cout << "\t 7. Close an Account" << endl;
    cout << "\t 8. Exit" << endl;
    cout << endl;
    
    cout << "Enter your choice (1-8): ";
    cin >> ch;
    
    switch(ch){
        case 1: // create account
            new_account();
            break;
        case 2: // deposit func
            system("cls");
            cout << "\t Enter the account number: ";
            cin >> acc_no;

            break; 
        case 3: // withdraw func
            system("cls");
            cout << "\t Enter the account number: ";
            cin >> acc_no;
            break; 
        case 4: // balance enquiry func
            system("cls");
            cout << "\t Enter the account number: ";
            cin >> acc_no;
            balance_enquiry(acc_no);
            break; 
        case 5: // account details func
            display_all_details();
            break; 
        case 6: // modify acc func
            break; 
        case 7: // close acc func
            system("cls");
            cout << "\t Enter the account number: ";
            cin >> acc_no;
            delete_account(acc_no);
            break; 
        case 8:
            cout << "\nThank you for using our service! Please come back again!!\n";
            break;
        }

    }while(ch != 8);
}

