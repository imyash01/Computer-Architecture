/* 
 * 
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */
 
#include<stdio.h>
#include<stdlib.h>

// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);

// main method starts here
int main(int argc, char** argv){
   FILE *fp = fopen(argv[1], "r");
   int cols;
   int rows;

   fscanf(fp, "%d\n" "%d\n", &cols, &rows);

   double** x = malloc(rows * sizeof(double*));
   for(int i = 0; i < rows; i++){
	   x[i] = malloc((cols+1)*sizeof(double));
   }
   double** Y = malloc(rows * sizeof(double*));
   for(int j = 0; j < rows; j++){
       Y[j] = malloc(sizeof(double));
   }

    for(int k = 0; k < rows; k++){
        for(int l = 0; l < cols + 1; l++){
            if(l == 0){
                x[k][0] = 1.0;
            }
            else{
                fscanf(fp, "%lf,", &x[k][l]);// the values are seperated by commas
            }
        }
        fscanf(fp, "%lf\n", &Y[k][0]);
    }
    

    double** xTrans = transposeMatrix(x, rows, cols + 1);

    double** xTtimesx = multiplyMatrix(xTrans,x,cols + 1, rows, rows, cols + 1);
    
    double** inverseOfMulti = inverseMatrix(xTtimesx, cols + 1);

    double** xTtimesY = multiplyMatrix(xTrans,Y, cols + 1, rows, rows, 1);

    double** w = multiplyMatrix(inverseOfMulti, xTtimesY,cols +1, cols + 1, cols + 1, 1);
    

    FILE *fo = fopen(argv[2], "r");
    
    int houseRows; //Number of houses we need to estimate the price of
    fscanf(fo, "%d\n",&houseRows);

    for (int m = 0; m < houseRows; m++)
    {
        double housePrice = 0;
        double val;
        for(int n = 0; n < cols+1; n++){
            if(n == 0){
                housePrice += w[n][0];
            }
            else{
                fscanf(fo, "%lf,", &val);
                housePrice += (val * w[n][0]);
            }
        }
        printf("%0.0lf\n", housePrice); //Change it to match the rounding in the docs
        housePrice = 0;
        fscanf(fo,"\n");
    }
    
    for(int i = 0; i < cols + 1; i++){
        free(w[i]);
    }
    free(w);

    for(int i = 0; i < cols + 1; i++){
        free(xTtimesY[i]);
    }
    free(xTtimesY);

    for(int i = 0; i < cols + 1; i++){
        free(inverseOfMulti[i]);
    }
    free(inverseOfMulti);

    for(int i = 0; i < cols + 1; i++){
        free(xTtimesx[i]);
    }
    free(xTtimesx);

    for(int i = 0; i < cols + 1; i++){
        free(xTrans[i]);
    }
    free(xTrans);

    for(int i = 0; i < rows; i++){
        free(Y[i]);
    }
    free(Y);

    for(int i = 0; i < rows; i++){
        free(x[i]);
    }
    free(x);

    fclose(fp);
    fclose(fo);
    return 0;
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double** result=malloc(r1*sizeof(double*)); 
    
    for (int i = 0; i < r1; i++){ 
         result[i] = malloc(c2 * sizeof(double));
    }

    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c2; j++){
            result[i][j] = 0;
        }
    }

    for(int r = 0; r < r1; r++){
        for(int c = 0; c < c2; c++){
            for(int i = 0; i < c1; i++){
                result[r][c] += matA[r][i] * matB[i][c];
            }
        }
    }
    
    return result;
}


double** transposeMatrix(double** mat, int row, int col)
{
	double** matTran=malloc(col*sizeof(double*));

    for (int i = 0; i < col; i++){
         matTran[i] = malloc(row * sizeof(double));
    }

    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            matTran[c][r] = mat[r][c];
        }
    }
    return matTran;        
}


double** inverseMatrix(double **matA, int dimension)
{

    double** matI=malloc(dimension*sizeof(double*)); 

    for (int i = 0; i < dimension; i++) 
         matI[i] = malloc(dimension * sizeof(double));
    
    for(int r = 0; r < dimension; r++){
        for(int c = 0; c < dimension; c++){
            if(r == c){
                matI[r][c] = 1.0;
            }
            else{
                matI[r][c] = 0.0;
            }
        }
    }
    for(int p = 0; p < dimension; p++){
        double f = matA[p][p];
        for(int j = 0; j < dimension; j++){ //loops through the row of original Mat and divides
            matA[p][j] /= f;
            matI[p][j] /= f;
        }
        for(int i = p + 1; i < dimension; i++){
            double f1 = matA[i][p];
            //subtract Mp * f from  Mi
            for(int temp = 0; temp < dimension; temp++){
                matA[i][temp] -= (matA[p][temp] * f1);
                matI[i][temp] -= (matI[p][temp] * f1);
            }
        }
    }
    for(int p = dimension - 1; p >= 0; p--){
        for (int i = p - 1 ; i >= 0; i--){
            double f2 = matA[i][p];
            //subtract Mp * f from Mi and same for Np
            for(int temp = 0; temp < dimension; temp++){
                matA[i][temp] -= (matA[p][temp] * f2);
                matI[i][temp] -= (matI[p][temp] * f2);
            }
        }        
    }
	return matI;
}