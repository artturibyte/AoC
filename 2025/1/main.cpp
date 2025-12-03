#include    <iostream>
#include    <fstream>
#include    <string>

int main(int argc, char const *argv[])
{
    int start_pos = 50;
    int position = start_pos;
    int zero_count = 0;
    std::ifstream file("input.txt");
    std::string str; 
    std::cout<< "The dial starts by pointing at " << position<<"\n";
    while (std::getline(file, str))
    {
        int count = stoi(str.substr(1, 4));
        char dir = str[0];
        //std::cout<<str[0] << "+" << count <<"\n";

        if (count > 100) {
            zero_count = zero_count + count / 100;
            count = count % 100;
            
        }

        switch (dir)
        {
        case 'L':
            //std::cout<<"Moved left...\n";
            if (position - count == 0) {
                position = position - count;
                zero_count++;
                std::cout<<"\n1 add 1";
            } else if (position - count < 0)
            {
                std::cout<<"\n2 add 1";
                if (position != 0) {
                    zero_count++;
                }
                
                position = 100 - (count - position);  // startpoint 99 + 1
            } else {
                position = position - count;
            }
            std::cout<< "The dial is rotated "<< dir << count << " to point at " << position<<"\n";
            break;
        
        case 'R':
            //std::cout<<"Moved right...\n"
            if (position + count == 100) {
                position = 0;
                zero_count++;
                std::cout<<"\n3 add 1";
            }
            else if (position + count > 100) {
                position = (position + count) - 100;
                zero_count++;
                std::cout<<"\n4 add 1";

            } else {
                position = position + count;
            }
            std::cout<< "The dial is rotated "<< dir << count << " to point at " << position<<"\n";
            break;
        }

        std::cout<<"Zero count is: "<<zero_count<<std::endl;
    }

    std::cout<<"Zero count is: "<<zero_count<<std::endl;
    return 0;
}
