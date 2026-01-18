#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "global.h"
using namespace std;


int main()
{
    cout<<"Enter the number of equations (must be less or equal to unknowns) : ";

    int eq = validateint_fullwithrangealso(eq);
    cout<<"Enter the number of unknowns : ";
    int un = validateint_fullwithrangealso(un);

    char ch = 'X';
        cout<<endl<<endl;
        float **arr = new float*[eq];
        float **arr_copy = new float*[eq];
        for(int i = 0 ; i<eq ; i++)
        {
            arr[i] = new float[un];
            arr_copy[i] = new float[un];
            cout<<"Enter the values for Equation # "<<i+1<<" : "<<endl;

            for(int j = 0 ; j<un ;j++)
            {
                cout<<ch<<j+1<<" of Equation # "<<i+1<<" : "<<endl;
                arr[i][j] = validatefloat_full(arr[i][j]);
                arr_copy[i][j] = arr[i][j];
            }
        }

        float **b = new float*[eq];
        float **b_copy = new float*[eq];
        for(int i = 0 ; i<eq; i++)
        {
            b[i] = new float[1];
            b_copy[i] = new float[1];
            cout<<"Enter the values for Constant # "<<i+1<<" : "<<endl;
            for(int j = 0 ; j<1; j++)
            {
                b[i][j] = validatefloat_full(b[i][j]);
                b_copy[i][j] = b[i][j];
            }
        }

    if(eq == un)
    {



        float **sol = inverse_row_echelon(arr , b , arr_copy , b_copy, eq, un);

        //Display the inverse :

            for(int i = 0 ; i< eq ; i++)
            {
                for(int j = 0 ; j < 1 ; j++)
                {
                    cout<<ch<<i+1<<" is : ";
                    print_float_as_integer_if_whole(sol[i][j] , 10);
                }
                cout<<endl;
            }

    }
    else if(eq < un)
    {
        cout<<"Equations are less than unknowns so there may be infinite or no solutions "<<endl;
    }
    else
    {
        cout<<"You entered a redundant equation making it overdetermined system "<<endl;
    }


    //Deallocations :

        for(int i = 0 ; i<eq ; i++)
        {
            delete[] arr[i];
            delete[] arr_copy[i];
            delete[] b_copy[i];
            delete[] b[i];
        }
        delete[] arr;
        delete[] arr_copy;
        delete[] b_copy;
        delete[] b;
        arr = nullptr;
        arr_copy = nullptr;
        b = nullptr;
        b_copy = nullptr;


    return 0;
}

