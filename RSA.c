#include<stdio.h>
#include<gmp.h>
#include<assert.h>
#include<time.h>
#include<stdlib.h>

void get_random(mpz_t random){
	
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	
	mpz_t seed;
	mpz_init(seed);
	
	

	int r =rand();
	
	printf("R is :%d\n",r);
	mpz_set_ui(seed,r);
	gmp_randseed(state,seed);
	
	mp_bitcnt_t n;
	n = 2048;
	
	
	mpz_urandomb(random,state,n);
	mpz_out_str(stdout,10,random);
	
	int is_prime;
	
	is_prime = mpz_probab_prime_p(random,40);
	printf("\n is_prime is %d\n",is_prime);
	if(is_prime == 2){
		printf("Rand is prime\n");
	}
	if(is_prime ==1){
		printf("Rand might be a prime\n");
	}
	else
		printf("Rand is not prime\n");
	
	while(is_prime == 0){
		mpz_nextprime(random,random);
		/*mpz_set_ui(seed,r);
		gmp_randseed(state,seed);
		mpz_urandomb(random,state,n);
		*/
		is_prime = mpz_probab_prime_p(random,40);
	}
	mpz_out_str(stdout,10,random);
	printf("\n Is Prime\n");

};

int main (){
	
	
	mpz_t k_large;
	
	srand(time(NULL));
	
	char k[1024];
	printf("Enter the value for k\n");
	scanf("%1023s",&k);
	
	
	
	mpz_init(k_large);
	mpz_set_ui(k_large,0);
	
	mpz_set_str(k_large,k,10);
	
	printf("GMP print of k=");
	mpz_out_str(stdout,10,k_large);
	printf("\n");
	
	printf("K^4 is:");
	mpz_mul(k_large,k_large,k_large);
	mpz_mul(k_large,k_large,k_large);
	mpz_out_str(stdout,10,k_large);
	printf("\n");
	
	
	/*
	FILE *input_file = fopen("encrypt.txt","r");
	if(input_file == NULL){
		printf("Error, could not open file\n");
	}
	*/
	
	
	mpz_t p;
	mpz_t q;
	mpz_t N;
	mpz_t phi_n;
	mpz_t e;
	mpz_t d;
	mpz_t test;

	mpz_init(p);
	mpz_init(q);
	mpz_init(N);
	mpz_init(phi_n);
	mpz_init(e);
	mpz_init(d);
	mpz_init(test);
	
	get_random(p);
	get_random(q);
	mpz_mul(N,p,q);
	mpz_mul(phi_n,(p-1),(q-1));
	mpz_set_ui(e,65537);
	mpz_invert(d,e,phi_n);
	
	mpz_mul(test,e,d);
	mpz_mod(test,test,phi_n);
	
	printf("Mod ed is :\n");
	mpz_out_str(stdout,10,test);
	printf("\n");
	
	printf("N is :\n");
	mpz_out_str(stdout,10,N);
	printf("\n");
	
	printf("Phi N is :\n");
	mpz_out_str(stdout,10,phi_n);
	printf("\n");
	
	return 1;
}






