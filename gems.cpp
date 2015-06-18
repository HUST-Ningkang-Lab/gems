#include <string>
#include <cstring>
#include <map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include "class.h"
#include "help.h"

#define Max_Num 300000000

using namespace std;

int Out_allele(ostream & out, Seq_Obj * seq_obj,int type, double end, double step){
    
    
        char Consensus_letter[11] = "ACGTMRWSYK"; 

        out << seq_obj->Get_ID() << "\t";
        out << seq_obj->Get_Num() << "\t";
        out << seq_obj->Get_Ref() << "\t";
        //outfile << vect[i]->Get_Ref_Info().size() <<"\t";
        //outfile << vect[i]->Get_Ref_Info() << "\t";
        //outfile << vect[i]->Get_Seq_Qual(0) << "\t";
        //outfile << vect[i]->Get_Seq_Qual(1) << "\t";
        
        //Do the Calc
        seq_obj->Calc_Value(type, end, step);
        
        double Result[type];
        int Max_Index = 0;
        double Max_Value = 0;
        
        //Max_Value
        for (int i = 0; i < type; i++){
             
             if (seq_obj->Get_Value_Result(i) > seq_obj->Get_Value_Result(Max_Index))
                Max_Index = i;
             Result[i] = seq_obj->Get_Value_Result(i);
        }
           
        out << Consensus_letter[Max_Index] << "\t";
        
        //ctor_Show(Result, type);
        
        Max_Value = Result[Max_Index];
        
        //printf("%d\t%.3f\n", Max_Index, Max_Value);
        
        //Xi -= Max, Exp(Xi), Sigma, Bayes
        double Sum = 0;
        for (int i = 0; i < type ; i++){
            Result[i] -= Max_Value;
            Result[i] = exp(Result[i]);
            Sum += Result[i];
            }
        
        //Vector_Show(Result, type);
        
        for (int i = 0; i < type ; i++)
            Result[i] /= Sum;
        
        //ctor_Show(Result, type);
        
        out << fixed << setprecision(4) << Result[Max_Index] << "\t";
        
        //Dixon
        
                       
        out << fixed << setprecision(4) << Dixon(Result, type);     

        out << endl;
        
          
        return 0;    
}


    
    
int String_Split(string buffer, string * obj, int n){
    int i = 0;
    int iter = 0;
    int length = buffer.size();
    
    obj[0] = "";
    while((iter < length)&&(i < n)){
               if ((buffer[iter] == ' ')||(buffer[iter] == '\t')) {
                                        i++;
                                        obj[i] = "";
                                        }
               else obj[i] += buffer[iter];
               
               iter ++;
               }
    return 0;
    }
    
int Read_File(const char * infilename, const char * outfilename, int type, unsigned int max_count, double step){
    string buffer;
    string obj[7];
    //Here is the file open and read process
    ifstream infile(infilename, ifstream::in);
    if (!infile){
                 cerr <<"Open infile error :" << infilename << endl;
                 exit(0);
                 //system("pause");
                 }
    /*
    Open file
    */
    
    ofstream outfile(outfilename, ofstream::out);
        if (!outfile){
                 cerr <<"Open outfile error :" << outfilename << endl;
                 //system("pause");
                 }
    int line_count = 0;
    int allele_count = 0;
    while(getline(infile, buffer)){
            if (buffer.size()==0) continue;
            String_Split(buffer, &(obj[0]), 7);
            //Chekc if qual_bq_length = qual_mq_length 
            if (obj[5].size() != obj[6].size()) cout <<"Qual Seq error: " << line_count<< endl;
               
            Seq_Obj *seq_obj = new Seq_Obj(obj, type);
            
            
            
               if (seq_obj->Seq_Init_Filter() == 1) cout << "this is the one with plus error: " << line_count  << endl;
            
               if ((seq_obj->Get_Ratio_nchar() >= 0.1)&&(seq_obj->Get_Ratio_del() < 0.05)){                  
                                        seq_obj->Seq_Qual_Filter(17, 20);
                                        seq_obj->Seq_Max_Filter(max_count);
                                        
                                        Out_allele(outfile, seq_obj, type, 0.25, step); 
                                        allele_count ++;    
                                        //cout << "Finished " << allele_count << endl;     
                                                       
                                    }

            
            delete(seq_obj);
            line_count ++;
            //cout << line_count <<endl;
            }

    infile.close();
    infile.clear();
    outfile.close();
    outfile.clear();
    return allele_count; 
}              


 
int main(int argc, char * argv[]){
    
    string infilename = "default.pileup";
    string outfilename = "default.out";
    
    int type = 10; //polidy
    int max_count = 255;//Max allele count
    
    float step = 0.001;//Steps
    
    int i = 1;
      
      if (argc ==1) 
      printhelp();
      
      while(i<argc){
         if (argv[i][0] != '-') {
                           cerr << "Argument " << i << " error : Arguments must start with -" << endl;
                           exit(0);
                           };           
         switch(argv[i][1]){
                            case 'i': infilename = argv[i+1]; break;
                            case 'o': outfilename = argv[i+1]; break;
                            case 'd': if (argv[i+1][0] == '1') type = 4; break;
                            case 's': step = atof(argv[i+1]); break;
                            case 'm': max_count = atoi(argv[i+1]); break;
                            case 'h': printhelp(); break;
                                                        
                            default : cerr<<"Unrec argument: " << argv[i] << endl; printhelp(); break; 
                            }
         i+=2;
         } 
    
    if (max_count < 0){
                   cerr << "Error : Max allele count must larger than 0!" << endl;
                   exit(0);
                   }
    
    
    srand((int)time(NULL)); 
    
    int table_size;

    int allele_count = Read_File(infilename.c_str(),outfilename.c_str(), type, max_count, step);
    
    //system("pause");
    
    //Show_table(table);

    //Get_Value_Table(table, type, 0.25, step);
    
    //Show_table(table);
    //Out_table(table, argv[2], atoi(argv[4]), type);
    //Out_table_order(table, outfilename.c_str(), type, 0.25, step);
    
    //system("pause");
    return 0;
}

