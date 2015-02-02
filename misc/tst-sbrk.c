/* Test sbrk.

   Copyright (C) 2013-2015 Free Software Foundation, Inc.
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
#include <stdio.h>
#include <unistd.h>

static int
do_test (void)
{
  /* Try to advance the program break by 1 MiB.  */
  void *one_mib = sbrk (1 * 1024 * 1024);
  if (one_mib == (void *) -1)
    {
      if (errno != ENOMEM)
        printf ("sbrk (1 MiB) failed, and with wrong errno: %m\n");
      else
        printf ("sbrk (1 MiB) failed\n");

      return 1;
    }
  else
    printf ("sbrk at %p\n", one_mib);

  return 0;
}

/* TODO: fix rlimit bug.  64 MiB (test-skeleton.c's default) should be
   enough.  */
#define TEST_DATA_LIMIT RLIM_INFINITY

#define TEST_FUNCTION do_test ()
#include "../test-skeleton.c"
