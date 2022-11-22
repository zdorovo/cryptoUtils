#include "cryptoUtils.h"
#include <iostream>

using namespace std;

int main(){
    RSA_doer r;
    unsigned int message = 1234;
    unsigned int encrypted = r.encrypt(1234);
    unsigned int decrypted = r.decrypt(encrypted);

    cout <<"Encrypting the message "<<message<<": "<< encrypted << endl;
    cout<< "Decrypting: "<< decrypted << endl; 


    //signedMessage s = r.sign(message); //SEGFAULT! to explore later

    //cout <<"Here's the message, " << s.message <<", along with the signature, "<< s.signature << endl;
    //cout <<"Is it authentic?? "<< r.verify(s) << endl;

    return 0;
}

