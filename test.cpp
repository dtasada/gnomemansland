#include <iostream>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        std::cout << "Thread " << id << " is running\n";
    }
    return 0;
}

