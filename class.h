#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "function.h"

using namespace std;

class Seq_Obj{
      public:
             Seq_Obj(string _ID, string _Num, string _Ref, int _Num_Two, string _Ref_Info, string _Seq, string _Seq_Two, int n){
                            this->ID = _ID;
                            this->Num = _Num;
                            this->Ref = _Ref;
                            this->Num_Two = _Num_Two;
                            this->Ref_Info = _Ref_Info;
                            this->Seq_Qual_1 = _Seq;
                            this->Seq_Qual_2 = _Seq_Two;
                            
                            this->Value = new _value[n]; 
                       }
             Seq_Obj(string * obj, int n){
                            this->ID = obj[0];
                            this->Num = obj[1];
                            this->Ref = obj[2];
                            this->Num_Two = atoi(obj[3].c_str());
                            this->Ref_Info = obj[4];                      
                            this->Seq_Qual_1 = obj[5];
                            this->Seq_Qual_2 = obj[6];
                            
                            this->Value = new _value[n]; 
                             
                            }
                       
             Seq_Obj(){
                       ID = "";
                       Num = "";
                       Ref = "";
                       Num_Two = -1;
                       Ref_Info = "";
                       Seq_Qual_1 = "";
                       Seq_Qual_2 = "";
                       }
                       
             ~Seq_Obj(){
                        }
             
             string Get_ID();
             string Get_Num();
             int Get_Ref_Length();
             string Get_Ref();
             string Get_Ref_Info();
             string Get_Seq_Qual(int n);
             
             int Seq_Init_Filter();
             int Seq_Qual_Filter(int bq, int mq);
             int Seq_Max_Filter(unsigned int max_count);
             
             float Get_Ratio_nchar();
             float Get_Ratio_del();
             
             int Calc_Value(int type, double end, double step);
             int Value_Sort(int n);
             
             struct _value{
                    double result;
                    double p;
                    };     
      
              double Get_Value_Result(int n);
              double Get_P(int n);
              double Get_Q_Value(int n);
              
      private:
              string ID; 
              string Num;
              string Ref;
              int Num_Two;
              string Ref_Info;
              string Seq_Qual_1;
              string Seq_Qual_2;
              
              _value * Value;
      
      };

string Seq_Obj::Get_ID(){
       return this->ID;
       }      

string Seq_Obj::Get_Num(){
    return this->Num;
}

int Seq_Obj::Get_Ref_Length(){
    return this->Ref_Info.size();
}

string Seq_Obj::Get_Ref(){
     return this->Ref;
    }

string Seq_Obj::Get_Ref_Info(){
       return this->Ref_Info;
}

string Seq_Obj::Get_Seq_Qual(int n){
    if (n == 0) return this->Seq_Qual_1;
    else return this->Seq_Qual_2;
}

double Seq_Obj::Get_Value_Result(int n){
       if (this->Value != NULL) return this->Value[n].result;
       else return -1;
       }

double Seq_Obj::Get_P(int n){
       if (this->Value != NULL) return this->Value[n].p;
       else return -1;
       }
      
int Seq_Obj::Seq_Init_Filter(){
                           int iter = 0;
                           int valid = 0;
                           int length = this->Ref_Info.size();
                           string temp_ref_info = "";
                           while(iter < length){//this->Ref_Info){
                                      char test = this->Ref_Info[iter];
                                      string temp = "";
                                      switch (test) {
                                             case '+': iter++; 
                                                       temp = "";
                                                       while((this->Ref_Info[iter] >= '0')&&(this->Ref_Info[iter] <='9')){
                                                       temp += Ref_Info[iter];
                                                       iter++;
                                                       }
                                                       //cout << temp << endl;
                                                       iter+=atoi(temp.c_str());
                                                       break;
                                             case '-': iter++; 
                                                       temp = "";
                                                       while((this->Ref_Info[iter] >= '0')&&(this->Ref_Info[iter] <='9')){
                                                       temp += Ref_Info[iter];
                                                       iter++;
                                                       }
                                                       //cout << temp << endl;
                                                       iter+=atoi(temp.c_str());
                                                       break;
                                             case '$': iter ++; break;
                                             case '^': iter += 2; break;

                                             default: temp_ref_info += test; iter ++; break;
                                             }
                                      }           
                           this->Ref_Info = temp_ref_info; 
                           if (this->Ref_Info.size() != this->Seq_Qual_1.size()){ 
                              valid = 1;
                              cout <<"diff: "<< this->Ref_Info.size()<<" "<<this->Seq_Qual_1.size()<<endl;
                              }
                           return valid;
                       }
                       
int Seq_Obj::Seq_Qual_Filter(int bq, int mq){
                           int iter = 0;                          
                           int length = this->Seq_Qual_1.size();
                           string temp_qual_1 = "";
                           string temp_qual_2 = "";
                           string temp_ref_info = "";
                           
                           int qual_bq = bq + 33;
                           int qual_mq = mq + 33;
                           
                           while(iter < length){
                                      if ((this->Ref_Info[iter] != 'N') && (this->Ref_Info[iter]!= '*')){
                                         if((this->Seq_Qual_1[iter] >= qual_bq) && (this->Seq_Qual_2[iter] >= qual_mq)){
                           
                                                                    temp_qual_1 += this->Seq_Qual_1[iter];
                                                                    temp_qual_2 += this->Seq_Qual_2[iter];
                                                                    if ((this->Ref_Info[iter] != '.') && (this->Ref_Info[iter]!= ','))
                                                                                              temp_ref_info += this->Ref_Info[iter];
                                                                    else temp_ref_info += this->Ref;
                                                                    }
                                                                    }
                                         iter ++;
                                      }
                                      
                           this->Seq_Qual_1 = temp_qual_1;
                           this->Seq_Qual_2 = temp_qual_2;
                           this->Ref_Info = temp_ref_info;
                           //cout << this->Ref_Info <<endl;
                           return this->Seq_Qual_1.size();
                       }
                       

