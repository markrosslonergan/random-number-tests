#include<iostream>
#include "TStopwatch.h"

//------ C++11 includes
#include<random>

//------ Root Includes
#include "TRandom3.h"
#include "TRandomGen.h"

//------ GSL includes
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


int main(){


    std::cout<<"-----------------------------------------------"<<std::endl; 
    std::cout<<"Running Poisson Test"<<std::endl;
    std::cout<<"-----------------------------------------------"<<std::endl; 
    int pois_N = 12.131;

    std::random_device c_rd;
    std::mt19937 c_gen_engine(c_rd());
    std::poisson_distribution<unsigned> c_gen(pois_N);

    TRandom3 r_gen(0);
    TRandomMT64 r_gen2(0);


    gsl_rng_env_setup();
    const gsl_rng_type * g_T=gsl_rng_default;
    gsl_rng * g_r=gsl_rng_alloc(g_T);


    TStopwatch watch;
    int N = 10000000;
    
    // ----------- ROOT TRandom
    watch.Reset();
    watch.Start();
    for(int i=0;i< N; i++){
        r_gen.Poisson(pois_N);
    }
    watch.Stop();
    std::cout << "Root\t|| done CpuTime=" << watch.CpuTime() << " RealTime=" << watch.RealTime() << std::endl;

    // ----------- ROOT TRandomMerse
    watch.Reset();
    watch.Start();
    for(int i=0;i< N; i++){
        r_gen2.Poisson(pois_N);
    }
    watch.Stop();
    std::cout << "Root Mer\t|| done CpuTime=" << watch.CpuTime() << " RealTime=" << watch.RealTime() << std::endl;


 // ----------- C++ random Mersenne Twister
    watch.Reset();
    watch.Start();
    for(int i=0;i< N; i++){
        c_gen(c_gen_engine);
    }
    watch.Stop();
    std::cout << "C++11\t|| done CpuTime=" << watch.CpuTime() << " RealTime=" << watch.RealTime() << std::endl;


 // ----------- GSL  TRandom
    watch.Reset();
    watch.Start();
    for(int i=0;i< N; i++){
        gsl_ran_poisson(g_r,pois_N);
    }
    watch.Stop();
    std::cout << "GSL \t|| done CpuTime=" << watch.CpuTime() << " RealTime=" << watch.RealTime() << std::endl;

    gsl_rng_free(g_r);



    return 0;
}
