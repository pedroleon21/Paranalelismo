#include <iostream>
#include <omp.h>
#include <time.h>
using namespace std;

int eprimo(double num);

int main()
{
    double num[100], soma = 0, mult = 1, somp = 0, tid;
    for (int i = 0; i < 100; i++)
    {
        num[i]=i;
        //num[i] = rand() % 100;
        cout << num[i] << " ";
    }
    cout << "\n";
#pragma omp parallel private(tid) shared(num, somp, soma, mult)
    {
        tid = (omp_get_thread_num());
        for (int i = 0; i < 100; i++)
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
                int tid2;
#pragma omp parallel private(tid2) shared(somp, num)
                {
                    if (eprimo(num[i]))
                    {
                        cout << num[i] << endl;
                        somp += num[i];
                    }
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
    for (int i = 2; i * i <= num; i++)
        if (!((int)num % i))
            return 0;
    return 1;
}