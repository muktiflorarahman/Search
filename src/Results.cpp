#include "Results.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
Results::Results()
{
    //ctor
}

//lägger till mätningar till resultat vektorn
void Results::add_measurements(size_t amountOfNumbers, double timeTaken)
{
    m_result.amountOfNumbers = amountOfNumbers;
    m_result.timeTaken = timeTaken;

    m_results.push_back(m_result);
}
//skriver ut posten timeTaken för varje post som är intressant
void Results::print_time_taken(size_t amountOfNumbers)
{
    for(size_t index = 0; index < m_results.size(); index++)
    {
        if(m_results[index].amountOfNumbers == amountOfNumbers)
        {
            std::cout << "Time taken for specific post: " << m_results[index].timeTaken << std::endl;
        }
    }

}


double Results::get_average(size_t amountOfNumbers)
{
    double average = 0.0;
    double sum = 0.0;
    size_t amount = 0;

    for(size_t index = 0; index < m_results.size(); index++)
    {
        //ska komma åt amount of numbers posten

        if(m_results[index].amountOfNumbers == amountOfNumbers)
        {
            sum = sum + m_results[index].timeTaken;
            amount++;
        }
    }
    average = sum / amount;

    return average;
}

double Results::get_standard_deviation(size_t amountOfNumbers)
{
    double standardDeviation = 0.0;
    double sum = 0.0;
    double average = get_average(amountOfNumbers);

     for(size_t index = 0; index < m_results.size(); index++)
    {
        if(m_results[index].amountOfNumbers == amountOfNumbers)
        {
            sum = sum + std::pow((m_results[index].timeTaken - average), 2);
        }
    }
    standardDeviation = std::sqrt(sum / get_iterations(amountOfNumbers));

    return standardDeviation;

}

size_t Results::get_iterations(size_t amountOfNumbers)
{
    size_t iterations = 0;

    for(size_t index = 0; index < m_results.size(); index++)
    {
        if(m_results[index].amountOfNumbers == amountOfNumbers)
        {
            iterations++;
        }
    }

    return iterations;
}

void Results::print_results(AlgorithmType algorithm)
{
    //skriver till en fil

    std::ofstream writeOut("results.dat", std::ios_base::app);
    switch(algorithm)
    {
        case AlgorithmType::LINEAR:
            std::cout << "Linear search\t - ";
            writeOut << "Linear search\t - ";
            break;

        case AlgorithmType::BINARY:
            std::cout << "Binary search\t - ";
            writeOut << "Binary search\t - ";
            break;

        case AlgorithmType::BINARY_SEARCH_TREE:
            std::cout << "Binary search tree\t - ";
            writeOut << "Binary search tree\t - ";
            break;

        case AlgorithmType::HASH_TABLE:
            std::cout << "Hash table\t - ";
            writeOut << "Hash table\t - ";
            break;

        default:
            break;

    }
    std::cout << "Sequential prime numbers" << std::endl;
    writeOut << "Sequential prime numbers" << std::endl;

    int WIDTH = 20;
	std::cout
		<< std::setw( WIDTH / 2 ) << std::left << "N"
		<< std::setw( WIDTH ) << "T [ ms ]"
		<< std::setw( WIDTH ) << "Stdev [ ms ]"
		<< std::setw( WIDTH ) << "Samples" << std::endl;
	writeOut
		<< std::setw( WIDTH / 2 ) << std::left << "N"
		<< std::setw( WIDTH ) << "T [ ms ]"
		<< std::setw( WIDTH ) << "Stdev [ ms ]"
		<< std::setw( WIDTH ) << "Samples" << std::endl;

    size_t amountOfNumbers = 0;
    // loopar igenom m_results vektorn
    for(size_t index = 0; index < m_results.size(); index++)
    {
        if(amountOfNumbers < m_results[index].amountOfNumbers)
        {
            amountOfNumbers = m_results[index].amountOfNumbers;
            double average = get_average(amountOfNumbers);
            double standardDeviation = get_standard_deviation(amountOfNumbers);
            size_t iterations = get_iterations(amountOfNumbers);

            std::cout
                << std::setw( WIDTH / 2 ) << std::left << amountOfNumbers
                << std::setw( WIDTH ) << average
                << std::setw( WIDTH ) << standardDeviation
                << std::setw( WIDTH ) << iterations << std::endl;

            writeOut
                << std::setw( WIDTH / 2 ) << std::left << amountOfNumbers
                << std::setw( WIDTH ) << average
                << std::setw( WIDTH ) << standardDeviation
                << std::setw( WIDTH ) << iterations << std::endl;
        }
    }

    std::cout << std::endl;
    writeOut << std::endl;
    writeOut.close();
    m_results.clear();


}






