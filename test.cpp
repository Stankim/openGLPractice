#include<iostream>
using namespace std;
constexpr int findNextPowerOfTwo(int N){
    N--;
    N |= N >> 1;
    N |= N >> 2;
    N |= N >> 4;
    N |= N >> 8;
    N |= N >> 16;
    N++;
    return N;
}
int main(){
	int o=0;
	o |= o >> 2;
	cout<< o<<endl;
	cout<<findNextPowerOfTwo(24)<<endl;
}