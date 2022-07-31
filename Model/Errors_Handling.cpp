#include "Calc_Model.h"

namespace s21 {

    void Calc_Model::Remove_Spaces(const char *default_str_) {
        size_t j = 0;
        nodes_.clear();
        for (size_t i = 0; i < 256; i++)
            str_[i] = '\0';
        for (size_t i = 0; i < strlen(default_str_); i++) {
            if (!strncmp(&default_str_[i], "mod", 3)) {
                str_[j++] = '%';
                i += 2;
            } else if (default_str_[i] == '+' && (i == 0 || default_str_[i - 1] == '(')) {
                continue;
            } else if (default_str_[i] == '-' && (i == 0 || default_str_[i - 1] == '(')) {
                str_[j++] = '0';
                str_[j++] = '-';
            } else if (default_str_[i] != ' ') {
                str_[j++] = default_str_[i];
            }
        }
        str_[j] = '\0';
        size_ = j;
    }

    int Calc_Model::Check_Last_Symbol_Before_Digit() {
        return (str_[cur_pos_ - 1] == 'x' || str_[cur_pos_ - 1] == ')');
    }

    int Calc_Model::Is_Digit(char c) {
        return c >= '0' && c <= '9';
    }

    // if function returns 0, then it means, that we have the same count of opening and closing brackets
    int Calc_Model::Check_Count_Of_Brackets() {
        int count_of_braces = 0;
        for (size_t i = 0; i < size_; i++) {
            if (str_[i] == '(')
                count_of_braces++;
            else if (str_[i] == ')')
                count_of_braces--;
            if (count_of_braces < 0)
                break;
        }
        return count_of_braces;
    }

    bool Calc_Model::Validate_Values(char *s1, char *s2, char *s3, char *s4) {
        if (strlen(s1) == 0 || strlen(s2) == 0 || strlen(s3) == 0 || strlen(s4) == 0)
            return false;
        return (!Check_Digit(s1, 0, false) && !Check_Digit(s2, 0, false) &&
        !Check_Digit(s3, 0, false) && !Check_Digit(s4, 0, false));
    }

    int Calc_Model::Check_Digit(char *str, size_t cur_pos, bool is_for_calculation) {
        size_ = strlen(str);
        if ((Is_Digit(str[cur_pos]) || str[cur_pos] == 'x') && cur_pos > 0)
            if (Check_Last_Symbol_Before_Digit()) return 1;
        if (Is_Digit(str[cur_pos])) {
            int count_of_dots = 0;
            while (cur_pos < size_ && str[cur_pos] && (Is_Digit(str[cur_pos]) || str[cur_pos] == '.')) {
                if (str[cur_pos] == '.')
                    count_of_dots++;
                if (count_of_dots > 1)
                    return 1;
                cur_pos++;
            }
        } else if (str[cur_pos] == 'x') {
            cur_pos++;
        }
        if (is_for_calculation)
            cur_pos_ = cur_pos;
        return 0;
    }

    int Calc_Model::Check_Sign() {
        if (cur_pos_ > 0 && strchr(str_of_signs_, str_[cur_pos_])) {
            if (str_[cur_pos_ - 1] == '(' && (str_[cur_pos_] == '*' || str_[cur_pos_] == '/' ||
            str_[cur_pos_] == '%'))
                return 1;
            if (str_[cur_pos_ - 1] == '.')
                return 1;
            if ((str_[cur_pos_ - 1] == '*' || str_[cur_pos_ - 1] == '/' || str_[cur_pos_ - 1] == '+'
            || str_[cur_pos_ - 1] == '-') && str_[cur_pos_] != '(')
                return 1;
            if (str_[cur_pos_] == ')' && str_[cur_pos_ - 1] != 'x' && !Is_Digit(str_[cur_pos_ - 1]) &&
                    str_[cur_pos_ - 1] != ')')
                return 1;
            if (str_[cur_pos_] == '(' && !strchr(str_of_signs_, str_[cur_pos_ - 1]) &&
                !strchr(last_symbol_of_functions_, str_[cur_pos_ - 1]))
                return 1;
            if (cur_pos_ == size_ - 1 && str_[cur_pos_] != ')')
                return 1;
            cur_pos_++;
        } else if (strchr(str_of_signs_, str_[cur_pos_])) {
            if (str_[cur_pos_] != '(' && str_[cur_pos_] != '+' && str_[cur_pos_] != '-')
                return 1;
            cur_pos_++;
        }
        return 0;
    }

    int Calc_Model::Check_Function() {
        if (cur_pos_ > 0 && (Check_Last_Symbol_Before_Digit() || Is_Digit(str_[cur_pos_ - 1])) &&
        strchr(first_symbol_of_functions_, str_[cur_pos_]))
            return 1;
        if (strchr(first_symbol_of_functions_, str_[cur_pos_])) {
            if (!strncmp(&str_[cur_pos_], "ln", 2))
                cur_pos_ += 2;
            else if (!strncmp(&str_[cur_pos_], "sin", 3) ||
            (str_[cur_pos_] == 'c' && !strncmp(&str_[cur_pos_], "cos", 3)) ||
                (str_[cur_pos_] == 't' && !strncmp(&str_[cur_pos_], "tan", 3)) ||
                (str_[cur_pos_] == 'l' && !strncmp(&str_[cur_pos_], "log", 3)))
                cur_pos_ += 3;
            else if (!strncmp(&str_[cur_pos_], "asin", 4) || !strncmp(&str_[cur_pos_], "atan", 4) ||
            !strncmp(&str_[cur_pos_], "acos", 4) || !strncmp(&str_[cur_pos_], "sqrt", 4))
                cur_pos_ += 4;
            else
                return 1;
        }
        return 0;
    }

    int Calc_Model::Check_Exp() {
        if (cur_pos_ > 0 && str_[cur_pos_] == 'e') {
            if (!Is_Digit(str_[cur_pos_ - 1]) || (str_[cur_pos_ + 1] != '+' &&
            str_[cur_pos_ + 1] != '-' && !Is_Digit(str_[cur_pos_ + 1])))
                return 1;
            cur_pos_++;
            while (cur_pos_ < size_ && Is_Digit(str_[cur_pos_]))
                cur_pos_++;
        } else if (str_[cur_pos_] == 'e' && (cur_pos_ == 0 || cur_pos_ == strlen(str_) - 1)) {
            return 1;
        }
        return 0;
    }

    int Calc_Model::Check_For_Errors() {
        if (Check_Count_Of_Brackets())
            return 1;
        cur_pos_ = 0;
        while (cur_pos_ < size_) {
            if (Check_Exp()) return 1;
            if (cur_pos_ < strlen(str_) && Check_Digit(str_, cur_pos_, true)) return 1;
            if (cur_pos_ < strlen(str_) && Check_Sign()) return 1;
            if (cur_pos_ < strlen(str_) && Check_Function()) return 1;
            if (cur_pos_ < strlen(str_) && !strchr(first_symbol_of_functions_, str_[cur_pos_]) &&
                !Is_Digit(str_[cur_pos_]) && !strchr(str_of_signs_, str_[cur_pos_]) &&
                str_[cur_pos_] != 'e' && str_[cur_pos_] != 'x')
                return 1;
        }
        return 0;
    }
}  // namespace s21
