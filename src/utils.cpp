#include "utils.h"
#include <math.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>

using namespace std;

vector<vector<double> > utils::loadMatrix(string file_name, unsigned int row, unsigned int col){

    double data;
    vector<vector<double> > output;
    vector<double> temp1;
    ifstream input(file_name.c_str(), ifstream::in);
    if (input.is_open()){
        for(unsigned int i = 0; i<row; i++){
            for(unsigned int j=0; j<col; j++){
                input >> data;
                temp1.push_back(data);
            }
            output.push_back(temp1);
            temp1.clear();
        }
        input.close();
    }
    else cout << "Unable to open file";

    return output;
}

vector<double> utils::loadVector(string file_name, unsigned int l){

    double data;
    vector<double> output;
    ifstream input(file_name.c_str(), ifstream::in);
    if (input.is_open()){
        for(unsigned int i = 0; i<l; i++){
                input >> data;
                output.push_back(data);
        }
        input.close();
    }
    else cout << "Unable to open file1";

    return output;
}

void utils::loadArray(string file_name, unsigned int l, double *pArray){

    double x;
    ifstream input(file_name.c_str(), ifstream::in);
    if (input.is_open()){
        for(unsigned int i = 0; i<l; i++){
            input >> x;
            pArray[i] = x;
        }
        input.close();
    }
    else cout << "Unable to open file1";

}

void utils::logVector(vector<double> x, string filename){

    ofstream logResult;
    logResult.open(filename.c_str(), ios::out);
    for(unsigned int i = 0; i < x.size(); i++){
        logResult << x[i] << endl;
    }
    logResult.close();
}


void utils::logVectorApp(vector<double> x, string filename){

    ofstream logResult;
    logResult.open(filename.c_str(), ios::app);
    for(unsigned int i = 0; i < x.size(); i++){
        logResult << x[i] << endl;
    }
    logResult.close();
}


double utils::interp_lin(vector<double> X, vector<double> Y, double x){

    int dim = X.size()-1;
    double y;

    // extreme cases (x<X(0) or x>X(end): extrapolation
    if(x <= X[0]){
        y = ( Y[1] - Y[0] ) / ( X[1] - X[0] )*( x - X[0] ) + Y[0] ;
        return y;
    }
    if(x >= X[dim]){
        y = Y[dim] + ( Y[dim] - Y[dim-1] ) / ( X[dim] - X[dim-1] ) * ( x - X[dim] );
        return y;
    }

    // otherwise
    // [ x - X(A) ] / [ X(B) - x ] = [ y - Y(A) ] / [ Y(B) - y ]
    // y = [ Y(B)*x - X(A)*Y(B) + X(B)*Y(A) - x*Y(A) ] / [ X(B) - X(A) ]
    double delta = 0.0;
    double min_d = numeric_limits<double>::max( );
    int j = -99;

    for(unsigned int i=0; i<X.size(); i++){
        if(X[i] == x){
            y = Y[i];
            return y;
        }
        delta = abs( X[i] - x ) ;
        if(delta < min_d){
            min_d = delta ;
            j = i;
        }
    }
    int k;
    if(X[j] < x){
        k = j;
    }else{
        k = j-1;
    }

    double a = (Y[k+1] - Y[k]) / (X[k+1] - X[k]) ;
    double b = Y[k] - a*X[k];
    y = a*x + b;

    return y;

}


double utils::gallonToCubicFeet(double x){

    double conv = 0.13368 ; // 1 gallon = 0.13368 cf
    return x*conv;
}

double utils::inchesToFeet(double x){

    double conv = 0.08333 ; // 1 inch = 0.08333 ft
    return x*conv;
}


double utils::cubicFeetToCubicMeters(double x){

    double conv = 0.0283 ; // 1 cf = 0.0283 m3
    return x*conv;
}


double utils::feetToMeters(double x){

    double conv = 0.3048 ; // 1 ft = 0.3048 m
    return x*conv;
}

double utils::acreToSquaredFeet(double x){
    double conv = 43560 ; // 1 acre = 43560 feet2
    return x*conv;
}

double utils::acreFeetToCubicFeet(double x){
    double conv = 43560 ; // 1 acre-feet = 43560 feet3
    return x*conv;
}

double utils::cubicFeetToAcreFeet(double x){
    double conv = 43560 ; // 1 acre = 43560 feet2
    return x/conv;
}



double utils::computeSum(vector<double> g){


    double z = 0.0;
    for(unsigned int i=0; i<g.size(); i++){
        z = z + g[i];
    }
    //double z = std::accumulate( g.begin(), g.end(), 0.0 ) ;
    return z;
}

double utils::computeMax(vector<double> g){
    double m = -1*numeric_limits<double>::max( );
    for(unsigned int i=0; i<g.size(); i++){
        if(g[i]>m){
            m = g[i];
        }
    }
    return m;
}

double utils::computeMin(vector<double> g){
    double m = numeric_limits<double>::max( );
    for(unsigned int i=0; i<g.size(); i++){
        if(g[i]<m){
            m = g[i];
        }
    }
    return m;
}

double utils::computeMean(vector<double> g){
    double z = computeSum(g)/g.size();
    return z;
}

double utils::computeVariance(vector<double> g){
    double v = 0.0;
    double M = computeMean(g);
    for(unsigned int i=0; i<g.size(); i++){
        v += ( g[i]-M )*( g[i]-M );
    }
    return v/g.size();
}


vector<vector<double> > utils::MatrixT( vector<vector<double> > M, int r, int c){

  vector<vector<double> > MT;
  for(int y=0; y<c; y++){
	for (int x=0; x<r; x++){
		MT[y][x] = M[x][y];

	}
  }
return MT;
}

vector<double> utils::normalizeVector(vector<double> X, vector<double> m, vector<double> M){

    vector<double> Y;
    double z;
    for(unsigned int i=0; i<X.size(); i++){
        z = ( X[i] - m[i] ) / ( M[i] - m[i] );
        Y.push_back( z );
    }
    return Y;
}

vector<double> utils::deNormalizeVector(vector<double> X, vector<double> m, vector<double> M){

    vector<double> Y;
    double z;
    for(unsigned int i=0; i<X.size(); i++){
        z = X[i]*( M[i] - m[i] ) + m[i] ;
        Y.push_back( z );
    }
    return Y;

}


vector<double> utils::standardizeVector(vector<double> X, vector<double> m, vector<double> s){

    vector<double> Y;
    double z;
    for(unsigned int i=0; i<X.size(); i++){
        z = ( X[i] - m[i] ) / ( s[i] );
        Y.push_back( z );
    }
    return Y;
}

vector<double> utils::deStandardizeVector(vector<double> X, vector<double> m, vector<double> s){

    vector<double> Y;
    double z;
    for(unsigned int i=0; i<X.size(); i++){
        z = X[i]*s[i] + m[i] ;
        Y.push_back( z );
    }
    return Y;

}
