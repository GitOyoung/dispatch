//
// Created by oyoung on 19-3-1.
//

#ifndef DISPATCH_INTEGER_HPP
#define DISPATCH_INTEGER_HPP

#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <initializer_list>
#include <oyoung/format.hpp>

namespace oyoung {
    namespace number {

        template<typename T>
        struct is_supported_package {
            constexpr static bool value = false;
        };

        template<>
        struct is_supported_package<char> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<unsigned char> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<short> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<unsigned  short> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<int> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<unsigned  int> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<long > {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<unsigned long> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<long long> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<unsigned long long> {
            constexpr static bool value = true;
        };

        template<>
        struct is_supported_package<float> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<double> {
            constexpr static bool value = true;
        };
        template<>
        struct is_supported_package<long double> {
            constexpr static bool value = true;
        };

        template<typename T>
        struct type_package {

            static_assert(is_supported_package<T>::value, "Unsupported type");

            type_package() : _raw_value() {}

            type_package(const T &value) : _raw_value(value) {}

            type_package(const char *string) : _raw_value(std::strtold(string, nullptr)) {}

            template<typename U>
            type_package(const type_package<U> &other): _raw_value(static_cast<T>(other._raw_value)) {}

            type_package(const type_package &other) : _raw_value(other._raw_value) {}

            type_package(type_package &&other) : _raw_value(other._raw_value) {}


            template<typename U>
            type_package &operator=(const type_package<U> &other) {
                _raw_value = static_cast<T>(other._raw_value);
                return *this;
            }

            template<typename U>
            type_package &operator=(const U &value) {
                _raw_value = static_cast<T>(value);
                return *this;
            }

            T value() const {
                return _raw_value;
            }

            T &ref() {
                return _raw_value;
            }

            const T &ref() const {
                return _raw_value;
            }

            operator T() const {
                return _raw_value;
            }

            template<typename U>
            explicit operator U() const {
                return static_cast<U>(_raw_value);
            }

            template<typename U>
            type_package<decltype(T() + U())> operator+(const type_package<U> &other) {
                return type_package<decltype(T() + U())>(_raw_value + other.ref());
            }

            template<typename U>
            type_package<decltype(T() - U())> operator-(const type_package<U> &other) {
                return type_package<decltype(T() - U())>(_raw_value - other.ref());
            }

            template<typename U>
            type_package<decltype(T() * U())> operator*(const type_package<U> &other) {
                return type_package<decltype(T() * U())>(_raw_value * other.ref());
            }

            template<typename U>
            type_package<decltype(T() / U())> operator/(const type_package<U> &other) {
                return type_package<decltype(T() / U())>(_raw_value / other.ref());
            }


            template<typename U>
            bool operator==(const type_package<U> &other) {
                return _raw_value == other.ref();
            }

            template<typename U>
            bool operator!=(const type_package<U> &other) {
                return _raw_value == other.ref();
            }

            template<typename U>
            bool operator<(const type_package<U> &other) {
                return _raw_value < other.ref();
            }

            template<typename U>
            bool operator<=(const type_package<U> &other) {
                return _raw_value <= other.ref();
            }

            template<typename U>
            bool operator>(const type_package<U> &other) {
                return _raw_value > other.ref();
            }

            template<typename U>
            bool operator>=(const type_package<U> &other) {
                return _raw_value >= other.ref();
            }

            type_package abs() const {
                return type_package(std::abs(_raw_value));
            }

            type_package square() const {
                return type_package(_raw_value * _raw_value);
            }

            type_package cube() const {
                return type_package(_raw_value * _raw_value * _raw_value);
            }

            type_package sqrt() const {
                return type_package(std::sqrt(_raw_value));
            }

//
//            const T *operator&() const {
//                return &_raw_value;
//            }

            type_package &operator++() {
                ++_raw_value;
                return *this;
            }

            type_package operator++(int) {
                return type_package(_raw_value++);
            }

            type_package &operator--() {
                --_raw_value;
                return *this;
            }

            type_package operator--(int) {
                return type_package(_raw_value--);
            }

            type_package &operator+=(const type_package &other) {
                _raw_value += other.ref();
                return *this;
            }

            type_package &operator-=(const type_package &other) {
                _raw_value -= other.ref();
                return *this;
            }

            type_package &operator*=(const type_package &other) {
                _raw_value *= other.ref();
                return *this;
            }

            type_package &operator/=(const type_package &other) {
                _raw_value /= other.ref();
                return *this;
            }

            std::chrono::duration<T> hours() const {
                return std::chrono::duration<T, std::ratio<3600>>(_raw_value);
            }

            std::chrono::duration<T> minutes() const {
                return std::chrono::duration<T, std::ratio<60>>(_raw_value);
            }

