#include <iostream>
#include <math.h> 
#include <vector>
#include <cstring>

using namespace std;
// all times using n = 1234567, average of 5 runs

/*
#1: Trial division, maintaining a list of all primes found so far.

Time: 6.25 seconds

void FillPrimeArray (int* table, int n){
	int count = 0;
	table [count++] = 2;
	for (int number = 3; count < n; number += 2){
		bool prime = true;
		for (int i = 0; table[i]*table[i] <= number; i++){
			if (number % table [i] == 0){
				prime = false;
				break;
			}
		}
		if (prime){
			table [count++] = number;
		}
	}
}

int main (){
	
	int n = 1234567;

	int table [n];
	FillPrimeArray (table, n);
	cout << table[n-1];

	return 0;
}

*/





/*

#2: implementation of Sieve of Atkin

Time: 2.73 seconds

int main(){
	int n = 1234567;
	int upper = ceil(n*(log(n) + log(log(n)))) + 1;
    vector<bool> is_prime(upper + 1);
    is_prime[2] = true;
    is_prime[3] = true;
    for (int i = 5; i <= upper; i++){
        is_prime[i] = false;
    }
    int lim = ceil(sqrt(upper));
    for (int x = 1; x <= lim; x++){
        for (int y = 1; y <= lim; y++){
            int num = (4 * x * x + y * y);
            if (num <= upper && (num % 12 == 1 || num % 12 == 5))
                is_prime[num] = true;
            num = (3 * x * x + y * y);
            if (num <= upper && (num % 12 == 7))
                is_prime[num] = true;
            if (x > y){
                num = (3 * x * x - y * y);
                if (num <= upper && (num % 12 == 11))
                    is_prime[num] = true;
            }
        }
    }
    for (int i = 5; i <= lim; i++){
        if (is_prime[i]){
            for (int j = i * i; j <= upper; j += i){
                is_prime[j] = false;
            }
        }
    }
 	int count = 0;
    for (int i = 2; i <= upper; i++){
	    if (is_prime[i])
	        count ++;
	    if (count == n){
	    	cout << i;
	     	break;
	    }
    }
	return 0;
}
*/





/*, 

#3: implementation of Sieve of Sundaram

Time: 1.87 seconds

int main(){
	int N = 1234567;
  	int max = floor(N*(log(N) + log(log(N))));
  	vector<bool> is_prime(max/2, false);
  	for (int i = 1; i < is_prime.size(); i++) {
    	for (int j = 1; j <= i; j++) {
      		int m = i + j + 2*i*j;
      		if (m < is_prime.size()) {
        		is_prime[m] = true;
      		} else {
        		break;
      		}
    	}
  	}
  	int count = 1;
  	for (int m = 1; m < is_prime.size(); m++) {
    	if (not is_prime[m]) count++;
		if (count == N) {
  			cout << 2*m + 1 << endl;
  			break;
		}
	}
	return 0;
}
*/





/*

#4: basic implementation of Sieve of Eratosthenes

Time: 0.74 seconds


int main(){
  int n;
  cout << "enter n";
  cin >> n;
  int upperBound = floor(n*(log(n) + log(log(n))));
  int upperBoundSquareRoot = (int)sqrt(upperBound);
  bool *isComposite = new bool[upperBound + 1];
  memset(isComposite, 0, sizeof(bool) * (upperBound + 1));
  int count = 0;
  for (int m = 2; m <= upperBoundSquareRoot; m+=1) {
    if (!isComposite[m]) {
      count++;
      if (count == n){
        cout << m;
        return 0;
      }
      for (int k = m * m; k <= upperBound; k += 2*m)
        isComposite[k] = true;
    }
  }
  for (int m = upperBoundSquareRoot; m <= upperBound; m++){
    if (!isComposite[m]){
      count++;
    }
    if (count==n){
      cout << m;
      return 0;
    }
  }
  delete [] isComposite;
  return 0;

}
*/






/*
#5: More efficient Sieve of Eratosthenes

Time: 0.33 seconds (0.18 on school machine, surprisingly fast)
*/

int main(){
  int n = 1234567;
  int upperBound = floor(n*(log(n) + log(log(n))));
  int upperBoundSquareRoot = (int)sqrt((double)upperBound);
  bool *isComposite = new bool[(int)upperBound/2 + 1];
  memset(isComposite, 0, sizeof(bool) * (upperBound/2 + 1));

  int count = 1;
  int temp;

  int m;
  for (int i = 1; m <= upperBoundSquareRoot; i++) {
    m = 2*i + 1;
    if (!isComposite[i]) {
      count++;
      if (count == n){
        cout << m << "\n";
        return 0;
      }
      for (int k = 2*i*i + 2*i; 2*k + 1 <= upperBound; k += 2*i + 1)
        isComposite[k] = true;
    }
    temp = i;
  }
  for (int i = temp; m <= upperBound; i++){
    m = 2*i + 1;
    if (!isComposite[i]){
      count++;
    }
    if (count==n){
      cout << m << "\n";
      return 0;
    }
  }
  delete [] isComposite;
  return 0;

}








/*

Failed (stuck for like two days) attempt at simply eliminating all multiples of 2 AND 3 from original array
would like to explore & try to make this work though, interesting approach

int main(){
  int n = 100;
  int upperBound = floor(n*(log(n) + log(log(n))));
  int upperBoundSquareRoot = (int)sqrt((double)upperBound);
  bool *isComposite = new bool[(int)upperBound/3 + 1];
  memset(isComposite, 0, sizeof(bool) * (upperBound/3 + 1));

  int count = 1;
  int temp;

  int m = 0;
  for (int i = 0; m <= upperBoundSquareRoot; i++) {
    m = 4*i - 2*(i/2) + 1;
    if (!isComposite[i]) {
      count++;
      if (count == n){
        cout << m << "\n";
        return 0;
      }
      for (int k = 3*i*i + 2*i; 4*k - 2*(k/2) + 1 <= upperBound; k += 2*i + 1){
        isComposite[k] = true;
        //cout << 4*k - 2*(k/2) + 1 << "\n";
      }
    }
    temp = i;
  }
  for (int i = temp; m <= upperBound; i++){
    m = 4*i - 2*(i/2) + 1;
    if (!isComposite[i]){
      count++;
    }
    if (count==n){
      cout << m << "\n";
      return 0;
    }
  }
  delete [] isComposite;
  return 0;

}
*/