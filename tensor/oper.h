/* tensor/oper.h
 * 
 * Copyright (C) 2020 Viktor Slavkovikj
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __OPER_H__
#define __OPER_H__

#include <gsl/gsl_complex.h>

#define DATA(t, idx) *FUNCTION (tensor, ptr_idx) (t, idx)

#define DATA_REAL(t, idx) GSL_REAL (DATA (t, idx))

#define DATA_IMAG(t, idx) GSL_IMAG (DATA (t, idx))

#define CONST_DATA(t, idx)                      \
  *FUNCTION (tensor, const_ptr_idx) (t, idx)

#define CONST_DATA_REAL(t, idx) GSL_REAL (CONST_DATA (t, idx))

#define CONST_DATA_IMAG(t, idx) GSL_IMAG (CONST_DATA (t, idx))
  
#endif  /* __OPER_H__ */
