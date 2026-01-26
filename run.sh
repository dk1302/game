#!/usr/bin/env bash

rm -rf game
rm -rf compile_commands.json
nix-build
cp result/bin/game game
cp result/bin/compile_commands.json compile_commands.json
./game
