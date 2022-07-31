#ifndef SRC_CONTROLLER_CALC_CONTROLLER_H_
#define SRC_CONTROLLER_CALC_CONTROLLER_H_

namespace s21 {

class Calc_Model;

class Calc_Controller {
 public:
   Calc_Controller();
   ~Calc_Controller();
   double Get_Digit();
   int String_processing(const char *str);
   bool Contains_X();
   void Set_X_Value(double val_x);
   bool Validate_Func_parameters(char *s1, char *s2, char *s3, char *s4);
   double Get_Result_With_X();

 private:
   Calc_Model *Model_;
   char default_str_[256];
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CALC_CONTROLLER_H_
