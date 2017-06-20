#include "heat.h"

/*
 * Function to copy one matrix into another
 */

void copy_mat (double *u, double *v, unsigned sizex, unsigned sizey)
{
    #pragma omp parallel for
    for (int i=1; i<=sizex-2; i++)
        for (int j=1; j<=sizey-2; j++) 
            v[ i*sizey+j ] = u[ i*sizey+j ];
}

/*
 * Blocked Jacobi solver: one iteration step
 */
double relax_jacobi (double *u, double *utmp, unsigned sizex, unsigned sizey)
{
    double diff, sum=0.0;
  
    int howmany = omp_get_max_threads();
    #pragma omp parallel for private(diff) reduction(+:sum)
    for (int blockid = 0; blockid < howmany; ++blockid) {
      int i_start = lowerb(blockid, howmany, sizex);
      int i_end = upperb(blockid, howmany, sizex);
      for (int i=max(1, i_start); i<= min(sizex-2, i_end); i++) {
        for (int j=1; j<= sizey-2; j++) {
	     utmp[i*sizey+j]= 0.25 * ( u[i * sizey + (j - 1)]+  // left
	                               u[i * sizey + (j + 1)]+  // right
				       u[(i - 1) * sizey + j]+  // top
				       u[(i + 1) * sizey + j]); // bottom
	     diff = utmp[i*sizey+j] - u[i*sizey + j];
	     sum += diff * diff; 
	 }
      }
    }

    return sum;
}

/*
 * Blocked Gauss-Seidel solver: one iteration step
 */
double relax_gauss (double *u, unsigned sizex, unsigned sizey)
{
    double unew, diff, sum=0.0;
    int howmany = omp_get_max_threads();
    int processedBlocks[howmany];
    for(int i = 0; i < howmany; ++i) processedBlocks[i] = 0;
    int nBlocs = 8;
    
    
    #pragma omp parallel for schedule(static) private(diff,unew) reduction(+:sum)
    for (int i = 0; i < howmany; ++i) {
        int ii_start = lowerb(i, howmany, sizex);
        int ii_end = upperb(i, howmany, sizex);
        for (int j = 0; j < nBlocs; j++){
            int jj_start = lowerb(j,nBlocs,sizey);
            int jj_end = upperb(j,nBlocs,sizey);
            if(i > 0){
                while(processedBlocks[i-1]<=j){
		    #pragma omp flush
                }
            }
            
            for (int ii=max(1, ii_start); ii<= min(sizex-2, ii_end); ii++) {
                for(int jj= max(1,jj_start); jj<= min(sizey-2, jj_end); jj++){
                    unew = 0.25* (u[ii * sizey + (jj-1)] +  // left
                                  u[ii * sizey + (jj+1)] +  // right
                                  u[(ii-1) * sizey + jj] +  // top
                                  u[(ii+1) * sizey + jj]); // bottom
                    diff = unew - u[ii * sizey + jj];
                    sum += diff*diff;
                    u[ii*sizey+jj] = unew;
                }
            }
            ++processedBlocks[i];
	    #pragma omp flush
        }
    }
    
    return sum;
/*
    int howmany=4;
    for (int blockid = 0; blockid < howmany; ++blockid) {
      int i_start = lowerb(blockid, howmany, sizex);
      int i_end = upperb(blockid, howmany, sizex);
      for (int i=max(1, i_start); i<= min(sizex-2, i_end); i++) {
        for (int j=1; j<= sizey-2; j++) {
	    unew= 0.25 * ( u[i * sizey + (j - 1)] +  // left
			   u[i * sizey + (j + 1)] +  // right
			   u[(i - 1) * sizey + j] +  // top
			   u[(i + 1) * sizey + j]); // bottom
	    diff = unew - u[i*sizey+ j];
	    sum += diff * diff; 
	    u[i*sizey+j]=unew;
        }
      }
    }

    return sum;
*/
}
