/*
 * Iterative solver for heat distribution
 */

#include <stdio.h>
#include <stdlib.h>
#include "heat.h"
#include <tareador.h>

void usage( char *s )
{
    fprintf(stderr, 
	    "Usage: %s <input file> [result file]\n\n", s);
}

int main( int argc, char *argv[] )
{
    unsigned iter;
    FILE *infile, *resfile;
    char *resfilename;

    // algorithmic parameters
    algoparam_t param;
    int np;

    double runtime, flop;
    double residual=0.0;

    // check arguments
    if( argc < 2 )
    {
	usage( argv[0] );
	return 1;
    }

    // check input file
    if( !(infile=fopen(argv[1], "r"))  ) 
    {
	fprintf(stderr, 
		"\nError: Cannot open \"%s\" for reading.\n\n", argv[1]);
      
	usage(argv[0]);
	return 1;
    }

    // check result file
    resfilename= (argc>=3) ? argv[2]:"heat.ppm";

    if( !(resfile=fopen(resfilename, "w")) )
    {
	fprintf(stderr, 
		"\nError: Cannot open \"%s\" for writing.\n\n", 
		resfilename);
	usage(argv[0]);
	return 1;
    }

    // check input

    if( !read_input(infile, &param) )
    {
	fprintf(stderr, "\nError: Error parsing input file.\n\n");
	usage(argv[0]);
	return 1;
    }
    print_params(&param);

    if( !initialize(&param) )
	{
	    fprintf(stderr, "Error in Solver initialization.\n\n");
	    usage(argv[0]);
	    return 1;
	}

    // full size (param.resolution are only the inner points)
    np = param.resolution + 2;
    
    tareador_ON();
    // starting time
    runtime = wtime();

    iter = 0;
    while(1) {
	switch( param.algorithm ) {
            case 0: // JACOBI
                tareador_start_task("relax_jacobi");
                residual = relax_jacobi(param.u, param.uhelp, np, np);
                tareador_end_task("relax_jacobi");
                // Copy uhelp into u
                tareador_start_task("Copy_mat");     
		copy_mat(param.uhelp, param.u, np, np);
                tareador_end_task("Copy_mat");
                break;
            case 1: // GAUSS
                tareador_start_task("relax_gauss");
                residual = relax_gauss(param.u, np, np);
                tareador_end_task("relax_gauss");
                break;
	    }

        iter++;

        // solution good enough ?
        if (residual < 0.00005) break;

        // max. iteration reached ? (no limit with maxiter=0)
        if (param.maxiter>0 && iter>=param.maxiter) break;
    }

    // Flop count after iter iterations
    flop = iter * 11.0 * param.resolution * param.resolution;
    // stopping time
    runtime = wtime() - runtime;
    tareador_OFF();

    fprintf(stdout, "Time: %04.3f ", runtime);
    fprintf(stdout, "(%3.3f GFlop => %6.2f MFlop/s)\n", 
	    flop/1000000000.0,
	    flop/runtime/1000000);
    fprintf(stdout, "Convergence to residual=%f: %d iterations\n", residual, iter);

    // for plot...
    coarsen( param.u, np, np,
	     param.uvis, param.visres+2, param.visres+2 );
  
    write_image( resfile, param.uvis,  
		 param.visres+2, 
		 param.visres+2 );

    finalize( &param );
    return 0;
}
