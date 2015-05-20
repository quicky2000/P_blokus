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
#ifndef FRAMEWORK_UI_IF
#define FRAMEWORK_UI_IF

#include <vector>
#include <string>

namespace FSM_framework
{
  class framework_UI_if
  {
  public:
    virtual void display_loaded_fsm(const std::vector<std::string> & p_FSM_list)=0;
    virtual void display_loaded_fsm_ui(const std::vector<std::string> & p_FSM_UI_list)=0;
    virtual void display_loaded_algorithm(const std::vector<std::string> & p_algorithm_list)=0;
    virtual void display_warning_message(const std::string & p_message)=0;
    virtual void display_error_message(const std::string & p_message)=0;

    virtual ~framework_UI_if(void);
  };
}
#endif // FRAMEWORK_UI_IF 
//EOF
