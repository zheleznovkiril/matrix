#include <iostream>
#include <string>
#include <ctime>


class matrix
{
private:
    float** Matrix = nullptr;
    int I = 0;
    int J = 0;
    bool initialization = NULL;
public:

    void create()
    {
        if (initialization != NULL)
        {
            std::cout << "Attention! You try initialize matrix is exist already!\nPlease delete it and try again";
        }
        else
        {
            std::cout << "Number of lines: ";
            std::cin >> I;
            std::cout << "Number of columns: ";
            std::cin >> J;
            std::cout << "Enter numbers:" << std::endl;

            initialization = 1;
            Matrix = new float* [I];
            for (int i = 0; i < I; ++i)
                Matrix[i] = new float[J];

            for (int i = 0; i < I; ++i)
                for (int j = 0; j < J; ++j)
                {
                    std::cout << "Matrix[" << i + 1 << "][" << j + 1 << "] = ";
                    std::cin >> Matrix[i][j];
                    std::cout << std::endl;
                }
        }
    }

    void deletem()
    {
        if (initialization == NULL);
        else
        {
            for (int i = 0; i < I; ++i)
                delete[] Matrix[i];
            delete[] Matrix;
            I = 0; J = 0; initialization = NULL;
            Matrix = nullptr;
        }
    }

    void printinfo()
    {
        if (initialization == NULL)
        {
            std::cout << "Matrix is not initialize." << std::endl;
        }
        else
        {
            for (int i = 0; i < I; ++i)
            {
                std::cout << "|\t";
                for (int j = 0; j < J; ++j)
                    std::cout << Matrix[i][j] << '\t';
                std::cout << "|\n" << std::endl;
            }
            std::cout << "Number of lines: " << I << '\n' << "Number of columns: " << J << std::endl;
        }
    }
    //-----Standart operations-----
    matrix* operator=(const matrix& other)
    {
        deletem();
        this->I = other.I;
        this->J = other.J;
        this->initialization = 1;

        this->Matrix = new float* [I];
        for (int i = 0; i < I; ++i)
        {
            this->Matrix[i] = new float[J];
            for (int j = 0; j < J; ++j)
                this->Matrix[i][j] = other.Matrix[i][j];
        }
        return this;
    }

    matrix operator+(const matrix& other)
    {
        matrix plus;
        if (this->initialization == 1 && other.initialization == 0)
            plus = *this;
        else if (this->initialization == 0 && other.initialization == 1)
            plus = other;
        else if (this->initialization == 1 && other.initialization == 1)
        {
            if (this->I == other.I)
                if (this->J == other.J)
                    for (int i = 0; i < I; ++i)
                        for (int j = 0; j < J; ++j)
                            plus.Matrix[i][j] = this->Matrix[i][j] + other.Matrix[i][j];
                else std::cout << "Error: different values of columns!" << std::endl;
            else std::cout << "Error: different values of lines!" << std::endl;
        }
        return plus;
    }
    //-----Standart operations-----
    //-----Getters-----
    bool is_exist()
    {return initialization;}
       
    float** get_matrix()
    {
        float** Copy = new float* [I];
        for (int i = 0; i < I; ++i)
        {
            Copy[i] = new float[J];
            for (int j = 0; j < J; ++j)
                Copy[i][j] = Matrix[i][j];
        }
        return Copy;
    }

    int get_I()
    {
        return I;
    }

    int get_J()
    {
        return J;
    }
    //-----Getters---
    //-----Random functions----- 
    //For right work make seed with srand()
    void random(int I0, int J0)
    {
        if (initialization != 0)
        {
            std::cout << "Attention! You try initialize matrix is exist already!\nPlease delete it and try again";
        }
        else
        {
            I = I0; J = J0; initialization = 1;
            Matrix = new float* [I];
            for (int i = 0; i < I; ++i)
                Matrix[i] = new float[J];

            for (int i = 0; i < I; ++i)
                for (int j = 0; j < J; ++j)
                    Matrix[i][j] = rand();
        }
    }

    void absoluterandom()
    {
        random(rand() % 15, rand() % 15);
    }

    void absoluterandom(int N) //N - число для задания диапазона количества элементов в столбце/колонке
    {
        random(rand() % N, rand() % N);
    }
    //-----Random functions-----
    //-----Constructors and destructor-----
    matrix() {}

    matrix(float** MatrixForCopy, int I0, int J0)
    {
        I = I0; J = J0; initialization = 1;
        Matrix = new float* [I];
        for (int i = 0; i < I; ++i)
            Matrix[i] = new float[J];

        for (int i = 0; i < I; ++i)
            for (int j = 0; j < J; ++j)
                Matrix[i][j] = MatrixForCopy[i][j];
    }

    ~matrix()
    {
        if (initialization == NULL);
        else
        {
            for (int i = 0; i < I; ++i)
                delete[] Matrix[i];
            delete[] Matrix;
        }
    }
    //-----Constructors and destructor-----
};



int main()// блять ошибка почему то
{
    srand(time(0));
    std::string a;
    matrix test;
    matrix test2;

    std::cout << test.is_exist() << "\n\n\n\n";

    test.random(5, 5);
    std::cout << test.get_I() << "\n\n\n";

    test2.random(5, 5);
    test.printinfo();
    test2.printinfo();
    test = test2 + test;
    test.printinfo();

    //test plus;
    std::cout << "Hello World!\n";
    return 0;
}
