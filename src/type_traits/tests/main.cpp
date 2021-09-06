#include <gtest/gtest.h>

#include <array>       // std::array
#include <type_traits> // std::is_same

import type_traits;

TEST(type_traits, TestIntegralConstant) {
  using two_t = isl::integral_constant<int, 2>;
  using four_t = isl::integral_constant<int, 4>;

  ASSERT_EQ(two_t::value * 2, 4) << "2 * 2 != 4";

  enum class my_e { e1, e2 };

  using my_e_e1 = isl::integral_constant<my_e, my_e::e1>;
  using my_e_e2 = isl::integral_constant<my_e, my_e::e2>;

  ASSERT_EQ(my_e_e1(), my_e::e1);
  ASSERT_EQ(my_e_e2(), my_e::e2);

  using same = isl::is_same<my_e_e2, my_e_e2>;
  ASSERT_TRUE(same::value) << "my_e_e2 != my_e_e2";
}

TEST(type_traits, TestRemoveCV) {
  using type1 = isl::remove_cv<const int>::type;
  using type2 = isl::remove_cv<volatile int>::type;
  using type3 = isl::remove_cv<const volatile int>::type;
  using type4 = isl::remove_cv<const volatile int *>::type;
  using type5 = isl::remove_cv<int *const volatile>::type;

  constexpr bool same1 = isl::is_same_v<int, type1>;
  constexpr bool same2 = isl::is_same_v<int, type2>;
  constexpr bool same3 = isl::is_same_v<int, type3>;
  constexpr bool same4 = isl::is_same_v<const volatile int *, type4>;
  constexpr bool same5 = isl::is_same_v<int *, type5>;

  ASSERT_TRUE(same1);
  ASSERT_TRUE(same2);
  ASSERT_TRUE(same3);
  ASSERT_TRUE(same4);
  ASSERT_TRUE(same5);
}

TEST(type_traits, TestAddCV) {
  using type1 = isl::add_cv<int>::type;
  using type2 = isl::add_const<int>::type;
  using type3 = isl::add_volatile<int>::type;

  constexpr bool same1 = isl::is_same_v<const volatile int, type1>;
  constexpr bool same2 = isl::is_same_v<const int, type2>;
  constexpr bool same3 = isl::is_same_v<volatile int, type3>;

  ASSERT_TRUE(same1);
  ASSERT_TRUE(same2);
  ASSERT_TRUE(same3);
}

TEST(type_traits, TestIsVoid) {
  ASSERT_TRUE(isl::is_void_v<void>);
  ASSERT_FALSE(isl::is_void_v<int>);
}

TEST(type_traits, TestIsNullPointer) {
  ASSERT_TRUE(isl::is_null_pointer_v<decltype(nullptr)>);
  ASSERT_FALSE(isl::is_null_pointer_v<int *>);
}

namespace IsIntegral {
class A {};
enum E : int {};
} // namespace IsIntegral

TEST(type_traits, TestIsIntegral) {
  ASSERT_FALSE(isl::is_integral_v<IsIntegral::A>);
  ASSERT_FALSE(isl::is_integral_v<IsIntegral::E>);
  ASSERT_FALSE(isl::is_integral_v<float>);

  ASSERT_TRUE(isl::is_integral_v<int>);
  ASSERT_TRUE(isl::is_integral_v<const int>);
  ASSERT_TRUE(isl::is_integral_v<bool>);
}

TEST(type_traits, TestIsFloatingPoint) {
  ASSERT_FALSE(isl::is_floating_point<IsIntegral::A>::value);
  ASSERT_TRUE(isl::is_floating_point<float>::value);
  ASSERT_FALSE(isl::is_floating_point<float &>::value);
  ASSERT_TRUE(isl::is_floating_point<double>::value);
  ASSERT_FALSE(isl::is_floating_point<double &>::value);
  ASSERT_FALSE(isl::is_floating_point<int>::value);
}

