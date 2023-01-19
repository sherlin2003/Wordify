#include<bits/stdc++.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <unistd.h>
#include<queue>

using namespace std;

class TrieNode
{
    private:
        TrieNode *children[26];
        bool endWord;
        string means;

    public:
        TrieNode *getNode();
        void insert_key(TrieNode*, string,string);
        void toTrie(TrieNode*);
        bool search_key(TrieNode*, string);
        void find_Meaning(TrieNode *, string);
        vector<string> level(TrieNode *,string);
        bool autoComplete(TrieNode *,string);
        bool game_generation(TrieNode *,string);
        void game(TrieNode *);

}trie;

TrieNode* TrieNode::getNode()
{
    TrieNode *temp = new TrieNode;
    temp->endWord = false;

    for(int i=0;i<26;i++)
        temp->children[i] = NULL;

    return temp;
}

void TrieNode::insert_key(TrieNode *root,string word,string meaning)
{
    TrieNode *temp = root;

    for(int i=0;i<word.length();i++)
    {
        int index = word[i]-'a';
        if(!temp->children[index])  //If the children is NULL Insert
            temp->children[index] = getNode();
        temp = temp->children[index];
    }

    temp->means=meaning;
    temp->endWord = true;
}

void TrieNode:: toTrie(TrieNode *root)
{
    ifstream dictionary("Word.txt");

    string word,means;
    while(dictionary.is_open() && !dictionary.eof())
    {
        getline(dictionary,word,':');
        getline(dictionary,means,'\n');
        trie.insert_key(root,word,means);
    }
    dictionary.close();
}

bool TrieNode::search_key(TrieNode *root, string word)
{
    TrieNode *temp = root;
    for(int i=0;i<word.length();i++)
    {
        int index = word[i]-'a';
        if(!temp->children[index])
            return false;
        temp = temp->children[index];
    }

    return temp->endWord;
}

void TrieNode::find_Meaning(TrieNode *root, string word)
{
    TrieNode *temp = root;
    if(trie.search_key(root,word))
    {
        for(int i=0;i<word.length();i++)
        {
            int index = word[i]-'a';
            if(!temp->children[index])
                return ;
            temp = temp->children[index];
        }
        cout<<endl<<word<<" meaning = "<<temp->means<<endl;
    }
}

vector<string> TrieNode::level(TrieNode *temp,string str)
{
  vector<string> wordString;
  queue<pair<TrieNode*,string> > q;

  TrieNode *cur = temp;
  q.push({cur, str});

  while(!q.empty())
  {
      TrieNode *cur = q.front().first;
      string str = q.front().second;
      q.pop();

      if(cur->endWord==true)
          wordString.push_back(str);

      for(int i=0;i<26;i++){
          if(cur->children[i]!=NULL){
              q.push({cur->children[i], str+char(i+'a')});
          }
      }
  }
  return wordString;
}

bool TrieNode::autoComplete(TrieNode *root,string key)
{
    TrieNode *temp = root;

    string s;
    string k;
    for(int i=0;i<key.length();i++)
    {
        k = key[i]; //Extract each letter
        s += k;     //Append letter to stirng
        int index = k[0]-'a';
        if(temp->children[index])
            temp = temp->children[index];
        else
            return false;
    }

    vector<string> wordString=trie.level(temp,s);

    for(int i=0;i<wordString.size();i++)
        cout<<wordString[i]<<endl;

    return true;
}

vector<string> taken;
bool TrieNode::game_generation(TrieNode *root,string key)
{
    TrieNode *temp = root;

    string k = key;
    int index = k[0]-'a';

    if(temp->children[index])
        temp = temp->children[index];
    else
        return false;

    vector<string> wordString = trie.level(temp,k);
    for(int i=0;i<wordString.size();i++)
    {
        int f=0;
        for(int j=0;j<taken.size();j++)
        {
            if(wordString[i]==taken[j]) //If already the word is taken
                f=1;
        }
        if(f!=1)
        {
            cout<<"Word = "<<wordString[i];
            taken.push_back(wordString[i]);
            return true;
        }
    }
    return false;
}

void TrieNode::game(TrieNode *root)
{
    string str;
    cout<<"\nEnter word : ";
    cin>>str;
    string endLetter;
    int n = str.length();
    endLetter = str[n-1];

    if(!trie.game_generation(root,endLetter))
        cout<<"No Word with the letter "<<endLetter<<" as start"<<endl;

    return;
}

