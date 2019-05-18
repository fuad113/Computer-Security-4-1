#include<bits/stdc++.h>

using namespace std;


int main()
{
    freopen("transposition-113.txt","r", stdin);
    freopen("output.txt","w",stdout);

    string ciphertext,dummy;
    getline(cin,ciphertext);
    getline(cin,dummy);

    string hints;
    getline(cin,hints);

    vector<string> hintwords;

    for(int i=0; i< ciphertext.length(); i++)
        ciphertext[i]=tolower(ciphertext[i]);

    //removing the "," from the string
    hints.erase(remove(hints.begin(),hints.end(),','),hints.end());

    //pushing each hint word to a vector of strings

    stringstream ss(hints);
    string str;

    while (getline(ss, str, ' '))
    {
        hintwords.push_back(str);
    }

    int cipherlength=ciphertext.length();


    bool answerfound=false;
    string plaintext;
    int keysize;
    vector<int> keyordering;


    for(int colnum=2 ;colnum<=10; colnum++)
    {

        if((cipherlength % colnum) != 0)
            continue;

        int rownum=cipherlength/colnum;

        //dividing the ciphertext into the chunk of rownum
        vector<string> tempvec;

        for(int i=0;i< cipherlength ;i+=rownum)
        {
            string tempstr;
            for(int j=i;j< i+rownum ;j++)
            {
                tempstr.push_back(ciphertext[j]);
            }
            tempvec.push_back(tempstr);
        }


        //temporary array for before permutation
        int colnumarray[colnum];

        for(int i=0;i<colnum;i++)
            colnumarray[i]=i;

        int maximummatching=0;

        string tempstr;
        int keyorder[colnum];

        do{
            tempstr.clear();

            int matchcounter=0;

            for(int i=0;i<rownum;i++)
            {
                for(int j=0;j< colnum;j++)
                {
                    tempstr+=tempvec[colnumarray[j]][i];
                }
            }


            //matching with the given hints words

            int matchingcounter=0;

            for(int i=0;i<hintwords.size();i++)
            {
                size_t s=tempstr.find(hintwords[i]);
                if(s != string::npos)
                    matchingcounter++;
            }

            if(matchingcounter>maximummatching)
            {
                maximummatching=matchingcounter;

            }

            if(matchingcounter==4)
            {
                answerfound=true;

                for(int i=0;i< colnum;i++)
                {
                    keyorder[i]=colnumarray[i];
                }

                break;
            }


        }while(next_permutation(colnumarray,colnumarray+colnum));


        if(answerfound==true)
        {
            plaintext=tempstr;
            keysize=colnum;

            for(int i=0;i<colnum;i++)
                keyordering.push_back(keyorder[i]);

            break;
        }

    }


    cout<< "Plain Text: " << plaintext << endl ;
    cout<< "Key Length: " << keyordering.size() << endl ;
    cout<< "Key Order: ";

    for(int i=0;i<keysize;i++)
    {
        cout<< keyordering[i]+1 << " " ;
    }
    return 0;
}
