#include "Calc_Model.h"

namespace s21 {
void Calc_Model::Add_To_Result(list_ &result, list_iter_ &iter) {
    result.emplace_back(iter->val_, iter->enum_, iter->priority_);
    nodes_.erase(iter);
}

void Calc_Model::Check_Last_Support(list_ &result, list_iter_ &iter, list_iter_ &previous) {
    if (previous->priority_ > iter->priority_ && previous->priority_ != 5 && previous != nodes_.end()) {
        Add_To_Result(result, previous);
        previous--;
        if (previous->enum_ != 0)
            Check_Last_Support(result, iter, previous);
    } else if (iter->priority_ == previous->priority_ && iter->priority_ != 5) {
        Add_To_Result(result, previous);
    }
}

void Calc_Model::Add_Operation(list_ &result, list_iter_ &iter) {
    if (iter != nodes_.begin()) {
        auto previous = iter;
        previous--;
        Check_Last_Support(result, iter, previous);
    }
}

void Calc_Model::Reverse_List() {
    list_ reverse;
    for (auto iter = nodes_.begin(); iter != nodes_.end(); iter++)
        reverse.emplace_front(iter->val_, iter->enum_, iter->priority_);
    nodes_ = reverse;
}

void Calc_Model::Handle_Closing_Bracket(list_ &result, list_iter_ &iter) {
    nodes_.erase(iter--);
    for (; iter->enum_ != open_bracket; iter--) {
        Add_To_Result(result, iter);
    }
    nodes_.erase(iter);
}

void Calc_Model::Polish_Notation() {
    list_ result;
    Reverse_List();
    for (auto iter = nodes_.begin(); iter != nodes_.end(); iter++) {
        if (iter->priority_ == 0)
            Add_To_Result(result, iter);
        else if (iter->priority_ != 5)
            Add_Operation(result, iter);
        else if (iter->enum_ == close_bracket)
            Handle_Closing_Bracket(result, iter);
    }
    Reverse_List();
    for (auto iter = nodes_.begin(); iter != nodes_.end(); iter++)
        Add_To_Result(result, iter);
    nodes_ = result;
}
}  // namespace s21
