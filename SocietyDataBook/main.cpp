#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

// Data structure to store member data
struct Member {
    string name;
    long long contactNumber;
    int age;
    string wing;
    int flatNumber;
    string email;
    string occupation;
    string address;
};

// Vector to store Society members
vector<Member> societyMembers;

// Authenticating the user before accessing the system
void authenticate(){
    system("cls");
    system("Color 0B");
    int attempt = 3;
    char USERNAME[10] = "admin";
    char PASSWORD[10] = "admin";
    char password[10];
    char username[10];
    while(attempt>0){
        cout<<"\n\n\t\t\t\t\t\tLogin Please -";
        cout<<"\n\n\n\t\t\t\tEnter Username :";
        cin>>username;
        cout<<endl;
        cout<<"\t\t\t\tEnter Password :";
        cin>>password;
        cout<<endl;
        if(strcmp(username,USERNAME)==0 && strcmp(password,PASSWORD)==0)
        {
            system("cls");
            cout<<"\n\n\n\n\n\t\t\t\t\t\tLogin Successful . . . ."<<endl;
            Sleep(2000);
            system("cls");
            return;
        }
        else
        {
            attempt--;
            system("cls");
            cout<<"\n\n\n\n\t\t\t\tIncorrect username or password ... Try again\n";
            cout<<"\n\t\t\t\tOnly "<<attempt<<" attempt remaining!";
            Sleep(1000);
            system("cls");
        }
    }
    system("cls");
    cout<<"\n\n\n\n\t\t\t\tPlease try again! You have exhausted your attempt."<<endl;
    Sleep(1000);
    exit(0);
}

// Loading required files at background while displaying the loading annimation
void load(){
    system("cls");
    SetConsoleTitle(" Society Data Book ");//setting console title to Village Governance System
    system("Color 04");//setting color of text to red
    cout<<"\n\n\n\n\n\n\n\n\n\n";
    cout<<"\t\t\t\t\t\t LOADING....\n\n" ;
    cout<<"\t\t\t\t";
    char x = 219;// A Special character printing sequence
    for(int i=0;i<35;i++)
     {
      cout<<x;
      if(i<10)
        Sleep(300);// Stops execution of the system for 300 ms
      if(i>=10&&i<20)
        Sleep(150);
      if(i>=10)
        Sleep(25);
     }
    system("cls");// For clearing console
    cout<<"\n\n\n\n";
    system("Color 02");// Setting text color to green after loading happens
    cout<<"\t\t\t\t------ WEL-COME TO SOCIETY DATA BOOK ------- \n\n\n" ;
    Sleep(1000);
}

// Saving data to the persistent data storage
void saveDataToFile() {
    system("cls");
    system("color 02");
    json data;
    for (const Member& member : societyMembers) {
        json memberData;
        memberData["name"] = member.name;
        memberData["contactNumber"] = member.contactNumber;
        memberData["age"] = member.age;
        memberData["wing"] = member.wing;
        memberData["flatNumber"] = member.flatNumber;
        memberData["email"] = member.email;
        memberData["occupation"] = member.occupation;
        memberData["address"] = member.address;
        data.push_back(memberData);
    }

    ofstream file("society_data.json");
    if (file.is_open()) {
        file << data.dump(4); // Save JSON data with indentation for readability
        file.close();
        cout << "Data saved to file." << endl;
    } else {
        cerr << "Error: Unable to save data to file." << endl;
    }
    Sleep(800);
    system("cls");
}

// Loading data from the persistent data storage
void loadDataFromFile() {
    system("cls");
    system("color 02");
    societyMembers.clear(); // Clear the existing data

    ifstream file("society_data.json");
    if (file.is_open()) {
        json data;
        try {
            file >> data; // Read JSON data from the file
            for (const auto& memberData : data) {
                Member member;
                member.name = memberData["name"];
                member.contactNumber = memberData["contactNumber"];
                member.age = memberData["age"];
                member.wing = memberData["wing"];
                member.flatNumber = memberData["flatNumber"];
                member.email = memberData["email"];
                member.occupation = memberData["occupation"];
                member.address = memberData["address"];
                societyMembers.push_back(member);
            }
            cout << "Data loaded from file." << endl;
        } catch (json::parse_error& e) {
            cerr << "Error: Unable to parse JSON data. " << e.what() << endl;
        }
        file.close();
    } else {
        // Create a new JSON file if it doesn't exist
        ofstream newFile("society_data.json");
        if (newFile.is_open()) {
            cout << "Data file created." << endl;
            newFile.close();
        } else {
            cerr << "Error: Unable to create data file." << endl;
        }
    }
    Sleep(800);
    system("cls");
}

