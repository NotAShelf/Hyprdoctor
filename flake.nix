{
  description = ''
    Basic utility to check your Hyprland logs for errors
    and suggest solutions from an errors database.
  '';

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs = inputs @ {flake-parts, ...}:
    flake-parts.lib.mkFlake {inherit inputs;} {
      systems = ["x86_64-linux" "aarch64-linux"];

      perSystem = {
        self',
        pkgs,
        ...
      }: {
        /*
        packages = {
          default = self'.packages.hyprdoctor;
          hyprdoctor = pkgs.callPackage ./hyprdoctor.nix {};
        };
        */

        devShells = {
          default = self'.devShells.hyprdoctor;
          hyprdoctor = pkgs.mkShell {
            buildInputs = with pkgs; [
              boost
              nlohmann_json
              gnumake
            ];
          };
        };
      };
    };
}
