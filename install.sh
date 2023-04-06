#!/bin/bash
set -e
thunarx_directory="${HOME}/.local/lib/thunarx-3/"
mkdir -p ${thunarx_directory}
cp file_filter_plugin.so ${thunarx_directory}

# thunar -q && thunar