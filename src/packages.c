#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_packages(long *packages){
    FILE*  fp;
    char buffer[256];
    *packages = 0;

    // List of commands for different distros
    const char *commands[] = {
            "which dpkg &>/dev/null && dpkg -l | grep '^ii' | wc -l 2>/dev/null",      // Debian-based systems
            "which rpm &>/dev/null && rpm -qa | wc -l 2>/dev/null",                  // Red Hat-based systems
            "which pacman &>/dev/null && pacman -Q | wc -l 2>/dev/null",                // Arch-based systems
            "which apk &>/dev/null && apk info | wc -l 2>/dev/null",                 // Alpine Linux
            "which xbps-query &>/dev/null && xbps-query -l | wc -l 2>/dev/null",            // Void Linux
            "which equo &>/dev/null && equo query list installed | wc -l 2>/dev/null", // Sabayon Linux
            "which flatpak &>/dev/null && flatpak list | wc -l 2>/dev/null",             // Flatpak packages
            "which snap &>/dev/null && snap list | wc -l 2>/dev/null",                // Snap packages
            "which nix-store &>/dev/null && nix-store --query --requisites /run/current-system | wc -l 2>/dev/null", // NixOS
            "which opkg &>/dev/null && opkg list-installed | wc -l 2>/dev/null",      // OpenWrt
            "which zypper &>/dev/null && zypper se --installed-only | wc -l 2>/dev/null", // openSUSE
            "which pkg &>/dev/null && pkg info | wc -l 2>/dev/null",                 // FreeBSD pkg
            "which pkg_info &>/dev/null && pkg_info | wc -l 2>/dev/null",                 // Older FreeBSD pkg_info
            "which emerge &>/dev/null && emerge --pretend --verbose world | grep 'Total:' | awk '{print $2}' 2>/dev/null", // Gentoo Linux
            "which guix &>/dev/null && guix package --list-installed | wc -l 2>/dev/null", // GNU Guix System
            "which brew &>/dev/null && brew list | wc -l 2>/dev/null"                 // Homebrew (Linuxbrew/macOS)
    };


    for(int i = 0; i<sizeof(commands)/sizeof(commands[0]); i++){
        fp = popen(commands[i], "r");
        if(fp != NULL){
            if(fgets(buffer, sizeof(buffer), fp) != NULL){
                *packages += atoi(buffer);
            }
        }
        pclose(fp);
    }

    if(*packages != 0){
        return 0;
    }
    return -1;

}