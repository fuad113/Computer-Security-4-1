#include <bits/stdc++.h>

using namespace std;

string key; //key
string pt; //plain text
string keybits;
string key56bits;

int PI [] = {58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7};


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



void Encryption(string str)
{
    string plaintext;

    for(int i=0; i<64; i++)
        plaintext.push_back(str[PI[i]-1]);

    for(int i=0;i<16;i++)
    {


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

    cout<< "After Padding: " << pt << endl;

    ///plain converting to bits
    Convertobits(pt);


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


    cout<< "key bitstrem: " << keybits << endl;

    key56bits=Conversionkeyto56bits(keybits);
    cout<< "Conversion key to 56 bits: " << key56bits << endl ;




}
