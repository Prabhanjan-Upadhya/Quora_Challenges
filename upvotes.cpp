#include<iostream>
#include<vector>

void upvotes_sol(const std::vector<int>& arr, const int& N, const int& K){
 
  std::vector<int> left_inc(N,1);
  std::vector<int> left_dec(N,1);
  std::vector<int> right_inc(N,1);
  std::vector<int> right_dec(N,1);
 
  long long inc_count = 0, dec_count = 0;
  
  /*
   *  Storing the memoization table of increasing 
   *  and decreasing sequences from left to right
   */

  for( int i = 0; i < N; i++ ){
    if( i > 0 ){
      if( arr[i] >= arr[i-1] )
        left_inc[i] += left_inc[i-1];
      
      if( arr[i] <= arr[i-1] )
        left_dec[i] += left_dec[i-1];
    }
  }

  /* 
   *  Storing memoization table for increasing 
   *  and decreasing sequences from right to left.
   */

  for( int i = N-1; i >= 0; i-- ){
    if( i < N-1 ){
      if( arr[i] >= arr[i+1] )
        right_inc[i] += right_inc[i+1];

      if( arr[i] <= arr[i+1] )
        right_dec[i] += right_dec[i+1];
    }
  }

  /*
   *  Initial Window calculation
   */

  for(int i = 0; i < K-1; i++){
    inc_count += left_inc[i];
    dec_count += left_dec[i];
  }

  /*
   *  Sliding the Window. Removing the result of
   *  last element in the window and adding the result
   *  of new element.
   */
  for(int i = K-1; i < N; i++){
    inc_count += std::min(K, left_inc[i]);
    dec_count += std::min(K, left_dec[i]);
    
    std::cout << (inc_count - dec_count) << std::endl;

    inc_count -= std::min(K, right_dec[i-(K-1)]);
    dec_count -= std::min(K, right_inc[i-(K-1)]);
  }
  return;
}

int main(){

  int N, K;
  std::cin >> N >> K;
  std::vector<int> arr;
  arr.reserve(N);
  int temp;

  for( int i=0; i<N; i++ ){
    std::cin >> temp;
    arr.push_back(temp);
  }

  upvotes_sol(arr, N, K);
  return 0;
}
