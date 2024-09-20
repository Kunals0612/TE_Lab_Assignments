#include <iostream> 
#include <thread> 
  
using namespace std; 
  
// import mutex from C++ standard library 
#include <mutex> 
  
// Create object for mutex 
mutex mtx; 
  
// Shared resource 
int number = 0; 
  
// function to increment the number 
void increment(){ 
      
    // Lock the thread using lock 
    mtx.lock(); 
      
    // increment number by 1 for 1000000 times 
    for(int i=0; i<1000000; i++){ 
        number++; 
    } 
      
    // Release the lock using unlock() 
    mtx.unlock(); 
} 
  
int main() 
{ 
    // Create thread t1 to perform increment() 
    thread t1(increment); 
      
    // Create thread t2 to perform increment() 
    thread t2(increment); 
      
    // Start both threads simultaneously 
    t1.join(); 
    t2.join(); 
      
    // Print the number after the execution of both threads 
    std::cout<<"Number after execution of t1 and t2 is "<<number; 
      
    return 0; 
} 