int main()
{
    string name;
    string pass="";

    //Formatting for Login Page
    cout<<"\n\t\t\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\n";
    cout<<"\t\t\xb0                                               \xb0\n";
    cout<<"\t\t\xb0      \xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4       \xb0\n";
    cout<<"\t\t\xb0                 WORDIFY!!                     \xb0\n";
    cout<<"\t\t\xb0      \xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4       \xb0\n";
    cout<<"\t\t\xb0                                               \xb0\n";
    cout<<"\t\t\xb0           Let's make words simple:)!          \xb0\n";
    cout<<"\t\t\xb0                                               \xb0\n";
    cout<<"\t\t\xb0                                               \xb0\n";
    cout<<"\t\t\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\n\n\n";
    cout<<"\n\t\t\t\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\n";

    cout<<"\t\t\t  USER NAME : ";
    cin>>name;
    if (name == "wordify")
    {
        int i=0,f=0;
        while(i<2)
        {
            cout<<"\t\t\t  PASSWORD  : ";
            cin>>pass;
            if(pass == "123") //password
            {
                cout << "\n\t\t\t\t ACCESS GRANTED!!\n";
                cout<<"PLEASE WAIT..";
                sleep(2);
                break;
            }
            else
            {
                cout << "\n\t\t\t WRONG PASSWORD !! TRY AGAIN \n";
                cout<<"\n\t\t\t\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\n";
                i++;
                f++;
            }
        }
        if(f==3)
        {
            cout<<"\n\t\t\t\tACCESS DENIED!!!\n" ;
            exit(0);
        }
    }
    else
    {
        cout<<"\t\t\t  INVALID USERNAME \n";
        exit(0);
    }
    cout<<"\n\t\t\t\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\n";
    string word , meaning;
    int x;

    TrieNode*root=trie.getNode();
    trie.toTrie(root);

    system("CLS");
    cout<<"\n\t\t\t\t\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\n";
    cout<<"\t\t\t\t MAIN MENU ...\n";
    cout<<"\t\t\t\t 1.Check the validity of the word w.r.t this dictionary\n";
    cout<<"\t\t\t\t 2.View the Dictionary words\n";
    cout<<"\t\t\t\t 3.Search for a word's meaning\n";
    cout<<"\t\t\t\t 4.Insert a New word into the dictionary\n";
    cout<<"\t\t\t\t 5.Auto-complete\n";
    cout<<"\t\t\t\t 6.Auto generation \n";
    cout<<"\t\t\t\t 7. Exit \n";
    cout<<"\n\t\t\t\t\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\n";
    do {
        cout<<"\nEnter your option : ";
        cin>>x;

        switch (x)
        {
            case 1:
            {
                cout<<endl<<setw(85)<<" Check the validity of the word w.r.t this dictionary \n" ;
                cout<<"Enter word to search for : ";
                cin>>word;

                if(trie.search_key(root,word))
                    cout<<"\t Word is meaningful and present in the Dictionary !"<<endl;
                else
                    cout<<"\t Word is not present in the dictionary !!"<<endl;
                break;
            }
            case 2:
            {
                cout<< endl<<setw(85) <<" View the Dictionary words \n";
                trie.autoComplete(root,"");
                break;
            }
            case 3:
            {
                cout<<"\n Search for a word's meaning \n";
                cout<<" Enter the word : ";
                cin>>word;
                trie.find_Meaning(root,word);
                break;
            }
            case 4:
            {
                cout<<endl <<setw(85)<<"Insert a New word into the dictionary \n ";
                cout<<"Enter the New word : ";
                cin>>word;
				cout<<"\nEnter the meaning of the word : ";
				cin>>meaning;
				trie.insert_key(root,word,meaning);
                break;
            }
            case 5:
            {
                cout<<"\n Auto-complete \n";
                cout<<"Enter to search..";
                cin>>word;
                if(!trie.autoComplete(root,word))
                    cout<<"No Match"<<endl;
                break;
            }
            case 6:
            {
                int x;
                trie.game(root);
                while(x)
                {
                    cout<<"\t\t\tDo you want to continue?(1/0) : ";
                    cin>>x;
                    if(x)
                        trie.game(root);
                }
                break;
            }
            case 7:
                exit(0);
        }

    }while(x>=1 && x<=6);
}



//Storing login details into the file
    /*if (name == "wordify")
    {
        cout<<"\t\t\t   Password  : ";
        char ch;
        ch = _getch();
        while (ch!=13)
        {
            pass.push_back(ch);
            cout << '*';
            ch = _getch();
        }
    }
    else
    {
        cout<<"\t\t\t   Invalid Username \n";
        exit(0);
    }
    cout<<"\n\t\t\t\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\n";
    for(int i=0; i<3;i++)
    {
        if(pass == "123") //password
        {
        cout << "\n\t\t\t\t ACCESS GRANTED!!\n";
        sleep(1);
        break;
        }
        else if( i<2)
        {
            cout << "\n\t\t\tWrong password !! Try again \n";
            cout<<"\n\t\t\t\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\n";
            cout<<"\t\t\t   Password  : ";
            char ch;
            ch = _getch();
            while (ch!=13)
            {
                pass.push_back(ch);
                cout << '*';
                ch = _getch();
            }
        }
        else
        {
            cout<<"\n\t\t\t\tACCESS DENIED!!!\n" ;
            exit(0);
        }
    }*/
