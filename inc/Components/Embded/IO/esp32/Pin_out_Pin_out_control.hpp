#pragma once

#include "Data/CompoMe_esp32.hpp"
#include "Interfaces/Embded/IO/Pin_out/Pin_out.hpp"

#include "Serialization_context.hpp"

namespace Embded {

namespace IO {

namespace esp32 {

class Pin_out;

class Pin_out_Pin_out_control : public ::Embded::IO::Pin_out {
public:
  //! Default constructor
  Pin_out_Pin_out_control(Pin_out *comp);

  //! Destructor
  virtual ~Pin_out_Pin_out_control() noexcept;

  bool is_fake() override { return false; }

  ///////////////////////////////////////////////////////////////////////////
  //                                FUNCTION                               //
  ///////////////////////////////////////////////////////////////////////////

  // Pin_out /////////////////////////////////////////////////////////
  virtual void on() override;
  virtual void off() override;
  virtual void set(Embded::IO::Pin_State ps) override;
  virtual void switch_v() override;

  ///////////////////////////////////////////////////////////////////////////
  //                              GET/SET                                  //
  ///////////////////////////////////////////////////////////////////////////

  // Pin_out ///////////////////////////////////////////////////////////////////
  // get/set state
  Embded::IO::Pin_State get_state() const override;
  void set_state(const Embded::IO::Pin_State &state) override;

  ///////////////////////////////////////////////////////////////////////////
  //                            SAVE/LOAD                                  //
  ///////////////////////////////////////////////////////////////////////////
  // void save(std::ostream& os) const;
  // void load(std::istream& is);
  std::ostream &to_stream(std::ostream &,
                          CompoMe::Serialization_context_export &) const;
  std::istream &from_stream(std::istream &,
                            CompoMe::Serialization_context_import &);

private:
  Pin_out &get_c() const;
  Pin_out *composant;

  ///////////////////////////////////////////////////////////////////////////
  //                                  DATA                                 //
  ///////////////////////////////////////////////////////////////////////////

  // DATA for Pin_out
  Embded::IO::Pin_State state;
};

} // namespace esp32

} // namespace IO

} // namespace Embded
