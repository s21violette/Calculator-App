#include "../Model/Calc_Model.h"

namespace s21 {

Calc_Controller::Calc_Controller() {
    Model_ = new Calc_Model;
}

Calc_Controller::~Calc_Controller() {
    delete Model_;
}

double Calc_Controller::Get_Digit() {
    return Model_->Start_Calc_Processing();
}

double Calc_Controller::Get_Result_With_X() {
    return Model_->Calculate();
}

bool Calc_Controller::Contains_X() {
    return Model_->Contains_x_;
}

void Calc_Controller::Set_X_Value(double val_x) {
    Model_->x_.second = val_x;
    Model_->x_.first = true;
}

bool Calc_Controller::Validate_Func_parameters(char *s1, char *s2, char *s3, char *s4) {
    return Model_->Validate_Values(s1, s2, s3, s4);
}

int Calc_Controller::String_processing(const char *str) {
    if (strlen(str) == 0 || strlen(str) > 255) return 1;
    strcpy(default_str_, str);
    if (strlen(default_str_) == 0 || strlen(default_str_) > 255)
        return 1;
    Model_->Remove_Spaces(default_str_);
    Model_->Contains_x_ = (strchr(Model_->str_, 'x') != nullptr);
    return Model_->Check_For_Errors();
}
}  // namespace s21
