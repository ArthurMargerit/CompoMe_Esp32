#include "Structs/S1_fac.hpp"
#include "Structs/S1.hpp"

#include <iostream>

S1_fac::S1_fac() { this->init(); }

S1_fac::~S1_fac() {}

S1 *S1_fac::build(const std::string &p_type, std::istream &p_stream,
                  CompoMe::Serialization_context_import &p_ctx) {

  if (p_type == "S1") {
    // void* l_addr = get_addr(is);
    // if(p_ctx.is_share_ptr(l_addr)) {
    //   std::shared_ptr<{NAME}}> b = std::make_shared<S1>();
    //   b->from_stream(p_stream, p_ctx);
    // } else {
    S1 *b = new S1();
    b->from_stream(p_stream, p_ctx);
    //    }
    return b;
  }

  // child build
  auto f = this->childs.find(p_type);
  if (f != this->childs.end()) {
    return f->second.first(p_type, p_stream, p_ctx);
  }

  std::cerr << "Error: of Serializable* build "
            << "Your type \"" << p_type
            << "\" is not include or not init as a child." << std::endl;

  return NULL;
}

std::shared_ptr<S1> S1_fac::build_sp(const std::string &p_type,
                                     std::istream &p_stream) {

  if (p_type == "S1") {
    auto b = std::make_shared<S1>();
    p_stream >> *b;
    return b;
  }

  // child build
  auto f = this->childs.find(p_type);
  if (f != this->childs.end()) {
    return f->second.second(p_type, p_stream);
  }

  std::cerr << "Error: of std::shared_ptr<S1> build "
            << "Your type \"" << p_type
            << "\" is not include or not init as a child." << std::endl;

  return std::shared_ptr<S1>();
}

void S1_fac::init() {

  CompoMe::Serializable_fac::Build_fac_f f =
      [](const std::string &str, std::istream &p_s,
         CompoMe::Serialization_context_import &l_ctx) {
        return dynamic_cast<CompoMe::Serializable_Item *>(
            S1_fac::get_inst().build(str, p_s, l_ctx));
      };
  CompoMe::Serializable_fac::Build_fac_f_sp f_sp = [](const std::string &str,
                                                      std::istream &p_s) {
    return S1_fac::get_inst().build_sp(str, p_s);
  };

  CompoMe::Serializable_fac::get_inst().subscribe("S1", f, f_sp);
}

void S1_fac::subscribe(const std::string &ss, Build_fac_f v,
                       Build_fac_f_sp v_sp) {

  this->childs[ss] = std::make_pair(v, v_sp);

  CompoMe::Serializable_fac::get_inst().subscribe(ss, v, v_sp);
}
