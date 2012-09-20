/* Copyright (C) 2012 Free Software Foundation, Inc.
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

#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <mach.h>

/* Advise the system about particular usage patterns the program follows
   for the region starting at ADDR and extending LEN bytes.  */

int
__madvise (__ptr_t addr, size_t len, int advice)
{
  kern_return_t err;
  vm_advice_t vmadvice;

  switch (advice)
    {
    case MADV_NORMAL:
      vmadvice = VM_ADVICE_NORMAL;
      break;
    case MADV_SEQUENTIAL:
      vmadvice = VM_ADVICE_SEQUENTIAL;
      break;
    case MADV_RANDOM:
      vmadvice = VM_ADVICE_RANDOM;
      break;
    default:
      __set_errno (ENOSYS);
      return -1;
    }

  if (err = __vm_advise (__mach_task_self (),
			 (vm_address_t) addr, (vm_size_t) len,
			 vmadvice))
    {
      errno = err;
      return -1;
    }
  return 0;
}
weak_alias (__madvise, madvise)
