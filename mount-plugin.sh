#!/usr/bin/env bash

throw() { echo "[-] fatal: $1"; exit 1; }
usage() {
	echo "Usage: ${BASH_SOURCE[0]} <albert-source-dir>";
	echo "";
	echo "  mount this plugin into building file of albert launcher plugins";
	echo "";
	exit 1;
}
mount-plugin() {
	cat "$target_cmake_file" |
		awk -v mountdir="$this_dir" -v msg='"Build the extension: ip"' '
			BEGIN { printable = 1; }
			/^\s*#region\s+albert-plugin-ip/ { printable = 0; next; }
			/^\s*#endregion\s+albert-plugin-ip/ { printable = 1; next; }
			printable { print $0; }
			END {
				print "#region albert-plugin-ip";
				print "option(BUILD_PLUGIN_IP " msg " ON)";
				print "if (BUILD_PLUGIN_IP)";
				print "    add_subdirectory(" mountdir " ip)";
				print "endif()";
				print "#endregion albert-plugin-ip";
			}
		';
}


[[ -n "$1" ]] || usage;
[[ -d "$1" ]] || throw "$1 is not a directory!";
[[ -f "$1/CMakeLists.txt" ]] || throw "CMakeLists.txt of 'albert' is not existed!";
[[ -d "$1/plugins" ]] || throw "$1/plugins is not a directory!";

target_cmake_file="$1/plugins/CMakeLists.txt";
[[ -f "$target_cmake_file" ]] || throw "$target_cmake_file is not a file!";

this_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )";
[[ -n "$this_dir" ]] || throw "get script directory failed!";

mount-plugin > /dev/null ||
	throw "mount this plugin into CMakeLists.txt of 'albert' plugins failed!"

new_cmake_content="$(mount-plugin)";
echo "$new_cmake_content" > "$target_cmake_file" ||
	throw "modify CMakeLists.txt of 'albert' plugins failed!";

echo "[+] mount this plugin into CMakeLists.txt of 'albert' plugins successed!";
