# Run with `nix-shell cuda-fhs.nix`
{ pkgs ? import <nixpkgs> {} }:
(pkgs.buildFHSUserEnv {
  name = "mpfr";
  targetPkgs = pkgs: with pkgs; [ 
    mpfr mpfr.dev
    gmp gmp.dev
  ];
  multiPkgs = pkgs: with pkgs; [ zlib ];
  runScript = "fish";
  profile = ''
    # export CUDA_PATH=${pkgs.cudatoolkit}
    # export LD_LIBRARY_PATH=${pkgs.linuxPackages.nvidia_x11}/lib
     export EXTRA_LDFLAGS="-L/lib -L${pkgs.mpfr.dev}/lib -L${pkgs.gmp.dev}/lib"
     export EXTRA_CCFLAGS="-I/usr/include -I${pkgs.mpfr.dev}/include -I${pkgs.gmp.dev}/include"
  '';
}).env

