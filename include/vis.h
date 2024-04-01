#ifndef _CPPVIS_VIS_H_
#define _CPPVIS_VIS_H_

#include <iostream>

#include <deque>
#include <list>
#include <vector>
#include <optional>
#include <queue>
#include <string>
#include <string_view>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <tuple>
#include <memory>

namespace cppvis {

  template<typename Test, template<typename...> class Ref>
  struct is_specialization : std::false_type {};
  
  template<template<typename...> class Ref, typename... Args>
  struct is_specialization<Ref<Args...>, Ref>: std::true_type {};
  
  template <typename T, T... S, typename F>
  constexpr void for_sequence(std::integer_sequence<T, S...>, F &&f) {
    (static_cast<void>(f(std::integral_constant<T, S>{})), ...);
  }
  
  namespace impl {
    template <typename T>
    void pr_all(std::ostream & out, const T &item);

    template <typename T>
    void pr_scalar(std::ostream & out, const T &item) {
      out << item;
    }

    template <typename T>
    void pr_char(std::ostream & out, const T &item) {
      switch (item) {
      case ' ': out << "\\space"; break;
      case '\n': out << "\\newline"; break;
      case '\r': out << "\\return"; break;
      case '\t': out << "\\tab"; break;
      case '\f': out << "\\formfeed"; break;
      case '\b': out << "\\backspace"; break;
      default:
	out << "\\" << item;
      }
    }

    template <typename T>
    void pr_string(std::ostream & out, const T &item) {
      const char *str;
      size_t size;
      if constexpr (std::is_same<T, std::string>().value ||
		    std::is_same<T, std::string_view>().value) {
	str = item.data();
	size = item.size();
      } else {
	str = item;
	size = strlen(item);
      }
      out << "\"";
      for (size_t i = 0; i < size; i++) {
	switch ((unsigned char)str[i]) {
	case 0 ... 7:
	case 11 ... 12:
	case 14 ... 31:
	case 127:
	  {
	    char buf[7];
	    snprintf(buf, sizeof(buf), "\\u%.4x", (unsigned char)str[i]);
	    out << buf;
	  }
	  break;
	case '\n':
	  out << "\\n";
	  break;
	case '\b':
	  out << "\\b";
	  break;
	case '\r':
	  out << "\\r";
	  break;
	case '\t':
	  out << "\\t";
	  break;
	case '"':
	  out << "\\\"";
	  break;
	case '\\':
	  out << "\\\\";
	  break;
	default:
	  out << str[i];
	}
      }
      out << "\"";
    }

    template <typename T>
    void pr_vector(std::ostream & out, const T &item) {
      out << "[";
      for (const auto &elem : item) {
	out << " ";
	pr_all(out, elem);
      }
      out << " ]";
    }

    template <typename T, size_t N>
    void pr_array(std::ostream & out, const T(&item)[N]) {
      out << "[";
      for (size_t i = 0; i < N; i++) {
	out << " ";
	pr_all(out, item[i]);
      }
      out << " ]";
    }

    template <typename T>
    void pr_queue(std::ostream & out, const std::queue<T> &item) {
      out << "[";
      auto copy = item;
      while (copy.size()) {
	out << " ";
	pr_any(copy.front());
	copy.pop();
      }
      out << " ]";
    }

    template <typename T>
    void pr_list(std::ostream & out, const T &item) {
      out << "(";
      for (const auto &elem : item) {
	out << " ";
	pr_all(out, elem);
      }
      out << " )";
    }

    template <typename T>
    void pr_set(std::ostream & out, const T &item) {
      out << "#{";
      for (const auto &elem : item) {
	out << " ";
	pr_all(out, item);
      }
      out << " }";
    }

    template <typename T>
    void pr_map(std::ostream & out, const T &item) {
      out << "{";
      bool is_first = true;
      for (const auto &it : item) {
	if (is_first) {
	  out << " ";
	  is_first = false;
	} else {
	  out << ", ";
	}
	pr_all(out, it.first);
	out << " ";
	pr_all(out, it.second);
      }
      out << " }";
    }

    template <typename T, typename Y>
    void pr_pair(std::ostream & out, const std::pair<T, Y> &item) {
      out << "[";
      pr_all(out, item.first);
      out << " ";
      pr_all(out, item.second);
      out << "]";      
    }
  
    template <typename ...T>
    void pr_tuple(std::ostream & out, const std::tuple<T...> &item) {
      out << "[";
      constexpr auto size = std::tuple_size<std::tuple<T...>>::value;
      for_sequence(std::make_index_sequence<size>{}, [&](auto i) {
	out << " ";
	pr_all(out, std::get<i>(item));
      });
      out << " ]";
    }

    template <typename T>
    void pr_optional(std::ostream & out, const T &item) {
      if (item == nullptr) {
	pr_all(out, *item);
      } else {
	out << "nil";
      }
    }

    template <typename T>
    void pr_all(std::ostream & out, const T &item) {
      if constexpr (std::is_same<T, char>().value) {
	pr_char(out, item);
      } else if constexpr (std::is_arithmetic<T>().value ||
			   std::is_same<T, bool>().value ||
			   std::is_enum<T>().value) {
	pr_scalar(out, item);
      } else if constexpr (std::is_same<T, std::string>().value ||
			   std::is_same<T, char *>().value ||
			   std::is_same<T, const char *>().value) {
	pr_string(out, item);
      } else if constexpr (is_specialization<T, std::optional>().value ||
			   is_specialization<T, std::unique_ptr>().value ||
			   is_specialization<T, std::shared_ptr>().value ||
			   std::is_pointer<T>().value) {
	pr_optional(out, item);
      } else if constexpr (is_specialization<T, std::deque>().value ||
			   is_specialization<T, std::vector>().value
			   ) {
	pr_vector(out, item);
      } else if constexpr (std::is_array<T>().value) {
	pr_array(out, item);
      } else if constexpr (is_specialization<T, std::queue>().value) {
	pr_queue(out, item);
      } else if constexpr (is_specialization<T, std::list>().value) {
	pr_list(out, item);
      } else if constexpr (is_specialization<T, std::pair>().value) {
	pr_pair(out, item);
      } else if constexpr (is_specialization<T, std::tuple>().value) {
	pr_tuple(out, item);
      } else if constexpr (is_specialization<T, std::set>().value ||
			   is_specialization<T, std::unordered_set>().value) {
	pr_set(out, item);
      } else if constexpr (is_specialization<T, std::map>().value ||
			   is_specialization<T, std::unordered_map>().value) {
	pr_map(out, item);
      }
    }
  };

  template <typename T>
  void pr(std::ostream & out, const T &item) {
    impl::pr_all(out, item);
  }
  
  template <typename T>
  void pr(const T &item) {
    impl::pr_all(std::cout, item);
  }

  template <typename T>
  void prn(std::ostream & out, const T &item) {
    impl::pr_all(out, item);
    out << "\n";
  }

  template <typename T>
  void prn(const T &item) {
    impl::pr_all(std::cout, item);    
    std::cout << "\n";
  }
};

#endif
