#include "compression.h"
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/copy.hpp>
//#include <boost/iostreams>

compression::compression()
{

}

void compression::batchCompress(std::vector<std::string> &Paths)
{
    std::cout<<"batch Compression"<<std::endl;

    unsigned int numberOfAvailableThreads = std::thread::hardware_concurrency();
    std::cout << "Number of available threads: " << numberOfAvailableThreads << std::endl;
    std::vector<std::thread> threads;


    if( Paths.size() <= numberOfAvailableThreads)
    {
        std::cout<<"batch Compression FIRST PART Start"<<std::endl;


        // open threads equals to Paths count

        for (unsigned int i = 0 ; i < Paths.size() ; i++)
        {
            threads.emplace_back(&compression::batchCompressionWorkFunction , this, 1, i, std::ref(Paths));
        }
        std::cout<<"batch Compression FIRST PART End"<<std::endl;


    }
    else
    {
        std::cout<<"batch Compression Second PART Start"<<std::endl;
        unsigned int work_count = Paths.size() / ( numberOfAvailableThreads - 1 );
        unsigned int residual_work_count = Paths.size() % ( numberOfAvailableThreads - 1 ) ;
        unsigned int  startIndex = 0 ;



        for (unsigned int i = 0 ; i < numberOfAvailableThreads - 1  ; i++)
        {
            std::cout << work_count << "    " << residual_work_count << "   " << startIndex <<"   "<<std::endl;
            threads.emplace_back(&compression::batchCompressionWorkFunction , this, work_count, startIndex, std::ref(Paths));
            startIndex += work_count ;
        }
        threads.emplace_back(&compression::batchCompressionWorkFunction ,this, residual_work_count, startIndex,  std::ref(Paths));
        std::cout<<"batch Compression Second PART End"<<std::endl;

    }


    for (auto& thread : threads)
    {
        thread.join();
    }

    std::cout<<"threads are joined"<<std::endl;

}

void compression::batchDecompress(std::vector<std::string> &Paths)
{
    std::cout<<"batch deCompression";

    unsigned int numberOfAvailableThreads = std::thread::hardware_concurrency();
    std::cout << "Number of available threads: " << numberOfAvailableThreads << std::endl;
    std::vector<std::thread> threads;


    if( Paths.size() <= numberOfAvailableThreads)
    {

       // qInfo()<<" FIRST PART " ;

        // open threads equals to Paths count

        for (unsigned int i = 0 ; i < Paths.size() ; i++)
        {
            threads.emplace_back(&compression::batchDecompressionWorkFunction, this, 1, i, std::ref(Paths));
        }


    }
    else
    {
       // qInfo()<<" SECOND PART " ;
        unsigned int work_count = Paths.size() / ( numberOfAvailableThreads - 1 );
        unsigned int residual_work_count = Paths.size() % ( numberOfAvailableThreads - 1 ) ;
        unsigned int  startIndex = 0 ;



        for (unsigned int i = 0 ; i < numberOfAvailableThreads - 1  ; i++)
        {
            std::cout << work_count << "    " << residual_work_count << "   " << startIndex <<"   "<<std::endl;
            threads.emplace_back(&compression::batchDecompressionWorkFunction, this, work_count, startIndex, std::ref(Paths));
            startIndex += work_count ;
        }
        threads.emplace_back(&compression::batchDecompressionWorkFunction, this, residual_work_count, startIndex, std::ref(Paths));
    }


    for (auto& thread : threads)
    {
        thread.join();
    }

}

void compression::batchCompressionWorkFunction(unsigned int workCount, unsigned int startIndex, std::vector<std::string> &Paths)
{
    std::cout<<"batchCompressionWorkFunction"<<std::endl;

    for (unsigned int i = 0 ; i <  workCount ; i++)
    {
       compression::compress_file_here(Paths[i+startIndex]);
    }
}

void compression::batchDecompressionWorkFunction(unsigned int workCount, unsigned int startIndex, std::vector<std::string> &Paths)
{
    for (unsigned int i = 0 ; i <  workCount ; i++)
    {
       compression::decompress_file_here(Paths[i+startIndex]);
    }
}

void compression::compress_file_here(const std::string &input_file_path)
{
    std::string output_file_path= input_file_path + ".gz";
    compress_file(input_file_path,output_file_path);

}


void compression::compress_file(const std::string& input_file_path, const std::string& output_file_path) {

    std::ifstream input_file(input_file_path, std::ios_base::in | std::ios_base::binary);
    std::ofstream output_file(output_file_path, std::ios_base::out | std::ios_base::binary);

    boost::iostreams::filtering_streambuf<boost::iostreams::output> out;
    out.push(boost::iostreams::gzip_compressor());
    out.push(output_file);
    boost::iostreams::copy(input_file, out);
}

void compression::decompress_file_here(const std::string &input_file_path){
    std::string output_file_path=input_file_path;
    output_file_path.erase(output_file_path.size() - 3, 3);
    decompress_file(input_file_path,output_file_path);
}

void compression::decompress_file(const std::string& input_file_path, const std::string& output_file_path) {
    std::ifstream input_file(input_file_path, std::ios_base::in | std::ios_base::binary);
    std::ofstream output_file(output_file_path, std::ios_base::out | std::ios_base::binary);

    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::gzip_decompressor());
    in.push(input_file);
    boost::iostreams::copy(in, output_file);
}

