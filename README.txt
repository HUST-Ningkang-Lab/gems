GeMS 1.0

Overview: Genotype Model Selection (GeMS) is a single nucleotide
          polymorphism (SNP) detector that works with alignment files of
          high-throughput sequencing (HTS) data.  GeMS calls SNPs based on
          a statistical model selection procedure and accounts for the
          errors that can occur during genomic sample preparation.

Compile:  Use a C++ compiler to compile gems.cpp.  For example, users of
          GCC in a Unix-like computing environment can use the command:
          $ g++ gems.cpp -o gems
          to compile GeMS with the associated header files.

Input:    GeMS accepts input files in the SAMtools pileup format.  To
          convert a SAM/BAM alignment file into the pileup format, users
          can use the SAMtools pileup procedure with option -s.

Filter:   Many HTS data alignment procedures record information about the
          short reads which are aligned to a reference genome.  Short reads
          with undesirable characteristics can be pre-filtered before 
          running GeMS.  For an explanation why pre-filtering may be
          desirable and for a brief tutorial on how to pre-filter SAM/BAM
          alignment files using SAMtools view, please see the PDF document
          entitled "Pre-Filtering Alignment Files" available at 
          https://sites.google.com/a/bioinformatics.ucr.edu/xinping-cui/
          home/software/ngs-snp-calling.

Usage:    gems -i input.pileup -o gems_output.txt [OPTIONS]

Options:  -d 0/1   0 indicates diploid, 1 indicates haploid, default is 0
          -s FLOAT maximum likelihood computing steps float value, smaller
                   is slower yet more precise, default is 0.001
          -m INT   maximum number of alleles to be considered at each site,
                   0 indicates unbounded, default is 255

Output:   The GeMS output consists of 6 columns:
          1. Chromosome identifier (character string)
          2. Reference site on chromosome (integer)
          3. Reference allele (single character)
          4. Consensus allele (single character)
          5. Largest posterior probability of the genotype models (float)
          6. p-value of Dixon's Q test (float)

          All sites which pass a SNP pre-filter are output.  The sites that
          qualify as GeMS SNP calls are those in which the reference allele
          differs from the consensus allele and the Dixon Q test p-value is
          less than the user specified alpha value.

Contact:  Xinping Cui <xinping.cui@ucr.edu>
          https://sites.google.com/a/bioinformatics.ucr.edu/xinping-cui/
