#include<iostream>
#include <fstream>
#include <sstream>
#include<string>

using namespace std;

class Node
{
public:
    int id;
    string name;
    float gpa;
    string depart;
    Node* left;
    Node* right;
    Node(int Id, string Name,float Gpa, string Dep) {
        id = Id;
        name = Name;
        gpa = Gpa;
        depart =Dep;
        left = right = nullptr;
    }
};

class BST
{
private:
    Node* root;
    int cs=0,it=0,ds=0,is =0;
    Node* Insert(Node* root,int id,string name,float gpa,string depart)
    {
        if(root == nullptr)
        {
            return new Node(id,name,gpa,depart);
        }
        if(id < root->id)
        {
            root->left = Insert(root->left,id,name,gpa,depart);
        }
        else if(id > root->id)
        {
            root->right = Insert(root->right,id,name,gpa,depart);
        }
        return root;
    }

    Node* FindMin(Node* node)
    {
        Node* current = node;
        while(current && current->left !=nullptr)
        {
            current = current->left;
        }
        return current;
    }
    Node* RemoveBst(Node* root,int id)
    {

        if(root == nullptr){return root;}
        if(id < root->id)
        {
            root->left = RemoveBst(root->left,id);
        }
        else if(id > root->id)
        {
            root->right = RemoveBst(root->right,id);
        }
        else
        {
            if(root->left == nullptr)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if(root->right == nullptr)
            {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = FindMin(root->right);
            root->id = temp->id;
            root->name = temp->name;
            root->gpa = temp->gpa;
            root->depart = temp->depart;
            root->right = RemoveBst(root->right,temp->id);


        }
        return root;
    }
    Node* SearchBst(Node* root,int id)
    {
        if(root == nullptr || root->id == id)
        {
            return root;
        }
        if(id < root->id)
        {
            return SearchBst(root->left,id);
        }

        return SearchBst(root->right,id);
    }

    void print(Node* root)
    {

        if(root==nullptr)
        {

            return;
        }
        print(root->left);
        cout<<"ID : "<<root->id<<endl;
        cout<<"Name : "<<root->name<<endl;
        cout<<"GPA : "<<root->gpa<<endl;
        cout<<"Department : "<<root->depart<<endl;
        if(root->depart =="CS"){cs++;}
        else if(root->depart =="IT"){it++;}
        else if(root->depart =="DS"){ds++;}
        else if(root->depart =="IS"){is++;}
        cout<<"------------------------------------"<<endl;
        print(root->right);

    }

public:
    BST() {
        root = nullptr;
    }
    void AddStudent(int id,string name,float gpa,string depart)
    {
        root = Insert(root,id,name,gpa,depart);
    }
    bool SearchStu(int id)
    {
        Node* result = SearchBst(root,id);
        if(result == nullptr)
        {
            cout << "Student not found" << endl;
            cout<<endl;
            return false;
        }
        else
        {
            cout << "Student is found" << endl;
            cout << "ID: " << result->id<< endl;
            cout<<"Name : "<<result->name<<endl;
            cout<<"GPA : "<<result->gpa<<endl;
            cout<<"Department : "<<result->depart<<endl;

            return true;
        }
    }
    void RemoveStu(int id)
    {
        if(SearchStu(id) == true)
        {
            root = RemoveBst(root,id);
            cout<<"Student is deleted "<<endl;
            cout<<endl;
        }

    }
    void PrintAll()
    {
        cs=0,it=0,ds=0,is =0;
        print(root);
        cout<<"Students per Departments: "<<endl;
        cout<<"CS "<<cs<<" Students"<<endl;
        cout<<"IT "<<it<<" Students"<<endl;
        cout<<"DS "<<ds<<" Students"<<endl;
        cout<<"IS "<<is<<" Students"<<endl;
        cout<<endl;
    }


};

int main()
{
    BST tree;
    int id;
    std::string name , d;
    float gpa;


    fstream myfile;
    myfile.open("test.txt",ios::in);
            if(myfile.is_open())
            {
                string line0,line1, line2, line3, line4;
                getline(myfile,line0);
                while (getline(myfile, line1) && getline(myfile, line2) && getline(myfile, line3) && getline(myfile, line4)) {
                    int StoreId;
                    string StoreName;
                    float StoreGpa;
                    std::string StoreDep;

                    std::istringstream iss1(line1);
                    if (!(iss1 >> StoreId)) {
                        std::cerr << "Error parsing line: " << line1 << '\n';
                        continue;
                    }

                    std::istringstream iss3(line3);
                    if (!(iss3 >> StoreGpa)) {
                        std::cerr << "Error parsing line: " << line3 << '\n';
                        continue;
                    }

                    StoreName= line2;
                    StoreDep = line4;
                    tree.AddStudent(StoreId, StoreName, StoreGpa, StoreDep);
                }


            }
    myfile.close();
    int option;
    cout<<"1. Add student"<<endl;
    cout<<"2. Remove student"<<endl;
    cout<<"3. Search student"<<endl;
    cout<<"4. Print All (sorted by id)"<<endl;
    cin>>option;
    while(option !=0)
    {
        if(option == 1)
        {

                cout<<"Enter the new student"<<endl;
                cout<<"id : ";
                cin>>id;
                cout<<"Name : ";
                cin.ignore(1,'\n');
                getline(cin,name);
                cout<<"GPA : ";
                cin>>gpa;
                cout<<"Department : ";
                cin>>d;
                tree.AddStudent(id,name,gpa,d);
                cout<<"Student is added Successfully "<<endl;
                cout<<endl;



        }
        else if(option == 2)
        {
            int RemoveID;
            cout<<"ID : ";
            cin>>RemoveID;
            tree.RemoveStu(RemoveID);

        }
        else if(option == 3)
        {
            int SearchId;
            cout<<"ID : ";
            cin>>SearchId;
            tree.SearchStu(SearchId);
        }

        else if(option == 4)
        {
            myfile.open("test.txt");
            string line0;
            if(getline(myfile,line0)){cout<<line0<<endl;}
            tree.PrintAll();
            myfile.close();
        }


        cout<<"1. Add student"<<endl;
        cout<<"2. Remove student"<<endl;
        cout<<"3. Search student"<<endl;
        cout<<"4. Print All (sorted by id)"<<endl;
        cin>>option;
    }







}
