#include <bits/stdc++.h>

using namespace std;

string key; //key
string pt; //plain text
string keybits;
string key56bits;
string ciphertext;
string cipherbits;

int PI [] = {58, 50, 42, 34, 26, 18, 10, 2,
             60, 52, 44, 36, 28, 20, 12, 4,
             62, 54, 46, 38, 30, 22, 14, 6,
             64, 56, 48, 40, 32, 24, 16, 8,
             57, 49, 41, 33, 25, 17, 9, 1,
             59, 51, 43, 35, 27, 19, 11, 3,
             61, 53, 45, 37, 29, 21, 13, 5,
             63, 55, 47, 39, 31, 23, 15, 7
            };

int PI_1[] = {40, 8, 48, 16, 56, 24, 64, 32,
              39, 7, 47, 15, 55, 23, 63, 31,
              38, 6, 46, 14, 54, 22, 62, 30,
              37, 5, 45, 13, 53, 21, 61, 29,
              36, 4, 44, 12, 52, 20, 60, 28,
              35, 3, 43, 11, 51, 19, 59, 27,
              34, 2, 42, 10, 50, 18, 58, 26,
              33, 1, 41, 9, 49, 17, 57, 25
             };


int PI_2 [] = {35, 38, 46, 6, 43, 40, 14, 45,
               33, 19, 26, 15, 23, 8, 22, 10,
               12, 11, 5, 25, 27, 21, 16, 31,
               28, 32, 34, 24, 9, 37, 2, 1
              };


int CP_1[]= {57, 49, 41, 33, 25, 17, 9,
             1, 58, 50, 42, 34, 26, 18,
             10, 2, 59, 51, 43, 35, 27,
             19, 11, 3, 60, 52, 44, 36,
             63, 55, 47, 39, 31, 23, 15,
             7, 62, 54, 46, 38, 30, 22,
             14, 6, 61, 53, 45, 37, 29,
             21, 13, 5, 28, 20, 12, 4
            };

int CP_2[]= {14, 17, 11, 24, 1, 5, 3, 28,
             15, 6, 21, 10, 23, 19, 12, 4,
             26, 8, 16, 7, 27, 20, 13, 2,
             41, 52, 31, 37, 47, 55, 30, 40,
             51, 45, 33, 48, 44, 49, 39, 56,
             34, 53, 46, 42, 50, 36, 29, 32
            };

