#include "compression.h"

compression::compression()
{

}

void compression::batchCompress(std::vector<std::string> &Paths)
{
    std::cout<<"batch Compression";

    unsigned int numberOfAvailableThreads = std::thread::hardware_concurrency();
    std::cout << "Number of available threads: " << numberOfAvailableThreads << std::endl;
    std::vector<std::thread> threads;


    if( Paths.size() <= numberOfAvailableThreads)
    {

        //qInfo()<<" FIRST PART " ;

        // open threads equals to Paths count

        for (unsigned int i = 0 ; i < Paths.size() ; i++)
        {
            threads.emplace_back(&compression::batchCompressionWorkFunction , this, 1, i, std::ref(Paths));
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
            threads.emplace_back(&compression::batchCompressionWorkFunction , this, work_count, startIndex, std::ref(Paths));
            startIndex += work_count ;
        }
        threads.emplace_back(&compression::batchCompressionWorkFunction ,this, residual_work_count, startIndex,  std::ref(Paths));
    }


    for (auto& thread : threads)
    {
        thread.join();
    }
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

    for (unsigned int i = 0 ; i <  workCount ; i++)
    {
       // Controller::compress_file_here(Paths[i+startIndex]);
        std ::cout <<"\n" <<  "calling mostafa way function" ;
    }
}

void compression::batchDecompressionWorkFunction(unsigned int workCount, unsigned int startIndex, std::vector<std::string> &Paths)
{
    for (unsigned int i = 0 ; i <  workCount ; i++)
    {
       // Controller::decompress_file_here(Paths[i+startIndex]);
        //   calling mostafa way function

    }
}

