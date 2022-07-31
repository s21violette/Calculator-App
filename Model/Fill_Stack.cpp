#include "Calc_Model.h"

namespace s21 {

    void Calc_Model::Set_Digit() {
        char value[20] = "";
        size_t i = 0;
        while (cur_pos_ < size_ && (Is_Digit(str_[cur_pos_]) || str_[cur_pos_] == 'e' ||
        str_[cur_pos_] == '.')) {
            value[i++] = str_[cur_pos_];
            if (str_[cur_pos_] == 'e' && (str_[cur_pos_ + 1] == '-' || str_[cur_pos_ + 1] == '+')) {
                value[i++] = str_[++cur_pos_];
            }
            cur_pos_++;
        }
        nodes_.emplace_front(strtod(value, nullptr), digit, 0);
    }

    void Calc_Model::Set_Sign() {
        switch (str_[cur_pos_++]) {
            case '+':
                nodes_.emplace_front(0., sum, 1);
                break;
            case '-':
                nodes_.emplace_front(0., sub, 1);
                break;
            case '*':
                nodes_.emplace_front(0., mul, 2);
                break;
            case '/':
                nodes_.emplace_front(0., div, 2);
                break;
            case '^':
                nodes_.emplace_front(0., exp, 3);
                break;
            case '%':
                nodes_.emplace_front(0., mod, 2);
                break;
            case '(':
                nodes_.emplace_front(0., open_bracket, 5);
                break;
            case ')':
                nodes_.emplace_front(0., close_bracket, 5);
                break;
        }
    }

    void Calc_Model::Set_Function() {
        if (!strncmp(&str_[cur_pos_], "ln", 2)) {
            nodes_.emplace_front(0, ln, 4);
            cur_pos_ += 2;
        } else if (!strncmp(&str_[cur_pos_], "cos", 3)) {
            nodes_.emplace_front(0, cos, 4);
            cur_pos_ += 3;
        } else if (!strncmp(&str_[cur_pos_], "sin", 3)) {
            nodes_.emplace_front(0, sin, 4);
            cur_pos_ += 3;
        } else if (!strncmp(&str_[cur_pos_], "tan", 3)) {
            nodes_.emplace_front(0, tan, 4);
            cur_pos_ += 3;
        } else if (!strncmp(&str_[cur_pos_], "log", 3)) {
            nodes_.emplace_front(0, log, 4);
            cur_pos_ += 3;
        } else if (!strncmp(&str_[cur_pos_], "sqrt", 4)) {
            nodes_.emplace_front(0, sqrt, 4);
            cur_pos_ += 4;
        } else if (!strncmp(&str_[cur_pos_], "atan", 4)) {
            nodes_.emplace_front(0, atan, 4);
            cur_pos_ += 4;
        } else if (!strncmp(&str_[cur_pos_], "acos", 4)) {
            nodes_.emplace_front(0, acos, 4);
            cur_pos_ += 4;
        } else if (!strncmp(&str_[cur_pos_], "asin", 4)) {
            nodes_.emplace_front(0, asin, 4);
            cur_pos_ += 4;
        }
    }

void Calc_Model::Set_Data_To_Stack() {
    cur_pos_ = 0;
    size_ = strlen(str_);
    nodes_.clear();
    while (cur_pos_ < size_) {
        if (Is_Digit(str_[cur_pos_])) Set_Digit();
        if (cur_pos_ < size_ && strchr(str_of_signs_, str_[cur_pos_])) Set_Sign();
        if (cur_pos_ < size_ && strchr(first_symbol_of_functions_, str_[cur_pos_])) Set_Function();
        if (cur_pos_ < size_ && str_[cur_pos_] == 'x') {
            nodes_.emplace_front(0., x_val, 0);
            cur_pos_++;
        }
    }
}
}  // namespace s21
