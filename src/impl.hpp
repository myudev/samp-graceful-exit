/*
 * This file is part of SAMP Graceful Exit.
 *
 * SAMP Graceful Exit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SAMP Graceful Exit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with SAMP Graceful Exit.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @license LGPL-3.0
 * @copyright 2019 MyU
 * @author MyU <myudev0@gmail.com>
 *
 */

#ifndef SAMP_GRACEFUL_EXIT_IMPL_H
#define SAMP_GRACEFUL_EXIT_IMPL_H

namespace Impl {
	enum ExitFlags : char {
		NoReason = 0,
		UserExit = 1 << 0,
		ForcedExit = 1 << 1,
		CtrlC = 1 << 2,
		UserSig1 = 1 << 3,
		UserSig2 = 1 << 4
	};

	bool IsSignalHandled();
	void SetSignalHandling(bool handle);
	void Startup();
	void ProcessQueue();
	void SignalExit(int flags); // return | true = handled, false = not handled
	void ExitProcess();
};

#endif
