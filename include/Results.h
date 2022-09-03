#ifndef RESULTS_H
#define RESULTS_H
#include <vector>
#include "Enums.h"


class Results
{

 private:
        struct Result
        {
            size_t amountOfNumbers{0};
            double timeTaken{0.0};
        };


    public:
        Results();

        void add_measurements(size_t, double);
        void print_time_taken(size_t);

        double get_average(size_t);
        double get_standard_deviation(size_t);

        size_t get_iterations(size_t);
        void print_results(AlgorithmType);



    private:
        std::vector<Result> m_results;
        Result m_result{0};
};

#endif // RESULTS_H