            std::chrono::duration<T> seconds() const {
                return std::chrono::duration<T>(_raw_value);
            }

            std::chrono::duration<T> milliseconds() const {
                return std::chrono::duration<T, std::ratio<1, 1000>>(_raw_value);
            }

            std::chrono::duration<T> miscroseconds() const {
                return std::chrono::duration<T, std::ratio<1, 1000000L>>(_raw_value);
            }

            std::chrono::duration<T> nanoseconds() const {
                return std::chrono::duration<T, std::ratio<1, 10000000000L>>(_raw_value);
            }

            type_package<std::size_t> byte_size() const {
                return sizeof(_raw_value);
            }

            void swap(type_package& other) noexcept {
                std::swap(_raw_value, other._raw_value);
            }

//    T*operator&() {
//        return &_raw_value;
//    }
//    operator bool() const {
//        return _raw_value;
//    }
//


        protected:
            T _raw_value;
        };

        using Int8 = type_package<std::int8_t>;
        using Int16 = type_package<std::int16_t>;
        using Int32 = type_package<std::int32_t>;
        using Int64 = type_package<std::int64_t>;

        using UInt8 = type_package<std::uint8_t>;
        using UInt16 = type_package<std::uint16_t>;
        using UInt32 = type_package<std::uint32_t>;
        using UInt64 = type_package<std::uint64_t>;



        using Char = type_package<char>;
        using UChar = type_package<unsigned char>;
        using Byte = UChar;

        using Short = type_package<short>;
        using UShort = type_package<unsigned short>;

        using Int = type_package<int>;
        using UInt = type_package<unsigned int>;

        using Long = type_package<long>;
        using ULong = type_package<unsigned long>;

        using LLong = type_package<long long>;
        using ULLong = type_package<unsigned long long>;

        struct Float : type_package<float> {
            Float() : type_package() {}

            Float(float v) : type_package(v) {}
            Float(const type_package<float>& v) : type_package(v) {}

            Float &operator++() = delete;

            Float operator++(int) = delete;

            Float &operator=(float v) {
                _raw_value = v;
                return *this;
            }
        };

        struct Double : type_package<double> {
            Double() : type_package() {}

            Double(double v) : type_package(v) {}

            Double(const type_package<double>& n): type_package(n) {}

            Double &operator++() = delete;

            Double operator++(int) = delete;

            Double &operator=(double v) {
                _raw_value = v;
                return *this;
            }
        };

        template<typename T, typename U>
        type_package<decltype(T() + U())> operator+(const T &value, const type_package<T> &package) {
            return type_package<decltype(T() + U())>(value + package.ref());
        };

        template<typename T, typename U>
        type_package<decltype(T() - U())> operator-(const T &value, const type_package<T> &package) {
            return type_package<decltype(T() - U())>(value - package.ref());
        };

        template<typename T, typename U>
        type_package<decltype(T() * U())> operator*(const T &value, const type_package<T> &package) {
            return type_package<decltype(T() * U())>(value * package.ref());
        };

        template<typename T, typename U>
        type_package<decltype(T() / U())> operator/(const T &value, const type_package<T> &package) {
            return type_package<decltype(T() / U())>(value / package.ref());
        };

        template<typename T, typename U>
        bool operator==(const T &lhs, const type_package<U> &rhs) {
            return lhs == rhs.ref();
        }

        template<typename T, typename U>
        bool operator!=(const T &lhs, const type_package<U> &rhs) {
            return lhs != rhs.ref();
        }

        template<typename T, typename U>
        bool operator<(const T &lhs, const type_package<U> &rhs) {
            return lhs < rhs.ref();
        }

        template<typename T, typename U>
        bool operator<=(const T &lhs, const type_package<U> &rhs) {
            return lhs <= rhs.ref();
        }

        template<typename T, typename U>
        bool operator>=(const T &lhs, const type_package<U> &rhs) {
            return lhs >= rhs.ref();
        }

        template<typename T, typename U>
        bool operator>(const T &lhs, const type_package<U> &rhs) {
            return lhs > rhs.ref();
        }

        template<typename OStream, typename T>
        OStream &operator<<(OStream &os, const type_package<T> &package) {
            os << static_cast<T>(package);
	        return os;
        };


        struct complex {
            complex() : _real(0), _imag(0) {}

            complex(double value) : _real(value), _imag(0) {}

            complex(const Double &real, const Double &imag) : _real(real), _imag(imag) {}

            complex(const std::initializer_list<double>& list)
                    : _real(list.size() ? *list.begin(): 0.0)
                    , _imag(list.size() > 1 ? *(list.begin() + 1): 0.0) {

            }

            complex(const complex& other): _real(other._real), _imag(other._imag) {}
            complex(complex&& other): _real(std::move(other._real)), _imag(std::move(other._imag)) {}

