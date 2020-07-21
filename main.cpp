#include <iostream>
#include <omp.h>
#include <time.h>
using namespace std;
int sizing = 1000000;
int eprimo(double num);

int main()
{
    double num[sizing], soma = 0, mult = 1, somp = 0, tid;
    for (int i = 0; i < sizing; i++)
    {
        num[i] = i+1;
        num[i] = rand() % sizing;
        cout << num[i] << " ";
    }
    cout << "\n";
#pragma omp parallel private(tid) shared(num, somp, soma, mult, sizing)
    {
        tid = (omp_get_thread_num());
        for (int i = 0; i < sizing; i++)
        {
            if (tid == 1)
            {
                soma += num[i];
            }
            else if (tid == 2)
            {
                mult *= num[i];
            }
            if (tid == 3)
            {
                if (eprimo(num[i]))
                {
                    cout << num[i] << endl;
                    somp += num[i];
                }
            }
        }
    }

    cout << "soma : " << soma << endl;
    cout << "soma de primos :" << somp << endl;
    cout << "miltiplicação : " << mult << endl;
    return 0;
}

int eprimo(double num)
{
    if (num < 2)
        return 0;
    for (int i = 2; i * i <= num; i++)
        if (!((int)num % i))
            return 0;
    return 1;
}