int SHIFT[]= {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int E[] = {32, 1, 2, 3, 4, 5,
           4, 5, 6, 7, 8, 9,
           8, 9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32, 1
          };

int P [] = {16, 7, 20, 21, 29, 12, 28, 17,
            1, 15, 23, 26, 5, 18, 31, 10,
            2, 8, 24, 14, 32, 27, 3, 9,
            19, 13, 30, 6, 22, 11, 4, 25
           };

string Conversionkeyto56bits(string str)
{
    string newkey;
    for(int i=0; i<56; i++)
        newkey.push_back(str[CP_1[i]-1]);

    return newkey;
}

string Subkeygenerator(int iteration)
{
    string strleft,strright;
    string finalleft,finalright,finalsubkey,subkey48bits;
    string temp1,temp2,temp3,temp4;

    int shiftnumber=SHIFT[iteration];

    //dividing into left and right 28 bits
    for(int i=0; i<28; i++)
        strleft.push_back(key56bits[i]);
    for(int i=28; i<56; i++)
        strright.push_back(key56bits[i]);

    //left shift of left 28 bits
    for(int i=0; i<shiftnumber; i++)
        temp1.push_back(strleft[i]);

    for(int i=shiftnumber; i<28; i++)
        temp2.push_back(strleft[i]);

    temp2+=temp1;
    finalleft=temp2;

    //left shift of right 28 bits
    for(int i=0; i<shiftnumber; i++)
        temp3.push_back(strright[i]);

    for(int i=shiftnumber; i<28; i++)
        temp4.push_back(strright[i]);

    temp4+=temp3;
    finalright=temp4;

    finalleft+=finalright;
    finalsubkey=finalleft;


    for(int i=0; i<48; i++)
    {
        subkey48bits.push_back(finalsubkey[CP_2[i]-1]);
    }

    return subkey48bits;

}




void Encryption(string str)
{
    string plaintext,leftold,rightold;
    string rightold48bits,funcxor48bits,funcxor32bits;
    string funcfinal,ekdomfinal;

    for(int i=0; i<64; i++)
        plaintext.push_back(str[PI[i]-1]);

    //left 32 bits stored in leftold
    for(int i=0; i<32; i++)
        leftold.push_back(plaintext[i]);

    //right 32 bits stored in rightold
    for(int i=32; i<64; i++)
        rightold.push_back(plaintext[i]);


    ///16 iterations starts
    for(int iter=0; iter<16; iter++)
    {
        string leftnew,rightnew;

        //new left 32 bits will be old right 32 bits
        leftnew=rightold;

        ///working of function

        //converting right old to 48 bits by E array

        for(int i=0; i<48; i++)
            rightold48bits.push_back(rightold[E[i]-1]);


        //XOR of e/right old 32 bits and subkey for this iteration

        string ki=Subkeygenerator(iter);

        for(int i=0; i<48; i++)
        {
            if(rightold48bits[i]==ki[i])
                funcxor48bits.push_back('0');
            else
                funcxor48bits.push_back('1');
        }

        // converting the result to 32 bits
        for(int i=0; i<32; i++)
            funcxor32bits.push_back(funcxor48bits[PI_2[i]-1]);

        // passing through the P-box
        for(int i=0; i<32; i++)
            funcfinal.push_back(funcxor32bits[P[i]-1]);


        // XOR of the left old and the output of function which is the right new
        for(int i=0; i<32; i++)
        {
            if(funcfinal[i]==leftold[i])
                rightnew.push_back('0');
            else
                rightnew.push_back('1');
        }

        leftold=leftnew;
        rightold=rightnew;

    }

    //swapping left and right 32 bits. rightold is the after swapped bit streams
    rightold+=leftold;

    for(int i=0; i<64; i++)
        ekdomfinal.push_back(rightold[PI_1[i]-1]);

    cipherbits=ekdomfinal;

    //conversion of cipherbits to cypher string
    for(int i=0; i<cipherbits.length(); i=i+8)
    {
        string temp;

        for(int j=i; j<i+8; j++)
            temp.push_back(cipherbits[j]);

        int power=1;
        int sum=0;

        for(int k=7; k>=0; k--)
        {
            int temp2=temp[k]- '0';
            sum=sum+temp2*power;
            power=power*2;
        }

        ciphertext.push_back((char)sum);

    }

}


void Convertobits(string str)
{

    char ch;

    for(int i=0; i<str.length(); i+=8)
    {
        string temp;
        for(int j=i; j<i+8; j++)
        {

            ch=str[j];

            for(int k= 0; k<8; k++)
            {
                temp.push_back(((ch >> k)&1)+'0');
            }

            reverse(temp.begin(), temp.end());
        }
        Encryption(temp);
    }

}



int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    ///input
    getline(cin,key);
    getline(cin,pt);

    ///padding
    while((pt.length()%8))
    {
        pt.push_back('~');
    }

    ///Key converting to bits
    char ch1;
    for(int i=0; i<8; i++)
    {
        ch1=key[i];
        string tempkeybits;

        for(int j= 0; j<8; j++)
        {
            tempkeybits.push_back(((ch1 >> j)& 1)+'0');
        }

        reverse(tempkeybits.begin(), tempkeybits.end());
        keybits+=tempkeybits;
    }



    ///plain converting to bits and call the Encryption
    Convertobits(pt);

    cout<< "Ciphered: " << ciphertext << endl;



}
