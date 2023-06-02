# Third-Party

Put all your libaries here. Make sure to not use packages from the system whenever possible, and *don't* put in compiled binaries here - only source.
This allows us to compile ERS on as many target platforms as possible without having to hunt down packages from apt/dnf/pkg/etc...

For superbuilds, put the lib in the SuperBuild directory, otherwise put it in the NonSuperbuild directory.

*Don't forget to add libraries to your CMakeLists.txt file!*
