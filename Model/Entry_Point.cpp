#include "Calc_Model.h"

namespace s21 {

double Calc_Model::Get_Result() {
    return Calculate();
}

double Calc_Model::Start_Calc_Processing() {
    Set_Data_To_Stack();
    Polish_Notation();
    return Get_Result();
}
}  // namespace s21
