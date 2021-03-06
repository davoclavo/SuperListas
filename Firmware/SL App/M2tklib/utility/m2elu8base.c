/*

  m2elu8base.c
  
  m2tklib = Mini Interative Interface Toolkit Library
  
  Copyright (C) 2011  olikraus@gmail.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.



*/

#include <stddef.h>
#include "m2.h"
#include "m2utl.h"

#ifdef M2_EL_MSG_DBG_SHOW
#include <stdio.h>
#endif

uint8_t m2_el_u8_get_max(m2_el_fnarg_p fn_arg)
{
  return m2_rom_get_u8(fn_arg->element, offsetof(m2_el_u8_t, max));
}

uint8_t m2_el_u8_get_min(m2_el_fnarg_p fn_arg)
{
  return m2_rom_get_u8(fn_arg->element, offsetof(m2_el_u8_t, min));
}

uint8_t *m2_el_u8_get_val_ptr(m2_el_fnarg_p fn_arg)
{
  return (uint8_t *)m2_rom_get_ram_ptr(fn_arg->element, offsetof(m2_el_u8_t, val));
}


M2_EL_FN_DEF(m2_el_u8base_fn)
{
  uint8_t *val_ptr;
  val_ptr = m2_el_u8_get_val_ptr(fn_arg);
  switch(fn_arg->msg)
  {
    case M2_EL_MSG_GET_LIST_LEN:
      return 0;  /* not a list, return 0 */
    case M2_EL_MSG_IS_DATA_ENTRY:
      return 1;
    case M2_EL_MSG_DATA_UP:
      if ( *val_ptr >= m2_el_u8_get_max(fn_arg) )
	*val_ptr = m2_el_u8_get_min(fn_arg);
      else
	(*val_ptr)++;
      return 1;
    case M2_EL_MSG_DATA_DOWN:
      if ( *val_ptr <= m2_el_u8_get_min(fn_arg) )
	*val_ptr = m2_el_u8_get_max(fn_arg);
      else
	(*val_ptr)--;
      return 1;
  }
  return m2_el_fnfmt_fn(fn_arg);
}

