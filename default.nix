with import <nixpkgs> { };

pkgs.stdenv.mkDerivation {
  pname = "game";
  version = "1.0.0";
  src = ./.;

  buildInputs = with pkgs; [
    glfw
  ];

  nativeBuildInputs = with pkgs; [
    bear
  ];

  dontStrip = true;

  buildPhase = ''
    bear -- g++ -Og -ggdb -x c++ $src/src/glad.c $src/src/main.cpp -o game \
      -I${glfw}/include/GLFW \
      -I$src/include \
      -L${glfw.out}/lib \
      -lglfw\
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp game $out/bin/game
    cp compile_commands.json $out/bin/compile_commands.json
  '';
}
