#include <iostream>
#include <string>
#include <fstream>
 
long long int biggestPair(std::string str) {
    int biggest_1 = 0;
    int last_index = 0;
    int next_index = 0; // second of number last picked
    std::string sum {};
 
    for (size_t num_index = 0; num_index < 12; num_index++)
    {
       
        biggest_1 = stoi(str.substr(next_index, 1));
        for (int i = next_index; i < str.length() - (11 - num_index); i++)
        {
           
            int num = std::stoi(str.substr(i, 1));    
            //std::cout<<num;
            if (num > biggest_1) {
                biggest_1 = num;
                last_index = i;
                //std::cout<<"first num "<<biggest_1<<"\n";
            }
        }
        next_index = last_index + 1;
        sum = sum + str.substr(last_index, 1);
        last_index = next_index;
        //std::cout<<"\n";
    }
 
    return stoul(sum);
}
 
int main(int argc, char const *argv[])
{
    unsigned long long int sum = 0;
    std::ifstream file("input.txt");
    std::string str;
    while (std::getline(file, str))
    {
        sum = sum + biggestPair(str);
    }
    std::cout<<sum<<std::endl;
    return 0;
}