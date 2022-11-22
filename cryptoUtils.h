# ifndef __RSA_DOER
# define __RSA_DOER


//todo:
// maybe define a "message" class?

int squareMod( int base,  int modulus);
int productMod( int a,  int b,  int modulus);
int raisePower( int base,  int exponent,  int modulus);
int gcdExtended(int a, int b, int *x, int *y);

struct signedMessage{
    int message;
    int signature;
};

//typedef unsigned int KeyType;

class RSA_doer{
    public:
         int encrypt(int m);
         int decrypt(int m);
         signedMessage sign(int m);
         bool verify(signedMessage); //should really pass the other
                                     //RSA_doer's public key.
                                     //But for now let's just verify
                                     //our own messages!

         int get_pubkey( ){ return pub_key;}
         int get_modulus( ){ return modulus;}

         RSA_doer();

    private:
         unsigned int p;
         unsigned int q;

         unsigned int modulus; 
         unsigned int phi;

         unsigned int priv_key;
         unsigned int pub_key; 
};

# endif /* __RSA_DOER */
