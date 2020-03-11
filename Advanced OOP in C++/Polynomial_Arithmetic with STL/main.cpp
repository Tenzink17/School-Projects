#include <fstream>
#include <iostream>
#include<string.h>
#include<string>
#include <cstdlib>
#include<map>
using namespace std;

string str[1];
string linkedList[20];


int totalPolynomials = 0;
int index = 0;

template<class T>

class node
{
private:
    T co;
    T exp;
    node* Link;

public:
    node()
    {
        Link=0;
    }
    node(T i, T j)
    {
        co=i;
        exp = j;
        Link=0;
    }
    T& coefficent()
    {
        return co;
    }
    T&exponent()
    {

        return exp;
    }

    node* & link()
    {
        return Link;
    }
};


template<class T>
void print_list(node<T>* p)
{
    while(p)
    {
        pair<int,int> value(p->exponent(),p->coefficent());
        cout<<value.first<<"   "<<value.second<<endl;
        p=p->link();

    }
    cout<<endl;
}
template<class T>
void addToMap(node<T>* p, map<int, int> &temp)
{
    while(p)
    {

        temp.insert({p->exponent(),p->coefficent()});
        p=p->link();

    }
    cout<<endl;


}

node<int>* make_int_list(int n)
{

    if(n<=0)
        return 0;

    node<int>* first,*p,*q;
    first=p=new node<int>(1, n);
    int e = 0;
    for(int i=2; i<=n; i++)
    {
        e = n-i;
        q=new node<int>(i,e);
        p->link()=q;
        p=q;
    }
    return first;
}

template<class T>
void print_list_rec(node<T>* p)
{
    if(p==0)
        return;
    cout<<p->coefficent()<<"x^"<<p->exponent()<<" ";
    print_list_rec( p->link());

}
template<class T>

void add_at_end(node<T>* &first, node<T>*r)
{
    node<T>* p;
    p=first;
    while(p->link())
    {
        p=p->link();
    }
    p->link()=r;

}

string getString(char x)
{
    // string class has a constructor
    // that allows us to specify size of
    // string as first parameter and character
    // to be filled in given size as second
    // parameter.
    string s(1, x);

    return s;
}

int initialStep()
{

    ifstream infile;
    infile.open("input.txt");

    if (infile.fail())
    {
        cout << "file opening failed" << endl;
    }

    while(!infile.eof())
    {
        infile>>str[totalPolynomials];
        totalPolynomials++;
    }

    infile.close();

    int x_length = 0;

    for(int p = 0; p<totalPolynomials; p++)
    {

        string x = str[p];
        x_length = x.length();
        char arr [x_length];


        for(int  i = 0; i<x_length; i++)
        {
            arr[i] = x.at(i);
        }

        for(int i = 0; i<x_length; i++)
        {

            if(i==0 && arr[0] != '-' )
            {
                string s = "+";
                s.append(getString(arr[0]));
                while(isdigit(arr[i+1]))
                {
                    s.append(getString(arr[i+1]));
                    i++;
                }
                if(arr[i]=='x')
                {
                    s.append(getString(arr[i]));
                    if(arr[i+1] == '^')
                    {
                        i++;
                        s.append(getString(arr[i]));

                        while(isdigit(arr[i+1]))
                        {
                            s.append(getString(arr[i+1]));
                            i++;
                        }
                    }

                }
                linkedList[index++] = s;

            }
            else if(i==0 && arr[0] == '-' )
            {
                string s = "";

                s.append(getString(arr[0]));

                while(isdigit(arr[i+1]))
                {
                    s.append(getString(arr[i+1]));
                    i++;
                }

                if(arr[i]=='x')
                {
                    s.append(getString(arr[i]));

                    if(arr[i+1] == '^')
                    {
                        i++;
                        s.append(getString(arr[i]));

                        while(isdigit(arr[i+1]))
                        {
                            s.append(getString(arr[i+1]));
                            i++;
                        }
                    }
                }
                linkedList[index++] = s;
            }
            if(arr[i] == '+'|| arr[i] == '-' || arr[i] == '*')
            {
                string  s = "";
                s.append(getString(arr[i]));
                if(isdigit(arr[i+1]))
                {
                    int  j = ++i;
                    while(isdigit(arr[i]))
                    {
                        s.append(getString(arr[i]));

                        i++;
                    }
                    if(arr[i]=='x')
                    {
                        s.append(getString(arr[i]));

                        if(arr[i+1]=='^')
                        {

                            s.append(getString(arr[i+1]));
                            i = i+1;
                        }
                        while(isdigit(arr[i+1]))
                        {
                            i++;
                            s.append(getString(arr[i]));
                        }
                    }
                }
                if(arr[i+1]=='x')
                {
                    s.append(getString(arr[i+1]));

                    if(arr[i+2]=='^')
                    {

                        s.append(getString(arr[i+2]));
                        i = i+2;
                    }
                    while(isdigit(arr[i+1]))
                    {
                        i++;
                        s.append(getString(arr[i]));

                    }

                }
                linkedList[index++] = s;

            }
            else
                continue;
        }
    }
    return index;
}


