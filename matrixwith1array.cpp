#include <iostream>
#include <string>
#include <ctime>

//Формула для нахождения номера элемента в одномерном массиве из двумерного массива(собственно матрицы), учтено, что индекс начинается с нуля, а не 1:
//N[i][j]=n[i*J+j]
//i - строчка элемента, j - столбец элемента, J - количество столбцов
//I*J- количество элементов, соответственно I*J-1 -индекс последнего элемента 
//перепиши на английский, даун

class matrix
{
private:
    float* Matrix = nullptr;
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
            Matrix = new float[I * J - 1];
            for (int i = 0; i < I; ++i)
                for (int j = 0; j < J; ++j)
                {
                    std::cout << "Matrix[" << i + 1 << "][" << j + 1 << "] = ";
                    std::cin >> Matrix[i * J + j];
                    std::cout << std::endl;
                }
        }
    }

    void deletem()//что-то неверно
    {
        if (initialization == NULL);
        else
        {
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
                    std::cout << Matrix[i * J + j] << '\t';
                std::cout << "|\n" << std::endl;
            }
            std::cout << "Number of lines: " << I << '\n' << "Number of columns: " << J << std::endl;
        }
    }

    void zero()
    {
        for (int i = 0; i < I * J; ++i)
            Matrix[i] = 0;
    }
    
    void zero(int I0, int J0)
    {
        if (initialization != NULL)
            std::cout << "Error: Matrix exist already"<<std::endl;
        else
        {
            this->I = I0; this->J = J0; this->initialization = 1;
            this->Matrix = new float[I * J];
            zero();
        }
    }
    //-----Standart operations-----
    matrix& operator=(const matrix& other)
    {
        deletem();
        this->I = other.I;
        this->J = other.J;
        this->initialization = 1;

        this->Matrix = new float[I * J];
        for (int i = 0; i < I * J; ++i)
            this->Matrix[i] = other.Matrix[i];
        return *this;
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
                {
                    plus.I = this->I; plus.J = this->J; plus.initialization = this->initialization;
                    plus.Matrix = new float[I * J];
                    for (int i = 0; i < I * J; ++i)
                        plus.Matrix[i] = this->Matrix[i] + other.Matrix[i];
                }
                else std::cout << "Error: different values of columns!" << std::endl;
            else std::cout << "Error: different values of lines!" << std::endl;
        }
        return plus;
    }

    matrix operator*(matrix& other)
    {
        matrix temp;

        if (other.initialization == 0 || this->initialization == 0)
            std::cout << "Error: one of matrix doesn't exist";
        else if (this->initialization == 1 && other.initialization == 1)
        {
            if (this->J == other.I)
            {
                temp.zero(this->I, other.J);
                for (int i = 0; i < temp.I; ++i)
                    for (int j = 0; j < temp.J; ++j)
                        for (int k = 0; k < this->J; ++k)
                            temp.Matrix[i * temp.J + j] += this->Matrix[i * (this->J) + k] * other.Matrix[k * other.J + j];
            }
            else std::cout << "Error: matrices aren't consistent!" << std::endl;
        }
        return temp;
    }
    //-----Standart operations-----
    //-----Getters-----

    float* get_matrix()
    {
        float* Copy = new float[I * J - 1];
        for (int i = 0; i < I; ++i)
            for (int j = 0; j < J; ++j)
                Copy[i * J + j] = Matrix[i * J + j];
        return Copy;
    }
    float get_N_elem(int i, int j) { return Matrix[(i - 1) * J + j - 1]; }
    int get_I() { return I; }
    int get_J() { return J; }
    bool is_exist() { return initialization; }
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
            Matrix = new float[I * J - 1];

            for (int i = 0; i < I; ++i)
                for (int j = 0; j < J; ++j)
                    Matrix[i * J + j] = rand() % 100 - 50;
        }
    }

    void absoluterandom()
    {
        random(rand() % 15 + 1, rand() % 15 + 1);
    }

    void absoluterandom(int N) //N - число для задания диапазона количества элементов в столбце/колонке
    {
        random(rand() % N + 1, rand() % N + 1);
    }
    //-----Random functions-----
    //-----Constructors and destructor-----
    matrix() {}

    matrix(float* MatrixForCopy, int I0, int J0)
    {
        I = I0; J = J0; initialization = 1;
        Matrix = new float[I * J - 1];

        for (int i = 0; i < I; ++i)
            for (int j = 0; j < J; ++j)
                Matrix[i * J + j] = MatrixForCopy[i * J + j];
    }

    ~matrix() { }//deletem();
    //-----Constructors and destructor-----
};



int main()// почини деструктор
{
    srand(time(0));
    std::string a;
    matrix test;
    matrix test2;
    matrix test3;
    std::cout << test.is_exist() << "\n\n\n\n";

    test.random(2,1);
    test.printinfo();

    test2.random(1,1);
    test2.printinfo();

    test3 = test * test2;
    test3.printinfo();

    //test plus;
    std::cout << "Hello World!\n";
    return 0;
}
