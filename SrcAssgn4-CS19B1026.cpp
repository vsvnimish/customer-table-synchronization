#include<iostream>  
#include <pthread.h>
#include <sys/time.h>
#include<unistd.h>
#include<atomic>
#include <ctime>
#include <chrono>
#include <iomanip>
#include<string>
#include<algorithm>
#include <thread> 
#include <random>
#include<string.h>
#include<random>
#include<fstream>
#include<semaphore.h>
using namespace std;
long long no_of_customers,no_of_tables,i;
double rand1,rand2,rand3;
long long noofpeople_eating=0;//keeps track of number of people eating 
long long waiting=0;//keeps track of number of people who are waiting in queue
sem_t mutex,x_sem;
struct tim{ //this structure will be used for storing timestamps
 long long id; //thread id will be stored
 string state;
 string time;
 int pr;
 long long wt;
};
tim* info;
string getTimestamp() {//this function is for getting current time
  const auto now = std::chrono::system_clock::now();
  const auto nowAsTimeT = std::chrono::system_clock::to_time_t(now);
  const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
  now.time_since_epoch()) % 1000;
  const auto nowMis = std::chrono::duration_cast<std::chrono::microseconds>(
  now.time_since_epoch()) % 1000;
  std::stringstream nowSs;
  nowSs
      << std::put_time(std::localtime(&nowAsTimeT), "%T")
      << ':' << std::setfill('0') << std::setw(3) << nowMs.count()
      << ':' << std::setfill('0') << std::setw(3) << nowMis.count();
  return nowSs.str(); 
}
void set(int k,long long id,int pr){
 (info + k*(no_of_customers) + id)->id=id;
 (info + k*no_of_customers + id)->time=getTimestamp();
 (info + k*(no_of_customers) + id)->pr=pr;
 (info + k*(no_of_customers) + id)->state="exit";
 if(pr==3)
    (info + k*(no_of_customers) + id)->state="request";
 else if(pr==2)
     (info + k*(no_of_customers) + id)->state="arrives";
    
}
void* testCS(void* tem){
 //chrono::high_resolution_clock;
 long long* seg =(long long*)tem;
 long long id=*seg;
 long long count;
 double number ;
 int seed =  
    chrono::system_clock::now().time_since_epoch().count(); 
    default_random_engine generator (seed);   
 set(0,id,3);//get request time
 auto start = std::chrono::high_resolution_clock::now();
 sem_wait(&mutex);
 if(noofpeople_eating>=no_of_tables||waiting!=0){//if either table is full or if some person is in waiting queue then we will send current thread to waiting queue
        waiting++;
        sem_post(&mutex);//release mutex
        sem_wait(&x_sem);//sending this process to waiting queue        
 }
 else{//this thread will be given permission to eat 
     noofpeople_eating++; //because thread is going to eat we will increment this variable
     sem_post(&mutex);
 }
 set(1,id,2);//get arrival time
 auto elapsed = std::chrono::high_resolution_clock::now() - start;
 (info + 1*(no_of_customers) + id)->wt= std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
 exponential_distribution<double> distribution1 (1/rand3);
 number= distribution1(generator); 
 chrono::duration<double> period (number); 
 this_thread::sleep_for(period/1000.0);//simulation of eating 
 sem_wait(&mutex);//this thread is going to exit  we will keep lock so that no other threads can exit or enter   
 noofpeople_eating--;//decrement it because thread is going to exit
 if(noofpeople_eating==0){//if no of people eating are zero then we will release some threads which are in waiting queue
    count=waiting;
    if(count>no_of_tables)
        count=no_of_tables;
    for(i=0;i<count;i++)
         sem_post(&x_sem); //we will release some threads in waiting queue
    waiting=waiting-count;//decrement it because threads are not waiting
    noofpeople_eating+=count;//increment it because they are going to eat
 }
 sem_post(&mutex);//relase mutex
 set(2,id,1);//get exit time
// printf("%d %d %d\n",0*(no_of_customers) + id,1*(no_of_customers) + id,2*(no_of_customers) + id);
 return NULL;     
}
bool compare(tim a,tim b){
 //cout<<"tid : "<<a.id+1<<" "<<b.id+1<<""<<"\n";
 if(a.time!=b.time)
        return a.time<b.time;
 if(a.pr!=b.pr)
      return a.pr>b.pr;
 return a.id<b.id;
} 
int main(){
  double number;
  int seed =  
    chrono::system_clock::now().time_since_epoch().count(); 
    default_random_engine generator (seed);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  sem_init(&mutex,0,1);
  sem_init(&x_sem,0,0);
  cin>>no_of_customers>>no_of_tables>>rand1>>rand2>>rand3;
  long long i,sender[no_of_customers],m=0,h,set=0;
  pthread_t t[no_of_customers];
  info=new tim[no_of_customers*3];
  for(i=0;i<no_of_customers;i++){
    sender[i]=i;
  }
  for(i=0;i<no_of_customers*3;i++){
    (info + i)->wt=0;
  }
  while(set!=no_of_customers){
  std::uniform_int_distribution<> distrib(1,rand2*no_of_tables);
  h=distrib(gen);//get the size of set of customers
  set=m+h;
  if(m+h>no_of_customers)
    set=no_of_customers;
  for(i=m;i<set;i++){
     pthread_create(&t[i],NULL,testCS,&sender[i]);//thread will be created and testCS function will be executed and we will pass thread id as argument                                            //an argument to testCS
  }
  exponential_distribution<double> distribution (1/rand1);
  number= distribution(generator); 
  chrono::duration<double> period (number); 
  this_thread::sleep_for(period/1000.0);
  m=m+h;
 }
///////////////////////////////////////////////////////////////////////////////
  for(i=0;i<no_of_customers;i++){
     pthread_join(t[i],NULL);//we will wait till all threads finishes their execution
  }
  double sum=0,sum1=0;
  sort(info,info+(no_of_customers*3),compare);//sort array of times
  for(i=0;i<(no_of_customers*3);i++){
      sum1+=(info + i)->wt;
      if((info + i)->state=="request")
         cout<<((info + i)->id)+1<<"th Customer access request at "<<(info + i)->time<<"\n";
      else if((info + i)->state=="arrives")
         cout<<((info + i)->id)+1<<"th Customer given access at "<<(info + i)->time<<"\n"; 
      else
         cout<<((info + i)->id)+1<<"th Customer exits at "<<(info + i)->time<<"\n";
  }    
  cout<<"Average waiting time : "<<double(sum1)/no_of_customers<<"\n";   
}
