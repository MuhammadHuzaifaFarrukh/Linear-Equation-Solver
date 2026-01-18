#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "global.h"

using namespace std;

//All global.h functions definitions

void print_float_as_integer_if_whole(float value, int integral_width = 0, char fill_char = ' ') //Width will be padded with char fill_char
{
    if (std::floor(value) == std::ceil(value))
    {
        // The value has no fractional part, so it's a whole number
        std::cout << std::setw(integral_width) << std::setfill(fill_char) << static_cast<int>(value) ;
    }
    else
    {
        // The value has a fractional part, so print it as a float
        std::cout << std::fixed << std::setprecision(5) << std::setw(integral_width) << std::setfill(' ') << value ;
    }
}


int validateint_fullwithrangealso(int n)
{
    using namespace std;

    char ch;

    while (1)
    {
        //cout << "Enter an integer : ";
        if (cin >> n)
        {
            // Check if there's leftover input (like a decimal point)
            if (cin.get(ch) && ch != '\n')
            {
                cout << "Invalid Input. Please enter a valid integer again.\n";
                cin.clear();  // Clear error flags
                while (cin.get() != '\n');  // Flush input buffer
            }
            else
            {
                if(n>0)
                {
                    return n;
                }
                else
                {
                    cout<<"Size or Equations or Unknowns Number cannot be less than 1"<<endl;
                }
            }
        }
        else
        {
            cout << "Invalid Input. Please enter a valid integer again.\n";
            cin.clear();  // Clear error state
            while (cin.get() != '\n');  // Flush input buffer
        }
    }
}

float validatefloat_full(float num)
{

    using namespace std;
    char ch;

    while (1)
    {
        //std::cout << "Enter a float number : ";

        // Read input and check if it is a valid float
        if (std::cin >> num)
        {
            // Check if there's extra invalid input (like characters after the number)
            if (std::cin.get(ch) && ch != '\n')
            {
                std::cout << "Invalid Input! Only numbers and a single decimal point are allowed.\n";
                std::cin.clear();  // Clear error flags
                while (std::cin.get() != '\n');  // Flush input buffer
            }
            else
            {
                return num;  // Valid float input
            }
        }
        else
        {
            std::cout << "Invalid Input! Please enter a valid float number.\n";
            std::cin.clear();  // Clear error state
            while (std::cin.get() != '\n');  // Flush input buffer
        }
    }
}

void allocate(float **arr, int rows, int columns)
{
    for(int i =0; i<rows ; i++)
    {
        arr[i] = new float[columns];
        for(int j = 0 ; j<columns ; j++)
        {
            cout<<"Enter the element ["<<i<<"]["<<j<<"] : ";
            arr[i][j] = validatefloat_full(arr[i][j]);
        }
    }
}

void swapping(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b= temp;
}



float** inverse_row_echelon(float **arr , float **b ,float **arr_copy , float **b_copy, int m , int n)
{

        int row_index = 0;
        int col_index = 0;

        int row_index_inv = 0;
        int col_index_inv = 0;
        int index =0;
        //rows = m , columns = n


        for(int iter = 0 ; iter < m-1 ; iter++)
        {
            //Find the row with the leading coefficient as non-zero
            if(arr[row_index][col_index] == 0 )
            {
                bool found = 0;
                for(int i = row_index+1 ; i<m ; i++)
                {
                    if(arr[i][col_index]!=0)
                    {

                        index = i;

                        found = 1;
                        break;
                    }
                }

                if(found)
                {
                    // 1) Swapping the rows :
                    for(int i = 0 ; i <n ; i++)
                    {
                        swapping(&arr[row_index][i], &arr[index][i]);

                    }

                    for(int i = 0 ; i<1 ; i++)
                    {
                        swapping(&b[row_index][i] , &b[index][i] );
                    }

                }
                //else
                //{

                //    cout<<"All columns are zero or there is a zero in the product of diagonal entries , hence inverse does not exist for this matrix "<<endl;

               //     return 0;
               // }

            }

            // 2) Scaling the rows :
            float pivot = arr[row_index][col_index];

            if(pivot!=1)
            {

                for(int i = col_index ; i<n ; i++)
                {
                    arr[row_index][i] = arr[row_index][i] / pivot ;

                }

                for(int i = 0 ; i < 1 ; i++)
                {
                    b[row_index][i] = b[row_index][i] / pivot;
                }


            }

            // 3) Adding a multiple of one row to other :

            for(int i = row_index ; i< m-1 ; i++)
            {
                float k = arr[i+1][col_index];

                for(int j = col_index ; j < n ; j++)
                {
                    arr[i+1][j]  = arr[i+1][j] +  (arr[row_index][j] *  (k) * (-1) );
                }

                for(int j = 0 ; j < 1 ; j++)
                {
                    b[i+1][j]  = b[i+1][j] +  (b[row_index][j] *  (k) * (-1) );
                }
            }

            row_index++;
            col_index++;

            //Final Row Scaling :
            if(row_index == m-1)
            {
                for(int i = 0 ; i<1 ; i++)
                {
                    b[row_index][i] = b[row_index][i] / arr[row_index][col_index] ;
                }


                if(arr[row_index][col_index] == 0 )
                {
                   //Do Nothing
                }
                else
                {
                    arr[row_index][col_index] /= arr[row_index][col_index];
                }

            }

        }

        //Above code gives only the row echelon form

        //Now doing the complete reduced row echelon form and checking the diagonal entries


        int pro = 1;
        for(int i = 0 ; i<m ; i++)
        {
            for(int j = 0 ; j<n ; j++)
            {
                if(i==j)
                {
                    pro *= arr[i][j];
                }
            }
        }

        if(pro == 0)
        {
             cout<<"This is not an Identity Matrix , Hence this system of equations does not have a Unique solution and may have either no solution or infinite solutions  "<<endl;
             for(int i = 0 ; i<m ; i++)
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

            exit(0);
        }
        else
        {
            cout<<"Solution for the set of below equations : "<<endl;

                for(int i = 0 ; i<m ; i++)
                {
                    char ch = 'X';
                    for(int j = 0 ; j<n ; j++)
                    {
                        if(arr_copy[i][j] == 0)
                        {
                            continue;
                        }
                        else if(arr_copy[i][j]<0 && i!=0)
                        {
                            cout<<"\b\b";
                            cout<<arr_copy[i][j]<<ch<<j+1<<" + ";
                        }
                        else
                        {
                            cout<<arr_copy[i][j]<<ch<<j+1<<" + ";
                        }
                    }
                    cout<<"\b\b";
                    cout<<" = ";
                    for(int j = 0 ; j<1 ; j++)
                    {
                        cout<<b_copy[i][0];
                    }
                    cout<<endl;
                }

            for(int iter = row_index ; iter >=1 ; iter--)
            {
                // 3) Adding a multiple of one row to other :

                for(int i = row_index ; i>=1 ; i--)
                {
                    float k = arr[i-1][col_index];

                    for(int j = col_index ; j > col_index-1 ; j--)
                    {
                        arr[i-1][j]  = arr[i-1][j] +  (arr[row_index][j] *  (k) * (-1) );
                    }

                    for(int j = 0 ; j<1 ; j++)
                    {
                        b[i-1][j]  = b[i-1][j] +  (b[row_index][j] *  (k) * (-1) );
                    }

                }

                row_index--;
                col_index--;


             }




        }



        /* //Use either below if or the if(value == -0.0)
        if(fabs(det) < 1e-10) // Treat very small values as 0
        {
             det = 0;
        }
        */
        return b;

}

