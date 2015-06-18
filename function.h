#include <string>
#include <cstring>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

double func_1(double p){
       return 1.0 - 3.0 * p;
       }

double func_2(double p){
       return p;
       }

double func_3(double p){
       return (1.0 - 2.0 * p)/2.0;
       }


int Func_Init(double (* (&func_ptr)[10][4])(double)){
    for (int i = 0; i< 4 ; i++)
        for (int j =0; j< 4; j++)
           if (i == j) func_ptr[i][j] = func_1;
           else func_ptr[i][j] = func_2;
    for (int i = 4; i< 10; i++)
        for (int j = 0; j< 4; j++)
            func_ptr[i][j] = func_2;
    int line = 4;
    for (int i = 0; i< 3; i++)
        for (int j =i+1; j< 4; j++){
            func_ptr[line][i] = func_3;
            func_ptr[line][j] = func_3;
            line ++;
            }
    return 0;
}

int Matrix_Show(double * m, int dim){
    for(int i = 0; i< dim; i++){
            for(int j = 0; j< dim; j++)
                    printf("%.3f\t", m[i*dim+j]);
            printf("\n");
            }
    printf("\n");
    return 0;
    }
    
int Vector_Show(double * v, int dim){
    for (int i = 0; i< dim; i++)
        printf("%.5f\t", v[i]);
    printf("\n");
    return 0;
    }

int Matrix_Mul(double * result, double * m1, double * m2, int dim){
       for (int i = 0; i< dim; i++)
           for (int j = 0; j< dim; j++){
               result[i * dim + j] = 0;
               for (int k = 0; k< dim; k++)
                   result[i * dim + j]+= m1[i * dim + k] * m2[k * dim + j];
               }
       return 0;
       }

int Matrix_Vector_Mul(double * result, double * m, double * v, int dim){
    for(int i = 0; i < dim; i++){
            result[i] = 0;
            for (int j = 0; j< dim; j++)
                result[i] += m[i * dim + j] * v[j];
            }
    return 0;
    }

