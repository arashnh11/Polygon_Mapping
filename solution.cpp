// Author: Arash Nemati Hayati
// Polygon Mapping
// This program maps an arbitrary polygon into a structured two-dimensional grid of an arbitrary size
// It's assumed that the polygon is inside the defined grid
// If a cell intersects with the polygon, the code prints X
// if a cell is outside the polygon, the code prints O
// If a cell is inside the polygon, the code prints I

#include "mylib.h"
int main() {

// Program description and instructions
description();
input_instruction();

// Input data
int T; // Number of test cases
T = get_int("T");
float *S_in; // Spacing of the Cartesian mesh along X and Y directions
int *Nx_in; // Number of vertices in the X direction
int *Ny_in; // Number of vertices in the Y direction
int *Nv_in; // Number of vertices of polygon
float pos_x; // X location of the polygon vertex
float pos_y; // Y location of the polygon vertex


// Store input data for all test cases
S_in = new float[T];
Nx_in = new int[T];
Ny_in = new int[T];
Nv_in = new int[T];
vector <float> ver_x;
vector <float> ver_y;

for (int ct = 0; ct < T; ct++){
    S_in[ct] = get_float("S");
    Nx_in[ct] = get_int("Nx");
    Ny_in[ct] = get_int("Ny");
    Nv_in[ct] = get_int("Nv");
    for (int cv = 0; cv < Nv_in[ct]; cv++){
        pos_x = get_float("Vx");
        pos_y = get_float("Vy");
	ver_x.push_back(pos_x);
	ver_y.push_back(pos_y);
	}
} // end storing input data

// Instructions for time execution
struct timespec start, stop;
double elapsedTime;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

// Load data for each test case
double S;
int Nx, Ny, Nv;
Point *Vp; 
int last_vec_len;
for (int ct = 0; ct < T; ct++){
    S = S_in[ct];
    Nx = Nx_in[ct];
    Ny = Ny_in[ct];
    Nv = Nv_in[ct];
    Vp = new Point[Nv + 1]; 
    if (ct == 0) last_vec_len = 0;
    else last_vec_len = Nv_in[ct - 1];
    for (int cv = 0; cv < Nv; cv++){
	Vp[cv].setloc(ver_x[cv + last_vec_len], ver_y[cv + last_vec_len]);
	}
	Vp[Nv] = Vp[0];

// Find the Bottom-Left & Top-Right corners of the polygon
Point *poly_corner;
poly_corner = new Point[2];
poly_corner = get_corners(Vp, Nv);

// Find the corners indices
Index *id;
id = new Index[2];
id = get_index(poly_corner, S);
Index idx = id[0];
Index idy = id[1];

// Grid generation - Square cell creation
Point *P;
P = new Point[4];
for (int j = Ny - 1; j >= 0; j--){
    for (int i = 1; i <= Nx; i++){
	// Apply the search reduction algorithm to minimize the 
	// launch of the inside_polygon functions
	if (i >= idx.start && i <= idx.end && j >= idy.start && j <= idy.end){
	int wn_sum = 0;
	P[0].setloc( i * S, j * S); // CCW winding rotation
	P[1].setloc( i * S, (j + 1) * S);
	P[2].setloc( (i - 1) * S, (j + 1) * S);
	P[3].setloc( (i - 1) * S, j * S);
	wn_sum += wind_method(&P[0], Vp, Nv);
	wn_sum += wind_method(&P[1], Vp, Nv);
	wn_sum += wind_method(&P[2], Vp, Nv);
	wn_sum += wind_method(&P[3], Vp, Nv);
	    if (wn_sum == 0) printf("O"); 
	    else if (wn_sum == 4) printf("I");
	    else  printf("X");
	} // end condition for search reduction
	else printf("O");
	} // end x loop
   printf("\n");
} // end y loop

// deallocate memory
delete [] Vp, Nx_in, Ny_in, Nv_in, S_in;
} // end test cases

// Instructions for execution time
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
elapsedTime = ( stop.tv_sec - start.tv_sec ) + 
	      ( stop.tv_nsec - start.tv_nsec )
	      / BILLION;
printf("Elapsed time = %1f sec\n", elapsedTime);

return 0;
}
