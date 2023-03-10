#include "Components/Embded/IO/esp32/Control_input.hpp"
#include "Serialization_context.hpp"
#include <iostream>

namespace Embded {

namespace IO {

namespace esp32 {

std::ostream &operator<<(std::ostream &os, const Control_input &c) {
  CompoMe::Serialization_context_export p_ctx;
  c.to_stream(os, p_ctx);
  p_ctx.export_wanted(os);
  return os;
}

std::istream &operator>>(std::istream &is, Control_input &c) {
  CompoMe::Serialization_context_import p_ctx;
  c.from_stream(is, p_ctx);
  p_ctx.import_wanted(is);
  return is;
}

constexpr unsigned int str2int(const char *str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

std::ostream &Control_input::to_stream_data(
    std::ostream &os, CompoMe::Serialization_context_export &p_ctx) const {
  os << ",data:{";
  os << "pool_down:";

  os << this->pool_down;
  os << ",";
  os << "pool_up:";

  os << this->pool_up;
  os << ",";
  os << "pin_id:";

  os << this->pin_id;
  os << "}";

  return os;
}

std::ostream &Control_input::to_stream_sc(
    std::ostream &os, CompoMe::Serialization_context_export &p_ctx) const {
  os << ",components:{";

  os << "}";
  return os;
}

std::ostream &Control_input::to_stream_provide(
    std::ostream &os, CompoMe::Serialization_context_export &p_ctx) const {
  os << ",provide:{";

  os << "control:";
  this->control.to_stream(os, p_ctx);

  os << "}";
  return os;
}

/////////////////////////////////////////////////////////////////////////////
//                            LOAD/SAVE                                    //
/////////////////////////////////////////////////////////////////////////////
std::ostream &
Control_input::to_stream(std::ostream &os,
                         CompoMe::Serialization_context_export &p_ctx) const {
  os << "{";
  os << "addr:" << (void *)this;
  p_ctx.declare(this);

  os << ",type:"
     << "Embded::IO::esp32::Control_input";

  this->to_stream_data(os, p_ctx);
  this->to_stream_provide(os, p_ctx);
  os << '}';
  return os;
}

std::istream &Control_input::from_stream_provide(
    std::istream &is, CompoMe::Serialization_context_import &p_ctx) {
  char l_c = is.get();
  if (l_c != '{') {
    std::cerr << "Wrong start: '" << l_c << "' != '{'";
    throw "Wrong start: '"
          "' != '{'";
  }

  do {
    std::string args;
    std::getline(is, args, ':');

    switch (str2int(args.c_str())) {
    case str2int("control"):
      this->get_control().from_stream(is, p_ctx);
      break;

    default:
      std::cerr << "wrong attribute: \"" << args
                << "\" not in data Control_input";
      throw "wrong attribute: \"" + args + "\" not in provide Control_input";
      break;
    }

    l_c = is.get();
  } while (l_c == ',');

  return is;
}

std::istream &
Control_input::from_stream_data(std::istream &is,
                                CompoMe::Serialization_context_import &p_ctx) {
  char l_c = is.get();
  if (l_c != '{') {
    std::cerr << "Wrong start: '" << l_c << "' != '{'";
    throw "Wrong start: '"
          "' != '{'";
  }

  do {
    std::string args;
    std::getline(is, args, ':');

    switch (str2int(args.c_str())) {
    case str2int("pool_down"):
      is >> this->pool_down;
      break;

    case str2int("pool_up"):
      is >> this->pool_up;
      break;

    case str2int("pin_id"):
      is >> this->pin_id;
      break;

    default:
      std::cerr << "wrong attribute: \"" << args
                << "\" not in data Control_input";
      throw "wrong attribute: \"" + args + "\" not in data Control_input";
      break;
    }

    l_c = is.get();
  } while (l_c == ',');

  return is;
}

std::istream &
Control_input::from_stream_sc(std::istream &is,
                              CompoMe::Serialization_context_import &p_ctx) {
  char l_c = is.get();
  if (l_c != '{') {
    std::cerr << "Wrong start: '" << l_c << "' != '{'";
    throw "Wrong start: '"
          "' != '{'";
  }

  do {
    std::string args;
    std::getline(is, args, ':');

    switch (str2int(args.c_str())) {

    default:
      std::cerr << "wrong attribute: \"" << args
                << "\" not in data Control_input";
      throw "wrong attribute: \"" + args +
          "\" not in sub components Control_input";
      break;
    }

    l_c = is.get();
  } while (l_c == ',');

  return is;
}

std::istream &
Control_input::from_stream(std::istream &is,
                           CompoMe::Serialization_context_import &p_ctx) {
  Control_input l_reset;
  *this = l_reset;

  char l_c = is.get();
  if (l_c != '{') {
    std::cerr << "Wrong start: '" << l_c << "' != '{'";
    throw "Wrong start: '"
          "' != '{'";
  }

  do {
    std::string args;
    std::getline(is, args, ':');

    switch (str2int(args.c_str())) {
      // TYPE ///////////////////////////////////////////////////////////////
    case str2int("type"): {

      auto t = CompoMe::get_word(is, {',', '}'});
      if (t.first != "Control_input") {
        throw "Wrong Type: "; // + "Control_input" + " != " + t.first ;
      }
      break;
    }

      // ADDR ///////////////////////////////////////////////////////////////
    case str2int("addr"): {
      void *addr;
      is >> addr;
      p_ctx.inscribe(addr, this);
      break;
    }

      // PARRENT ////////////////////////////////////////////////////////////

      // DATA ///////////////////////////////////////////////////////////////

    case str2int("data"): {
      this->from_stream_data(is, p_ctx);
      break;
    }

      // COMPONENT //////////////////////////////////////////////////////////

      // PROVIDE ////////////////////////////////////////////////////////////

    case str2int("provide"): {
      this->from_stream_provide(is, p_ctx);
      break;
    }

    default: {
      std::cerr << "wrong attribute: \"" << args << "\" not in Control_input";
      throw "wrong attribute: \"" + args + "\" not in Control_input";
      break;
    }
    }

    l_c = is.get();
  } while (l_c == ',');

  if (l_c != '}') {
    std::cerr << "Wrong end: '" << l_c << "' != '}'" << std::endl;
    throw "Wrong end";
  }

  //   default:
  //     std::cerr << "wrong attribute: \""<< args <<"\" not in Control_input";
  //     throw "wrong attribute: \""+ args +"\" not in Control_input";
  //     break;
  //   }

  //

  //   //
  //   // case str2int("pool_down"):
  //   //
  //   //   is >> this->pool_down;
  //   //
  //   //   break;
  //   //
  //   // case str2int("pool_up"):
  //   //
  //   //   is >> this->pool_up;
  //   //
  //   //   break;
  //   //
  //   // case str2int("pin_id"):
  //   //
  //   //   is >> this->pin_id;
  //   //
  //   //   break;
  //   //

  //   l_c = is.get();
  // }while(l_c == ',');

  // if(l_c != '}') {
  //   std::cerr << "Wrong end: '"<< l_c <<"' != '}'" << std::endl;
  //   throw "Wrong end";
  // }

  return is;
}

} // namespace esp32

} // namespace IO

} // namespace Embded