TEST(type_traits, TestIsArray) {
  ASSERT_FALSE(isl::is_array<IsIntegral::A>::value);
  ASSERT_TRUE(isl::is_array<IsIntegral::A[]>::value);
  ASSERT_TRUE(isl::is_array<IsIntegral::A[3]>::value);
  ASSERT_FALSE(isl::is_array<float>::value);
  ASSERT_FALSE(isl::is_array<int>::value);
  ASSERT_TRUE(isl::is_array<int[]>::value);
  ASSERT_TRUE(isl::is_array<int[3]>::value);

  using array = std::array<int, 3>;
  ASSERT_FALSE(isl::is_array<array>::value);
}

namespace IsFunction {
struct A {
  int fun() const &;
};

template <typename> struct PM_traits {};

template <class T, class U> struct PM_traits<U T::*> { using member_type = U; };

int f();
} // namespace IsFunction
TEST(type_traits, TestIsFunction) {
  ASSERT_FALSE(isl::is_function<IsFunction::A>::value);
  ASSERT_TRUE(isl::is_function<int(int)>::value);
  ASSERT_TRUE(isl::is_function<decltype(IsFunction::f)>::value);
  ASSERT_FALSE(isl::is_function<int>::value);

  using T = IsFunction::PM_traits<
      decltype(&IsFunction::A::fun)>::member_type; // T is int() const&
  ASSERT_TRUE(isl::is_function<T>::value);
}

namespace IsPointer {
class A {};
} // namespace IsPointer

TEST(type_traits, TestIsPointer) {
  ASSERT_TRUE(not isl::is_pointer<IsIntegral::A>::value);
  ASSERT_TRUE(not isl::is_pointer_v<IsIntegral::A>); // same thing as above, but
                                                     // in C++17!
  ASSERT_TRUE(not isl::is_pointer<IsIntegral::A>()); // same as above, using
                                                     // inherited operator bool
  ASSERT_TRUE(not isl::is_pointer<IsIntegral::A>{}); // ditto
  ASSERT_TRUE(not isl::is_pointer<IsIntegral::A>()()); // same as above, using
                                                       // inherited operator()
  ASSERT_TRUE(not isl::is_pointer<IsIntegral::A>{}()); // ditto
  ASSERT_TRUE(isl::is_pointer<IsIntegral::A *>::value);
  ASSERT_TRUE(not isl::is_pointer<IsIntegral::A &>::value);
  ASSERT_TRUE(not isl::is_pointer<int>::value);
  ASSERT_TRUE(isl::is_pointer<int *>::value);
  ASSERT_TRUE(isl::is_pointer<int **>::value);
  ASSERT_TRUE(not isl::is_pointer<int[10]>::value);
  ASSERT_TRUE(not isl::is_pointer<std::nullptr_t>::value);
}

TEST(type_traits, TestIsLvalueReference) {
  ASSERT_FALSE(isl::is_lvalue_reference<IsIntegral::A>::value);
  ASSERT_TRUE(isl::is_lvalue_reference<IsIntegral::A &>::value);
  ASSERT_FALSE(isl::is_lvalue_reference<IsIntegral::A &&>::value);
  ASSERT_FALSE(isl::is_lvalue_reference<int>::value);
  ASSERT_TRUE(isl::is_lvalue_reference<int &>::value);
  ASSERT_FALSE(isl::is_lvalue_reference<int &&>::value);
}

TEST(type_traits, TestIsRvalueReference) {
  ASSERT_FALSE(isl::is_rvalue_reference<IsIntegral::A>::value);
  ASSERT_FALSE(isl::is_rvalue_reference<IsIntegral::A &>::value);
  ASSERT_TRUE(isl::is_rvalue_reference<IsIntegral::A &&>::value);
  ASSERT_FALSE(isl::is_rvalue_reference<int>::value);
  ASSERT_FALSE(isl::is_rvalue_reference<int &>::value);
  ASSERT_TRUE(isl::is_rvalue_reference<int &&>::value);
}

namespace IsMemberObjectPointer {
class cls {};
} // namespace IsMemberObjectPointer

