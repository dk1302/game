with import <nixpkgs> { };

pkgs.stdenv.mkDerivation {
  pname = "game";
  version = "1.0.0";
  src = ./.;

  buildInputs = with pkgs; [
    glfw
    glm
  ];

  nativeBuildInputs = with pkgs; [
    bear
  ];

  dontStrip = true;

  buildPhase = ''
    bear -- g++ -Og -ggdb -x c++ \
      $src/src/main.cpp \
      $src/src/renderer.cpp \
      $src/src/glad.c \
      -o game \
      -I$src/include \
      -I${glfw}/include/GLFW \
      -L${glfw.out}/lib \
      -lglfw \
      -I${glm}/include/glm \
      -L${glm.out}/lib \
      -lglm \
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp game $out/bin/game
    cp compile_commands.json $out/bin/compile_commands.json
  '';
}
