// Author: Arash Nemati Hayati
// Polygon Mapping
// This program maps an arbitrary polygon into a structured two-dimensional grid of an arbitrary size
// It's assumed that the polygon is inside the defined grid
// If a cell intersects with the polygon, the code prints X
// if a cell is outside the polygon, the code prints O
// If a cell is inside the polygon, the code prints I
// mylib.h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <vector>
#include <math.h>
#define BILLION 1000000000L; // For time execution estimation
using namespace std;

// This class defines cell points and polygon vertices
class Point {
	public:
	double x, y;
	void setloc(double xin, double yin);
	double dir(Point P0, Point P1);
	Point() {x = y = 0;}
	Point(double xin, double yin){
	x = xin; y = yin;
	}
	~Point(void){}
};

void Point::setloc(double xin, double yin){
	x = xin; y = yin;
}

// This function determines the location of a point with respect to a line
// if gauge > 0 : Point is left of the line defined by the input points
// if gauge = 0 : Point is on the line defined by the input points
// if gauge < 0 : Point is right of the line defined by the input points
double Point::dir(Point P0, Point P1){
	double gauge = ( (P1.x - P0.x) * (this->y - P0.y) - (this->x - P0.x) * (P1.y - P0.y) );
	return gauge;
}

// This function determines the location of a point with respect to a polygon
// based on winding number method 
// Joseph O'Rourke, "Point in  Polygon" in Computational Geometry in C (2nd Edition) (1998)
// Sunday, Dan (2001), Inclusion of a Point in a Polygon (2001)
// if wind_number = 0 : Point is outside the polygon
// if wind_number = 1 : Point is inside the polygon

int wind_method(Point *P, Point *V, int NV) {
	int wind_number = 0;
	for (int i = 0; i < NV; i++) {
	    if (V[i].y <= P->y) {
		if (V[i+1].y > P->y)
		   if ( P->dir(V[i], V[i+1]) > 0)
			wind_number++;
	    }
	else { 
	     if (V[i+1].y <= P->y)
		if ( P->dir(V[i], V[i+1]) < 0)
			wind_number--;
	     }
	}
	return wind_number;
}

// This function find the Bottom-Left and Top-Right corners of a polygon
// P[0] : Bottom-Left corner
// P[1] : Top-Right corner
Point *get_corners(Point *V, int NV) {
	Point *P;
	P = new Point[2];
	P[0] = P[1] = V[0];
	for (int i = 0; i < NV; i++){
	    P[0].x = P[0].x < V[i].x ? P[0].x : V[i].x;
	    P[0].y = P[0].y < V[i].y ? P[0].y : V[i].y;
	    P[1].x = P[1].x < V[i].x ? V[i].x : P[1].x;
	    P[1].y = P[1].y < V[i].y ? V[i].y : P[1].y;
	}
	return P;
}

// This structure simplifies the access to the search indices
struct Index {
	int start;
	int end;
	};

// This function finds the indices of a point in X and Y directions
// id 0 : indices for Bottom-Right corner
// id 1 : indices for Top-Left corner
Index *get_index(Point *P, int S) {
	Index *id;
	int offset = 1; // account for the cell length/width
			// make sure no grid point is missed
	id = new Index[2];
	id[0].start = floor(P[0].x / S) - offset; // starting x index
	id[0].end = ceil(P[1].x / S) + offset; // ending x index
	id[1].start = floor(P[0].y / S) - offset; // starting y index
	id[1].end = ceil(P[1].y / S) + offset; // ending y index
	
	id[0].start = id[0].start < 0 ? 0 : id[0].start;
	id[1].start = id[1].start < 0 ? 0 : id[1].start;
	id[0].end = id[0].end < 0 ? 0 : id[0].end;
	id[1].end = id[1].end < 0 ? 0 : id[1].end;
	return id;
}	

// This function avoids users errors in entering input data
int get_int (string text) {
    int n;
    cin >> n;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Not a valid input for "<< text << " . Please enter a number: " << endl;
        cin >> n;
    }
    return n;
}

// This function avoids users errors in entering input data
float get_float (string text) {
    float n;
    cin >> n;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Not a valid input for "<< text << " . Please enter a number: " << endl;
        cin >> n;
    }
    return n;
}
// This function prints the description of the problem
int description(void){
	cout << "Polygon_mapping:" << endl;
	cout << "Author: Arash Nemati Hayati (November 5, 2017)" << endl;
	cout << "" << endl;
	cout << "A rectangular two-dimensional domain is populated by a Cartesian mesh with identical spacing in the X and Y directions." << endl;
	cout << "The left bottom corner of the domain is located at (0.0, 0.0)." << endl;
	cout << "An arbitrary shaped polygon described as a sequence of vertices ordered in anti-clockwise direction is overlaid on this Cartesian mesh." << endl;
	cout << "The polygon is completely contained in the rectangular domain."<< endl;
	cout << "This program marks the cells of the Cartesian mesh with a location attribute described in the following manner:" << endl;
	cout << "Completely inside the polygon: I" << endl;
	cout << "Intersecting the polygon segments: X" << endl;
	cout << "Completely outside the polygon: O" << endl;
}

// This function prints user instructions to enter input data
int input_instruction(void){
	cout << "" << endl;
	cout << "Nomenclature" << endl;
	cout << "S: Spacing of the Cartesian mesh along the X and Y directions (float)" << endl;
	cout << "Nx: Number of cells in the X direction (integer)" << endl;
	cout << "Ny: Number of cells in the Y direction (integer)" << endl;
	cout << "Nv: Number of vertices of the polygon (integer)" << endl;
	cout << "Vx: X coordinate of a vertex of the polygon (float)" << endl;
	cout << "Vy: Y coordinate of a vertex of the polygon (float)" << endl;
	cout << "" << endl;
	cout << "Please provide the following inputs to run the program:" << endl;
	cout << "First line will contain number of tests cases T, followed by description of T test cases." << endl; 
	cout << "For each test case the following information will be specified." << endl;
	cout << "S Nx Ny" << endl;
	cout << "Nv" << endl;
	cout << "Vx Vy" << endl;
	cout << "" << endl;
}
