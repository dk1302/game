#!/usr/bin/env bash

rm -rf game
nix-build
cp result/bin/game game
echo "" >gdb.output
gdb --command=gdb.conf --args game
