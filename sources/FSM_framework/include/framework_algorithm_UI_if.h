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
#ifndef FRAMEWORK_ALGORITHM_UI_IF_H
#define FRAMEWORK_ALGORITHM_UI_IF_H

#include <string>
#include <map>

namespace FSM_framework
{
  class framework_algorithm_UI_if
  {
  public:
    virtual const std::string & get_type(void)const=0;
    
    inline virtual ~framework_algorithm_UI_if(void){}
  };

  typedef framework_algorithm_UI_if *(*FSM_framework_algorithm_UI_creator_t)(void);

  void register_framework_algorithm_ui(const std::string & p_algorithm_name,
                                       FSM_framework_algorithm_UI_creator_t p_creator,
                                       std::map<std::string,FSM_framework_algorithm_UI_creator_t> &p_factory);
}
#endif // FRAMEWORK_ALGORITHM_UI_IF_H 
//EOF
