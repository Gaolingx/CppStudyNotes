#include <iostream>
using namespace std;
int main()
{
    int k, day = 0, sum = 0;
    cin >> k;
   
    int count = 0;
    for (int i = 1; day < k; i++) {
        for (int j = 1; j <= i; j++) {
            day++;
            if (day > k) {
                break;
            }
            sum += i;
        }
        count++;
    }
   
    cout << sum << endl;
  
    return 0;
}