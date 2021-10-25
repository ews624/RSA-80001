# RSA-8001
RSA algorithm for CS 8001
-------

## Compile and Execution
The gmplib library is necessary to run my code. Instructions and source code are available at https://gmplib.org/ . 
Using a gcc compiler on Ubuntu to compile the code I used ``` gcc -o rsa RSA.c -lgmp``` and then it can be executed with
typing ```./rsa``` 
The program will then ask for an integer k input. This will be used to determine how many bits are used the encryption.


## Files
* RSA.c
  * This is the file that contains all the source code
* X.txt
  * This contains the 'x' that will be encrypted and then decrypted with the RSA algorithm
* dN.txt
  * Contains d and N, the private key, which will allow for decryption of the encrypted value
* Encrypt.txt
  * Contains the e, p, q, which will be used as the private key      
* encryptX.txt
  * Contains the Encrypted 'x' which was encrypted by e and can be decrypted with d
 
