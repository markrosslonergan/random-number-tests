//------ C++11 includes
#include<iostream>
#include<random>

//------ Root Includes
#include "TStopwatch.h"
#include "TRandom3.h"
#include "TRandomGen.h"

//------ GSL includes
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


int main(){
    //Pick a number to generate Poisson random numbers from 
    int pois_N = 12.131;
    TStopwatch watch;
    int N = 2000000; // Total comparason number

    std::cout<<"-----------------------------------------------"<<std::endl; 
    std::cout<<"Running Poisson Test, generating "<<N<<" random numbers"<<std::endl;
    std::cout<<"-----------------------------------------------"<<std::endl; 


    //c++11 <random> setup
    std::random_device c_rd;
    std::mt19937 c_gen_engine(c_rd());
    std::mt19937_64 c_gen_engine64(c_rd());
    std::poisson_distribution<unsigned> c_gen(pois_N);

    //Root setup
    TRandom3 root_gen(121);
    TRandomMT64 root_gen64(121);

    // GSL setup
    gsl_rng_env_setup();
    const gsl_rng_type * g_T=gsl_rng_default;
    gsl_rng * g_r=gsl_rng_alloc(g_T);




    //According to ROOT's reference guide: https://root.cern.ch/doc/master/classTRandom3.html
    // TRandom3 is based on:
    // Matsumoto and T. Nishimura, Mersenne Twister: A 623-diminsionally equidistributed uniform pseudorandom number generator ACM Transactions on Modeling and Computer Simulation, Vol. 8, No. 1, January 1998, pp 3–30.
    //
    // ----------- ROOT TRandom3
    watch.Reset();
    watch.Start();
    for(int i=0;i< N; i++){
        root_gen.Poisson(pois_N);
    }
    watch.Stop();
    std::cout << "TRandom3\t|| done  RealTime=" << watch.RealTime() << std::endl;


    //Root also implements a generator based on the exact c++ 11 <random> implementation that we are looking at 
    //Generator based on a the Mersenne-Twister generator with 64 bits, using the implementation provided by the standard library, std::mt19937_64 (see http://www.cplusplus.com/reference/random/mt19937_64/ )

    // ----------- ROOT TRandom implementation of M
    watch.Reset();
    watch.Start();
    for(int i=0;i< N; i++){
        root_gen64.Poisson(pois_N);
    }
    watch.Stop();
    std::cout << "TRandomMT64\t|| done  RealTime=" << watch.RealTime() << std::endl;



 // This is the 32-bit implementaion of the mersenne twister using the same documented parameters as the one cite din TRandom3's reference:32-bit Mersenne Twister by Matsumoto and Nishimura, 1998
 //  https://en.cppreference.com/w/cpp/numeric/random
 //
 // ----------- C++ random Mersenne Twister
    watch.Reset();
    watch.Start();
    for(int i=0;i< N; i++){
        c_gen(c_gen_engine);
    }
    watch.Stop();
    std::cout << "C++ mt19937\t|| done  RealTime=" << watch.RealTime() << std::endl;


    //This is the same as above but using the 64-bit mersenne_twister. 
    watch.Reset();
    watch.Start();
    for(int i=0;i< N; i++){
        c_gen(c_gen_engine64);
    }
    watch.Stop();
    std::cout << "C++ mt19937_64\t|| done  RealTime=" << watch.RealTime() << std::endl;





 //Just for comparason
 // ----------- GSL implementation
    watch.Reset();
    watch.Start();

    for(int i=0;i< N; i++){
        gsl_ran_poisson(g_r,pois_N);
    }

    watch.Stop();
    std::cout << "GSL \t\t|| done  RealTime=" << watch.RealTime() << std::endl;

    gsl_rng_free(g_r);



    return 0;
}
