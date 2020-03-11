#include<iostream>
#include <cstdlib>
#include<cassert>

using namespace std;

template <class T> // forward declaration
class SA;
template <class T> //forward declaration
ostream& operator<<(ostream& os, SA<T> s);
template < class T>
class SA
{
private:

    int low, high, low2, high2;
    T** p;                                                                                          // int, float, double array


public:

    // default constructor
    // allows for writing things like SA a;


    SA()
    {
        low = 0;
        high = -1;
        low2 = 0;
        high2 = -1;
        p = NULL;
    }


    // 2 parameter constructor lets us write
    // SA x(10,20);

    SA(int l, int h, int l2, int h2)
    {
        if (((h - l + 1) <= 0 )||((h2-l2+1)<=0))
        {
            cout << "constructor error in bounds definition" << endl;
            exit(1);
        }
        low = l;
        high = h;
        low2 = l2;
        high2 = h2;
        p = new T*[h - l + 1];
        for (int i = 0; i < (h - l + 1); i++)
        {
            p[i] = new T[h2 - l2 + 1];
        }
    }


    // single parameter constructor lets us
    // create a SA almost like a "standard" one by writing
    // SA x(10); and getting an array x indexed from 0 to 9

    SA(int i, int j)
    {
        low = 0;
        high = i - 1;
        low2 = 0;
        high2 = j - 1;
        p = new T* [i];
        for (int row = 0; row < i; row++)
        {
            p[row] = new T[j];
        }
    }
    // copy constructor for pass by value and
    // initialization

    SA(const SA<T>& s)
    {
        int size = s.high - s.low + 1;
        int size2 = s.high2 - s.low2 +1;
        p = new T*[size];

        for (int row = 0; row < size; row++)
        {
            p[row] = new T[size2];
        }

        for (int i = 0; i < size; i++)
        {
            for(int j = 0; j <size2; j++)
            {
                p[i][j] = s.p[i][j];
            }
        }
        low = s.low;
        high = s.high;
        low2 = s.low2;
        high2 = s.high2;

    }
    // move constructor
     SA(SA<T> && s)
    {
        low = s.low;
        high = s.high;
        low2 = s.low2;
        high2 = s.high2;
        p = s.p;
        s.p = nullptr;
    }
    
    // destructor

    ~SA()
    {
        for (int i = 0; i < (high - low + 1); i++)
            delete[] p[i];
        delete[] p;
    }




    //overloaded [] lets us write
    //SA x(10,20); x[15]= 100;
//    T& operator[](int i)
//    {
//        if(i<low || i>high)
//        {
//            cout<< "index "<<i<<" out of range"<<endl;
//            exit(1);
//        }
//        return *p[i-low];
//    };

    //overloaded [] lets us write
    //SA x(10,20); x[15]= 100;
    T&operator()(int i, int j)
    {
        if(i<low || i>high || j<low2 || j>high2)
        {
            cout<< "index "<<i<<" &"<<j<<" out of range"<<endl;
            exit(1);
        }
        return p[i-low][j-low2];
    }


    // overloaded assignment lets us assign
    // one SA to another

    SA& operator=(const SA<T>& s)
    {

        int size = high - low + 1;
        int size2 = high2 - low2+1;
        if (this == &s)
            return *this;

        for (int i = 0; i < size; i++)                      //destroy the old heap allocations
        {
            delete[] p[i];
        }
        delete[] p;

        high = s.high;
        low = s.low;
        high2 = s.high2;
        low2 = s.low2;

        int s1 = s.high - s.low + 1;
        int s2  = s.high2 - s.low2+ 1;

        p = new T*[s1];
        // new heap location
        for (int i = 0; i < s1; i++)
        {
            p[i] = new T[s2];
        }

        for(int i = 0; i<s1; i++)                               //  copy the values
        {
            for(int j = 0; j<s2; j++)
            {
                p[i][j] = s.p[i][j];
            }
        }
        return *this;
    };

    void populate()
    {
        int size = (high-low+1);
        int size2 = (high2-low2+1);
        for(int i =0 ; i<size; i++)
        {
            for(int j = 0; j<size2; j++)
            {
                p[i][j] = (rand()%100);
            }
        }
    }

    void print()
    {
        int size = (high-low+1);
        int size2 = (high2-low2+1);
        for(int i =0 ; i<size; i++)
        {
            for(int j = 0; j<size2; j++)
            {
                cout<<p[i][j]<<" ";
            }
            cout<<endl;
        }
    }


    SA& operator*(const SA<T> a)
    {
        if(this->high2==a.high)
        {
            SA<T> temp(1,1);
            int size = high - low + 1;
            int size2 = a.high2 - a.low2+1;
            temp.high2 = a.high2;
            temp.high = high;
            temp.low2 = a.low2;
            temp.low = low;
            temp.p = new T*[size];                                    // new heap location
            for (int i = 0; i < size; i++)
            {
                temp.p[i] = new T[size2];
            }
            int row =size;
            int col = high2 - a.low2+1;
            int col2 = size2;
            int sum = 0;
            for(int i = 0; i<row; i++)
            {
                for(int j = 0; j<col2; j++)
                {
                    for(int k = 0; k<col; k++)
                    {
                        sum = sum+p[i][k]*a.p[k][j];
                    }
                    temp.p[i][j] = sum;
                    sum= 0;
                }
                delete [] p[i];
            }
            delete [] p;

            high = temp.high;
            low = temp.low;
            high2 = temp.high2;
            low2 = temp.low2;

            size = high-low+1;
            size2 = high2-low2+1;

        for(int i = 0; i<size; i++)
        {
            p = new T*[size];
           for(int j = 0; j<size2; j++)
           {
               p[j] = new T[size2];
           }
        }

        for(int i = 0; i<size; i++)
        {
            for(int j = 0; j<size2; j++)
            {
                p[i][j] = temp.p[i][j];
            }

        }
        }
        return *this;
    }

    // overloads << so we can directly print SAs

    friend ostream& operator<<(ostream& os,  const SA<T> & s);

};

template <class T>
ostream& operator<<(ostream& os, const SA<T> &s)
{
    int size=s.high-s.low+1;
    int size2 = s.high2 - s.low2 +1;
    for(int i=0; i<size; i++)
    {
        for(int j = 0; j<size2; j++)
        {
            os<<s(i,j)<<endl;
        }
    }
    return os;
};


int main()
{
    SA<int> a(2,3);
    SA<int> b(3,2);
    
    SA<int> c;

    SA<int> d = std::move(c);  //  now c->p==nullptr 
    
    a(1,1) = 1;
    a(1,2) = 2;
    a(1,0) = 0;

    a(0,0) = 0;
    a(0,1) = 1;
    a(0,2) = 2;

    b(0,0)  = 0;
    b(0,1) = 1;
    b(1,0) = 2;
    b(1,1) = 3;
    b(2,0) = 4;
    b(2,1) =  5;

    cout<<"a matrix \n";

    a.print();

     cout<<"b matrix \n";
    b.print();


    a.operator*(b);

     cout<<"a * b matrix \n";
    a.print();



    return 0;
};

