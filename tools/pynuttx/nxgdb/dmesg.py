############################################################################
# tools/pynuttx/nxgdb/dmesg.py
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.
#
############################################################################

import gdb

from . import utils

CONFIG_RAMLOG_SYSLOG = utils.get_symbol_value("CONFIG_RAMLOG_SYSLOG")
CONFIG_SYSLOG_RPMSG = utils.get_symbol_value("CONFIG_SYSLOG_RPMSG")


class Dmesg(gdb.Command):
    def __init__(self):
        if CONFIG_RAMLOG_SYSLOG or CONFIG_SYSLOG_RPMSG:
            super().__init__("dmesg", gdb.COMMAND_USER)

    def _get_ramlog(self):
        if not (sysdev := utils.gdb_eval_or_none("g_sysdev")):
            return "RAM log not available"

        rl_header = sysdev["rl_header"]
        rl_bufsize = sysdev["rl_bufsize"]

        offset = rl_header["rl_head"] % rl_bufsize  # Currently writing to this offset
        tail = rl_bufsize - offset  # Total size till buffer end.
        rl_buffer = int(rl_header["rl_buffer"].address)  # rl_buffer is a char array

        inf = gdb.selected_inferior()
        buf = bytes(inf.read_memory(offset + rl_buffer, tail))
        buf = buf.lstrip(b"\0")  # Remove leading NULLs
        buf += bytes(inf.read_memory(rl_buffer, offset))
        buf = buf.replace(
            b"\0", "␀".encode("utf-8")
        )  # NULL is valid utf-8 but not printable

        return buf.decode("utf-8", errors="replace")

    def _get_rpmsg_syslog(self):
        if not (priv := utils.gdb_eval_or_none("g_syslog_rpmsg")):
            return "RPMsg syslog not available"

        buffer = bytes(gdb.selected_inferior().read_memory(priv.buffer, priv.size))
        buf = buffer.replace(b"\0", "␀".encode("utf-8"))
        return buf.decode("utf-8", errors="replace")

    def diagnose(self, *args, **kwargs):
        ramlog = self._get_ramlog()
        rpmsg_syslog = self._get_rpmsg_syslog()

        return {
            "title": "RAM log and RPMsg Syslog",
            "summary": (
                f"RAM log length: {len(ramlog)} bytes. RPMSG log length:{len(rpmsg_syslog)} bytes."
            ),
            "result": "info",
            "command": "dmesg",
            "message": f"RAM log:\n{ramlog}\n RPMSG syslog:{rpmsg_syslog}",
        }

    def invoke(self, args, from_tty):
        ramlog = self._get_ramlog()
        rpmsg_syslog = self._get_rpmsg_syslog()

        print(f"RAM log:{ramlog}\n---END of RAMLOG")
        print(f"RPMSG syslog:{rpmsg_syslog}\n---END of RPMSG SYSLOG---")
