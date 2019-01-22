//Zhuk Anna Lab4 srom var#7
#include <iostream>
#include <string>
#include <stdlib.h>


using namespace std;

const int m = 251; // rozmirnist' za variantom
int Matrix[m][m] = {};

void getOpt(int* operand) // вивід на екран
{
//    for(int i = 0; i < m; ++i)
//    {
//        cout << operand[i] ;
//    }
    for(int i = m-1; i > -1; i--) // maybe m-1 -> deg()
    {
        cout << operand[i];
    }
    cout << endl;
}

void setOptOpt(int* optLeft, int* optRight) // =
{
    for(int i = 0; i < m; ++i)
    {
        optLeft[i] = optRight[i];
    }
}

void cyclicShiftRightOpt(int* operand, int shift)// опт >>> шагов
{
    int temp[m] = {};
    setOptOpt(temp, operand);

    for(int i = shift; i < m; i++)
    {
        operand[i] = temp[i-shift];
    }
    for(int i = 0; i < shift; i++)
    {
        operand[i] = temp[m - shift + i];
    }
}

void cyclicShiftLeftOpt(int* operand, int shift)
{
    //cyclicShiftRightOpt(operand, m - shift);

    int temp[m] = {};
    setOptOpt(temp, operand);

    for(int i =m-shift ; i < m; i++)
    {
        operand[i] = temp[i-m+shift] ;
    }
    for(int i = 0  ; i < m-shift; i++)
    {
        operand[i] = temp[i+shift];
    }
}

void setOptNull(int* operand)
{
    for(int i = 0; i < m; ++i)
    {
        operand[i] = 0;
    }
}

void setOptStr(int* operand, string str)
{
    string temp;
    int optPos = 0;
    for(int i = str.length()-1; i > -1; i--)
    {
        temp = str[i];
        if(optPos <= m)
        {
            operand[optPos] = strtol(temp.c_str(), nullptr, 2);
            optPos++;
        }
        else
        {
            cout << "this string is too big. overflow error." << endl;
            return;
        }

    }
}

void squareOpt(int* result, int* operand)
{
    setOptOpt(result, operand);
    cyclicShiftRightOpt(result, 1);
}

void additionOpt(int* result, int* operand1, int* operand2)
{
    for(int i = 0; i < m; ++i)
    {
        result[i] = operand1[i]^operand2[i];
    }
}

void setupMultMatrix() // нижчне нічого не робить :(
{
    int degreeOf2[m] = {}; // maybe m-1
    degreeOf2[0] = 1;

    for(int i = 1; i < m; ++i)
    {
        degreeOf2[i] = ((degreeOf2[i-1] * 2) % ((2*m)+1)); //maybe 2*(m-1)

    }
    int degreeI = 0;
    int degreeJ = 0;
    for(int i = 0; i < m; ++i)
    {
        degreeI = degreeOf2[i];
        for(int j = 0; j < m; ++j)
        {
            degreeJ = degreeOf2[j];//((2*m)+1)
            if((((degreeI + degreeJ) %((2*m)+1)) == 0) || (((degreeI - degreeJ) %((2*m)+1)) == 0) ||
               (((-degreeI + degreeJ) %((2*m)+1)) == 0) || (((-degreeI - degreeJ) %((2*m)+1)) == 0) )
            {
                Matrix[i][j] = 1;
            }
            else
            {
                Matrix[i][j] = 0;
            }
        }
    }

}

void getMatrix()
{
    for(int i = 0; i < m; ++i)
    {
        cout << endl;
        for(int j = 0; j < m; ++j)
        {
            cout << Matrix[i][j];
        }
    }
}

int multiplicationOptMatrix( int* operand1, int* operand2)
{
    int temp1[m] = {};
    int temp2[m] = {};
    int temp3[m] = {};//?
    int temp = 0;

    for(int i = 0; i < m; ++i)
    {
        temp = 0;
        for(int j = 0; j < m ; ++j)
        {
            //temp = 0;
            temp1[j] = Matrix[i][j] & operand1[j];
        }
        for(int a = 0; a < m; ++a)
        {
            temp = temp^temp1[a];
        }

        temp2[i] = temp;
    }
    temp = 0;
    for(int i = 0; i < m; ++i)
    {
        temp = temp^ (temp2[i] & operand2[i]);
    }
    return temp;
}

void multiplicationOpt(int* result, int* operand1, int* operand2)
{
    for(int i = 0; i < m; ++i)
    {
        result[i] = multiplicationOptMatrix(operand1, operand2);
        cyclicShiftLeftOpt(operand1, 1);
        cyclicShiftLeftOpt(operand2, 1);
    }
}


//int main()
//{
//    setupMultMatrix();
//    getMatrix();
//    return 0;
//}
int main()
{
    int opt1[m] = {};
    int opt2[m] = {};
    int optN[m] ={};
    int resultOpt[m] = {};

    string initStr = "10110000110000000110001000000100000111100110011001001000000101000001010100011110011011010110100100001100101101101101111011111011110011100010001101011111000111000010111011000000110110000001111001000000101110101110111100110101001111101101110111001100110";
    setOptStr(opt1, initStr);

    initStr = "11101010101111000001101001000101100010100110010010011010001000100110100110001111110010001011010110011111110001101111100000100001100101111111100001111111000000000001000010010000001010101001111001110001101001000101110101011000011110101101111111010110110";
    setOptStr(opt2, initStr);

    initStr = "00001100100111110000011111110111111101111101000100000010100100100011000101100001010000111111011000010011000100011100000000100100110110010000110101100111010000111011111111100001110110001010000000001011101101011101010101110111000111111110000110010100010";
    setOptStr(optN, initStr);

    getOpt(opt1);
    getOpt(opt2);
//    getOpt(optN);
    getOpt(resultOpt);

    cout << endl << endl;

    //+
//    additionOpt(resultOpt, opt1, opt2);
//    getOpt(resultOpt);

    //square opt
//    squareOpt(resultOpt, opt1);
//    getOpt(resultOpt);


    // opt >>> shift and opt <<< shift
//    cyclicShiftRightOpt(opt1, 249);
//    cout << endl;
//    getOpt(opt1);
//    cyclicShiftLeftOpt(opt1, 249);


    //set and get The Matrix for m
    setupMultMatrix();
   // getMatrix();

   //*
  // multiplicationOpt(resultOpt, opt1, opt2); NOT working
  // getOpt(resultOpt);

    cout << endl << endl;

    getOpt(opt1);
    getOpt(opt2);
//    getOpt(optN);
    getOpt(resultOpt);




    return 0;
}
