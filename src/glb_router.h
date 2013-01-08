/*
 * Copyright (C) 2008-2012 Codership Oy <info@codership.com>
 *
 * $Id$
 */

#ifndef _glb_router_h_
#define _glb_router_h_

#include "glb_cnf.h"

typedef struct glb_router glb_router_t;

extern glb_router_t*
glb_router_create (const glb_cnf_t* cnf);

extern void
glb_router_destroy ();

/*!
 * Modifies internal list of destinations
 * If destination is not in the list, adds it, if it is there - changes its
 * weight, if weight is -1 - removes destination from the list
 * @return index of record changed or negative error code
 */
extern int
glb_router_change_dst (glb_router_t* router, const glb_dst_t* dst);

#ifdef GLBD

/*!
 * Returns file descriptor of a new destinaiton conneciton and fills
 * dst_addr with real server address
 *
 * Not thread-safe. Supposed to be called ONLY from the listener main loop.
 *
 * @return 0 or negative error code
 */
extern int
glb_router_connect (glb_router_t* router, const glb_sockaddr_t* src_addr,
                    glb_sockaddr_t* dst_addr, int* sock);

/*!
 * Decrements connection reference count for destination
 */
extern void
glb_router_disconnect (glb_router_t* router, const glb_sockaddr_t* dst_addr,
                       bool failed);

#else /* GLBD */

extern int __glb_router_connect(glb_router_t* const router, int const sockfd);

#endif /* GLBD */

// Returns the length of the string
extern size_t
glb_router_print_info (glb_router_t* router, char* buf, size_t buf_len);

#endif // _glb_router_h_
