#include <iostream>

using namespace std;

int printhelp(){
   
    // Width 123456789112345678921234567893123456789412345678951234567896123456789712345 
    cout << "GeMS 1.0\n\n";
    cout << "Overview: Genotype Model Selection (GeMS) is a single nucleotide\n";
    cout << "          polymorphism (SNP) detector that works with alignment files of\n";
    cout << "          high-throughput sequencing (HTS) data.  GeMS calls SNPs based on\n";
    cout << "          a statistical model selection procedure and accounts for the\n";
    cout << "          errors that can occur during genomic sample preparation.\n\n";
    cout << "Input:    GeMS accepts input files in the SAMtools pileup format.  To\n";
    cout << "          convert a SAM/BAM alignment file into the pileup format, users\n";
    cout << "          can use the SAMtools pileup procedure with option -s.\n\n";
    cout << "Filter:   Many HTS data alignment procedures record information about the\n";
    cout << "          short reads which are aligned to a reference genome.  Short reads\n";
    cout << "          with undesirable characteristics can be pre-filtered before\n";
    cout << "          running GeMS.  For an explanation why pre-filtering may be\n";
    cout << "          desirable and for a brief tutorial on how to pre-filter SAM/BAM\n";
    cout << "          alignment files using SAMtools view, please see the PDF document\n";
    cout << "          entitled \"Pre-Filtering Alignment Files\" available at\n";
    cout << "          https://sites.google.com/a/bioinformatics.ucr.edu/xinping-cui/\n";
    cout << "          home/software/ngs-snp-calling.\n\n";
    cout << "Usage:    gems -i input.pileup -o gems_output.txt [OPTIONS]\n\n";
    cout << "Options:  -d 0/1   0 indicates diploid, 1 indicates haploid, default is 0\n";
    cout << "          -s FLOAT maximum likelihood computing steps float value, smaller\n";
    cout << "                   is slower yet more precise, default is 0.001\n";
    cout << "          -m INT   maximum number of alleles to be considered at each site,\n"; 
    cout << "                   0 indicates unbounded, default is 255\n\n";
    cout << "Output:   The GeMS output consists of 6 columns:\n";
    cout << "          1. Chromosome identifier (character string)\n";
    cout << "          2. Reference site on chromosome (integer)\n";
    cout << "          3. Reference allele (single character)\n";
    cout << "          4. Consensus allele (single character)\n";
    cout << "          5. Largest posterior probability of the genotype models (float)\n";
    cout << "          6. p-value of Dixon's Q test (float)\n\n";
    cout << "          All sites which pass a SNP pre-filter are output.  The sites that\n";
    cout << "          qualify as GeMS SNP calls are those in which the reference allele\n";
    cout << "          differs from the consensus allele and the Dixon Q test p-value is\n";
    cout << "          less than the user specified alpha value.\n\n";
    cout << "Contact:  Xinping Cui <xinping.cui@ucr.edu>\n";
    cout << "          https://sites.google.com/a/bioinformatics.ucr.edu/xinping-cui/\n";
    // Width 123456789112345678921234567893123456789412345678951234567896123456789712345 
    
    exit(0);
    return 0;
    
    }
