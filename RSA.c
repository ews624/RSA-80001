#include<stdio.h>
#include<gmp.h>
#include<assert.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

// This function saves the contents of var into the FILE ptr
size_t save(FILE *ptr,mpz_t var){
	
	size_t check;
	
	mpz_t newline;
	mpz_init(newline);
	

	check =mpz_out_str(ptr,10,var);
	fprintf(ptr,"\n");
	
	if(check == 0){
		printf("Error saving file");
		return 0;	
	}
	
	return check;

};
//Opens a file and then error checks 
void file_save(char *filename, mpz_t var){
	FILE *input_file = fopen(filename,"a+");
	if(input_file == NULL){
		printf("Error with fopen\n");
		return;
	}
	save(input_file,var);
	fclose(input_file);
};
//Generates a random prime of size k bits and checks if it actually prime
void get_random(mpz_t random, mpz_t k){
	
	mpz_t seed;
	int r =rand();
	int is_prime;
	gmp_randstate_t state;
	mp_bitcnt_t n = mpz_get_ui(k);
	
	gmp_randinit_mt(state);
	mpz_init(seed);
	
	mpz_set_ui(seed,r);
	gmp_randseed(state,seed);
	
	mpz_urandomb(random,state,n);
	
	is_prime = mpz_probab_prime_p(random,40);
	
	while(is_prime == 0){
		mpz_nextprime(random,random);
		is_prime = mpz_probab_prime_p(random,40);
	}

};
//This Function is used for the PKCS padding by concatinating the padding bytes and the values together
char *concat(char *k){

	char l[2048] = "0";
	
	int num = rand();
	num = (num %10)+48;
	
	char a[2048];
	a[0] = num;
	char b[2048] = "2";
	char c[2048] = "0";
		
	strcat(l,k);
	
	strcat(a,l);
	strcat(b,a);
	strcat(c,b);
	
	char *ptr;
	ptr = c;
	
	return ptr;
};

void encrypt(mpz_t x,mpz_t k_large,mpz_t e, mpz_t N){
	mpz_powm_sec(x,k_large,e,N);
};

void decrypt(mpz_t y,mpz_t x, mpz_t d, mpz_t N){
	mpz_powm_sec(y,x,d,N);
};

int main (){
	
	//Getting our input K to use for our program
	char file_name[64];
	mpz_t k_large;
	mpz_t cat_large;
	
	mpz_init(k_large);
	mpz_init(cat_large);
	//Generate PSrandom functionality
	srand(time(NULL));
	
	//Set the value of k to a maximum of 1024 bytes
	char *k =(char*)malloc(1024*sizeof(char));
	printf("Enter the value for k:");
	scanf("%1023s",k);
	
	char *cat=(char*)malloc(1024*sizeof(char));
	//We use the k-integer for our PKCS padding scheme
	cat = concat(k);
	printf("PKCS padding is:%s\n",cat);
	
	mpz_set_ui(k_large,0);
	mpz_set_ui(cat_large,0);

	mpz_set_str(k_large,k,10);
	mpz_set_str(cat_large,cat,10);
	
	
	//All variables that are used in main
	mpz_t p;
	mpz_t q;
	mpz_t N;
	mpz_t phi_n;
	mpz_t e;
	mpz_t d;
	mpz_t test;
	mpz_t x;
	mpz_t y;
	mpz_t pkcs_x;
	mpz_t pkcs_y;
	mpz_t p_minus;
	mpz_t q_minus;
	
	mpz_init(p);
	mpz_init(q);
	mpz_init(N);
	mpz_init(phi_n);
	mpz_init(e);
	mpz_init(d);
	mpz_init(test);
	mpz_init(x);
	mpz_init(y);
	mpz_init(pkcs_x);
	mpz_init(pkcs_y);
	mpz_init(p_minus);
	mpz_init(q_minus);
	//Loads in 'e' from encrypt.txt
	FILE *test_file = fopen("encrypt.txt","a+");
	mpz_inp_str(e,test_file,10);
	
	//Makes a random prime p of size k bits
	get_random(p,k_large);
	
	printf("P is :\n");
	mpz_out_str(stdout,10,p);
	printf("\n");
	
	//Makes a random prime q of size k bits
	get_random(q,k_large);
	
	printf("Q is :\n");
	mpz_out_str(stdout,10,q);
	printf("\n");
	
	//Make p-1 and q-1
	mpz_sub_ui(p_minus,p,1);
	mpz_sub_ui(q_minus,q,1);
	
	printf("Q-1 is :\n");
	mpz_out_str(stdout,10,q_minus);
	printf("\n");
	
	//Makes N=pq
	mpz_mul(N,p,q);
	
	//Makes phi(N) from (q-1)(p-1)
	mpz_mul(phi_n,p_minus,q_minus);
	
	printf("N is :\n");
	mpz_out_str(stdout,10,N);
	printf("\n");
	
	printf("Phi N is :\n");
	mpz_out_str(stdout,10,phi_n);
	printf("\n");
	
	//Check if gcd(e,phi(n))==1)
	while(mpz_gcd_ui(NULL,e,mpz_get_ui(phi_n))!=1){
		mpz_add_ui(e,e,1);
	
	}
	printf("E is relative prime to phi(N), e is now:");
	mpz_out_str(stdout,10,e);
	printf("\n");
	
	
	mpz_invert(d,e,phi_n);
	
	printf("D is :\n");
	mpz_out_str(stdout,10,d);
	printf("\n");
	
	//Test if ed = 1 mod phi(N) 
	mpz_mul(test,e,d);
	mpz_mod(test,test,phi_n);
	
	printf("ed mod phi n is :\n");
	mpz_out_str(stdout,10,test);
	printf("\n");
	
	
	//Load in x to be encrypted
	FILE *x_file = fopen("X.txt","a+");
	mpz_inp_str(x,x_file,10);
	
	
	//Encrypt x here
	
	encrypt(x,x,e,N);
	
	
	printf("Encrypted X or Y is :\n");
	mpz_out_str(stdout,10,x);
	printf("\n");
	
	//Decrypt x here
	decrypt(y,x,d,N);
	
	
	printf("Decrypted Y or X is :\n");
	mpz_out_str(stdout,10,y);
	printf("\n");
	
	
	//PKCS encrypt
	printf("GMP print of PKCS=");
	mpz_out_str(stdout,10,cat_large);
	printf("\n");
	
	encrypt(pkcs_x,cat_large,e,N);
	
	printf("Encrypted PKCS X or PKCS Y is :\n");
	mpz_out_str(stdout,10,pkcs_x);
	printf("\n");
	
	//PKCS decrypt
	mpz_powm(pkcs_y,pkcs_x,d,N);
	
	printf("Decrypted PKCS Y or PKCS X is :\n");
	mpz_out_str(stdout,10,pkcs_y);
	printf("\n");
	
	//Where do you want to save your values?
	printf("What do you want to name the file for d and N?\n");
	scanf("%s",file_name);
	file_save(file_name,N);
	file_save(file_name,d);
	
	
	printf("What do you want to name the file for E(x)?\n");
	scanf("%s",file_name);
	file_save(file_name,x);
	
	
	printf("What do you want to name the file for D(c)?\n");
	scanf("%s",file_name);
	file_save(file_name,y);
	
	
	return 1;
}






