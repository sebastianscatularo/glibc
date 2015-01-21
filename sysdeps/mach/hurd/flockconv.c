/* Convert between `struct flock' format, and `struct flock64' format.
   Copyright (C) 2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <fcntl.h>

static inline int
flock64_conv (struct flock *buf, const struct flock64 *buf64)
{
  if (sizeof *buf == sizeof *buf64
      && sizeof buf->l_start == sizeof buf64->l_start
      && sizeof buf->l_len == sizeof buf64->l_len)
    {
      *buf = *(struct flock *) buf64;
      return 0;
    }

  buf->l_type = buf64->l_type;
  buf->l_whence = buf64->l_whence;
  buf->l_start = buf64->l_start;
  buf->l_len = buf64->l_len;
  buf->l_pid = buf64->l_pid;

  if ((sizeof buf->l_start != sizeof buf64->l_start
       && buf->l_start != buf64->l_start)
      || (sizeof buf->l_len != sizeof buf64->l_len
	  && buf->l_len != buf64->l_len))
    {
      __set_errno (EOVERFLOW);
      return -1;
    }

  return 0;
}

static inline int
flock_conv (struct flock64 *buf64, const struct flock *buf)
{
  if (sizeof *buf == sizeof *buf64
      && sizeof buf->l_start == sizeof buf64->l_start
      && sizeof buf->l_len == sizeof buf64->l_len)
    {
      *buf64 = *(struct flock64 *) buf;
      return 0;
    }

  buf64->l_type = buf->l_type;
  buf64->l_whence = buf->l_whence;
  buf64->l_start = buf->l_start;
  buf64->l_len = buf->l_len;
  buf64->l_pid = buf->l_pid;

  return 0;
}