int Inverse_Matrix(double * result, double * m, int dim){
    if (dim == 2){
            double delta = (m[0] * m[3] - m[1] * m[2]);
            if (delta == 0) return -1;
            
            result[0] = m[3] / delta;
            result[1] = m[1] * (-1) / delta;
            result[2] = m[2] * (-1) / delta;
            result[3] = m[0] / delta; 
            
            }
    else if (dim == 4 ){
                 double delta = m[0]*m[5]*m[10]*m[15] + m[0]*m[6]*m[11]*m[13] + m[0]*m[7]*m[9]*m[14]
                              + m[1]*m[4]*m[11]*m[14] + m[1]*m[6]*m[8]*m[15] + m[1]*m[7]*m[10]*m[12]
                              + m[2]*m[4]*m[9]*m[15] +  m[2]*m[5]*m[11]*m[12] + m[2]*m[7]*m[8]*m[13]
                              + m[3]*m[4]*m[10]*m[13] + m[3]*m[5]*m[8]*m[14] + m[3]*m[6]*m[9]*m[12]
                              
                              - m[0]*m[5]*m[11]*m[14] - m[0]*m[6]*m[9]*m[15] - m[0]*m[7]*m[10]*m[13]
                              - m[1]*m[4]*m[10]*m[15] - m[1]*m[6]*m[11]*m[12] - m[1]*m[7]*m[8]*m[14]
                              - m[2]*m[4]*m[11]*m[13] - m[2]*m[5]*m[8]*m[15] - m[2]*m[7]*m[9]*m[12]
                              - m[3]*m[4]*m[9]*m[14] - m[3]*m[5]*m[10]*m[12] - m[3]*m[6]*m[8]*m[13];
                  
                 
                 //if (delta = 0.0) return -1;
                 
                 //printf("Delta = %.10f\n", delta);
                 
                 result[0] = m[5]*m[10]*m[15] + m[6]*m[11]*m[13] + m[7]*m[9]*m[14]- m[5]*m[11]*m[14] - m[6]*m[9]*m[15] - m[7]*m[10]*m[13];
                 result[1] = m[1]*m[11]*m[14] + m[2]*m[9]*m[15] + m[3]*m[10]*m[13] - m[1]*m[10]*m[15] - m[2]*m[11]*m[13] - m[3]*m[9]*m[14];
                 result[2] = m[1]*m[6]*m[15] + m[2]*m[7]*m[13] + m[3]*m[5]*m[14] - m[1]*m[7]*m[14] - m[2]*m[5]*m[15] - m[3]*m[6]*m[13];
                 result[3] = m[1]*m[7]*m[10] + m[2]*m[5]*m[11] + m[3]*m[6]*m[9] - m[1]*m[6]*m[11] - m[2]*m[7]*m[9] - m[3]*m[5]*m[10];
                 
                 result[4] = m[4]*m[11]*m[14] + m[6]*m[8]*m[15] + m[7]*m[10]*m[12] - m[4]*m[10]*m[15] - m[6]*m[11]*m[12] - m[7]*m[8]*m[14];
                 result[5] = m[0]*m[10]*m[15] + m[2]*m[11]*m[12] + m[3]*m[8]*m[14] - m[0]*m[11]*m[14] - m[2]*m[8]*m[15] - m[3]*m[10]*m[12];
                 result[6] = m[0]*m[7]*m[14] + m[2]*m[4]*m[15] + m[3]*m[6]*m[12] - m[0]*m[6]*m[15] - m[2]*m[7]*m[12] - m[3]*m[4]*m[14];
                 result[7] = m[0]*m[6]*m[11] + m[2]*m[7]*m[8] + m[3]*m[4]*m[10] - m[0]*m[7]*m[10] - m[2]*m[4]*m[11] - m[3]*m[6]*m[8];
                 
                 result[8] = m[4]*m[9]*m[15] + m[5]*m[11]*m[12] + m[7]*m[8]*m[13] - m[4]*m[11]*m[13] - m[5]*m[8]*m[15] - m[7]*m[9]*m[12];
                 result[9] = m[0]*m[11]*m[13] + m[1]*m[8]*m[15] + m[3]*m[9]*m[12] - m[0]*m[9]*m[15] - m[1]*m[11]*m[12] - m[3]*m[8]*m[13];
                 result[10] = m[0]*m[5]*m[15] + m[1]*m[7]*m[12] + m[3]*m[4]*m[13] - m[0]*m[7]*m[13] - m[1]*m[4]*m[15] - m[3]*m[5]*m[12];
                 result[11] = m[0]*m[7]*m[9] + m[1]*m[4]*m[11] + m[3]*m[5]*m[8] - m[0]*m[5]*m[11] - m[1]*m[7]*m[8] - m[3]*m[4]*m[9];
                 
                 result[12] = m[4]*m[10]*m[13] + m[5]*m[8]*m[14] + m[6]*m[9]*m[12] - m[4]*m[9]*m[14] - m[5]*m[10]*m[12] - m[6]*m[8]*m[13];
                 result[13] = m[0]*m[9]*m[14] + m[1]*m[10]*m[12] + m[2]*m[8]*m[13] - m[0]*m[10]*m[13] - m[1]*m[8]*m[14] - m[2]*m[9]*m[12];
                 result[14] = m[0]*m[6]*m[13] + m[1]*m[4]*m[14] + m[2]*m[5]*m[12] - m[0]*m[5]*m[14] - m[1]*m[6]*m[12] - m[2]*m[4]*m[13];
                 result[15] = m[0]*m[5]*m[10] + m[1]*m[6]*m[8] + m[2]*m[4]*m[9] - m[0]*m[6]*m[9] - m[1]*m[4]*m[10] - m[2]*m[5]*m[8];

                 //show(result, dim);
                 
                 for (int i = 0; i< 16; i++)
                     result[i] /= delta;
                 
         }
         
    else return -1;
    
    return 0;
    
    }