TEST(type_traits, TestIsMemberObjectPointer) {
  ASSERT_TRUE(
      isl::is_member_object_pointer_v<int(IsMemberObjectPointer::cls::*)>);
  ASSERT_FALSE(
      isl::is_member_object_pointer_v<int (IsMemberObjectPointer::cls::*)()>);
}

namespace IsMemberFunctionPointer {
class A {
public:
  void member() {}
};
} // namespace IsMemberFunctionPointer

TEST(type_traits, TestIsMemberFunctionPointer) {
  ASSERT_TRUE(isl::is_member_function_pointer_v<
              decltype(&IsMemberFunctionPointer::A::member)>);
  ASSERT_FALSE(
      isl::is_member_function_pointer_v<int(IsMemberFunctionPointer::A::*)>);
}

TEST(type_traits, TestIsConst) {
  ASSERT_FALSE(isl::is_const_v<int>);
  ASSERT_TRUE(isl::is_const_v<const int>);
  ASSERT_FALSE(isl::is_const_v<const int *>);
  ASSERT_TRUE(isl::is_const_v<int *const>);
  ASSERT_FALSE(isl::is_const_v<const int &>);
  ASSERT_TRUE(isl::is_const_v<std::remove_reference_t<const int &>>);
}

TEST(type_traits, TestIsVolatile) {
  ASSERT_FALSE(isl::is_volatile_v<int>);
  ASSERT_TRUE(isl::is_volatile_v<volatile int>);
}

namespace IsAbstract {
struct A {
  int m;
};

struct B {
  virtual void foo();
};

struct C {
  virtual void foo() = 0;
};

struct D : C {};
} // namespace IsAbstract

TEST(type_traits, TestIsAbstract) {
  ASSERT_FALSE(isl::is_abstract<IsAbstract::A>::value);
  ASSERT_FALSE(isl::is_abstract<IsAbstract::B>::value);
  ASSERT_TRUE(isl::is_abstract<IsAbstract::C>::value);
  ASSERT_TRUE(isl::is_abstract<IsAbstract::D>::value);
}

TEST(type_traits, TestIsSigned) {
  ASSERT_FALSE(isl::is_signed<IsAbstract::A>::value);
  ASSERT_TRUE(isl::is_signed<float>::value);
  ASSERT_TRUE(isl::is_signed<signed int>::value);
  ASSERT_FALSE(isl::is_signed<unsigned int>::value);
  ASSERT_FALSE(isl::is_signed<IsAbstract::B>::value);
  ASSERT_FALSE(isl::is_signed<IsAbstract::C>::value);

  // shorter:
  ASSERT_FALSE(isl::is_signed_v<bool>);
  ASSERT_TRUE(isl::is_signed<signed int>());
  ASSERT_FALSE(isl::is_signed<unsigned int>{});
}

namespace IsUnsigned {
class A {};
enum B : unsigned {};
enum class C : unsigned {};
} // namespace IsUnsigned

TEST(type_traits, TestIsUnsigned) {
  ASSERT_FALSE(isl::is_unsigned<IsUnsigned::A>::value);
  ASSERT_FALSE(isl::is_unsigned<float>::value);
  ASSERT_FALSE(isl::is_unsigned<signed int>::value);
  ASSERT_TRUE(isl::is_unsigned<unsigned int>::value);
  ASSERT_FALSE(isl::is_unsigned<IsUnsigned::B>::value);
  ASSERT_FALSE(isl::is_unsigned<IsUnsigned::C>::value);
}

TEST(type_traits, TestIsBoundedArray) {
  ASSERT_FALSE(isl::is_bounded_array_v<IsUnsigned::A>);
  ASSERT_FALSE(isl::is_bounded_array_v<IsUnsigned::A[]>);
  ASSERT_TRUE(isl::is_bounded_array_v<IsUnsigned::A[3]>);
  ASSERT_FALSE(isl::is_bounded_array_v<float>);
  ASSERT_FALSE(isl::is_bounded_array_v<int>);
  ASSERT_FALSE(isl::is_bounded_array_v<int[]>);
  ASSERT_TRUE(isl::is_bounded_array_v<int[3]>);
}