// Adding member
void addMember() {
    system("cls");
    system("color 02");
    Member newMember;
    cin.ignore();
    cout << "Enter member name: ";
    getline(cin,newMember.name);
    cout << "Enter member contact number: ";
    cin >> newMember.contactNumber;
    cout << "Enter member age: ";
    cin >> newMember.age;
    cout << "Enter member wing: ";
    cin >> newMember.wing;
    cout << "Enter member flat number: ";
    cin >> newMember.flatNumber;
    cout << "Enter member email: ";
    cin >> newMember.email;
    cin.ignore();
    cout << "Enter member occupation: ";
    cin >> newMember.occupation;
    cout << "Enter member address: ";
    cin.ignore();
    getline(cin, newMember.address);

    societyMembers.push_back(newMember);
    saveDataToFile(); // Save data after adding a member
    cout << "Member added successfully!" << endl;
}

// View the members
void viewMembers() {
    system("cls");
    system("color 02");
    cout << "Society Members:" << endl;
    for (const Member& member : societyMembers) {
        cout << "Name: " << member.name << ", Contact Number: " << member.contactNumber
             << ", Age: " << member.age << ", Wing: " << member.wing << ", Flat Number: "
             << member.flatNumber << ", Email: " << member.email << ", Occupation: "
             << member.occupation << ", Address: " << member.address << endl;
    }
}

// Search a member
void searchMember() {
    system("cls");
    system("color 02");
    string searchName;
    cout << "Enter the name to search for: ";
    cin.ignore();
    getline(cin, searchName);
    for (const Member& member : societyMembers) {
        if (member.name == searchName) {
            cout << "Member found:" << endl;
            cout << "Name: " << member.name << ", Contact Number: " << member.contactNumber
                 << ", Age: " << member.age << ", Wing: " << member.wing << ", Flat Number: "
                 << member.flatNumber << ", Email: " << member.email << ", Occupation: "
                 << member.occupation << ", Address: " << member.address << endl;
            return;
        }
    }
    cout << "Member not found." << endl;
}

// Remove the member
void removeMember() {
    system("cls");
    system("color 02");
    string removeName;
    cout << "Enter the name of the member to remove: ";
    cin.ignore();
    getline(cin, removeName);

    for (auto it = societyMembers.begin(); it != societyMembers.end(); ++it) {
        if (it->name == removeName) {
            societyMembers.erase(it);
            cout << "Member removed successfully!" << endl;
            saveDataToFile(); // Save data after removing a member
            return;
        }
    }
    cout << "Member not found. No removal performed." << endl;
}

// Driver method
int main()
{
    system("cls");
    system("color 02");
    // Loading the required files
    load();
    // Authenticate the user
    authenticate();
    // Load data from the file when the program starts
    loadDataFromFile();

    do {
        cout << "\n\t\t\t\t\t*-*-*-*-*-*-* MENU *-*-*-*-*-*-*"<<endl;
        cout << "\t\t\t\t\t 1. Add Member" << endl;
        cout << "\t\t\t\t\t 2. View Members" << endl;
        cout << "\t\t\t\t\t 3. Search Member" << endl;
        cout << "\t\t\t\t\t 4. Remove Member" << endl;
        cout << "\t\t\t\t\t 5. Save" << endl;
        cout << "\t\t\t\t\t 6. Refresh" << endl;
        cout << "\t\t\t\t\t 7. Exit" << endl;
        cout<<endl;
        cout<<"\t\t\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
        cout<<endl;
        int choice;
        cout<<"\t\t\t\t\tEnter your choice --> ";
        cin >> choice;

        switch (choice) {
            case 1:
                addMember();
                break;
            case 2:
                viewMembers();
                break;
            case 3:
                searchMember();
                break;
            case 4:
                removeMember();
                break;
            case 5:
                saveDataToFile();
                break;
            case 6:
                loadDataFromFile();
                break;
            case 7:
                system("cls");
                saveDataToFile(); // Save data to the file before exiting
                cout<<"\n\n\n\n\n\n\n";
                cout<<"\t\t\t\tPreparing for Exiting The System ...\n\n\n"<<endl;
                system("Color 04");//Again setting color of text to red
                Sleep(1000);
                cout<<"\t\t\t\t EXITING : ";
                for(int i;i<5;i++)
                {
                    cout<<" *_* ";
                    Sleep(1000);
                }
                cout<<"\n\n\n\n\n";
                exit(0);
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }
    }while(true);
}
