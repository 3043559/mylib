//
// Created by HanHaocheng on 2024/4/12.
//


#include <boost/test/unit_test.hpp>

#include "../mylib/untils/until.h"

BOOST_AUTO_TEST_SUITE(untils_suite_test)

BOOST_AUTO_TEST_CASE(test_untils_base) {
  //mylib::String b = mylib::GetClassName(__PRETTY_FUNCTION__);
  //std::string t1 = __func__;
  //std::string t2 = __PRETTY_FUNCTION__;
  //std::string t3 = __CLASS_NAME__;

  //std::cout << "t1:" << t1 << std::endl;
  //std::cout << "t2:" << t2 << std::endl;
  //std::cout << "t3:" << t3 << std::endl;
  //static const char *d = "123";
  //constexpr const static char *a = date;
  //MYLIB_SPACE_NAME::String ttt = d;

  constexpr static char d[] = {mylib::ToUpper("a"[0])};

  std::cout << d << '\n'
            << std::flush;
  std::cout << "asdf" << '\n'
            << std::flush;
  std::cout << d << '\n'
            << std::flush;
}

BOOST_AUTO_TEST_SUITE_END()