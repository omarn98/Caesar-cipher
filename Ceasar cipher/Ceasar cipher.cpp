#include <iostream>
#include <string>
#include <fstream>
#include <omp.h>
#include <time.h>


#define numOfThreads 2

std::string readFile();
char ceasarCipher(char text, int shift);
void writeToFile(std::string text);



int main()
{
    clock_t tStart = clock();

    int shift = 2;

    std::string text = readFile();

    //divide string by number of threads

    omp_set_num_threads(numOfThreads);

    #pragma omp parallel
        {
       
        int i;
        #pragma omp for schedule(static)
                for (i = 0; i < text.length(); i++)
                    {
                    char x;

                    int ascii;

                  

                   /* if (text[i] == ' ')
                    {
                        x =  ' ';
                        continue;

                    }
                    ascii = int(text[i]);

                    if (ascii >= 65 && ascii <= 90)
                    {
                        ascii += 32;
                    }

                    if (ascii >= 97 && ascii <= 122)
                    {
                        ascii += shift;
                    }

                    if (ascii > 122)
                    {
                        ascii -= 26;
                    }
                    x =   char(ascii);
                    */


                    ascii = int(text[i]);

                    if (ascii >= 32 && ascii <= 254)
                    {
                        ascii += shift;
                    }

                    if (ascii > 254)
                    {
                        ascii -= 222;
                    }
                    x = char(ascii);

                    
                        text[i] = x;
                    
                        
                    }
        }
    

 
       
        

    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    writeToFile(text);
}

std::string readFile()
{
    std::string word, text = "";
    
    std::ifstream textFile;
    textFile.open("plainText.txt");

    while (textFile >> word)
    {
        if (text == "")
        {
            text = word;
        }
        else
        {
            text += " " + word;
        }
    }


    textFile.close();

    return text;
}




void writeToFile(std::string text)
{
    std::ofstream cipherFile("cipherText.txt");
    if (cipherFile.is_open())
    {
        cipherFile << text;
    }
    else
    {
        std::cout << "unable to open file";
    }
    return;
}