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
    double* Matrix = nullptr;
    int I = 0;
    int J = 0;
    bool initialization = NULL;

    double easy_detA()//использовал числа, потому что функция для подсчета определителся матрицы 2х2 и 1х1
    {
        if (I == 2)
            return (Matrix[0] * Matrix[3] - Matrix[1] * Matrix[2]);
        else if (I == 1)
            return Matrix[0];
    }
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
            Matrix = new double[I * J];
            for (int i = 0; i < I; ++i)
                for (int j = 0; j < J; ++j)
                {
                    std::cout << "Matrix[" << i + 1 << "][" << j + 1 << "] = ";
                    std::cin >> Matrix[i * J + j];
                    std::cout << std::endl;
                }
        }
    }

    void deletem()
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

    double detA()
    {
        if (initialization == NULL)
        {
            std::cout << "Error: Matrix doesn't exist" << std::endl;
            return 0;
        }
        else if (I != J)
        {
            std::cout << "Error: detA doesn't exist for not square matrix" << std::endl;
            return 0;
        }
        else if (I <= 2)
            return easy_detA();
        else
        {
            matrix* arr = new matrix[I];
            double det = 0;
            for (int i = 0; i < I; ++i) //инициализация массива для матриц с пониженным рангом, количество элементов равно количеству элементов строки
            {
                arr[i].I = I - 1; arr[i].J = I - 1; arr[i].initialization = 1;
                arr[i].Matrix = new double[arr[i].I * arr[i].I];
            }


            for (int kj = 0; kj < I; ++kj)//понижение порядка матрицы для каждого элемента и записывается в arr, убирается первая (0) строка и j столбец
            {
                for (int i = 0, i2 = 1; i < I - 1; ++i, ++i2)
                    for (int j = 0, j2 = 0; j < I - 1; ++j, ++j2)
                    {
                        if (j2 == kj)
                            ++j2;
                        arr[kj].Matrix[i * (J - 1) + j] = this->Matrix[i2 * (this->J) + j2];
                    }
            }
            for (int i = 0; i < I; ++i) //сложение всех миноров 1-ой строки, умноженных на (-1)^i и i элемент и их суммирование
            {
                if (this->Matrix[i] == 0);
                else if (i % 2 == 0)
                    det += (this->Matrix[i]) * arr[i].detA();
                else
                    det -= (this->Matrix[i]) * arr[i].detA();
            }

            delete[] arr;
            return det;
        }
    }

    void identity()
    {
        if (initialization == NULL)
            std::cout << "Error: Matrix doesn't exist" << std::endl;
        else if (I != J)
            std::cout << "Error: Not square matrix can't be tranform" << std::endl;
        else
        {
            zero();
            for (int i = 0; i < I * J; i += (J + 1))
                this->Matrix[i] = 1;
        }
    }

    void identity(int I)
    {
        if (initialization != NULL)
            deletem();
        this->I = I; this->J = I; this->initialization = 1;
        this->Matrix = new double[I * I];
        (*this).identity();
    }

    void zero()
    {
        if (initialization == NULL)
            std::cout << "Error: Matrix doesn't exist" << std::endl;
        else
            for (int i = 0; i < I * J; ++i)
                Matrix[i] = 0;
    }

    void zero(int I0, int J0)
    {
        if (initialization != NULL)
            deletem();
        this->I = I0; this->J = J0; this->initialization = 1;
        this->Matrix = new double[I * J];
        zero();
    }
    //-----Elementary operations-----
    template <typename T>
    matrix& multiply(T x)
    {
        if (initialization == NULL)
            std::cout << "Error: Matrix doesn't exist" << std::endl;
        else
            for (int i = 0; i < this->I * this->J; ++i)
                this->Matrix[i] *= x;
        return *this;
    }

    template <typename T>
    matrix operator*(T x)
    {
        matrix temp = *this;
        return temp.multiply(x);
    }

    matrix& transposition()
    {
        if (initialization == NULL)
            std::cout << "Error: Matrix doesn't exist" << std::endl;
        else
        {
            matrix temp;
            temp.I = this->J; temp.J = this->I; temp.initialization = 1;
            temp.Matrix = new double[I * J];
            for (int i = 0; i < I; ++i)
                for (int j = 0; j < J; ++j)
                    temp.Matrix[j * (this->I) + i] = this->Matrix[i * J + j];
            (*this) = temp;
        }
        return *this;
    }
    matrix& operator=(const matrix& other)
    {
        deletem();
        this->I = other.I;
        this->J = other.J;
        this->initialization = 1;
        this->Matrix = new double[I * J];
        for (int i = 0; i < I * J; ++i)
            this->Matrix[i] = other.Matrix[i];
        return *this;
    }

    matrix operator-(const matrix& other)
    {
        matrix temp;
        if (this->initialization == 1 && other.initialization == 0)
        {
            std::cout << "Error: one of matrix doesn't exist" << std::endl;
            temp = *this;
        }
        else if (this->initialization == 0 && other.initialization == 1)
        {
            std::cout << "Error: one of matrix doesn't exist" << std::endl;
            temp = other;
        }
        else if (this->initialization == 1 && other.initialization == 1)
        {
            if (this->I == other.I)
                if (this->J == other.J)
                {
                    temp.zero(this->I, other.J);
                    for (int i = 0; i < I * J; ++i)
                        temp.Matrix[i] = this->Matrix[i] - other.Matrix[i];
                }
                else std::cout << "Error: different values of columns!" << std::endl;
            else std::cout << "Error: different values of lines!" << std::endl;
        }
        return temp;
    }

    matrix operator+(const matrix& other)
    {
        matrix temp;
        if (this->initialization == 1 && other.initialization == 0)
        {
            std::cout << "Error: one of matrix doesn't exist" << std::endl;
            temp = *this;
        }
        else if (this->initialization == 0 && other.initialization == 1)
        {
            std::cout << "Error: one of matrix doesn't exist" << std::endl;
            temp = other;
        }
        else if (this->initialization == 1 && other.initialization == 1)
        {
            if (this->I == other.I)
                if (this->J == other.J)
                {
                    temp.zero(this->I, other.J);
                    for (int i = 0; i < I * J; ++i)
                        temp.Matrix[i] = this->Matrix[i] + other.Matrix[i];
                }
                else std::cout << "Error: different values of columns!" << std::endl;
            else std::cout << "Error: different values of lines!" << std::endl;
        }
        return temp;
    }

    matrix operator*(matrix& other)
    {
        matrix temp;

        if (other.initialization == 0 || this->initialization == 0)
            std::cout << "Error: one of matrix doesn't exist" << std::endl;
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

    matrix& operator*=(matrix& other)
    {
        (*this) = (*this) * other;
        return *this;
    }

    matrix& operator+=(matrix& other)
    {
        (*this) = (*this) + other;
        return *this;
    }

    matrix& operator-=(matrix& other)
    {
        (*this) = (*this) - other;
        return *this;
    }

    /*void power(int pow) исправь потом
    {
        if (pow >= 1)
        {
            matrix temp = (*this);
            if (this->I != this->J)
            {
                std::cout << "Error: Matrix isn't square" << std::endl;
            }
            else if (this->initialization == NULL)
            {
                std::cout << "Error: Matrix doesn't exist" << std::endl;
            }
            else
            {
                for (int i = 1; i < pow; ++i)
                    temp *= (*this);
                (*this) = temp;
            }
        }
        else
        {
            std::cout << "Error: The weird value for power" << std::endl;
        }
    }*/
    //-----Standart operations-----
    //-----Getters-----

    double* get_matrix()
    {
        double* Copy = new double[I * J];
        for (int i = 0; i < I; ++i)
            for (int j = 0; j < J; ++j)
                Copy[i * J + j] = Matrix[i * J + j];
        return Copy;
    }
    double get_N_elem(int i, int j) { return Matrix[(i - 1) * J + j - 1]; }
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
            Matrix = new double[I * J];

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
    matrix(const matrix& other)
    {
        this->I = other.I; this->J = other.J; this->initialization = other.initialization;
        this->Matrix = new double[I * J];

        for (int i = 0; i < I; ++i)
            for (int j = 0; j < J; ++j)
                this->Matrix[i * J + j] = other.Matrix[i * J + j];
    }

    matrix(double* MatrixForCopy, int I0, int J0)
    {
        I = I0; J = J0; initialization = 1;
        Matrix = new double[I * J];

        for (int i = 0; i < I; ++i)
            for (int j = 0; j < J; ++j)
                Matrix[i * J + j] = MatrixForCopy[i * J + j];
    }

    ~matrix() { deletem(); }
    //-----Constructors and destructor-----
};


int main()
{
    srand(time(0));
    std::string a;
    double Matrix[9]{ 5,7,1,-4,1,0,2,0,3 }; //detA = 97

    matrix test;
    matrix test2(Matrix, 3, 3);
    matrix test3;
    //matrix test4;
    //std::cout << test.is_exist() << "\n\n\n\n";

    //test.random(50, 50);
    //std::cout << std::fixed << test2.detA() << std::endl;
    test.zero(4, 4);
    test = test2*2;
    test.printinfo();
    // test2.transposition();
    // test2.printinfo();
    // std::cout<< test2.detA() << std::endl;

     //std::cout << test.detA() << std::endl;

     //test plus;
    std::cout << "Hello World!\n";
    return 0;
}