int Seq_Obj::Seq_Max_Filter(unsigned int max_count){
                                if ((max_count == 0)||(max_count >= this->Ref_Info.size())) return this->Ref_Info.size();
                                string temp_qual_1 = "";
                                string temp_qual_2 = "";
                                string temp_ref_info = "";
                                
                                int order[max_count];
                                
                                int check = Get_Random(this->Ref_Info.size(), max_count, order);
                                
                                //for (int i = 0; i< check; i++)
                                    //cout << order[i] << " ";
                                
                                //cout << endl;
                                
                                for (int i = 0; i< max_count; i++){
                                    temp_qual_1 += this->Seq_Qual_1[order[i]];
                                    temp_qual_2 += this->Seq_Qual_2[order[i]];
                                    temp_ref_info += this->Ref_Info[order[i]];
                                    }
                               
                               this->Seq_Qual_1 = temp_qual_1;
                               this->Seq_Qual_2 = temp_qual_2;
                               this->Ref_Info = temp_ref_info;
                               
                               return max_count;
                                    
    }



float Seq_Obj::Get_Ratio_nchar(){
                         int iter = 0;
                         int length = this->Ref_Info.size();
                         int valid = 0;
                         while(iter < length){
                                    char test = this -> Ref_Info[iter];
                                    if ((test != '.')&&(test !=','))
                                    valid ++ ;
                                    iter ++;
                                    }
                         return (float)valid / (float)length;
                         }

float Seq_Obj::Get_Ratio_del(){
                         int iter = 0;
                         int length = this->Ref_Info.size();
                         int star = 0;
                         while(iter < length){
                                    char test = this -> Ref_Info[iter];
                                    if (test == '*')
                                    star ++ ;
                                    iter ++;
                                    }
                         return (float)star / (float)length;
                         }
                         
int Seq_Obj::Value_Sort(int n){
    for (int i = 0; i< n-1; i++)
       for (int j = i+1; j < n; j++ )
           if (this->Value[i].result < this->Value[j].result){
                         _value temp;
                         temp = this->Value[i];
                         this->Value[i] = this->Value[j];
                         this->Value[j] = temp;
                         }
       return 0;
}
           

int Seq_Obj::Calc_Value(int n, double end, double step){
      
                        end = end - step / 10.0;
                        int length = this->Seq_Qual_1.size();       
                        double w_value[length];
                        for (int i = 0; i < length; i++)
                                w_value[i] = 1- pow(10.0, ((((Seq_Qual_1[i] < Seq_Qual_2[i])? Seq_Qual_1[i]:Seq_Qual_2[i]) - 33) * (-0.1) ));
                           
                                
                        //Function table
                        double (* func_ptr[10][4])(double);
                        Func_Init(func_ptr);
                        
                        // For each row in the func table
                        for (int i = 0; i < n; i++){
                            this->Value[i].result = -1000000000.0;
                            this->Value[i].p = 0.0;
                            double test_p = step;
                            //Try from 0.00 - 0.25
                            while( test_p < end ){
                                         double test_result = 0.0;
                                         //For each point in the Ref_Info to get the sum of Ref_Info
                                         for (int j = 0; j < length; j++){
                                             int num = 0;
                                             switch (this->Ref_Info[j]){
                                                   case 'a' :
                                                   case 'A' : num = 0; break;
                                                   
                                                   case 'c' :
                                                   case 'C' : num = 1; break;
                                                   
                                                   case 'g' :
                                                   case 'G' : num = 2; break;
                                                   
                                                   case 't' :
                                                   case 'T' : num = 3; break;
                                                   
                                                   default : num = 0; break;
                                                   }
                                             //Get the sum of each row of the table
                                             double row_sum = 0.0;
                                             for (int k = 0; k< 4; k++)
                                                 if (k == num)      
                                                    row_sum += (*func_ptr[i][k])(test_p) * w_value[j];
                                                 else 
                                                    row_sum += (*func_ptr[i][k])(test_p) * (1.0 - w_value[j])/3.0;
                                             
                                             //cout << "row_sum" << log(row_sum) <<endl;
                                             test_result = test_result + log(row_sum);
                                             }
                                             
                                        //cout << test_p<<":  "<<test_result<<" VS "<<this->Value[i].result<<endl;      
                                        
                                        if (test_result > this->Value[i].result){
                                                        this->Value[i].result = test_result;
                                                        this->Value[i].p = test_p;
                                                        }
                                                  
                                        test_p += step;
                                               }  
                            //this->Value[i].result = exp(this->Value[i].result);
                            //system("pause");
                                        }
                            return 0;
                            }                   


double Seq_Obj::Get_Q_Value(int n){
       
    double sum = 0.0;
    
    for (int i = 0; i < n; i++){
        this->Value[i].result = this->Value[i].result / this->Value[0].result;
        sum += this->Value[i].result;
        }
        
    cout <<"Sum: "<<sum<<endl;
    for (int i = 0; i < n; i++)
        this->Value[i].result = this->Value[i].result / sum;
   
    double denom = this->Value[0].result - this->Value[8].result;
    //cout <<"Denom " <<denom<<endl;
    
    if (denom == 0.0) return -1;
    else return (this->Value[0].result - this->Value[1].result) / denom;
    
    }
