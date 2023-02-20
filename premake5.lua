workspace "Networking"
    architecture "x86_64"
    configurations { "Debug", "Release" }

application = "Examples"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Renderer"

include "Server"

include (application)