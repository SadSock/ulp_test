# Run with `nix-shell cuda-fhs.nix`
{ pkgs ? import <nixpkgs> {} }:
(pkgs.buildFHSUserEnv {
  name = "ulp test";
  targetPkgs = pkgs: with pkgs; [ 
    git
    gitRepo
    gnupg
    autoconf
    curl
    procps
    gnumake
    util-linux
    m4
    gperf
    unzip
    cudatoolkit
    clang-tools
    linuxPackages.nvidia_x11
    libGLU libGL
    xorg.libXi xorg.libXmu freeglut
    xorg.libXext xorg.libX11 xorg.libXv xorg.libXrandr zlib 
    ncurses5
    stdenv.cc
    binutils
    mpfr mpfr.dev gmp gmp.dev
    gcc fish
    rocm-runtime
    rocm-smi
    hip
    rocblas
    blas
    blas.dev
    python311
    python311Packages.pip
    python311Packages.virtualenv
  ];
  multiPkgs = pkgs: with pkgs; [ zlib ];
  runScript = "fish";
  profile = ''
    export CUDA_PATH=${pkgs.cudatoolkit}
    # export LD_LIBRARY_PATH=${pkgs.linuxPackages.nvidia_x11}/lib
    export EXTRA_LDFLAGS="-L/lib  -L${pkgs.rocblas}/lib -L${pkgs.blas.dev}/lib -L${pkgs.linuxPackages.nvidia_x11}/lib -L${pkgs.mpfr.dev}/lib -L${pkgs.gmp.dev}/lib"
    export EXTRA_CCFLAGS="-I/usr/include -I${pkgs.rocblas}/include  -I${pkgs.blas.dev}/include -I${pkgs.mpfr.dev}/include -I${pkgs.gmp.dev}/include"
  '';
}).env

