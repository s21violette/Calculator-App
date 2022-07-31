#include <gtest/gtest.h>
#include "Model/Calc_Model.h"

using namespace s21;

const double EXP = 1e-7;

TEST(Test, Test_success) {
    Calc_Controller Control;
    EXPECT_EQ(Control.String_processing("1 + 2 /acos54"), 0);
    EXPECT_EQ(Control.String_processing("sin45 + cos (-5.12) + sqrt(-23)"), 0);
    EXPECT_EQ(Control.String_processing("+45- (2 - 1)"), 0);
    EXPECT_EQ(Control.String_processing("12e-15 + 43"), 0);
    EXPECT_EQ(Control.String_processing("123 + 1.2-6 ^ (1 - 3) / 2"), 0);
    EXPECT_EQ(Control.String_processing("(cos((-5)))+ln( (10/(5*7))^2)-(tan(sin(-3mod2))-5mod3*4/5/ 7)"), 0);
    EXPECT_EQ(Control.String_processing("1e-5 + 3"), 0);
    EXPECT_EQ(Control.String_processing("124e-12412"), 0);
    EXPECT_EQ(Control.String_processing("2e1"), 0);
    EXPECT_EQ(Control.String_processing("9 * atan5 / acos1 - 2e-4 ^ ln13"), 0);
}

TEST(Test, Test_fail) {
    Calc_Controller Control;
    EXPECT_EQ(Control.String_processing(""), 1);
    EXPECT_EQ(Control.String_processing("/12 - 3"), 1);
    EXPECT_EQ(Control.String_processing("asin(acos(atan(-1.12))"), 1);
    EXPECT_EQ(Control.String_processing("(acos((-5)))+ln( *(10/(5*7))^2)-(atan(sin(-3mod2))-5mod3*4/5/  7)"),
              1);
    EXPECT_EQ(Control.String_processing("x + b"), 1);
    EXPECT_EQ(Control.String_processing("e+2"), 1);
    EXPECT_EQ(Control.String_processing("sifn45"), 1);
    EXPECT_EQ(Control.String_processing("123 + 1e"), 1);
    EXPECT_EQ(Control.String_processing("Hello"), 1);
    EXPECT_EQ(Control.String_processing("e12 + 1"), 1);
    EXPECT_EQ(Control.String_processing("(((sin(45 - 1e-))))"), 1);
    EXPECT_EQ(Control.String_processing("x + 1e-14 / x.2"), 1);
    EXPECT_EQ(Control.String_processing(")2 + 1("), 1);
    EXPECT_EQ(Control.String_processing("1.2.3"), 1);
    EXPECT_EQ(Control.String_processing("()12 + 3"), 1);
    EXPECT_EQ(Control.String_processing("1sin(45)"), 1);
    EXPECT_EQ(Control.String_processing("sin(45) +"), 1);
    EXPECT_EQ(Control.String_processing("1(12 - 3)"), 1);
    EXPECT_EQ(Control.String_processing(".(12 - 3)"), 1);
    EXPECT_EQ(Control.String_processing("2.(12 - 3)"), 1);
}

TEST(Test, Calculation) {
    Calc_Controller Control;
    Control.String_processing("1 + 2 - 3");
    EXPECT_TRUE(Control.Get_Digit() - (1 + 2 - 3) < EXP);
    Control.String_processing("1 - 2 * 12 - 3 ^ 2");
    EXPECT_TRUE(Control.Get_Digit() - (-32) < EXP);
    Control.String_processing("ln(12)^3 - 1 * (-12 + 5)");
    EXPECT_TRUE(Control.Get_Digit() - (pow(log(12), 3.0) - 1 * (-12 + 5)) < EXP);
    Control.String_processing("1e-4 + asin(0.5)");
    EXPECT_TRUE(Control.Get_Digit() - (1e-4 + asin(0.5)) < EXP);
    Control.String_processing("1 - log(15) / 5");
    EXPECT_TRUE(Control.Get_Digit() - (1 - log10(15) / 5) < EXP);
    Control.String_processing("sqrt(atan(12))");
    EXPECT_TRUE(Control.Get_Digit() - (sqrt(atan(12))) < EXP);
    Control.String_processing("3 mod sin45");
    EXPECT_TRUE(Control.Get_Digit() - (fmod(3, sin(45))) < EXP);
    Control.String_processing("cos(3*2)");
    EXPECT_TRUE(Control.Get_Digit() - cos(3 * 2) < EXP);
    Control.String_processing("tan(1)");
    EXPECT_TRUE(Control.Get_Digit() - tan(1) < EXP);
    Control.String_processing("acos(1)");
    EXPECT_TRUE(Control.Get_Digit() - acos(1) < EXP);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
