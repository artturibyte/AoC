#include    <iostream>
#include    <fstream>
#include    <string>
#include    <math.h>

bool checkSameDigits(long long int N)
{
    std::string str = std::to_string(N);
    char digit = str[0];

    for (int i = 1; i < str.length(); i++)
    {
        if (str[i] != digit)
        {
            return false;
        }
    }

    return true;
}

bool checkSameChunks(long long int N, int chunk)
{
    // 222 222 222 
    std::string str = std::to_string(N);
    std::string part = str.substr(0, chunk);

    for (int i = 1; i < str.length() / chunk; i++)
    {
        std::string next_part = str.substr(i*chunk, chunk);
        if (next_part != part)
        {
            return false;
        }

        
    }
    
    std::cout<<str<< " chunk "<<part<<" pass\n";
    return true;
}


int main(int argc, char const *argv[])
{
    unsigned long long int sum = 0;
    std::ifstream file("input.txt");
    std::string str; 
    while (std::getline(file, str, ',')) {

        int pos = str.find("-");

        unsigned long int a = stoul(str.substr(0, pos));
        unsigned long int b = stoul(str.substr(pos +1));

        for (unsigned long int i = a; i < b + 1; i++)
        {
            int size = trunc(log10(i)) + 1;
            if (size % 2 == 0)
            {

                int modulo = pow(10, size >> 1);
                std::pair<u_int32_t, u_int32_t> parts = {i / modulo, i % modulo};

                if (parts.first == parts.second)
                {
                    sum = sum + i;
                    std::cout<<i<< " pass\n";
                    continue;
                }
            }

            if (checkSameDigits(i) & size > 1)
            {
                // num not even but all digits are same
                sum = sum + i;
                std::cout<<i<< " pass\n";
                continue;
            }

            for (int c = 2; c < size / 2; c++)
            {
                if (size % c == 0) {
                    
                if (checkSameChunks(i, c)) {

                    sum = sum + i;
                }
            }
            }
        }
    }

    std::cout<<sum<<"\n";
}