TEST(type_traits, TestIsUnboundedArray) {
  ASSERT_FALSE(isl::is_unbounded_array_v<IsUnsigned::A>);
  ASSERT_TRUE(isl::is_unbounded_array_v<IsUnsigned::A[]>);
  ASSERT_FALSE(isl::is_unbounded_array_v<IsUnsigned::A[3]>);
  ASSERT_FALSE(isl::is_unbounded_array_v<float>);
  ASSERT_FALSE(isl::is_unbounded_array_v<int>);
  ASSERT_TRUE(isl::is_unbounded_array_v<int[]>);
  ASSERT_FALSE(isl::is_unbounded_array_v<int[3]>);
}

namespace IsConstructible {
class C {};
class Foo {
  int v1;
  double v2;

public:
  Foo(int n) : v1(n), v2() {}
  Foo(int n, double f) noexcept : v1(n), v2(f) {}
};
} // namespace IsConstructible

TEST(type_traits, TestIsConstructible) {
  constexpr bool value_1 =
      isl::is_constructible_v<IsConstructible::Foo,
                              const IsConstructible::Foo &>;
  constexpr bool value_2 = isl::is_constructible_v<IsConstructible::Foo, int>;

  ASSERT_TRUE(value_1);
  ASSERT_TRUE(value_2);

  constexpr bool value_3 =
      isl::is_constructible_v<IsConstructible::Foo, IsConstructible::C>;
  constexpr bool value_4 =
      isl::is_nothrow_constructible_v<IsConstructible::Foo, int>;
  constexpr bool value_5 =
      isl::is_nothrow_constructible_v<IsConstructible::Foo, int, double>;

  ASSERT_FALSE(value_3);
  ASSERT_FALSE(value_4);
  ASSERT_TRUE(value_5);
}

namespace IsDefaultConstructible {
struct Ex1 {
  std::string str; // member has a non-trivial default ctor
};
struct Ex2 {
  int n;
  Ex2() = default; // trivial and non-throwing
};
struct Ex3 {
  Ex3() = delete;
};
} // namespace IsDefaultConstructible

TEST(type_traits, TestIsDefaultConstructible) {
  constexpr bool value_1 =
      isl::is_default_constructible<IsDefaultConstructible::Ex1>::value;
  ASSERT_TRUE(value_1);

  constexpr bool value_2 =
      isl::is_nothrow_default_constructible<IsDefaultConstructible::Ex2>::value;
  ASSERT_TRUE(value_2);

  constexpr bool value_3 =
      isl::is_default_constructible<IsDefaultConstructible::Ex3>::value;
  ASSERT_FALSE(value_3);
}

namespace IsCopyConstructible {
struct Ex1 {
  std::string str; // member has a non-trivial default ctor
};
struct Ex2 {
  int n;
  Ex2(const Ex2 &) = default; // trivial and non-throwing
};
struct Ex3 {
  Ex3(const Ex3 &) = delete;
};
} // namespace IsCopyConstructible

TEST(type_traits, TestIsCopyConstructible) {
  constexpr bool value_1 =
      isl::is_copy_constructible<IsCopyConstructible::Ex1>::value;
  ASSERT_TRUE(value_1);

  constexpr bool value_2 =
      isl::is_nothrow_copy_constructible<IsCopyConstructible::Ex2>::value;
  ASSERT_TRUE(value_2);

  constexpr bool value_3 =
      isl::is_copy_constructible<IsCopyConstructible::Ex3>::value;
  ASSERT_FALSE(value_3);
}

namespace IsMoveConstructible {
struct Ex1 {
  std::string str; // member has a non-trivial default ctor
};
struct Ex2 {
  int n;
  Ex2(Ex2 &&) = default; // trivial and non-throwing
};
struct Ex3 {
  Ex3(const Ex3 &) = default;
};
struct NoMove {
  NoMove(NoMove &&) = delete;
};
} // namespace IsMoveConstructible

