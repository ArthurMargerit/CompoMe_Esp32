#pragma once

#include "Serialization_context.hpp"
#include <functional>
#include <istream>
#include <map>
#include <memory>

class S1;

class S1_fac {
public:
  using Build_fac_f =
      std::function<S1 *(const std::string &, std::istream &,
                         CompoMe::Serialization_context_import &)>;
  using Build_fac_f_sp =
      std::function<std::shared_ptr<S1>(const std::string &, std::istream &)>;

  static S1_fac &get_inst() {
    static S1_fac inst;
    return inst;
  }

  S1 *build(const std::string &p_type, std::istream &p,
            CompoMe::Serialization_context_import &p_ctx);
  std::shared_ptr<S1> build_sp(const std::string &p_type, std::istream &p);

  void init();

  void subscribe(const std::string &ss, Build_fac_f v, Build_fac_f_sp v_sp);

private:
  S1_fac();
  virtual ~S1_fac();
  std::map<std::string, std::pair<Build_fac_f, Build_fac_f_sp>> childs;
};
