#include<stdio.h>
#include<gmp.h>
#include<assert.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

size_t save(FILE *ptr,mpz_t var){
	
	size_t check;
	
	mpz_t newline;
	
	mpz_init(newline);
	
	//mpz_set_str(newline,"\n",62);
	
	//fprintf(ptr,"\n");
	check =mpz_out_str(ptr,10,var);
	fprintf(ptr,"\n");
	
	
	if(check == 0){
		printf("Error saving file");
		return 0;	
	}
	
	return check;

};


void get_random(mpz_t random){
	
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	
	mpz_t seed;
	mpz_init(seed);
	
	int r =rand();
	
	//printf("R is :%d\n",r);
	mpz_set_ui(seed,r);
	gmp_randseed(state,seed);
	
	mp_bitcnt_t n;
	n = 2048;
	
	
	mpz_urandomb(random,state,n);
	//mpz_out_str(stdout,10,random);
	
	int is_prime;
	
	is_prime = mpz_probab_prime_p(random,40);
	
	while(is_prime == 0){
		mpz_nextprime(random,random);
		/*mpz_set_ui(seed,r);
		gmp_randseed(state,seed);
		mpz_urandomb(random,state,n);
		*/
		is_prime = mpz_probab_prime_p(random,40);
	}
	//mpz_out_str(stdout,10,random);
	//printf("\n Is Prime\n");

};

char *concat(char *k){

	char l[2048] = "0";
	printf("Char size is:%ld",sizeof(char));
	//char *ran;
	int num = rand();
	num = (num %10)+48;
	//ran = num;
	char a[2048];// = num;
	a[0] = num;
	//strcpy(a,ran);// = (char)ran;
	char b[2048] = "2";
	char c[2048] = "0";
	
	//l = 0x00;
	printf("Dereferenced k:%s\n",k);
	
	
	strcat(l,k);
	
	printf("combined is:%s\n",l);
	
	strcat(a,l);
	strcat(b,a);
	strcat(c,b);
	printf("Fully combined is:%s\n",c);
	
	char *ptr;
	ptr = c;
	
	return ptr;


};

int main (){
	
	
	mpz_t k_large;
	mpz_t cat_large;
	
	mpz_init(k_large);
	mpz_init(cat_large);
	
	srand(time(NULL));
	
	
	char *k =(char*)malloc(1024*sizeof(char));
	printf("Enter the value for k\n");
	scanf("%1023s",k);
	
	
	char *cat=(char*)malloc(1024*sizeof(char));
	
	cat = concat(k);
	printf("PKCS padding is:%s\n",cat);
	
	
	
	mpz_set_ui(k_large,0);
	mpz_set_ui(cat_large,0);
	
	
	mpz_set_str(k_large,k,10);
	mpz_set_str(cat_large,cat,10);
	
	
	printf("GMP print of k=");
	mpz_out_str(stdout,10,k_large);
	printf("\n");
	
	
	
	mpz_t p;
	mpz_t q;
	mpz_t N;
	mpz_t phi_n;
	mpz_t e;
	mpz_t d;
	mpz_t test;
	mpz_t x;
	mpz_t y;


	mpz_init(p);
	mpz_init(q);
	mpz_init(N);
	mpz_init(phi_n);
	mpz_init(e);
	mpz_init(d);
	mpz_init(test);
	mpz_init(x);
	mpz_init(y);
	
	
	get_random(p);
	
	printf("P is :\n");
	mpz_out_str(stdout,10,p);
	printf("\n");
	
	get_random(q);
	
	printf("Q is :\n");
	mpz_out_str(stdout,10,q);
	printf("\n");
	
	mpz_mul(N,p,q);
	
	mpz_t p_minus;
	mpz_t q_minus;
	
	mpz_init(p_minus);
	mpz_init(q_minus);
	
	
	mpz_sub_ui(p_minus,p,1);
	
	
	//mpz_sub_ui(p,p,1);
	mpz_sub_ui(q_minus,q,1);
	
	printf("Q-1 is :\n");
	mpz_out_str(stdout,10,q_minus);
	printf("\n");
	
	mpz_mul(phi_n,p_minus,q_minus);
	
	printf("N is :\n");
	mpz_out_str(stdout,10,N);
	printf("\n");
	
	printf("Phi N is :\n");
	mpz_out_str(stdout,10,phi_n);
	printf("\n");
	
	
	
	mpz_set_ui(e,65537);
	
	
	mpz_invert(d,e,phi_n);
	
	printf("D is :\n");
	mpz_out_str(stdout,10,d);
	printf("\n");
	
	
	mpz_mul(test,e,d);
	mpz_mod(test,test,phi_n);
	
	printf("ed mod phi n is :\n");
	mpz_out_str(stdout,10,test);
	printf("\n");
	
	
	
	//Encrypt here
	mpz_powm(x,k_large,e,N);
	
	printf("Encrypted X/Y is :\n");
	mpz_out_str(stdout,10,x);
	printf("\n");
	
	//Decrypt here
	
	mpz_powm(y,x,d,N);
	
	printf("Decrypted Y/X is :\n");
	mpz_out_str(stdout,10,y);
	printf("\n");
	
	
	
	
	//PKCS encrypt
	mpz_t pkcs_x;
	mpz_init(pkcs_x);
	
	
	printf("GMP print of PKCS=");
	mpz_out_str(stdout,10,cat_large);
	printf("\n");
	
	mpz_powm(pkcs_x,cat_large,e,N);
	
	printf("Encrypted PKCS X/Y is :\n");
	mpz_out_str(stdout,10,pkcs_x);
	printf("\n");
	
	//PKCS decrypt
	mpz_t pkcs_y;
	mpz_init(pkcs_y);
	
	mpz_powm(pkcs_y,pkcs_x,d,N);
	
	printf("Decrypted PKCS Y/X is :\n");
	mpz_out_str(stdout,10,pkcs_y);
	printf("\n");
	
	
	
	
	FILE *input_file = fopen("encrypt.txt","a+");
	if(input_file == NULL){
		printf("Error with fopen\n");
	}
	size_t check;
	
	check =save(input_file,e); //mpz_out_str(input_file,10,e);
	check =save(input_file,p);
	check =save(input_file,q);
	if(check ==0){
		return -1;
	}
	fclose(input_file);
	
	input_file = fopen("private.txt","a+");
	check =save(input_file,N);
	check =save(input_file,d);
	fclose(input_file);
	
	input_file = fopen("X.txt","a+");
	check =save(input_file,k_large);
	fclose(input_file);
	
	
	input_file = fopen("encryptX.txt","a+");
	check =save(input_file,x);
	fclose(input_file);
	
	input_file = fopen("cipher.txt","a+");
	check =save(input_file,x);
	fclose(input_file);
	
	input_file = fopen("decrypted.txt","a+");
	check =save(input_file,y);
	fclose(input_file);
	
	
	
	
	
	
	
	return 1;
}