            complex&operator=(const complex& other) {
                if(this != &other) {
                    complex(other).swap(*this);
                }
                return *this;
            }

            complex&operator=(complex&& other) {
                complex(std::move(other)).swap(*this);
                return *this;
            }

            complex&operator=(const std::initializer_list<double>& list) {

                complex(list).swap(*this);
                return *this;
            }

            Double radius() const {
                return (_real.square() + _imag.square()).sqrt();
            }

            Double theta() const {
                return std::atan2(_imag.ref(), _real.ref());
            }

            void swap(complex& other) noexcept {
                _real.swap(other._real);
                _imag.swap(other._imag);
            }

            complex conjugate() const {
                return complex(_real, -_imag);
            }

            Double &real() { return _real; }

            const Double &real() const { return _real; }

            Double &imag() { return _imag; }

            const Double &imag() const { return _imag; }

        protected:
            Double _real, _imag;
        };

        template <typename Char, typename CharTraits>
        ::std::basic_ostream<Char, CharTraits> &operator<<(::std::basic_ostream<Char, CharTraits> &os, const complex &comp) {
            const auto &real = comp.real();
            const auto &image = comp.imag();
            os << oyoung::format("%1 %2 %3i")
                    .arg(real.ref())
                    .arg(image < 0 ? "-" : "+")
                    .arg(image.abs().ref()).to_string();
            return os;
        }




        complex operator+(const complex &left, const complex &right)  {
            return complex(left.real() + right.real(), left.imag() + right.imag());
        }

        complex operator-(const complex &left, const complex &right)  {
            return complex(left.real() - right.real(), left.imag() - right.imag());
        }

        complex operator*(const complex &left, const complex &right)  {
            auto real = left.real() * right.real() - left.imag() * right.imag();
            auto image = left.imag() * right.real() + left.real() * right.imag();
            return complex(real, image);
        }

        complex operator*(const complex &comp, const Double &number)  {
            return complex(comp.real() * number, comp.imag() * number);
        }

        complex operator/(const complex &left, const complex &right)  {
            auto de = right.real().square() + right.imag().square();
            auto real = left.real() * right.real() + left.imag() * right.imag();
            auto image = left.imag() * right.real() - left.real() * right.imag();
            return complex(real / de, image / de);
        }

        complex operator/(const complex &comp, const Double& number) {
            return complex(comp.real() / number, comp.imag() / number);
        }

        bool operator==(const complex& left, const complex& right) {
            return left.real() == right.real() and left.imag() == right.imag();
        }

        bool operator!=(const complex& left, const complex& right) {
            return left.real() != right.real() or left.imag() != right.imag();
        }

        namespace literals {

            inline complex operator"" _i(long double imag) {
                return complex(0, imag);
            }

            inline complex operator"" _i(unsigned long long imag) {
                return complex(0, imag);
            }

            namespace chrono_literals {

                inline std::chrono::hours operator "" _h(unsigned long long hours) {
                    return std::chrono::hours(static_cast<long>(hours));
                }

                inline std::chrono::minutes operator "" _min(unsigned long long minutes) {
                    return std::chrono::minutes(static_cast<long>(minutes));
                }

                inline std::chrono::seconds operator "" _s(unsigned long long seconds) {
                    return std::chrono::seconds(seconds);
                }

                inline std::chrono::milliseconds operator "" _ms(unsigned long long milliseconds) {
                    return std::chrono::milliseconds(static_cast<long>(milliseconds));
                }

                inline std::chrono::microseconds operator "" _us(unsigned long long microseconds) {
                    return std::chrono::microseconds(static_cast<long>(microseconds));
                }

                inline std::chrono::nanoseconds operator "" _ns(unsigned long long nanoseconds) {
                    return std::chrono::nanoseconds(static_cast<long>(nanoseconds));
                }
            }

            using namespace chrono_literals;
        }
        

        template<typename T, typename = typename std::enable_if<std::is_pod<T>::value>::type>
        complex operator+(const T& left, const complex& right) {
            return complex(left + right.real(), right.imag());
        }

        template<typename T, typename = typename std::enable_if<std::is_pod<T>::value>::type>
        complex operator-(const T& left, const complex& right) {
            return complex(left - right.real(), -right.imag());
        }

        template<typename T, typename = typename std::enable_if<std::is_pod<T>::value>::type>
        complex operator*(const T& left, const complex& right) {
            return complex(left * right.real(), left * right.imag());
        }
        template<typename T, typename = typename std::enable_if<std::is_pod<T>::value>::type>
        complex operator/(const T& left, const complex& right) {
            return left * right.conjugate() / (right * right.conjugate());
        }
    }
}



#endif //DISPATCH_INTEGER_HPP
