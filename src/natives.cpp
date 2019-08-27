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

#include "natives.hpp"
#include "impl.hpp"

cell Natives::SetCatchExit(AMX* amx, cell* params) {
	Impl::SetSignalHandling(static_cast<bool>(params[1]));
    return 1;
}


cell Natives::ExitProcess(AMX* amx, cell* params) {
	Impl::ExitProcess();
	return 1;
}