void prepareStuff(char op [],int  co [], int  exp[], int sz = index)
{
    for(int i = 0; i<sz; i ++)
    {
        string x = linkedList[i];
        int l = x.length();
        int a = 0;
        int ex= 0;
        int coe= 0;
        if(x.at(a)=='+'||x.at(a)=='*'|| x.at(a)=='-')
        {

            op[i] = x.at(a);
            string s = "";
            a++;

            bool  p = false;
            while(l>a&& isdigit(x.at(a)))
            {
                s.append(getString(x.at(a)));
                coe = atoi(s.c_str());
                a++;
                p = true;

            }

            if(p)
            {
                co[i] = atoi(s.c_str());
            }
            else
            {
                co[i] = 1;
            }
            if(l>a && x.at(a)=='x')
            {
                string s1 = "";
                a++;

                if(l>a &&x.at(a)=='^')
                {
                    a++;

                    while(l>a && isdigit(x.at(a)))
                    {
                        s1.append(getString(x.at(a)));
                        a++;
                    }
                    exp[i] =atoi(s1.c_str());
                    ex = exp[i];

                }
                else
                {
                    exp[i] = 1;
                    ex = exp[i];
                }
            }
            else
            {
                exp[i] = 0;
            }
        }
    }

}

void polynomialList(node<int> * & head, char op [ ], int co [], int  ex[], int length)
{
    for(int i = 1; i<length; i++)
    {
        node<int> *temp;
        if(op[i]=='-')
        {
            temp = new node<int>(-abs(co[i]), ex[i]);
            add_at_end(head,temp);
        }
        else if (op[i]=='+')
        {
            temp = new node<int>(co[i], ex[i]);
            add_at_end(head,temp);
        }
    }
}
void my_swap (node<int> *node_1, node <int>*node_2)
{
    int temp = node_1->coefficent();
    int temp2 = node_1->exponent();
    node_1->exponent()= node_2 ->exponent();
    node_1->coefficent() = node_2->coefficent();
    node_2 ->exponent() = temp2;
    node_2->coefficent() = temp;

}
void bubble_sort(node<int> *head)
{
    int swapped;

    node<int> *lPtr; // left pointer will always point to the start of the list
    node<int> *rPrt = NULL; // right pointer will always point to the end of the list
    do
    {
        swapped = 0;
        lPtr = head;
        while(lPtr->link() != rPrt)
        {
            if (lPtr->exponent() < lPtr->link()->exponent())
            {
                my_swap(lPtr, lPtr->link());
                swapped = 1;
            }
            lPtr = lPtr->link();
        }
        rPrt = lPtr;

    }
    while(swapped);
}

node<int> * performOperation(node<int> * head)
{
    int i = 0;
    node<int> * start = head;
    node<int>* finish = head->link();
    node<int>* newNode, *ptr;

    while(start!=nullptr)
    {
        if(finish!=nullptr && start->exponent()==finish->exponent())
        {
            int co = (start->coefficent()+finish->coefficent());
            int exp = start->exponent();

            node<int>* check = finish->link();

            bool checked = false;
            while(start->exponent()==check->exponent())
            {
                co = co + check->coefficent();

                check = check->link();
                checked = true;
            }
            if(checked)
            {
                start= check;
                finish = check->link();
            }
            else
            {
                start = finish->link();
                finish = finish->link()->link();
            }
            if(i==0)
            {
                newNode = new node<int>(co,exp);
                ptr = newNode;
                i++;
            }
            else
            {
                node<int>* t = new node <int>(co,exp);
                ptr->link() =t;
                ptr = t;
            }
}
        else
{
            int co1 = start->coefficent();
            int exp1 = start->exponent();
            if(i==0)
            {
                newNode = new node<int>(co1,exp1);
                ptr = newNode;
                i++;
            }
            else
            {
                node<int>*t =  new node <int>(co1, exp1);
                ptr->link() = t;
                ptr = t;

}
if(start && finish==nullptr)
    {
        start = nullptr;
        ptr  = nullptr;
    }
    else{
        start = finish;
            finish = finish ->link();
    }
}

}

    return newNode;
}


int main()
{
    map<int,int> poly1,poly2,sum;

    const int &length = initialStep();
    char op[length];
    int co [length];
    int ex[length];


    prepareStuff(op,co,ex);

    node<int> *head;
    if(op[0]=='-')
    {
        head = new node<int>(-abs(co[0]),ex[0] );
    }
    else
    {
        head = new node<int>(co[0],ex[0] );
    }
    polynomialList(head,op,co,ex,length);



    cout<<"Read from text file \n";

    cout<<str[0]<<"\n";

    cout<<"\n";

    cout<<"K = expo , V = coef"<<endl;
    cout<<"In Map(K,V) \n";

    print_list(head);
    addToMap(head, poly1);

    cout<<"\n";

    bubble_sort(head);

    cout<<"Sorted by highest Exponent / Key \n";

    print_list(head);
    addToMap(head,poly2);

    cout<<"\n";


    node<int> * temp = performOperation(head);

    cout<<"Canonical Form \n";


    addToMap(temp,sum);

    auto it = sum.end();
    it--;

    for(; it!= sum.begin(); it--)
    {
        cout<<it->first<<"  "<<it->second<<"\n";
    }
    cout<<it->first<<"  "<<it->second<<"\n";






    return 0;
}
