#ifndef SRC_MODEL_CALC_MODEL_H_
#define SRC_MODEL_CALC_MODEL_H_

#include <iostream>
#include <cmath>
#include <cstring>
#include <list>

#include "../Controller/Calc_Controller.h"

namespace s21 {
class Calc_Model {
    friend double Calc_Controller::Get_Digit();
    friend int Calc_Controller::String_processing(const char *str);
    friend void Calc_Controller::Set_X_Value(double val_x);
    friend bool Calc_Controller::Contains_X();
    friend bool Calc_Controller::Validate_Func_parameters(char *s1, char *s2, char *s3, char *s4);
    friend double Calc_Controller::Get_Result_With_X();

 private:
    enum Operations_ {
        digit,          // 0
        sum,            // 1
        sub,            // 2
        div,            // 3
        mul,            // 4
        mod,            // 5
        cos,            // 6
        sin,            // 7
        tan,            // 8
        acos,           // 9
        asin,           // 10
        atan,           // 11
        sqrt,           // 12
        ln,             // 13
        log,            // 14
        exp,            // 15
        open_bracket,   // 16
        close_bracket,  // 17
        x_val           // 18
    };

    struct node_t {
        double val_;
        Operations_ enum_;
        int priority_;

        node_t(double value, Operations_ operations, int priority) :
        val_(value), enum_(operations), priority_(priority) {}
    };

    using list_ = std::list<node_t>;
    using list_iter_ = list_::iterator;

    // Main Functions
    int Check_For_Errors();
    double Start_Calc_Processing();
    double Calculate();
    double Get_Result();
    void Handle_Operator(list_iter_ &iter, list_ &tmp);
    void Handle_Function(list_iter_ &iter, list_ &tmp);

    // Parsing
    void Remove_Spaces(const char *default_str_);
    // if functions below return 0 - Success, 1 - Bad format
    int Is_Digit(char c);
    int Check_Count_Of_Brackets();
    int Check_Digit(char *str, size_t cur_pos, bool is_for_calculation);
    int Check_Sign();
    int Check_Function();
    int Check_Exp();
    int Check_Last_Symbol_Before_Digit();

    void Set_Digit();
    void Set_Sign();
    void Set_Function();

    // Polish notation
    void Set_Data_To_Stack();
    void Polish_Notation();
    void Add_To_Result(list_ &result, list_iter_ &iter);
    void Add_Operation(list_ &result, list_iter_ &iter);
    void Check_Last_Support(list_ &result, list_iter_ &iter, list_iter_ &previous);
    void Handle_Closing_Bracket(list_ &result, list_iter_ &iter);
    void Reverse_List();

    bool Validate_Values(char *s1, char *s2, char *s3, char *s4);

    const char str_of_signs_[9] = "+-/*()^%";
    const char last_symbol_of_functions_[6] = "sngtd";
    const char first_symbol_of_functions_[6] = "sctal";

    char str_[256] = "";
    size_t cur_pos_ = 0;
    size_t size_;
    list_ nodes_;
    bool Contains_x_;
    std::pair<bool, double> x_ = {false, 0};
};
}  // namespace s21

#endif  // SRC_MODEL_CALC_MODEL_H_
