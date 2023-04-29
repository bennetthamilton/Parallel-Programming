// CS475 Project 2
// Bennett Hamilton
// 4/29/23

#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int	NowYear;	    	// 2023 - 2028
int	NowMonth;	    	// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// rye grass height in inches
int	NowNumRabbits;		// number of rabbits in the current population
unsigned int seed = 0;  // seed for random number generation

const float RYEGRASS_GROWS_PER_MONTH =		20.0;   // units are in inches
const float ONE_RABBITS_EATS_PER_MONTH =	 1.0;   

const float AVG_PRECIP_PER_MONTH =	       12.0;	// average (units are in inches)
const float AMP_PRECIP_PER_MONTH =	    	4.0;	// plus or minus
const float RANDOM_PRECIP =		        	2.0;	// plus or minus noise

const float AVG_TEMP =			        	60.0;	// average
const float AMP_TEMP =			        	20.0;	// plus or minus
const float RANDOM_TEMP =	        		10.0;	// plus or minus noise

const float MIDTEMP =			        	60.0;   // units are in fahrenheit
const float MIDPRECIP =		        		14.0;

float Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

float Sqr( float x )
{
    return x*x;
}

float TempFactor()
{
    return exp(   -Sqr(  ( NowTemp - MIDTEMP ) / 10.  )   )
} 

float PrecipFactor = exp(   -Sqr(  ( NowPrecip - MIDPRECIP ) / 10.  )   );

void Rabbits()
{

}

void RyeGrass()
{

}

void Watcher()
{

}

// void MyFarmer()
// {

// }

void run_simulation(int NowMonth, int nowR, float nowH)
{
    float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );

    if( NowPrecip < 0. ) NowPrecip = 0.;

    #ifdef _OPENMP
        //fprintf( stderr, "OpenMP is supported -- version = %d\n", _OPENMP );
    #else
            fprintf( stderr, "No OpenMP support!\n" );
            return;
    #endif

        omp_set_num_threads( 3 );	// same as # of sections 
        #pragma omp parallel sections 
        {
            #pragma omp section
            {
                Rabbits( );
            }

            #pragma omp section
            {
                RyeGrass( );
            }

            #pragma omp section
            {
                Watcher( );
            }

            #pragma omp section
            {
                //MyFarmer( );	
            }
        }       // implied barrier -- all functions must return in order
                // to allow any of them to get past here
}

void main()
{
    
    // starting date and time:
    NowMonth =    0;
    NowYear  = 2023;

    // starting state (feel free to change this if you want):
    NowNumRabbits = 1;
    NowHeight =  5.;

    // run the simulation for every month from 
    // ref: https://www.w3schools.com/cpp/cpp_while_loop.asp
    while (NowYear <= 2028)
    {
        // go through each month
        // ref: https://www.w3schools.com/cpp/cpp_for_loop.asp
        for (int i = NowMonth; i < 12; i++)
        {
            run_simulation(i, );
        }

        NowYear ++;     // go to next year
        
    }

}
