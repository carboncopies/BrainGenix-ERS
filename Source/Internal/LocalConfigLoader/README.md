# ERS Internal Library: LocalConfigLoader

## Description

The LocalConfigLoader provides a failsafe way of getting the config.yaml file. If the file is missing or otherwise bad, then the module will chuck an error rather than crashing horribly. This is mostly because mac machines for some god forsaken reason run the executables in a random ass path, so we have to try and see if the config is there and if not, then try loading it from somewhere else.