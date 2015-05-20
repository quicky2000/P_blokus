/*    This file is part of FSM_framework
      The aim of this software is to provided generic facilities for FSM analyzis
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef ALGORITHM_DEEP_RAW
#define ALGORITHM_DEEP_RAW

#include "framework_algorithm_if.h"
#include "smart_situation_stack.h"
#include <iostream>
#include <inttypes.h>

namespace FSM_framework
{
  class algorithm_deep_raw: public framework_algorithm_if
  {
  public:
    inline algorithm_deep_raw(void);
    inline const uint64_t & get_total_situations(void)const;
    inline void stop(void);
    void print_status(void)const;
    // Methods inherited from interface
    void run(void);
    const std::string & get_string(void)const;
  
    static void register_algorithm(std::map<std::string,FSM_framework_algorithm_creator_t > &p_factory);
  private:
    FSM_framework::smart_situation_stack m_situation_stack;
    uint64_t m_nb_situation_explored;
    bool m_stop;
    static const std::string m_class_name;
  };

  framework_algorithm_if & create_algorithm_deep_raw(void);

  //----------------------------------------------------------------------------
  algorithm_deep_raw::algorithm_deep_raw(void):
    m_nb_situation_explored(0),
    m_stop(false)
    {
    }

  //----------------------------------------------------------------------------
  const uint64_t & algorithm_deep_raw::get_total_situations(void)const
    {
      return m_nb_situation_explored;
    }

  //----------------------------------------------------------------------------
  void algorithm_deep_raw::stop(void)
  {
    m_stop = true;
  }

}
#endif // ALGORITHM_DEEP_RAW 
//EOF
