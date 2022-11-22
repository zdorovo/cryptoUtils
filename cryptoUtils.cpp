#include"cryptoUtils.h"
#include<cstdlib>
#include<time.h>
#include<iostream>
#include<climits> 
using namespace std;


/*******************************************
 * Some utils                              *
 ******************************************/
 int squareMod( int base,  int modulus){
    base = base % modulus;
    if( base > modulus/2){
        base = modulus - base; //this is -base. its square is the
                               //same though. This should prevent
                               //help overflow errors somewhat.
                               //idk what to do if base is between
                               //sqrt INT_MAX and modulus - sqrt(INT_MAX)
                               //though
    }

    return (base*base) % modulus;
}

 int productMod( int a,  int b,  int modulus){
    return ((a%modulus)*(b%modulus)) % modulus; //what about overflow??
}

 int raisePower( int base,  int exponent,  int modulus){
    base = base % modulus; 
    //some base cases... "base" hehe
    if( base == 0 )
        return 0;
    if( base == 1 )
        return 1; 
    if( exponent == 0 )
        return 1;
    //else if( exponent == 1 )  // redundant!
    //    return base; 
    else if( exponent % 2 == 0 )
        return raisePower( squareMod( base, modulus), exponent/2, modulus);
    else
        return productMod(base, raisePower( squareMod( base, modulus), (exponent-1)/2, modulus), modulus);
}

//solve for xa + yb = gcd(a,b)
//this was shamelessly stolen from geeksforgeeks.org
 int gcdExtended( int a,  int b, int *x, int *y) 
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of
    // recursive call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

/*******************************************
 * RSA_doer implementation                 *
 ******************************************/

 int RSA_doer::encrypt( int m){
    return raisePower(m, this->pub_key, modulus);
}

 int RSA_doer::decrypt( int m){
    return raisePower(m, this->priv_key, modulus);
}

RSA_doer::RSA_doer(){
//    p = 24571;
//    q = 115249; //"Cuban" primes!
//
//    let's try something smaller first
    p = 101;
    q = 97;
                //todo: write a genPrime() function
    phi = (p-1)*(q-1);
    modulus = p*q;

    srand(time(0));

    int a,b;
    
    pub_key = rand() % modulus;  //I'm free to mod out by anything large here
    while ( gcdExtended(pub_key, phi, &a, &b) != 1){
        pub_key = rand() % modulus; 
    }

    priv_key = a; //or a % phi? It shouldn't make a difference
}

signedMessage RSA_doer::sign(int m){
    signedMessage toReturn;

    toReturn.message = m;
    toReturn.signature = decrypt(m);

    return toReturn;
}

bool RSA_doer::verify(signedMessage possibleForgery){
    return possibleForgery.message == encrypt(possibleForgery.signature);

}

