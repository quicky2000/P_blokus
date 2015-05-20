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
#ifndef FRAMEWORK_CONTROLER_H
#define FRAMEWORK_CONTROLER_H

#include <string>

namespace FSM_framework
{
  class framework_UI_if;
  class framework_base;

  class framework_controler
  {
  public:
    framework_controler(framework_UI_if *p_framework_UI);
    ~framework_controler(void);
    void load_library(const std::string & p_name);
    void select_fsm(const std::string & p_name);
    void select_fsm_ui(const std::string & p_name);
    void select_algorithm(const std::string & p_name);
    void run(void);
    void display_warning_message(const std::string & p_message);
    void display_error_message(const std::string & p_message);
    framework_base* get_framework(void);

  private:
    framework_UI_if *m_framework_ui;
    framework_base *m_framework;
  };
}
#endif /* FRAMEWORK_CONTROLER_H */
