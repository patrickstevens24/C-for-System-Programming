/*
 * pws24-hw1.c
 *
 *  Created on: Mar 30, 2016
 *      Author: Patrick Stevens
 */

#include <stdio.h>
#include <math.h>

long decimalBinary(long p);
int binaryDecimal(int n);
int decimalHex(long n);
int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
    char c, c1;
    char n = 0;
    char cp = 0;
    char xp = 0;
    char which;
    long total2;
    long total;
	long totalb;
    while (c != 'q') {
        scanf("%c", &c);


        if (c == 'i') {
        	scanf("%c", &c1);
        	which = 0;
        	totalb = 0;
        	if (c1 == 'b') {
        		which = 'b';
        		while(n != '\n') {
        		scanf("%c", &n);
        		    if (n == ' ') {
        		  } else if ('0' <= n && n <= '9') {
        		        totalb *= 10;
        		        totalb += (n - '0');
        		    }
        		 }

        	} else if (c1 == 'd') {
        		which = 'd';
        		total = 0;
        		cp = ' ';
        		while(cp != '\n') {
        			scanf("%c", &cp);
        			if (cp == ' ') {
        			} else if ('0' <= cp && cp <= '9') {
        				total *= 10;
        				total += (cp - '0');
        			}
        		}

        	} else if (c1 == 'x') {

        		total2 = 0;
        		which = 'x';
        		xp = ' ';
        		while (xp != '\n') {
        		scanf("%c", &xp);

        		if (cp == ' ') {
        		} else if ('0' <= xp && xp <= '9') {
        			printf("totalb\n");
        		        total2 *= 16;
        		        total2 += (xp - '0');
        		  } else if (xp == 'a' || xp == 'b' || xp == 'c' || xp == 'd' ||xp == 'e' || xp == 'f') {
        			  total2 *= 16;
        			  total2 += (xp - 'W');
        		  }
        		}
        	}
        } else if (c == 'o') {
        	scanf("%c", &c1);

        	if (c1 == 'b') {
        		if (which == 'd') {
        			 decimalBinary(total);
        		} else if (which == 'b'){
               decimalBinary(binaryDecimal(totalb));
        			//printf("%ld\n",totalb);
        		} else if (which == 'x'){
        			decimalBinary(total2);

        		}
        	} else if (c1 == 'd'){
        		if (which == 'd') {
        			printf("%ld\n", total);
        		} else if (which == 'b') {
        			printf("%d\n", binaryDecimal(totalb));
        		} else if (which == 'x'){
        			printf("%ld\n", total2);

        		}

        	} else if (c1 == 'x') {

        		if (which == 'd') {
        			decimalHex(total);
        			printf("\n");

        		} else if (which == 'b') {
        			decimalHex(binaryDecimal(totalb));
        			printf("\n");

        		 } else if (which == 'x') {
        			 decimalHex(total2);
        			 printf("\n");

        		 }


        	}
        }
    }
    return 0;
}

int decimalHex(long n) {
	char hexnum[100];
	int x = 1, j, temp;
	int counter = 0;
	while (n!=0) {
		temp = n % 16;
		if (temp < 10) {
			temp = temp + 48;

		} else {
			temp = temp + 87;
		}
		hexnum[x++] = temp;
		n = n /16;
	}
	for (j = x - 1; j > 0; j--) {

		counter++;
		if (counter % 2 == 0 && counter > 2) {
						printf(",");
					}
		printf("%c", hexnum[j]);
	}

	return 0;

}
int binaryDecimal(int n) {
	float value = 0, i = 0, rem;
	while (n != 0) {
		rem = n % 10;
		n = n / 10;
		value += rem * pow(2,i);
		++i;

	}
	return value;
}

long decimalBinary(long p) {
	int rem = 0;
	long bin = 0;
   char add;
	long i = 1, x = 1, j;
	char binnum[100];

	int counter;
	while (p != 0) {

		rem = p % 2;
		p = p/2;
		bin = bin + (rem * i);
		counter++;
		i = i * 10;
        add = (rem + 48);
		binnum[x++] = add;

	}
	counter = 0;
	for (j = x - 1; j > 0; j--) {

			printf("%c", binnum[j]);
			if (counter % 4 == 0 && counter > 0) {
						printf(",");
					}
			counter++;
	}
	printf("\n");
	return bin;
}