TEST(type_traits, TestIsMoveConstructible) {
  constexpr bool value_1 =
      isl::is_move_constructible<IsMoveConstructible::Ex1>::value;
  ASSERT_TRUE(value_1);

  constexpr bool value_2 =
      isl::is_nothrow_move_constructible<IsMoveConstructible::Ex2>::value;
  ASSERT_TRUE(value_2);

  constexpr bool value_3 =
      isl::is_move_constructible<IsMoveConstructible::Ex3>::value;
  ASSERT_TRUE(value_3);

  constexpr bool value_4 =
      isl::is_move_constructible<IsMoveConstructible::NoMove>::value;
  constexpr bool value_5 =
      isl::is_nothrow_move_constructible<IsMoveConstructible::NoMove>::value;

  ASSERT_FALSE(value_4);
  ASSERT_FALSE(value_5);
}

namespace IsAssignable {
struct Foo {
  int n;
};
} // namespace IsAssignable

TEST(type_traits, TestIsAssignable) {
  constexpr bool int_int = isl::is_assignable<int, int>::value;
  ASSERT_FALSE(int_int);

  constexpr bool int_ref_int = isl::is_assignable<int &, int>::value;
  ASSERT_TRUE(int_ref_int);

  constexpr bool int_double = isl::is_assignable<int, double>::value;
  ASSERT_FALSE(int_double);

  constexpr bool int_ref_double =
      isl::is_nothrow_assignable<int &, double>::value;
  ASSERT_TRUE(int_ref_double);

  constexpr bool string_double = isl::is_assignable<std::string, double>::value;
  ASSERT_TRUE(string_double);

  constexpr bool foo_ref_foo =
      isl::is_assignable<IsAssignable::Foo &, const IsAssignable::Foo &>::value;
  ASSERT_TRUE(foo_ref_foo);
}

TEST(type_traits, TestIsCopyAssignable) {
  ASSERT_TRUE(isl::is_copy_assignable_v<IsAssignable::Foo>);
  ASSERT_FALSE(isl::is_copy_assignable_v<int[2]>);

  ASSERT_TRUE(isl::is_copy_assignable_v<int>);
  ASSERT_TRUE(isl::is_nothrow_copy_assignable_v<int>);
}

namespace IsMoveAssignable {
struct NoMove {
  // prevents implicit declaration of default move assignment operator
  // however, the class is still move-assignable because its
  // copy assignment operator can bind to an rvalue argument
  NoMove &operator=(const NoMove &) { return *this; }
};
} // namespace IsMoveAssignable

TEST(type_traits, TestIsMoveAssignable) {
  ASSERT_TRUE(isl::is_nothrow_move_assignable<std::string>::value);
  ASSERT_FALSE(isl::is_move_assignable<int[2]>::value);
  ASSERT_TRUE(isl::is_move_assignable<IsAssignable::Foo>::value);

  ASSERT_TRUE(isl::is_move_assignable<IsMoveAssignable::NoMove>::value);
  ASSERT_FALSE(
      isl::is_nothrow_move_assignable<IsMoveAssignable::NoMove>::value);
}

namespace IsEnum {
class A {};
enum E {};
enum class Ec : int {};
class D {
  operator int() { return 1; }
};
} // namespace IsEnum

TEST(type_traits, TestIsEnum) {
  using namespace IsEnum;

  constexpr bool t_class = isl::is_enum_v<A>;
  constexpr bool t_enum = isl::is_enum_v<E>;
  constexpr bool t_int = isl::is_enum_v<int>;
  constexpr bool t_enum_class = isl::is_enum_v<Ec>;
  constexpr bool t_class_int = isl::is_enum_v<D>;

  ASSERT_FALSE(t_class);
  ASSERT_TRUE(t_enum);
  ASSERT_TRUE(t_int);
  ASSERT_TRUE(t_enum_class);
  ASSERT_FALSE(t_class_int);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
