#include "Calc_Model.h"

namespace s21 {

    void Calc_Model::Handle_Operator(list_iter_ &iter, list_ &tmp) {
        auto first_val = iter;
        auto second_val = iter;
        first_val--;
        first_val--;
        second_val--;
        switch (iter->enum_) {
            case sum:
                first_val->val_ += second_val->val_;
                break;
            case sub:
                first_val->val_ -= second_val->val_;
                break;
            case div:
                first_val->val_ /= second_val->val_;
                break;
            case mul:
                first_val->val_ *= second_val->val_;
                break;
            case mod:
                first_val->val_ = std::fmod(first_val->val_, second_val->val_);
                break;
            case exp:
                first_val->val_ = std::pow(first_val->val_, second_val->val_);
                break;
            default:
                break;
        }
        tmp.erase(second_val);
        tmp.erase(iter++);
    }

    void Calc_Model::Handle_Function(list_iter_ &iter, list_ &tmp) {
        auto value = iter;
        value--;
        switch (iter->enum_) {
            case cos:
                value->val_ = std::cos(value->val_);
                break;
            case sin:
                value->val_ = std::sin(value->val_);
                break;
            case tan:
                value->val_ = std::tan(value->val_);
                break;
            case acos:
                value->val_ = std::acos(value->val_);
                break;
            case asin:
                value->val_ = std::asin(value->val_);
                break;
            case atan:
                value->val_ = std::atan(value->val_);
                break;
            case sqrt:
                value->val_ = std::sqrt(value->val_);
                break;
            case ln:
                value->val_ = std::log(value->val_);
                break;
            case log:
                value->val_ = log10(value->val_);
                break;
            default:
                break;
        }
        tmp.erase(iter++);
    }

    double Calc_Model::Calculate() {
        list_ tmp = nodes_;
        auto iter = tmp.begin();
        while (tmp.size() > 1) {
            if (iter->priority_ < 4 && iter->priority_ > 0) {
                Handle_Operator(iter, tmp);
            } else if (iter->priority_ == 4) {
                Handle_Function(iter, tmp);
            } else {
                if (iter->enum_ == x_val && x_.first)
                    iter->val_ = x_.second;
                iter++;
            }
        }
        double ret = tmp.begin()->val_;
        tmp.clear();
        return ret;
    }
}  // namespace s21
