/*
 * Copyright (c) 2014, 2018, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2.0, as
 * published by the Free Software Foundation.
 *
 * This program is also distributed with certain software (including
 * but not limited to OpenSSL) that is licensed under separate terms,
 * as designated in a particular file or component or in included license
 * documentation.  The authors of MySQL hereby grant you an
 * additional permission to link the program and your derivative works
 * with the separately licensed software that they have included with
 * MySQL.
 *
 * Without limiting anything contained in the foregoing, this file,
 * which is part of MySQL Connector/C++, is also subject to the
 * Universal FOSS Exception, version 1.0, a copy of which can be found at
 * http://oss.oracle.com/licenses/universal-foss-exception.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License, version 2.0, for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
 */

/* @EDIT_WARNING_MESSAGE@ */

#define MYCPPCONN_DM_MAJOR_VERSION @CONNECTOR_MAJOR@
#define MYCPPCONN_DM_MINOR_VERSION @CONNECTOR_MINOR@
#define MYCPPCONN_DM_PATCH_VERSION @CONNECTOR_PATCH@

#define MYCPPCONN_DM_VERSION     "@CONNECTOR_MAJOR@.@CONNECTOR_MINOR_PADDED@.@CONNECTOR_PATCH_PADDED@"
#define MYCPPCONN_DM_VERSION_ID  @CONNECTOR_MAJOR@@CONNECTOR_MINOR_PADDED@@CONNECTOR_PATCH_PADDED@


/* Driver version info */

#define MYCPPCONN_STATIC_MYSQL_VERSION     "@MYSQL_VERSION@"
#define MYCPPCONN_STATIC_MYSQL_VERSION_ID  @MYSQL_NUM_VERSION@

#define MYCPPCONN_BOOST_VERSION            @Boost_VERSION@
