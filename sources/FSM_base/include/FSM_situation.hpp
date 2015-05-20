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
namespace FSM_base
{
  //-----------------------------------------------------------------------------
  template <class T_CONTEXT>
  FSM_situation<T_CONTEXT>::FSM_situation(void):
    m_context(NULL),
    m_valid(true)
  {
  }

  //-----------------------------------------------------------------------------
  template <class T_CONTEXT>
  FSM_situation<T_CONTEXT>::FSM_situation(const FSM_situation &p_situation):
    m_context(new T_CONTEXT(*(p_situation.get_context()))),
    m_valid(p_situation.is_valid())
  {
  }

  //-----------------------------------------------------------------------------
  template <class T_CONTEXT>
  FSM_situation<T_CONTEXT>::~FSM_situation(void)
  {
    if(m_context != NULL)
      {
	delete m_context ;
	m_context = NULL;
      }
  }

  //-----------------------------------------------------------------------------
  template <class T_CONTEXT>
  typename FSM_situation<T_CONTEXT>::FSM_context_if * FSM_situation<T_CONTEXT>::get_current_context(void)const
  {
    return m_context;
  }

  //-----------------------------------------------------------------------------
  template <class T_CONTEXT>
  bool FSM_situation<T_CONTEXT>::is_valid(void)const
  {
    return m_valid;
  }

  //-----------------------------------------------------------------------------
  template <class T_CONTEXT>
  T_CONTEXT * FSM_situation<T_CONTEXT>::get_context(void)const
  {
    assert(m_context);
    return m_context;
  }

  //-----------------------------------------------------------------------------
  template <class T_CONTEXT>
  void FSM_situation<T_CONTEXT>::set_context
  (
   T_CONTEXT & p_context
   )
  {
    m_context = & p_context;
  }

  //-----------------------------------------------------------------------------
  template <class T_CONTEXT>
  void FSM_situation<T_CONTEXT>::set_invalid
  (
   void
   )
  {
    m_valid = false;
  }

}
//EOF
