#include<bits/stdc++.h>

using namespace std;

///function for Transposition Encryption

string TranspositionEncryption (string plaintext,vector<int>keyorder)
{
    int columnnuber=keyorder.size();
    int rownumber= plaintext.length()/columnnuber ;
    string encryptedtext;
    int mapping[columnnuber];

    for(int i=0;i<plaintext.length();i++)
        plaintext[i]=toupper(plaintext[i]);

    vector<string> v;

    for(int i=0;i<columnnuber;i++)
    {
        string str;
        for(int j=i ; j< plaintext.length() ; j+=columnnuber)
        {
            str.push_back(plaintext[j]);
        }

        v.push_back(str);
    }

    //mapping for key ordering
    for(int i=0;i<keyorder.size();i++)
    {
        mapping[keyorder[i]]=i;
    }

    for(int i=0;i<columnnuber;i++)
    {
        encryptedtext+= v[mapping[i]];
    }

     return encryptedtext;


}



int main()
{
    freopen("transposition-113.txt","r", stdin);
    freopen("transposition_output.txt","w",stdout);

    string mainciphertext,ciphertext,dummy;
    getline(cin,ciphertext);
    getline(cin,dummy);

    string hints;
    getline(cin,hints);

    vector<string> hintwords;

    mainciphertext=ciphertext;

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

    //guessing that the column number maybe between 2 and 10
    for(int colnum=2 ;colnum<=10; colnum++)
    {

        if((cipherlength % colnum) != 0)
            continue;

        //row number
        int rownum=cipherlength/colnum;

        //getting the columns of the given ciphertext
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


        //temporary array before permutation
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

            //if all the hint words are found then break
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

    cout<< "Given Ciphertext: " << mainciphertext << endl;
    cout<< "\n" ;
    cout<< "Plain Text: " << plaintext << endl ;
    cout<< "\n" ;
    cout<< "Key Length: " << keyordering.size() << endl ;
    cout<< "\n" ;
    cout<< "Key Order: ";

    for(int i=0;i<keysize;i++)
    {
        cout<< keyordering[i]+1 << " " ;
    }

    cout<< "\n\n" ;


   string encrypt=TranspositionEncryption(plaintext,keyordering);
   cout<< "Encrypted: " << encrypt << endl;


   int matchingcounter=0;


   for(int i=0;i<cipherlength;i++)
   {
        if(mainciphertext[i]==encrypt[i])
            matchingcounter++;
   }

   cout<< "\n" ;
   float accuracy= (matchingcounter/cipherlength)*100 ;
   cout<< "Accuracy Percentage: " << accuracy << "%" << endl ;


    return 0;
}