double Dixon(double * Result, int type){
    
    //Sort 
    for (int i = 0; i< type-1; i++)
        for (int j = i+1; j< type; j++)
            if (Result[i] > Result[j]){
                          double temp = Result[i];
                          Result[i] = Result[j];
                          Result[j] = temp;
                          }
    
    //Vector_Show(Result, type);
    
    //system("pause");
    
    //Get P
    if ((Result[type - 1] == Result[1]) || (Result[type - 1] == Result[0])) return 1;
    double p = 0;
    if (type == 10)
             p = (Result[type - 1] - Result[type - 2])/ (Result[type - 1] - Result[1]);
    else 
             p = (Result[type - 1] - Result[type - 2])/ (Result[type - 1] - Result[0]);
    
    
    //printf("p = %.3f\n", p);
    
    double quants[15] = {0.95, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.05, 0.025, 0.02, 0.01, 0.005};
    double probs[2][15] = {0.014, 0.03, 0.063, 0.098, 0.134, 0.173, 0.216, 0.265, 0.325, 0.409, 0.477, 0.534, 0.551, 0.597, 0.639, 
                        0.033, 0.065, 0.13, 0.193, 0.257, 0.324, 0.394, 0.471, 0.56, 0.679, 0.765, 0.829, 0.846, 0.889, 0.926};
             
    int probc = 0;
    if (type == 4) probc = 1; 
    
    int dim = 0;
    if ((p <= probs[probc][0]) || (p >= probs[probc][14])) dim = 2;
    else dim = 4;
    
    int index[dim];
    
    double m1[dim * dim];
    double m2[dim * dim];
    double v[dim];
     
    if (p <= probs[probc][0]){ 
          index[0] = 0;
          index[1] = 1;
          }
    else if (p >= probs[probc][14]){
          index[0] = 13;
          index[1] = 14;
         }
    else {
    
         int x = 1;
         while (p > probs[probc][x]) x++;
         x = ((probs[probc][x] - p) < (p - probs[probc][x - 1]))? x:(x-1);
         if (x < 1) x = 1;
         else if (x > 12) x = 12;

         index[0] = x - 1;
         index[1] = x;
         index[2] = x + 1;
         index[3] = x + 2;

         }    
     
     //for (int i = 0; i< dim; i++)
     //    printf("%d\t", index[i]);
     //printf("\n");
     
     //Vector    
     for (int i = 0; i< dim; i++)
             v[i] = quants[index[i]];
             
     //Matrix
     for (int i = 0; i< dim; i++)
         for (int j = 0; j< dim; j++){
             m1[i * dim + j] = pow(probs[probc][index[j]], i);
             m2[i * dim + j] = pow(probs[probc][index[i]], j);
             }
             
     //Matrix_Show(m1, dim);
     //Matrix_Show(m2, dim);
     
     double m1m2[dim * dim];
     Matrix_Mul(m1m2, m1, m2, dim);

     //Matrix_Show(m1m2, dim);
          
     double inverse_m1m2[dim * dim];
     double check_inverse[dim * dim];
     if (Inverse_Matrix(inverse_m1m2, m1m2, dim) == -1 ) {
                                
                                printf("Comp Matrix Error\n");
                                
                                return -1;
                                
                                };
          
     //Matrix_Show(inverse_m1m2, dim);
     
     //Check_inverse
     
     Matrix_Mul(check_inverse, m1m2, inverse_m1m2, dim);
     
     //Matrix_Show(check_inverse, dim);
     
     double m1v[dim * dim];
     Matrix_Vector_Mul(m1v, m1, v, dim);
          
     double b[dim * dim];
     Matrix_Vector_Mul(b, inverse_m1m2, m1v, dim); 
     
     //Vector_Show(b, dim);
     
     double result = 0;
     
     for (int i = 0; i < dim; i++)
         result += b[i] * pow(p, i);
     
     
     //system("pause");
     
     if (result < 0) return 0;
     else if (result > 1) return 1;
          else return result;
    }
    

int Get_Random(int total, int n, int * order){
    
    int table[total];
    int order_table[total];
    
    for(int i = 0; i< total; i++){
            table[i] = i;
            order_table[i] = 0;
            }
    for (int i = 0; i < n; i++ ){
         
         int j=(int)((float) (total-1-i)* rand()/(RAND_MAX+1.0)); 
         order_table[table[j]] = 1;
         table[j] = table[total-1-i];
         order[i] = 0;
        }
    
    int j = 0;
    
    for (int i = 0; i< total; i++)
        if (order_table[i] == 1){
           order[j] = i;
           j++;
        }
        
    return j;
}
/*
int main(){
    double (* func_ptr[10][4])(double);
    Func_Init(func_ptr);
    for (int i = 0; i < 10 ; i++){
        for (int j = 0; j< 4; j++)
          cout << (*func_ptr[i][j])(0.1) <<"  ";
        cout << endl;
        }
    
    system("pause");
    return 0;
}

*/

