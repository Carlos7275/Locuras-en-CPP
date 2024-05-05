#ifndef CALCULATOR_CPP
#define CALCULATOR_CPP

#include "../headers/Enums.h"
class Calculator
{
private:
    double _num1, _num2;

public:
    /**
     * @brief Construct a new Calculator object
     *
     * @param num1
     * @param num2
     */
    Calculator(double num1, double num2)
    {
        _num1 = num1;
        _num2 = num2;
    }
    /**
     * @brief Addition
     *
     * @return double
     */
    double Add()
    {
        return _num1 + _num2;
    }

    /**
     * @brief Subtraction
     *
     * @return double
     */
    double Sub()
    {
        return _num1 - _num2;
    }

    /**
     * @brief Multiply
     *
     * @return double
     */
    double Mul()
    {
        return _num1 * _num2;
    }
    /**
     * @brief Division
     *
     * @return double
     */
    double Div()
    {
        return _num1 / _num2;
    }
    /**
     * @brief Operate a Calculator
     *
     * @param operation
     * @return double
     */
    double Operate(int operation)
    {
        switch (operation)
        {
        case RADD:
            return Add();
            break;
        case RSUB:
            return Sub();
            break;
        case RMUL:
            return Mul();
            break;
        case RDIV:
            return Div();
            break;
        default:
            break;
        }
    }
};

#endif // CALCULATOR_CPP