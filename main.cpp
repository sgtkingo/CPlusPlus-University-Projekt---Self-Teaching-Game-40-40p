#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
#define LINE_LENGTH 40
#define LINE 100

unsigned int UserWin=0, ProgramWin=0, AnimalsCounter=0;

class PrimalTree
{
private:

    	class Node
	{
	public:
		string data;
		bool type;
		Node *truePointer = nullptr;
		Node *falsePointer = nullptr;

        Node (string);
		Node (string, bool type);
		Node (string,Node* TempPointer, bool type);
	};
    Node* root=nullptr;
    Node* backroot=nullptr;
    Node* firstRoot=nullptr;
public:
	bool asw;
    void SetStart(bool);

    void GetQuestion();
    void GetAnswer(bool);

    void CreateNewAnimal(string a,bool);
    void CreateNewQuestion(string q);
    void CreateNewQuestion(string q, Node*&);
    void CreateNewQuestion(string q,Node*&,Node* TempAnimalPointer, bool type);

	bool EndStatus();

    bool Answer();
	void GetNext();

	void Line(char);
};

void PrimalTree::SetStart(bool SetType)
{
    SetType ? this->root=this->firstRoot : this->firstRoot=this->root;
}

PrimalTree::Node::Node(string x)
{
    this->data=x;
}

PrimalTree::Node::Node(string x, bool type)
{
    this->data=x;
    this->type=type;
}

PrimalTree::Node::Node(string x,Node* TempPointer, bool type)
{
    this->data=x;
    this->type=type;
    this->falsePointer=TempPointer ;
}

void PrimalTree::CreateNewQuestion(string x,Node*&root)
{
    if (root==nullptr)
    {
        root=new Node(x);
        return;
    }

    if (root->type)
    {
        CreateNewQuestion(x,backroot->truePointer,backroot->truePointer, root->type);
    }
    else
        CreateNewQuestion(x,backroot->falsePointer,backroot->falsePointer, root->type);
}

void PrimalTree::CreateNewQuestion(string x,Node*&proot,Node* Temp, bool type)
{
        proot=new Node(x,Temp, type);
        asw ? root->type=true : root->type=false;
        root=proot;
}

void PrimalTree::CreateNewQuestion(string x)
{
        CreateNewQuestion(x,this->root);
}


void PrimalTree::CreateNewAnimal(string a, bool type)
{
    AnimalsCounter++;
    if (type)
    {
        this->root->truePointer=new Node(a,type);
    }
    else
    {
        this->root->falsePointer=new Node(a,type);
    }

}


void PrimalTree::GetQuestion()
{
    if (root->truePointer==root->falsePointer)
    {
        cout<<"Je to "<<root->data<<" ?"<<endl;
    }
    else
        cout<<root->data<<endl;
}

void PrimalTree::GetAnswer(bool a)
{
    this->asw=a;
}

bool PrimalTree::Answer()
{
    string asw;
    cout<<"Odpoved: ";
    cin>>asw;
    while (asw!="ano"&&asw!="ne")
    {
       cin.ignore(LINE,'\n');
       cout<<"Neplatna odpoved! \t Opakujte: ";
       cin>>asw;
    }
    if (asw=="ano") return true;
    if (asw=="ne") return false;
    return true;
}

void PrimalTree::GetNext()
{
    if (asw)
    {
        this->backroot=root;
        this->root=root->truePointer;
    }
    else
    {
        this->backroot=root;
        this->root=root->falsePointer;
    }
}

bool PrimalTree::EndStatus()
{
    if (root->truePointer==root->falsePointer)
    {
        if(asw)
        {
          cout<<root->data<<" is correct!\t"<<"I am a WINNER!"<<endl;
          ProgramWin++;
        }
         else
                {
                    cout<<"I am lose :("<<endl;
                    cout<<"Please say me the correct animal:";
                    getchar();

                    string a;
                    getline(cin,a);

                    cout<<"Thanks, now please say me the question that is true for "<<a<<" and false for "<<root->data<<": ";
                    string q;
                    getline(cin,q);
                    Line('-');
                    cout<<"Thx for teaching me!"<<endl;
                    UserWin++;

                    CreateNewQuestion(q,root);
                    CreateNewAnimal(a,true);

                    cout<<"Now i know total "<<AnimalsCounter<<" animals!"<<endl;
                }
        return true;
    }
    else
        return false;
}

void PrimalTree::Line(char c)
{
    for (int i=0;i<LINE_LENGTH;i++)
    {
        cout<<c;
    }
    cout<<endl;
}

int main()
{
    bool End=false;
    PrimalTree AnimalGame;

    cout << "Lets play a game!" << endl;
    cout << "I will give you a question and you will answer ok? (please enter ano/ne): ";
     while(!AnimalGame.Answer())
           {
              cout << "What is your problem heh? enter :ano: ! -_-" << endl;
           }
    cout << "OK, lets start!" << endl;
    AnimalGame.Line('X');

    AnimalGame.CreateNewQuestion("Zije ve vode?");
    AnimalGame.SetStart(false);
    AnimalGame.CreateNewAnimal("Ryba",true);
    AnimalGame.CreateNewAnimal("Had",false);

    do
    {
        AnimalGame.SetStart(true);
        do
        {
            AnimalGame.Line('-');
            AnimalGame.GetQuestion();
            AnimalGame.GetAnswer(AnimalGame.Answer());

            End=AnimalGame.EndStatus();
            if(!End)AnimalGame.GetNext();
        }
        while(!End);
        AnimalGame.Line('*');
        cout << "Next game?" << endl;
    }
    while (AnimalGame.Answer());

    AnimalGame.Line('X');

    cout << "\t\tSCORE" << endl;
    cout<<"User wins: "<<UserWin<<"\t Program wins: "<<ProgramWin<<endl;
    if (UserWin!=ProgramWin)
    UserWin>ProgramWin ? cout<<"\tUser is WINNER!"<<endl : cout<<"\tProgram is WINNER!"<<endl;
    else
    cout<<"\t\tREMIZE!"<<endl;
    AnimalGame.Line('-');
    cout<<"Total number of know animals: "<<AnimalsCounter<<endl;
    AnimalGame.Line('-');

    cout << "Exit...Thx for game :)" << endl;

    getchar();
    cout << "Press any key to exit..." << endl;
    getchar();
    return 0;
}
