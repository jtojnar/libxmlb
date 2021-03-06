/*
 * Copyright (C) 2018 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#ifndef __XB_COMMON_H
#define __XB_COMMON_H

#include <glib-object.h>

G_BEGIN_DECLS

void		 xb_string_append_union			(GString	*xpath,
							 const gchar	*fmt,
							 ...) G_GNUC_PRINTF (2, 3);

G_END_DECLS

#endif /* __XB_COMMON_H */
