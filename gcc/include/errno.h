// "Standard" errno values -- Copied from newlib /usr/include/sys/errno.h
// Use this instead of the errno.h supplied with AVR-libc!

// Copyright (C)2019, Philip Munts, President, Munts AM Corp.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef _ERRNO_H_
#define _ERRNO_H_

#define EOK         0   // Success
#define EPERM       1   // Not super-user
#define ENOENT      2   // No such file or directory
#define ESRCH       3   // No such process
#define EINTR       4   // Interrupted system call
#define EIO         5   // I/O error
#define ENXIO       6   // No such device or address
#define E2BIG       7   // Arg list too long
#define ENOEXEC     8   // Exec format error
#define EBADF       9   // Bad file number
#define ECHILD      10  // No children
#define EAGAIN      11  // No more processes
#define ENOMEM      12  // Not enough core
#define EACCES      13  // Permission denied
#define EFAULT      14  // Bad address
#define ENOTBLK     15  // Block device required
#define EBUSY       16  // Mount device busy
#define EEXIST      17  // File exists
#define EXDEV       18  // Cross-device link
#define ENODEV      19  // No such device
#define ENOTDIR     20  // Not a directory
#define EISDIR      21  // Is a directory
#define EINVAL      22  // Invalid argument
#define ENFILE      23  // Too many open files in system
#define EMFILE      24  // Too many open files
#define ENOTTY      25  // Not a typewriter
#define ETXTBSY     26  // Text file busy
#define EFBIG       27  // File too large
#define ENOSPC      28  // No space left on device
#define ESPIPE      29  // Illegal seek
#define EROFS       30  // Read only file system
#define EMLINK      31  // Too many links
#define EPIPE       32  // Broken pipe
#define EDOM        33  // Math arg out of domain of func
#define ERANGE      34  // Math result not representable
#define ECONNRESET  104 // Connection reset by peer

#ifdef __cplusplus
extern "C"
{
#endif
  extern int errno;
#ifdef __cplusplus
}
#endif

#endif
