#include <kernel-features.h>
#include <sys/syscall.h>
#if !defined __NR_recvmmsg && defined __NR_socketcall
# define socket	recvmmsg
# ifndef __ASSUME_RECVMMSG
#  define __socket __internal_recvmmsg
#  define NO_WEAK_ALIAS
# endif
# define NARGS 5
# define NEED_CANCELLATION
# include <socket.S>
# ifdef __ASSUME_RECVMMSG
libc_hidden_def (__recvmmsg)
# endif
#endif
