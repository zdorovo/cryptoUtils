# ifndef __RSA_DOER
# define __RSA_DOER

unsigned int squareMod(unsigned int base, unsigned int modulus);
unsigned int productMod(unsigned int a, unsigned int b, unsigned int modulus);
unsigned int raisePower(unsigned int base, unsigned int exponent, unsigned int modulus);
int gcdExtended(int a, int b, int *x, int *y);

struct signedMessage{
    unsigned int message;
    unsigned int signature;
};


class RSA_doer{
    public:
        unsigned int encrypt(unsigned int m);
        unsigned int decrypt(unsigned int m);
        signedMessage sign(unsigned int m);
        bool verify(signedMessage);

        unsigned int get_pubkey( ){ return pub_key;}
        unsigned int get_modulus( ){ return modulus;}

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
