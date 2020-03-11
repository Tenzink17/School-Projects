#include<iostream>
#include <cstdlib>
#include<cassert>
#include<bits/stdc++.h>


using namespace std;

template <class T> // forward declaration
class VNT;
template <class T> //forward declaration
ostream& operator<<(ostream& os, VNT<T> s);
template < class T>
class VNT
{
private:

    int low, high, low2, high2;
    int max = INT_MAX;
    T** p;
    int count = 0;
    // int, float, double array

public:

    // default constructor
    // allows for writing things like SA a;

//    VNT()
//    {
//        low = 0;
//        high = -1;
//        low2 = 0;
//        high2 = -1;
//        p = NULL;
//    }


    // 2 parameter constructor lets us write
    // SA x(10,20);

//    VNT(int l, int h, int l2, int h2)
//    {
//        if (((h - l + 1) <= 0 )||((h2-l2+1)<=0))
//        {
//            cout << "constructor error in bounds definition" << endl;
//            exit(1);
//        }
//        low = l;
//        high = h;
//        low2 = l2;
//        high2 = h2;
//        p = new T*[h - l + 1];
//        for (int i = 0; i < (h - l + 1); i++)
//        {
//            p[i] = new T[h2 - l2 + 1];
//        }
//    }


    // single parameter constructor lets us
    // create a SA almost like a "standard" one by writing
    // SA x(10); and getting an array x indexed from 0 to 9

    VNT(int i, int j)
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
        int size = high-low+1;
        int size2 = high2-low2+1;

        for(int i = 0; i<size; i++)                                    // unitiliazed matrix;
        {
            for(int j = 0; j<size2; j++)
            {
                p[i][j]= max;                                               // empty
            }
        }
    }
    // copy constructor for pass by value and
    // initialization

    VNT(const VNT<T>& s)
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
    // destructor

    ~VNT()
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

    //overloaded () lets us write
    // VNT x(10,20);  x[5][15]= 100;
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

    VNT& operator=(const VNT<T>& s)
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

//    void populate()
//    {
//        int size = (high-low+1);
//        int size2 = (high2-low2+1);
//        for(int i =0 ; i<size; i++)
//        {
//            for(int j = 0; j<size2; j++)
//            {
//                p[i][j] = (rand()%100);
//            }
//        }
//    }

    void print()
    {
        int size = getRow();
        int size2 = getCol();
        for(int i =0 ; i<size; i++)
        {
            for(int j = 0; j<size2; j++)
            {
                cout<<p[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    VNT& operator*(const VNT<T> a)
    {
        if(this->high2==a.high)
        {
            VNT<T> temp(1,1);
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

    void add(int value)
    {
        int row = getRow()-1;
        int col = getCol()-1;

        if(p[row][col]!=max)                                   // if its full
        {
            cout<<"The matrix is full, cannot add"<<endl;
            return;
        }
        p[row][col] = value;                                //  insert bottom right most;

        addToVNT(row, col);
    }

    void addToVNT(int row, int col)
    {
        int i = row;
        int j = col;

            if(i==0 && j==0)
            {
                return;
            }

            if(i==0)                                                    // if row is 0
            {
                if(p[i][j-1] > p[i][j])
                {
                    swap(p[i][j-1], p[i][j]);
                    addToVNT(i,j-1);
                }
                return;
            }

            if(j==0)                                                  // if the col is 0
            {
                if(p[i-1][j] > p[i][j])
                {
                    swap(p[i-1][j],p[i][j]);
                    addToVNT(i-1,j);
                }
                return;
            }
            if(p[i-1][j]>p[i][j])                                 // move up (row) the VNT
            {
                swap(p[i-1][j],p[i][j]);
                addToVNT(i-1,j);
            }

            if(p[i][j-1]>p[i][j])                               // move left (column) the VNT
            {
                swap(p[i][j-1],p[i][j]);
                addToVNT(i,j-1);
            }
        }

    void swap(int &t, int &t1)
    {
        int temp = t;
        t = t1;
        t1 = temp;
    }

    int getRow()
    {
        return high-low+1;
    }
    int getCol()
    {
        return high2 - low2 +1;
    }

    bool isEmpty()
    {
        if(p[0][0]==max)
            return true;
        return false;
    }

    bool isFull()
    {
        if((p[high-1][high2-1])!=INT_MAX)
        {
            return true;
        }
        return false;
    }
    int getMin()
    {
        if(isEmpty())                                           // if its empty return MAX_INT
        {
            return max;
        }
        int tempMin = p[0][0];

        p[0][0]= max;                                     // mark as empty

        adjustVNT(0,0);                                 // now readjust from the beginning;

        return tempMin;                               // current min;
    }

    void adjustVNT(int i, int j)
    {

	int bottom = (i + 1 <= high) ? p[i + 1][j] : max;
	int right = (j + 1 <=high2) ? p[i][j + 1] : max;

	if (bottom < right)	// go down
	{
		swap(p[i][j], p[i + 1][j]);
		adjustVNT( i + 1, j);
	}

	if (bottom > right)	// go right
	{
		swap(p[i][j], p[i][j + 1]);
		adjustVNT( i, j + 1);
	}
}

    bool find(int value)
    {
        int * f = std::find(*p,(*(p+high)+high2+1),value);

        if(*f==value)
            return true;
        else
            return false;
    }

    void sort(int *k, int size)
    {
        int counter = 0;
        for(int i = 0; i<getRow(); i++)
        {
            for(int j =0; j<getCol(); j++)
            {
                *(k+counter) = p[i][j];
                counter++;
            }
        }

        std::sort(k,(k+size));

    }

    // overloads << so we can directly print SAs

    friend ostream& operator<<(ostream& os,  const VNT<T> &s);
};

template <class T>
ostream& operator<<(ostream& os,  const VNT<T> &s)
{
    int size=s.getRow();
    int size2 = s.getCol();
    for(int i=0; i<size; i++)
    {
        for(int j= 0; j<size2; j++)
        {
            os<<s(i,j)<<" ";
        }
        os<<endl;
    }
    return os;
}

int main()
{
    VNT<int> a{4,4};                // 12 elements     m = 4, n = 4  so  m*n = 16

    int arr [] = {3,2,6,7,9,1,11,22,66,21,10,0,13,24, 15,16};   // 16 elements         n = 4     so    n * n = 16

    int nSquared = (sizeof(arr)/sizeof(arr[0]));      // 16


    cout<<"Before sorting the array \n";

    for(int i = 0; i<nSquared; i++)
    {
        cout<<arr[i]<<" ";
        a.add(arr[i]);
    }
    cout<<"\n \n";


    cout<<"VNT after adding the values using add()\n";
    a.print();


    cout<<"\n \n";

    int v = 15;
    cout<<"finding the value "<<v<<" in VNT using STL find(). True(1) False(0) : ";
    cout<<a.find(v)<<"\n \n";                         // STL FIND

    a.sort(arr,nSquared);                               // sort the array by adding to it and adjust VNT

    cout<<"After sorting the array using the STL sort() \n";
    for(int i = 0; i<nSquared; i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<"\n";



    return 0;
};

