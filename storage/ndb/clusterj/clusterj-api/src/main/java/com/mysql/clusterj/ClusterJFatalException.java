/*
   Copyright (c) 2010 Sun Microsystems, Inc.
   Use is subject to license terms.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

package com.mysql.clusterj;

/** ClusterJFatalException represents an exception that is not recoverable.
 *
 */
public class ClusterJFatalException extends ClusterJException {

    private static final long serialVersionUID = 5092290629928148399L;

    public ClusterJFatalException(String string) {
        super(string);
    }

    public ClusterJFatalException(String string, Throwable t) {
        super(string, t);
    }

    public ClusterJFatalException(Throwable t) {
        super(t);
    }
}