/*
 * Copyright (C) 2018 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#ifndef __XB_BUILDER_SOURCE_PRIVATE_H
#define __XB_BUILDER_SOURCE_PRIVATE_H

#include <gio/gio.h>

#include "xb-builder-source.h"
#include "xb-builder-node.h"

G_BEGIN_DECLS

XbBuilderNode	*xb_builder_source_get_info	(XbBuilderSource	*self);
gchar		*xb_builder_source_get_guid	(XbBuilderSource	*self);
const gchar	*xb_builder_source_get_prefix	(XbBuilderSource	*self);
GInputStream	*xb_builder_source_get_istream	(XbBuilderSource	*self);
GFile		*xb_builder_source_get_file	(XbBuilderSource	*self);
gboolean	 xb_builder_source_funcs_node	(XbBuilderSource	*self,
						 XbBuilderNode		*bn,
						 GError			**error);
XbBuilderSourceFlags xb_builder_source_get_flags(XbBuilderSource	*self);

G_END_DECLS

#endif /* __XB_BUILDER_SOURCE_PRIVATE_H */
