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
	
	srand(time(NULL));
	int r =rand();
	
	printf("R is :%d",r);
	mpz_set_ui(seed,r);
	gmp_randseed(state,seed);
	
	mp_bitcnt_t n;
	n = 1024;
	
	
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
	
	
	mpz_t random1;

	mpz_init(random1);

	get_random(random1);
	mpz_out_str(stdout,10,random1);
	return 1;
}






