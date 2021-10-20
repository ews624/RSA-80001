#include<stdio.h>
#include<gmp.h>
#include<assert.h>

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
	
	FILE *input_file = fopen("encrypt.txt","r");
	if(input_file == NULL){
		printf("Error, could not open file\n");
	}
	
	
	return 1;
}






