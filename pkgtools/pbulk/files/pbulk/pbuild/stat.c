/* $NetBSD: stat.c,v 1.6 2020/08/04 02:35:09 tnn Exp $ */

/*-
 * Copyright (c) 2007 Joerg Sonnenberger <joerg@NetBSD.org>.
 * All rights reserved.
 *
 * This code was developed as part of Google's Summer of Code 2007 program.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <nbcompat.h>

#include <sys/socket.h>
#include <nbcompat/err.h>
#include <errno.h>
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#include <nbcompat/stdlib.h>
#include <nbcompat/stdio.h>
#include <nbcompat/string.h>
#include <nbcompat/unistd.h>

#include <arpa/inet.h>

#include "pbulk.h"
#include "pbuild.h"

void
stat_mode(const char *client_port)
{
	ssize_t recv_bytes, sent_bytes;
	char buf[7 * 4];
	struct build_stat st;
	uint32_t tmp;
	int fd;

	if ((fd = connect_sockaddr(client_port)) == -1)
		err(1, "Could not create connection to %s", client_port);

	sent_bytes = write(fd, "S", 1);
	if (sent_bytes == -1)
		err(1, "Could not write to socket");
	if (sent_bytes == 0)
		exit(0);
	if (sent_bytes != 1)
		errx(1, "Premature end of stream while writing to socket");

	recv_bytes = atomic_read(fd, &buf, 7 * 4);
	if (recv_bytes == 0 || (recv_bytes == -1 && errno == ECONNRESET))
		exit(0);
	if (recv_bytes == -1)
		err(1, "Could not read from socket");
	if (recv_bytes != 7 * 4)
		errx(1, "Premature end while reading statistics from socket");

	(void)memcpy(&tmp, buf, 4);
	st.open_jobs = ntohl(tmp);
	(void)memcpy(&tmp, buf + 4, 4);
	st.in_processing = ntohl(tmp);
	(void)memcpy(&tmp, buf + 8, 4);
	st.failed = ntohl(tmp);
	(void)memcpy(&tmp, buf + 12, 4);
	st.prefailed = ntohl(tmp);
	(void)memcpy(&tmp, buf + 16, 4);
	st.indirect_failed = ntohl(tmp);
	(void)memcpy(&tmp, buf + 20, 4);
	st.indirect_prefailed = ntohl(tmp);
	(void)memcpy(&tmp, buf + 24, 4);
	st.done = ntohl(tmp);

	(void)printf("Jobs not yet processed: %lu\n",
	    (unsigned long)st.open_jobs);
	(void)printf("Jobs currently in processing: %lu\n",
	    (unsigned long)st.in_processing);
	(void)printf("Successful builds: %lu\n",
	    (unsigned long)st.done);
	(void)printf("Failing builds: %lu\n",
	    (unsigned long)(st.failed + st.prefailed + st.indirect_failed + st.indirect_prefailed));
	(void)printf("  Directly broken: %lu\n",
	    (unsigned long)st.failed);
	(void)printf("  Broken due to a broken dependency: %lu\n",
	    (unsigned long)st.indirect_failed);
	(void)printf("  Not built as explicitly marked broken: %lu\n",
	    (unsigned long)st.prefailed);
	(void)printf("  Broken due to an explicitly broken dependency: %lu\n",
	    (unsigned long)st.indirect_prefailed);

	exit(0);
}
